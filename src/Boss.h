#ifndef BOSS_H
#define BOSS_H

#include "needed.h"

class Boss : public Dot {
    
    public:
        Boss();
        Boss(SDL_Renderer * screen );
        ~Boss();
        void setClipsWalk();
        void renderBoss ( SDL_Renderer * screen );
        void frameProcessing ();
        bool loadBoss(SDL_Renderer* screen );
        void resetBoss();
        void playSound ();
        void pauseSound ( );

    protected : 
    int mPosX, mPosY ;
    SDL_Rect frameWalk [150];
    int frameOfWalk ;
    Mix_Music * bossAppeared ; 

    

};


#endif