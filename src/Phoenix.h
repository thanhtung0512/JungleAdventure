#ifndef PHOENIX_H 
#define PHOENIX_H

#include"needed.h"


class Phoenix : public Character
{
    public :
    Phoenix();
    ~Phoenix();

    bool loadPhoenix (SDL_Renderer * screen );
    void setSpritePhoenix ();
    void renderPhoenix ( SDL_Renderer  * screen );
    int getPhoenixX ();
    void resetPhoenix ();

    protected :
    int mPosX, mPosY ;
    SDL_Rect spriteOfPhoenix[13];
    int framePhoenix ;

};



#endif