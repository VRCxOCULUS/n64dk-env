#include  <nusys.h>
#include  "config.h"
#include "sprite_testing_checkered_tile.h"


static void ClearBackground(u8 r, u8 g, u8 b);


static u8 b;

static int x; // x position of sprite
static int y;// y position of sprite

void DrawChecker(int x, int y); // Create a prototype for function


void stage00_init(void)
{
    b = 255;
    x = 32; // Give x a value when the stage starts
    y = 32; // Give y a value when the stage starts
}


void stage00_update(void)
{
    b-=5;
}


void stage00_draw(void)
{
    // Assign our glist pointer to our glist array for ease of access
    glistp = glist;

    // Initialize the RCP
    RCPInit(glistp);

    // Wipe the background with a color
    ClearBackground(0, 0, b);

    DrawChecker(x, y); // Draw sprite after drawing background

    // Syncronize the RCP and CPU
    gDPFullSync(glistp++);
    
    // Specify that our display list has ended
    gSPEndDisplayList(glistp++);
    
    // Start the display task
    nuGfxTaskStart(glist, (s32)(glistp - glist) * sizeof(Gfx), NU_GFX_UCODE_F3DEX, NU_SC_SWAPBUFFER);
}


static void ClearBackground(u8 r, u8 g, u8 b)
{
    gDPSetCycleType(glistp++, G_CYC_FILL);
    gDPSetDepthImage(glistp++, nuGfxZBuffer); // nuGfxZBuffer is Nusys’ Z-Buffer 
    gDPSetColorImage(glistp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, nuGfxZBuffer);
    gDPSetFillColor(glistp++, (GPACK_ZDZ(G_MAXFBZ, 0) << 16 | GPACK_ZDZ(G_MAXFBZ, 0)));
    gDPFillRectangle(glistp++, 0, 0, SCREEN_WD - 1, SCREEN_HT - 1);
    gDPPipeSync(glistp++);

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


void DrawChecker(int x, int y)
{
    gDPSetCycleType(glistp++, G_CYC_1CYCLE);
    gDPSetCombineMode(glistp++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(glistp++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE);
    gDPSetDepthSource(glistp++, G_ZS_PRIM);
    gDPSetPrimDepth(glistp++, 0, 0);
    gDPSetTexturePersp(glistp++, G_TP_NONE);
    gDPLoadTextureBlock(glistp++, 
        sprite_testing_checkered_tile, 
        G_IM_FMT_RGBA, G_IM_SIZ_16b, 
        16, 16, 0, 
        G_TX_WRAP, G_TX_WRAP, 
        G_TX_NOMASK, G_TX_NOMASK, 
        G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(glistp++, 
        x-8<<2, y-8<<2, 
        (x + 8)<<2, (y + 8)<<2,
        G_TX_RENDERTILE, 
        0 << 5, 0 << 5, 
        1 << 10, 1 << 10);
    gDPPipeSync(glistp++);
}
