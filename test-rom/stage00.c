/*========================================================
				Stage 0 logic and rendering
========================================================*/
/*=================================
            Libraries
=================================*/
#include  <nusys.h>
#include  "config.h"


/*=================================
             Prototypes
=================================*/

static void ClearBackground(u8 r, u8 g, u8 b);


/*=================================
         Global Variables
=================================*/

static u8 b;


/*=================================
            stage00_init
        Initialize the stage
=================================*/

void stage00_init(void)
{
    b = 255;
}


/*=================================
          stage00_update
   Update variables and objects
=================================*/

void stage00_update(void)
{
    b-=5;
}


/*=================================
            stage00_draw
           Draw the stage
=================================*/

void stage00_draw(void)
{
    // Assign our glist pointer to our glist array for ease of access
    glistp = glist;

    // Initialize the RCP
    RCPInit(glistp);

    // Wipe the background with a color
    ClearBackground(0, 0, b);

    // Syncronize the RCP and CPU
    gDPFullSync(glistp++);
    
    // Specify that our display list has ended
    gSPEndDisplayList(glistp++);
    
    // Start the display task
    nuGfxTaskStart(glist, (s32)(glistp - glist) * sizeof(Gfx), NU_GFX_UCODE_F3DEX, NU_SC_SWAPBUFFER);
}


/*=================================
           ClearBackground
 Wipe the background with a color
=================================*/

static void ClearBackground(u8 r, u8 g, u8 b)
{    
    // Specify the RDP Cycle type
    gDPSetCycleType(glistp++, G_CYC_FILL);
    
    // Specify the color type
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, osVirtualToPhysical(nuGfxCfb_ptr));
    
    // Specify the color
    gDPSetFillColor(glistp++, (GPACK_RGBA5551(r, g, b, 1) << 16 | GPACK_RGBA5551(r, g, b, 1)));
    
    // Draw a rectangle to the screen
    gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
    
    // Resyncronize for the next display list task
    gDPPipeSync(glistp++);
}