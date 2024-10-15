#include <nusys.h>
#include "config.h"

static void callback_prenmi();

void callback_prenmi()
{
    nuGfxDisplayOff();
    osViSetYScale(1);
}

Gfx glist[GLIST_LENGTH];
Gfx* glistp;

static void vsyncCallback(int pendingTaskCount);

void mainproc(void * dummy)
{
    if (TV_TYPE == PAL)
    {
        osViSetMode(&osViModeTable[OS_VI_FPAL_LAN1]);
        osViSetYScale(0.833);
        nuPreNMIFuncSet((NUScPreNMIFunc)callback_prenmi);
    }
    else if (TV_TYPE == MPAL)
    {
        osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1]);
    }
    nuGfxInit();
    stage00_init();
    nuGfxFuncSet((NUGfxFunc)vsyncCallback);
    NuGfxDisplayOn();

    while(1)
        ;
}

void vsyncCallback(int pendingTaskCount)
{
    stage00_update();
    if(pendingTaskCount < 1)
    {
        stage00_draw();
    }
}