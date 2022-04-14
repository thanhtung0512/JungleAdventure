#ifndef SKY_FIREBALL_H
#define SKY_FIREBALL_H
#include"needed.h"

class SkyFireball : public LTexture{
    
    public :
        SkyFireball();
        ~SkyFireball();
        void setFrame();
        bool loadFireball(SDL_Renderer * screen);
        void renderSkyFireball (SDL_Renderer * screen );
        void autoMove();    
        void frameProcessing();
        void checkCollisionWithMainCharacter(Character * gTestCharacter);
        void setCoordinate ( double X, double Y);
        void setVelocity(double vel );
    private:
    
    double mPosX, mPosY;
    SDL_Rect skyFireballFrames[61];
    int frameSkyfireball ;
    double mVel;
};


#endif