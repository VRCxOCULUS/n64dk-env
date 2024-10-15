#include <nusys.h>
#include "config.h"

void RCPInit(Gfx *glistp)
{
    gSPSegment(glistp++, 0, 0);
    gSPDisplayList(glistp++, OS_K0_TO_PHYSICAL(rspinit_dl));
}

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
};

typedef struct {
    short view_scale[4];
    short view_transformation[4];
    long long int force_structure_alignment;
}