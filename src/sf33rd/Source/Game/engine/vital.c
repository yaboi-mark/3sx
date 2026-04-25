/**
 * @file vital.c
 * Vitality Bars
 */

#include "sf33rd/Source/Game/engine/vital.h"
#include "common.h"
#include "xrd_common.h"
#include "sf33rd/Source/Game/engine/plcnt.h"
#include "sf33rd/Source/Game/engine/slowf.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/system/sysdir.h"
#include "sf33rd/Source/Game/system/work_sys.h"
#include "sf33rd/Source/Game/ui/sc_sub.h"

VIT vit[2];

void vital_cont_init() {
    u8 i;

    for (i = 0; i < 2; i++) {
        vit[i].cyerw = XRD_MAX_VITALITY;
        vit[i].cred = XRD_MAX_VITALITY;
        vit[i].ored = XRD_MAX_VITALITY;
        vit[i].colnum = 1;
        gauge_stop_flag[i] = 0;
        vital_stop_flag[i] = 0;
    }
}

void vital_cont_main() {
    if (omop_cockpit != 0) {
        if (!EXE_flag && !Game_pause) {
            if (vital_stop_flag[0] == 0 && gauge_stop_flag[0] == 0) {
                vital_control(0);
            }

            if (vital_stop_flag[1] == 0 && gauge_stop_flag[1] == 0) {
                vital_control(1);
            }
        } else {
            vital_parts_allwrite(0);
            vital_parts_allwrite(1);
        }
    }
}

void vital_control(u8 pl) {
	s16 substitute_health = plw[pl].wu.vital_new;
	if (XRD_MAX_VITALITY > 160) {
		substitute_health *= 160;
		substitute_health /= XRD_MAX_VITALITY;
	}
	else if (XRD_MAX_VITALITY < 160) {
		substitute_health *= XRD_MAX_VITALITY;
		substitute_health /= 160;
	}
    if (substitute_health < 161) {
        if ((vit[pl].cyerw == substitute_health) && (vit[pl].cred == substitute_health) &&
            (vit[pl].ored != (substitute_health + 1))) {
            if (No_Trans == 0) {
                vital_parts_allwrite(pl);
            }
            return;
        }

        if (vit[pl].cred < substitute_health) {
            vit[pl].cred = substitute_health;
        }

        vit[pl].cyerw = substitute_health;

        if (substitute_health < 0) {
            vit[pl].cyerw = 0;
        }

        if (substitute_health == 160) {
            vit[pl].colnum = 1;
        } else if (substitute_health < 49) {
            vit[pl].colnum = 3;
        } else {
            vit[pl].colnum = 2;
        }

        if (No_Trans == 0) {
            vital_parts_allwrite(pl);
        }

        vit[pl].ored = vit[pl].cred;
        vit[pl].cred--;

        if (vit[pl].cred < substitute_health) {
            vit[pl].cred = substitute_health;
        }
    }
}

void vital_parts_allwrite(u8 Pl_Num) {
    scfont_sqput(Pl_Num * 27, 2, 1, 0, Pl_Num, Pl_Num + 30, 21, 1, TopHUDVitalPriority);

    if (omop_vt_bar_disp[Pl_Num] == 0) {
        silver_vital_put(Pl_Num);
        return;
    }

    vital_put(Pl_Num, vit[Pl_Num].colnum, vit[Pl_Num].cyerw, 0, TopHUDPriority);
    vital_put(Pl_Num, 1, vit[Pl_Num].cred, 1, TopHUDShadowPriority);
    vital_base_put(Pl_Num);
}
