// Triple-buffered slot calls found by tools/family_scan.py --immediates: each forwards the current
// buffer phase (the frame counter modulo three) to one virtual of the item in a grid cell. They differ
// only in the virtual; functions are named after their address. Status: matching/README.md.

class PhasedItem {
public:
    virtual void v00();
    virtual void v08();
    virtual void v10();
    virtual void v18();
    virtual void v20();
    virtual void apply_phase_a(unsigned int phase);                         // +28
    virtual void apply_phase_b(unsigned int phase);                         // +30
    virtual void apply_phase_c(unsigned int phase);                         // +38
    virtual void apply_phase_d(unsigned int phase);                         // +40
    virtual void apply_phase_e(unsigned int phase);                         // +48
};

struct PhasedGrid {
    unsigned char pad[0x710e0];
    unsigned int frame;       // +710e0
    unsigned char pad710e4[4];
    PhasedItem* items[1][14]; // +710e8
};

// 0x71003d65a4: virtual +38
void apply_cell_phase_3d65a4(PhasedGrid* grid, int row, int column) {
    unsigned int phase = grid->frame % 3;
    grid->items[row][column]->apply_phase_c(phase);
}

// 0x71003d65f0: virtual +28
void apply_cell_phase_3d65f0(PhasedGrid* grid, int row, int column) {
    unsigned int phase = grid->frame % 3;
    grid->items[row][column]->apply_phase_a(phase);
}

// 0x71003d663c: virtual +30
void apply_cell_phase_3d663c(PhasedGrid* grid, int row, int column) {
    unsigned int phase = grid->frame % 3;
    grid->items[row][column]->apply_phase_b(phase);
}

// 0x71003d6688: virtual +40
void apply_cell_phase_3d6688(PhasedGrid* grid, int row, int column) {
    unsigned int phase = grid->frame % 3;
    grid->items[row][column]->apply_phase_d(phase);
}

// 0x71003d6818: virtual +48
void apply_cell_phase_3d6818(PhasedGrid* grid, int row, int column) {
    unsigned int phase = grid->frame % 3;
    grid->items[row][column]->apply_phase_e(phase);
}
