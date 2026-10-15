# Builds the 3ba734 scratch unit (argument, default build/s5/g3ba/d3ba734.cpp) from misc/s5_functions02.cpp's menu
# part and docs/s5_wip/3ba734.cpp. Run from matching/.
import re
import sys

src = open('src/misc/s5_functions02.cpp', newline='').read().replace('\r\n', '\n')
s = src[:src.index('struct AllocInfo448544')]

# The pane gains the slots 13-16 (bind_anim at +80) and the fields after translate.
s = s.replace('''    virtual Pane3bdbf0* find_pane(const char* name, bool recursive);
    unsigned char pad8[0x28];
    Float3_3bdbf0 translate;          // +30
    unsigned char pad3c[0x1c];
    unsigned char flags;              // +58
''', '''    virtual Pane3bdbf0* find_pane(const char* name, bool recursive);
    virtual void slot_13();
    virtual void slot_14();
    virtual void slot_15();
    virtual void bind_anim(struct Anim3ba734* anim, bool a, bool b);
    unsigned char pad8[0x28];
    Float3_3bdbf0 translate;          // +30
    Float3_3bdbf0 rotate;             // +3c
    float scale[2];                   // +48
    float size[2];                    // +50
    unsigned char flags;              // +58
    unsigned char pad59[2];
    unsigned char origin;             // +5b
''')
s = s.replace('''    void set_translate(const Float3_3bdbf0& t) {
        translate = t;
        flags |= 0x10;
    }
};''', '''    void set_translate(const Float3_3bdbf0& t) {
        translate = t;
        flags |= 0x10;
    }
    void set_scale(float x, float y) {
        scale[0] = x;
        scale[1] = y;
        flags |= 0x10;
    }
    void set_size(float w, float h) {
        size[0] = w;
        size[1] = h;
        flags |= 0x10;
    }
};''')

# The layout: anim list, root, accessor.
s = s.replace('''struct Layout3bdbf0 {
    unsigned char pad0[0x18];
    Pane3bdbf0* root;                 // +18
};''', '''// nn::util-style intrusive list node: prev, then next.
struct ListNode3ba734 {
    ListNode3ba734* prev;
    ListNode3ba734* next;
    void link_prev(ListNode3ba734* node) {
        ListNode3ba734* last = node->prev;
        node->prev = prev;
        last->next = this;
        prev->next = node;
        prev = last;
    }
};

struct Layout3bdbf0 {
    void* f0;
    ListNode3ba734 anims;             // +8
    Pane3bdbf0* root;                 // +18
    unsigned char pad20[0x20];
    void* accessor;                   // +40
    void* find_anim(const char* name);        // 0x71005d4fec
};''')

# The menu: all the fields the build sets.
s = s.replace('''    unsigned char pad548[0x2b8];
    Layout3bdbf0* layout;             // +800
    unsigned char pad808[0x158];
    Pane3bdbf0* panes_960[2];         // +960
    unsigned char pad970[0x10];
    Pane3bdbf0* panes_980[2];         // +980
    unsigned char pad990[0xb0];
    Pane3bdbf0* sources_a40[4];       // +a40
    unsigned char pada60[0xb61c8];
    int kinds[32];                    // +b6c28
''', '''    unsigned char pad548[0x2b8];
    Layout3bdbf0* layout;             // +800
    Layout3bdbf0* plates;             // +808
    Layout3bdbf0* areas;              // +810
    Layout3bdbf0* attributes;         // +818
    Layout3bdbf0* recommend;          // +820
    unsigned char pad828[0x8];
    unsigned char res_830[0x110];     // +830
    Pane3bdbf0* panes[4];             // +940
    Pane3bdbf0* panes_960[2];         // +960
    unsigned char pad970[0x10];
    Pane3bdbf0* panes_980[2];         // +980
    Pane3bdbf0* panes_990[22];        // +990
    Pane3bdbf0* sources_a40[4];       // +a40
    PaneAnim3ba734 faces[11];         // +a60
    AnimBase3ba734* anims[26];        // +b10
    AnimBase3ba734* difficulty;       // +be0
    AnimBase3ba734* skulltula;        // +be8
    Pane3bdbf0* rcm_pos;              // +bf0
    Pane3bdbf0* cursor;               // +bf8
    Pane3bdbf0* windows[4];           // +c00
    Text3ba734* texts[10];            // +c20
    unsigned char padc70[0x10a00];
    int field_11670;                  // +11670
    unsigned char pad11674[4];
    Plate3ba734 plates_11678[32];     // +11678
    Area3ba734 areas_12478[32];       // +12478
    PaneAnim3ba734 attrs[32];         // +b2578
    Pane3bdbf0* rcm;                  // +b2778
    Anim3ba734* rcm_anims[3];         // +b2780
    unsigned char padb2798[0x4448];
    Sub379b08 sub_b6be0;              // +b6be0
    unsigned char padb6be1[0x47];
    int kinds[32];                    // +b6c28
    unsigned char padb6ca8[4];
    unsigned char ready;              // +b6cac
''')
s = s.replace('''    void refresh_lines();
};''', '''    void refresh_lines();
    void build();
};''', 1)

# the panes of the 32-slot array are panes[0..32]: keep refresh_lines' names, the rest follow
new_types = '''struct AnimBase3ba734 {
    virtual void slot_0();
    virtual void slot_1();
    virtual void slot_2();
    virtual void slot_3();
    virtual void set_enable(bool enable);
    virtual void slot_5();
    virtual void slot_6();
    virtual void slot_7();
    virtual void set_resource(void* device, void* accessor, void* block);
    virtual void slot_9();
    virtual void slot_10();
    virtual void slot_11();
    virtual void slot_12();
    virtual void slot_13();
    virtual void slot_14();
    virtual void slot_15();
    virtual void slot_16();
    virtual void slot_17();
    virtual void slot_18();
    virtual void slot_19();
    virtual void slot_20();
    virtual void slot_21();
    virtual void slot_22();
    virtual void slot_23();
    virtual void set_frame(float frame);
    virtual void slot_25();
    virtual void play();
    ListNode3ba734 link;              // +8
    unsigned char pad18[0x30];
    AnimBase3ba734();                 // 0x71005d026c
    static void* operator new(unsigned long size) throw();     // 0x71005d4380
};

struct Anim3ba734 : AnimBase3ba734 {
    void* field_48;                   // +48
    int field_50;                     // +50
    Anim3ba734() : field_48(nullptr), field_50(0) {}
    virtual void key();
};

struct AnimInfo3ba734 {
    void* f0;
    void* block;                      // +8
    void* f10;
    void* f18;
    AnimInfo3ba734(void* res);        // 0x71005cfac8
};

struct PaneAnim3ba734 {
    Pane3bdbf0* pane;
    Anim3ba734* anim;
};

struct Plate3ba734 {
    Pane3bdbf0* pane;                 // +0
    Anim3ba734* anims[10];            // +8
    unsigned char pad58[0x18];
};

struct TextBase3ba734 : Pane3bdbf0 {
    unsigned char pad5c[0x104];
    TextBase3ba734();                 // 0x71005dc664
    static void* operator new(unsigned long size) throw();     // 0x71005d4380
};

struct Text3ba734 : TextBase3ba734 {
    void* field_160;                  // +160
    void* field_168;                  // +168
    void* field_170;                  // +170
    void* field_178;                  // +178
    Text3ba734() : field_160(nullptr), field_168(nullptr), field_170(nullptr) {}
    virtual void text_slot();
};

struct Area3ba734 {
    Pane3bdbf0* pane;                 // +0
    Pane3bdbf0* attr_pos;             // +8
    Text3ba734* texts[3];             // +10
    Anim3ba734* anims[3];             // +28
    unsigned char pad40[0x4fc8];
};

struct Sub379b08 {
    void init(int id);                // 0x7100379b08
};

'''
s = s.replace('struct Menu3bdbf0 {', new_types + 'struct Menu3bdbf0 {', 1)

decls = '''
extern const char kSnaSeleParts_7db544[] __attribute__((visibility("hidden")));
extern const char kSnaPlateParts_7db559[] __attribute__((visibility("hidden")));
extern const char kSnaBtlarea_7db56f[] __attribute__((visibility("hidden")));
extern const char kIconAttribute_7d5c0b[] __attribute__((visibility("hidden")));
extern const char kIconRecommend_7da6d1[] __attribute__((visibility("hidden")));
extern const char kIconPos04Dlc_7db581[] __attribute__((visibility("hidden")));
extern const char kIconPos05Dlc_7db591[] __attribute__((visibility("hidden")));
extern const char kIconPos08Dlc_7db5a1[] __attribute__((visibility("hidden")));
extern const char kIconPos09Dlc_7db5b1[] __attribute__((visibility("hidden")));
extern const char kIconRcmPos_7db5c1[] __attribute__((visibility("hidden")));
extern const char kFace_7d9d39[] __attribute__((visibility("hidden")));
extern const char kDifficulty_7db6b0[] __attribute__((visibility("hidden")));
extern const char kSkulltula_7db6bb[] __attribute__((visibility("hidden")));
extern const char kCursorEasy_7db6c5[] __attribute__((visibility("hidden")));
extern const char kWindowEasy_7db6d1[] __attribute__((visibility("hidden")));
extern const char kWindowNormal_7db6dd[] __attribute__((visibility("hidden")));
extern const char kWindowHard_7db6eb[] __attribute__((visibility("hidden")));
extern const char kWindowVeryhard_7db6f7[] __attribute__((visibility("hidden")));
extern const char kSnaPlateParts_740e57[] __attribute__((visibility("hidden")));
extern const char kSnaPlateOff_7db74d[] __attribute__((visibility("hidden")));
extern const char kSnaPlateOn01_7db75b[] __attribute__((visibility("hidden")));
extern const char kSnaPlateOffDlc_7db76b[] __attribute__((visibility("hidden")));
extern const char kSnaPlateOnDlc_7db77d[] __attribute__((visibility("hidden")));
extern const char kSnaBtlarea_740e4b[] __attribute__((visibility("hidden")));
extern const char kBtlAttributePos_7da7ad[] __attribute__((visibility("hidden")));
extern const char kFontBtlAreaName_7da807[] __attribute__((visibility("hidden")));
extern const char kFontEffAttribute_7da81a[] __attribute__((visibility("hidden")));
extern const char kFontRes_7d5c8f[] __attribute__((visibility("hidden")));
extern const char kIconAttribute_740d16[] __attribute__((visibility("hidden")));
extern const char kAttribute_7d5c33[] __attribute__((visibility("hidden")));
extern const char kRecommend_7db794[] __attribute__((visibility("hidden")));
extern const char kIconAnyone00_7db81b[] __attribute__((visibility("hidden")));
extern const char kFontHen_7db79e[] __attribute__((visibility("hidden")));
extern const char kText7a7_7db7a7[] __attribute__((visibility("hidden")));
extern const char kText7b5_7db7b5[] __attribute__((visibility("hidden")));
extern const char kText7c3_7db7c3[] __attribute__((visibility("hidden")));
extern const char kText7d2_7db7d2[] __attribute__((visibility("hidden")));
extern const char kText7e1_7db7e1[] __attribute__((visibility("hidden")));
extern const char kText7ed_7db7ed[] __attribute__((visibility("hidden")));
extern const char kText7f7_7db7f7[] __attribute__((visibility("hidden")));
extern const char kText803_7db803[] __attribute__((visibility("hidden")));
extern const char kText80d_7db80d[] __attribute__((visibility("hidden")));
extern const char* const kSelAnims_bdb558[26] __attribute__((visibility("hidden")));
extern const char* const kFacePanes_bdb628[4] __attribute__((visibility("hidden")));
extern const char* const kPlateAnims_bdb648[10] __attribute__((visibility("hidden")));
extern const char* const kPlateAnimsDlc_bdb698[10] __attribute__((visibility("hidden")));
extern const char* const kAreaAnims_bdb6e8[3] __attribute__((visibility("hidden")));
extern const char* const kRcmAnims_bdb700[3] __attribute__((visibility("hidden")));
extern const char* const kStagePanes_bdb398[32];
extern const char* const kFaceParents_bdb498[7];
'''
s = s.replace('extern const char* const kLine3Names_bdb860[3] __attribute__((visibility("hidden")));\n',
              'extern const char* const kLine3Names_bdb860[3] __attribute__((visibility("hidden")));\n' + decls, 1)

build = open('docs/s5_wip/3ba734.cpp', newline='').read()
s = s + '\n' + build
for a, b in [('panes_960[0]', 'panes[4]'), ('panes_960[1]', 'panes[5]'), ('panes_980[0]', 'panes[8]'),
             ('panes_980[1]', 'panes[9]')]:
    s = s.replace(a, b)
open(sys.argv[1] if len(sys.argv) > 1 else 'build/s5/g3ba/d3ba734.cpp', 'w', newline='\n').write(s)
