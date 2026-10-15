// 0x71001e73c0 TextRenderer::draw (8,468 B), fourth session, set aside before any source was written (the
//   coordinator moved the session back to its near misses). What the function is, from the Ghidra export
//   (tools/s5/ghidra.py 1e73c0) and the disassembly:
//   - draw(float max_width, float max_height, TextRenderer* r, Vertex* out, const unsigned char* text,
//     unsigned count, bool pad, bool flag): the vertex format is (out->flags & 0x7f): 0 picks five local glyph
//     emitters (labels at 1e94d4, 1e9b24, 1e9a24, 1e98ac, 1e96ac), 1 picks the functions at 1e9c3c, 1ea42c,
//     1ea324, 1ea1ac and 1e9edc, anything else returns 0;
//   - the renderer's state lives in a 0x21000-byte object: the box at +20b4c/+20b54, the text scale at +20b5c, the
//     area at +20b74/+20b78 (screen_width() 0x71003df258 for layouts 0, 9, 10 and 11), the alignment at +20b9c
//     (1 centre, 2 right), the layout kind at +210d4;
//   - the text is measured first (TextRenderer::measure 0x71001e5e08) and rescaled once if it is wider than
//     max_width, then a switch over the bytes handles ESC codes 'A'..'Z' (colours, icons through a table at
//     0x71007ef7bc, line breaks and others) and emits glyphs through the chosen emitters; padding calls the first
//     emitter count - n times;
//   - afterwards up to eight passes push overlapping lines apart (records of 0x48 bytes for format 0 and 0x88 for
//     format 1, the same loop written twice with modff for the step), indexed by line tables at +20c04/+20d04.
// Not attempted: no source. The generator stops on its loop shape; the two formats look like one template body
// instantiated twice (or a macro), which is the first thing to settle.
