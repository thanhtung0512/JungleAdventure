#ifndef FIRE_BALL_H
#define FIRE_BALL_H
#include"needed.h"
#include "Character.h"

#define BE_CREATED 1 
#define NONE_CREATED 0 
#define FIREBAL_VEL  0.01/2

class Fireball : public Dot  {
    public :
    Fireball();
    ~Fireball();

    void setXPos ( int X) ;
    void setYPos ( int Y) ;

    void autoMove();

    double getXPos ();
    double getYPos ();

    void setSpriteFireball ();

    void renderFireball (SDL_Renderer * screen );
    bool loadFireball (SDL_Renderer * screen );

    void resetFireball ();
    void manageFireball (SDL_Renderer * screen );

    int getStatusDamage ();
    void setStatusDamage(int status );

    private :

    SDL_Rect  spriteOfFireball [31];
    double  mPosX , mPosY ;
    int status ;
    double mVelX;
    int frameFireball ; 
    int affectDamage ; 
} ;


#endif 
