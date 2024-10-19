#include <nusys.h>
#include "config.h"
#include "stages.h"


static void vsyncCallback(int pendingTaskCount);
static void callback_prenmi();

NUContData contdata[]; // Number of controllers to keep track of (1)
u8 contPattern; // Which controllers are plugged in


void mainproc(void * dummy)
{
    // Start by selecting the proper television
    if (TV_TYPE == PAL)
    {
        osViSetMode(&osViModeTable[OS_VI_FPAL_LAN1]);
        osViSetYScale(0.833); // Dirty but works
        nuPreNMIFuncSet((NUScPreNMIFunc)callback_prenmi);
    }
    else if (TV_TYPE == MPAL)
        osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1]);

    // Initialize and activate the graphics thread and Graphics Task Manager.
    nuGfxInit();

    contPattern = nuContInit();

    // Create a callback function
    nuGfxFuncSet((NUGfxFunc)vsyncCallback);

    // Initialize stage 0
    stage00_init();
    
    // Turn on the screen
    nuGfxDisplayOn();

    // Loop forever to keep the idle thread busy
    while(1)
        ;
}


/*=================================
          vsyncCallback
This is a callback functions which
  execute instructions, and once
it has run out of instructions, it
  activates the display process.
=================================*/

void vsyncCallback(int pendingTaskCount)
{
    // Update the stage
    stage00_update();

    // If we've run out of tasks, draw the stage
    if (pendingTaskCount < 1)
        stage00_draw();
}

// To prevent crashing when the reset button is pressed
void callback_prenmi()
{
    nuGfxDisplayOff();
    osViSetYScale(1);
}