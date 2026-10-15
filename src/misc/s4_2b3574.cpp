// The grade record of a result screen (fourth session, template family 2b3574): ResultRecord::init finds the record's
// panes in its layout group, hides the group, shows the prime record for mode 1 and, except in mode 8, creates the
// grade layout (result_grade.bflyt) and places it by rank. The original has two identical copies (0x71002b3574,
// 0x71002b828c), written as one template with a dummy copy number. Names are descriptive placeholders.

#include "event/demo_effects.h"

struct GradePart {
    unsigned char pad0[0x18];
    void* pane;               // +18
};
GradePart* find_part_1e3770(LightEffectNode* node, const char* name, int depth);   // 0x71001e3770
void set_pane_scale_1e4570(void* pane, float scale);                               // 0x71001e4570

extern const char kRupeeS_2b3574[] __attribute__((visibility("hidden")));         // 0x71007d7bc5 "rupee_s"
extern const char kRupeeL_2b3574[] __attribute__((visibility("hidden")));         // 0x71007d7bcd "rupee_l"
extern const char kRecord_2b3574[] __attribute__((visibility("hidden")));         // 0x71007d7bba "num_record"
extern const char kBonusS_2b3574[] __attribute__((visibility("hidden")));         // 0x71007d7ba2 "num_bonus_s"
extern const char kBonusL_2b3574[] __attribute__((visibility("hidden")));         // 0x71007d7bae "num_bonus_l"
extern const char kRupee_2b3574[] __attribute__((visibility("hidden")));          // 0x7100740db7 "num_rupee"
extern const char kFont_2b3574[] __attribute__((visibility("hidden")));           // 0x71007d60c9 "font_txt"
extern const char kPrime_2b3574[] __attribute__((visibility("hidden")));          // 0x71007d7bd5 "num_record_prime"
extern const char kLayout_2b3574[] __attribute__((visibility("hidden")));         // 0x71007d7c5f "result_grade.bflyt"
extern const char kGradeIn_2b3574[] __attribute__((visibility("hidden")));        // 0x71007d7c72 "grade_in"
extern const char kGrade_2b3574[] __attribute__((visibility("hidden")));          // 0x71007d7c7b "grade"

struct GroupFlags {
    unsigned char pad0[0x58];
    unsigned char visible : 1;   // +58 bit 0
    unsigned char : 7;
};

class ResultRecord {
public:
    template <int Copy> void init(EffectGroup* root, int rank, int mode);

    int rank;                 // +00
    int mode;                 // +04
    long index;               // +08
    LightEffectNode* node;    // +10
    GradePart* grade_in;      // +18
    unsigned char pad20[0x18];
    EffectGroup* root;        // +38
    EffectGroup* rupee_s;     // +40
    EffectGroup* rupee_l;     // +48
    EffectGroup* record;      // +50
    EffectGroup* bonus_s;     // +58
    EffectGroup* bonus_l;     // +60
    EffectGroup* rupee;       // +68
    EffectGroup* font;        // +70
    EffectGroup* grade;       // +78
};

template <int Copy>
void ResultRecord::init(EffectGroup* root_, int rank_, int mode_) {
    reinterpret_cast<GroupFlags*>(root_)->visible = 0;
    root = root_;
    rank = rank_;
    mode = mode_;
    rupee_s = root->find(kRupeeS_2b3574, 1);
    rupee_l = root->find(kRupeeL_2b3574, 1);
    record = root->find(kRecord_2b3574, 1);
    bonus_s = root->find(kBonusS_2b3574, 1);
    bonus_l = root->find(kBonusL_2b3574, 1);
    rupee = root->find(kRupee_2b3574, 1);
    font = root->find(kFont_2b3574, 1);
    EffectGroup* prime = root->find(kPrime_2b3574, 1);
    reinterpret_cast<GroupFlags*>(prime)->visible = mode_ == 1;
    if (mode_ != 8) {
        gEffectManager->create_node(&node, 0x4213, kLayout_2b3574);
        gEffectManager->sync();
        GradePart* p = find_part_1e3770(node, kGradeIn_2b3574, 1);
        grade_in = p;
        set_pane_scale_1e4570(p->pane, node->group->scale48);
        float y = (float)(rank * -0x37 + 0x37);
        EffectGroup* g = node->group;
        g->offset30 = 0.0f;
        g->offset34 = y;
        g->offset38 = 0.0f;
        g->flags58 |= 0x10;
        grade = node->group->find(kGrade_2b3574, 1);
    }
    index = -1;
    prime->offset30 += 12.0f;
    prime->flags58 |= 0x10;
}

template void ResultRecord::init<0>(EffectGroup*, int, int);
template void ResultRecord::init<1>(EffectGroup*, int, int);
