#ifndef dot_h
#define dot_h
#include"needed.h"

class Dot : public LTexture{
    public :
    static const int   DOT_WIDTH =20;
    static const int   DOT_HEIGHT =20;

    static const int   DOT_VEL =1 ;

    Dot();
    ~Dot();

    // take key presses and ajust the dot velocity 
    void handleEvent ( SDL_Event & e);

    //moves the dot 
    void move ();

    //show the dot on the screen 
    void renderDot  (SDL_Renderer * screen ,LTexture dot );

    int  getPosX();
    int  getPosY();

    void setPosX ( int posX);
    void setPosY ( int posY);

    private :
    // coordinate of the dot 
    int   mPosX, mPosY;

    // velocity of the dot 
    int   mVelX, mVelY ;

};




#endif 