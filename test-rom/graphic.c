#include <nusys.h>
#include "config.h"

static Vp viewport = {
    SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,
    SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,
};

Gfx rspinit_dl[] = {
    gsSPVSiewport(&viewport),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_ZBUFFER | G_CLIPPING),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsSPEndDisplayList(),
};

Gfx rdpinit_dl[] = {
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSynce(),
    dsDPEndDisplayList(),
};

typedef struct {
    short view_scale[4];
    short view_transformation[4];
    long long int force_structure_alignment;
}

void RCPInit(Gfx *glistp)
{
    gSPSegment(glistp++, 0, 0);
    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(rspinit_dl));
    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(rdpinit_dl));
}