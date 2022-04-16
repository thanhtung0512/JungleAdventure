#ifndef BOSS_H
#define BOSS_H

#include "needed.h"

class Boss : public Dot {
    
    public:
        Boss();
        ~Boss();
        void setClipsWalk();
        void renderBoss ( SDL_Renderer * screen );
        void frameProcessing ();
        bool loadBoss(SDL_Renderer* screen );
        void resetBoss();

    protected : 
    int mPosX, mPosY ;
    SDL_Rect frameWalk [150];
    int frameOfWalk ;
    

};


#endif