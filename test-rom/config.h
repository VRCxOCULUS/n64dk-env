#ifndef N64_CONFIG_H
#define N64_CONFIG_H

    #define NTSC    0
    #define PAL     1
    #define MPAL    2
    
    #define TV_TYPE PAL

    #define SCREEN_WD   320
    #define SCREEN_HT   240

    #define GLIST_LENGTH    (2048)
    
    extern Gfx glist[GLIST_LENGTH];
    extern Gfx* glistp;

    extern NUContData contdata[NU_CONT_MAXCONTROLLERS];
    extern u8 contPattern;

    void RCPInit(Gfx *glistp);

#endif