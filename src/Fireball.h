#ifndef FIRE_BALL_H
#define FIRE_BALL_H
#include"needed.h"
#include "Character.h"

#define BE_CREATED 1 
#define NONE_CREATED 0 
#define FIREBAL_VEL  0.02

class Fireball : public Dot  {
    public :
    Fireball();
    ~Fireball();


    void setFrameFireball ();
    
    void setXPos ( int X) ;
    void setYPos ( int Y) ;

    void autoMove();


    double getXPos ();
    double getYPos ();

    private :
    SDL_Rect  frame_fireball [32];
    double  mPosX , mPosY ;
    int status ;
    double mVelX;

} ;


#endif 
