#ifndef SKY_FIREBALL_H
#define SKY_FIREBALL_H
#include"needed.h"

class SkyFireball : public LTexture {
    
    public :
        SkyFireball();
        ~SkyFireball();
        void setFrame();
        bool loadFireball(SDL_Renderer * screen);
        void renderSkyFireball (SDL_Renderer * screen , const int * point  );
        void autoMove();    
        void frameProcessing();
        void checkCollisionWithMainCharacter(Character * gTestCharacter);
        void setCoordinate ( double X, double Y);
        void setVelocity(double vel );
        void resetSkyFireball ();
        void manageFireball (SDL_Renderer * screen , int * point , Character *gTestCharacter );
    private:
    
    bool isAppeared ;
    double mPosX, mPosY;
    SDL_Rect skyFireballFrames[61];
    int frameSkyfireball ;
    double mVel;
};


#endif