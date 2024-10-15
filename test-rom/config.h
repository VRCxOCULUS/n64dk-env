#ifndef N64_CONFIG_H
#define N64_CONFIG_H

    #define SCREEN_WD 320
    #define SCREEN_HT 240

    #define GLIST_LENGTH 2048

    extern Gfx glist[GLIST_LENGTH];
    extern Gfx* glistp;

    void RCPInit(Gfx *glistp);

#endif