#include <nusys.h>
#include "config.h"

Gfx glist[GLIST_LENGTH];
Gfx* glistp;

static void vsyncCallback(int pendingTaskCount);

void mainproc(void * dummy)
{
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