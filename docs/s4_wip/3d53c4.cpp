// Parked (fourth session): relaxed group 3d53c4 x3, DrawRenderer::gather<0..2> (0x71003d53c4, 0x71003d5a34,
// 0x71003d5db4, 896 bytes each; each calls collect<Copy> of src/misc/s4_3db158.cpp). Best: 4 abstract / 20
// instruction diffs, same size. To retry, put this after collect<> in s4_3db158.cpp with the DrawPacket / DrawView /
// DrawRenderer types below and register _ZN12DrawRenderer6gatherILi{0,1,2}EEEviiP10DrawPacket.
//
// What is left:
// 1. The record_count load. The original loads it in the count_b join block, before `orr w8, w26, w25; cbz`. Ours is
//    in the if-body: the pre-inline InstCombine sinks the load into the if-body, because its single user (the zext for
//    the record size) is in the if-body's first block at that point and nothing after the load writes memory. Reading it
//    between na and nb (a call to visible_b() follows it then) keeps it out, but it lands in count_b's first block,
//    not in the join block. `size_t nrec`, other if-conditions (`na + nb`, `(na | nb) != 0`, calls in the condition):
//    no change.
// 2. copy_b (`copy + na`). The original computes it in loop 1's exit block, `add x9, x22, w25, uxtw #4`, but also keeps
//    zext(na) from right after the first memcpy, spilled to [sp, #8], for loop 2's start. Ours: assigning copy_b right
//    after the first memcpy gives the same spill but keeps the add early, in x21 (not sunk). Assigning it between the
//    loops gives the late add but no early zext and no spill (8 abstract). Loop 2 indexed from copy (`copy[na + i]`,
//    `(copy + na)[i]`, size_t index): worse.
// 3. The relocation loop latch: original `sub w10, w10, #1; add x9, x9, #0x10; cbnz`, ours `add; sub; cbnz`.
//    Pointer, count-down, while (n--), int and size_t index loops: all worse.
//
// Found on the way (all in the version below):
// - The relocation must use an integer add (`reinterpret_cast<long>(p.b) + delta`). With a char* add the loop body
//   is small enough that the loop unroller runtime-unrolls it by 2.
// - `FrameArena* arena = &arenas[f]` before `DrawRecord** head = &lists[f]` (constant order at the top).

struct DrawPacket {
    unsigned char pad0[0x820];
    unsigned int count_a;     // +820
    unsigned int count_b;     // +824
    unsigned int pair_total;  // +828
    unsigned int pad82c;
    DrawPair* pairs;          // +830
    unsigned char pad838[0xc];
    unsigned int record_count; // +844
    unsigned int start_a;     // +848
    unsigned int limit_a;     // +84c
    unsigned int start_b;     // +850
    unsigned int limit_b;     // +854

    DrawPair* first_a() { return pairs + start_a; }
    DrawPair* first_b() { return pairs + count_a + start_b; }
    unsigned int visible_a() {
        if (count_a <= start_a) return 0;
        unsigned int n = count_a - start_a;
        return n > limit_a ? limit_a : n;
    }
    unsigned int visible_b() {
        if (count_b <= start_b) return 0;
        unsigned int n = count_b - start_b;
        return n > limit_b ? limit_b : n;
    }
    DrawPartB* records() { return reinterpret_cast<DrawPartB*>(first_a() + pair_total); }
};

struct DrawView {
    unsigned char pad0[8];
    DrawPair* pairs[3];       // +08
    DrawPair* pairs_b[3];     // +20
    DrawPartB* records[3];    // +38
    unsigned int count_a[3];  // +50
    unsigned int count_b[3];  // +5c
};

struct DrawRenderer {
    template <int Copy> void gather(int row, int col, DrawPacket* packet);

    unsigned char pad0[0x710dc];
    unsigned int frame;       // +710dc
    unsigned char pad710e0[8];
    DrawView* views[2][14];   // +710e8
    DrawRecord* lists[3];     // +711c8
    unsigned char pad711e0[0xf0];
    FrameArena arenas[3];     // +712d0
};

template <int Copy>
void DrawRenderer::gather(int row, int col, DrawPacket* packet) {
    unsigned int f = frame % 3;
    DrawView* v = views[row][col];
    FrameArena* arena = &arenas[f];
    DrawRecord** head = &lists[f];
    collect<Copy>(packet->first_a(), packet->visible_a(), arena, head);
    collect<Copy>(packet->first_b(), packet->visible_b(), arena, head);
    unsigned int na = packet->visible_a();
    unsigned int nb = packet->visible_b();
    unsigned int nrec = packet->record_count;
    DrawPair* copy = 0;
    DrawPair* copy_b = 0;
    DrawPartB* recs = 0;
    if (na || nb) {
        size_t bytes = (static_cast<size_t>(na + nb) * sizeof(DrawPair) + 31) & ~static_cast<size_t>(31);
        copy = static_cast<DrawPair*>(arena->take_aligned(bytes, 32));
        memcpy(copy, packet->first_a(), bytes);
        copy_b = copy + na;
        size_t rec_bytes = (nrec * sizeof(DrawPartB) + 31) & ~static_cast<size_t>(31);
        recs = static_cast<DrawPartB*>(arena->take_aligned(rec_bytes, 32));
        memcpy(recs, packet->records(), rec_bytes);
        long delta = reinterpret_cast<char*>(recs) - reinterpret_cast<char*>(packet->records());
        for (unsigned int i = 0; i < na; i++) {
            DrawPair& p = copy[i];
            if (p.b) p.b = reinterpret_cast<DrawPartB*>(reinterpret_cast<long>(p.b) + delta);
        }
        for (unsigned int i = 0; i < nb; i++) {
            DrawPair& p = copy_b[i];
            if (p.b) p.b = reinterpret_cast<DrawPartB*>(reinterpret_cast<long>(p.b) + delta);
        }
    }
    v->pairs[f] = copy;
    v->pairs_b[f] = copy_b;
    v->records[f] = recs;
    v->count_a[f] = na;
    v->count_b[f] = nb;
}

template void DrawRenderer::gather<0>(int, int, DrawPacket*);
template void DrawRenderer::gather<1>(int, int, DrawPacket*);
template void DrawRenderer::gather<2>(int, int, DrawPacket*);
