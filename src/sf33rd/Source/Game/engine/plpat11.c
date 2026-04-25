/**
 * @file plpat11.c
 * Ken Attacks
 */

#include "sf33rd/Source/Game/engine/plpat11.h"
#include "common.h"
#include "sf33rd/Source/Game/effect/effi3.h"
#include "sf33rd/Source/Game/engine/charset.h"
#include "sf33rd/Source/Game/engine/cmd_data.h"
#include "sf33rd/Source/Game/engine/grade.h"
#include "sf33rd/Source/Game/engine/plpat.h"
#include "sf33rd/Source/Game/engine/plpatuni.h"
#include "sf33rd/Source/Game/engine/pls01.h"
#include "sf33rd/Source/Game/engine/pls02.h"
#include "sf33rd/Source/Game/stage/bg.h"

void (*const pl11_exatt_table[18])(PLW*);
u8 get_lever_dir_ken(PLW* wk);

void pl11_extra_attack(PLW* wk) {
    pl11_exatt_table[wk->wu.routine_no[2] - 16](wk);
}

void Att_PL11_TOKUSHUKOUDOU(PLW* wk) {
    wk->scr_pos_set_flag = 0;

    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        hoken_muriyari_chakuchi(wk);
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        break;

    case 1:
        char_move(&wk->wu);

        switch (wk->wu.cg_type) {
        case 40:
            wk->wu.cg_type = 0;
            add_sp_arts_gauge_tokushu(wk);
            break;

        case 20:
            wk->wu.cg_type = 0;
            wk->tk_dageki += 10;

            if (wk->tk_dageki > 10) {
                wk->tk_dageki = 10;
            }

            break;

        case 64:
            grade_add_personal_action(wk->wu.id);
            break;
        }

        break;
    }
}

s32 kabe_check_ken(PLW* wk) {
    if (get_lever_dir_ken(wk) != 1) {
        return 0;
    }

    if (wk->wu.xyz[1].disp.pos < 33) {
        return 0;
    }

    return (wk->wu.rl_flag + wk->micchaku_flag == 2);
}

void Att_AIRDASH_KEN(PLW* wk) {
    switch (wk->wu.routine_no[3]) {
    case 0:
        wk->wu.routine_no[3]++;
        wk->wu.rl_flag = wk->wu.rl_waza;
        set_char_move_init(&wk->wu, 5, wk->as->char_ix);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;

    case 1:
        char_move(&wk->wu);

        if (kabe_check_ken(wk) != 0) {
            wk->wu.rl_flag = (wk->wu.rl_flag + 1) & 1;
            wk->wu.xyz[0].disp.pos = wk->wu.rl_flag ? bg_w.bgw[1].l_limit2 - 192 : bg_w.bgw[1].r_limit2 + 192;
            set_char_move_init(&wk->wu, 5, 65);
            wk->wu.routine_no[3] = 5;
            wk->wu.cg_type = 0;
            effect_I3_init(&wk->wu, 4);
            break;
        }

        add_mvxy_speed(&wk->wu);
        cal_mvxy_speed(&wk->wu);

        switch (wk->wu.cg_type) {
        case 20:
            setup_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
            break;

        case 25:
            add_to_mvxy_data(&wk->wu, wk->wu.mvxy.index);
            wk->wu.mvxy.index++;
            wk->wu.cg_type = 0;
            break;

        case 30:
            setup_mvxy_data(&wk->wu, wk->as->data_ix);
            wk->wu.routine_no[3] = 3;
            wk->wu.cg_type = 0;
            break;
        }

        break;

    case 3:
        jumping_union_process(&wk->wu, 4);

        if (kabe_check_ken(wk)) {
            wk->wu.rl_flag = wk->wu.rl_flag + 1 & 1;
            wk->wu.xyz[0].disp.pos = wk->wu.rl_flag ? bg_w.bgw[1].l_limit2 - 192 : bg_w.bgw[1].r_limit2 + 192;
            set_char_move_init(&wk->wu, 5, 65);
            wk->wu.routine_no[3] = 5;
            wk->wu.cg_type = 0;
            effect_I3_init(&wk->wu, 4);
        }

        break;

    case 4:
        char_move(&wk->wu);
        break;

    case 5:
        char_move(&wk->wu);

        if (wk->wu.cg_type == 0xFF) {
            wk->wu.cg_type = 0;
            wk->wu.routine_no[3]++;
        }

        break;

    case 6:
        wk->wu.routine_no[3] = 1;
        char_move_cmj4(&wk->wu);
        reset_mvxy_data(&wk->wu);
        wk->wu.mvxy.index = wk->as->r_no;
        break;
    }
}

u8 get_lever_dir_ken(PLW* wk) {
    u8 num;

    if (wk->wu.work_id == 1) {
        if (wk->py->flag == 0) {
            num = wcp[wk->wu.id].lever_dir;
        } else {
            num = 0;
        }
    } else {
        num = wcp[((WORK_Other*)wk)->master_id & 1].lever_dir;
    }

    return num;
}

void (*const pl11_exatt_table[18])(PLW*) = { Att_HADOUKEN,
                                             Att_SHOURYUUKEN,
                                             Att_SENPUUKYAKU,
                                             Att_SHOURYUUREPPA,
                                             Att_SHOURYUUREPPA,
                                             Att_SLIDE_and_JUMP,
                                             Att_KUUCHUUNICHIRINSHOU,
                                             Att_CHOUCHUURENGEKI,
                                             Att_DUMMY, //Att_AIRDASH_KEN
                                             Att_DUMMY,
                                             Att_DUMMY,
                                             Att_DUMMY,
                                             Att_DUMMY,
                                             Att_DUMMY,
                                             Att_PL11_TOKUSHUKOUDOU,
                                             Att_DUMMY,
                                             Att_METAMOR_WAIT,
                                             Att_METAMOR_REBIRTH };
