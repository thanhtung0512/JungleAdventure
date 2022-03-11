#include"needed.h"
#include"Dot.h"


Dot :: Dot (){
    mVelX = mVelY =0;
    mPosX = 0;
    mPosY = DEFAULT_MAIN_CHARACTER_Y ;
}


Dot::~Dot (){;}


void Dot:: handleEvent (SDL_Event &e){
    if ( e.type == SDL_KEYDOWN  && e.key.repeat ==0 ){
        switch ( e.key.keysym.sym ){
            case SDLK_UP :{
                mVelY -= DOT_VEL ;
                // renderJumpAnimation();
                break;
            }
            // case SDLK_DOWN :{
            //     mVelY+= DOT_VEL;
            //     break;
            // }
            case SDLK_RIGHT :{
                mVelX  += DOT_VEL ;
                //renderRightAnimation 
                break;
            }
            case SDLK_LEFT :{
                mVelX -= DOT_VEL;
                // renderLetfAnimation 
                break;
            }
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat ==0 ){
        switch ( e.key.keysym.sym){
            case SDLK_UP :{
                mVelY += DOT_VEL ;
                break;
            }
            // case SDLK_DOWN :{
            //     mVelY-= DOT_VEL;
            //     break;
            // }
            case SDLK_RIGHT :{
                mVelX  -= DOT_VEL ;
                break;
            }
            case SDLK_LEFT :{
                mVelX += DOT_VEL;
                break;
            }
        }
    }
}

void Dot::move (){
    // move dot left or right 
    mPosX += mVelX;
    if (mPosX<0 || (mPosX + DOT_WIDTH >SCREEN_WIDTH )){
        mPosX -= mVelX;
    }

    // move up or down 
    mPosY+=mVelY;
    if ( mPosY < 0 ||( mPosY + DOT_HEIGHT >SCREEN_HEIGHT )){
        mPosY -= mVelY;
    }
}

void Dot::renderDot (SDL_Renderer * screen,LTexture dot  ){
    dot.render(mPosX,mPosY,screen,NULL);
}


int Dot :: getPosX(){
    return mPosX;
}


int Dot :: getPosY(){
    return mPosY;
}


void Dot :: setPosX ( int posX){
    mPosX = posX;
}


void Dot :: setPosY ( int posY){
    mPosY = posY;
}