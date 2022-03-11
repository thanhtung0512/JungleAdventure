#include"needed.h"
#include"Fireball.h"


Fireball :: Fireball (){
    mPosX = 40;
    mPosY = DEFAULT_PHOENIX_Y + 90;
    status = NONE_CREATED;
    mVelX = 0 ;
    
}

Fireball ::~Fireball(){

}


void Fireball :: setFrameFireball (){
    for(int i=1;i<= 30;i++){
        frame_fireball[i].x=(i-1) * 10;
        frame_fireball[i].y=0;
        frame_fireball[i].w=10;
        frame_fireball[i].h=26;
    }
}


void Fireball :: setXPos ( int X){
        mPosX = X; 
}


void Fireball :: setYPos ( int Y){
        mPosY = Y;
}

double Fireball :: getXPos(){
    return mPosX;
}

double Fireball :: getYPos(){
    return mPosY ; 
}

void Fireball :: autoMove (){
    mVelX += FIREBAL_VEL;
    mPosX += mVelX ;
    if (mPosX + FIREBALL_WIDTH > SCREEN_WIDTH + 1000){
        mPosX = 40;
        mVelX = 0;
    }
}

