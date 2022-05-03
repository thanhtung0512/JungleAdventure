#include"needed.h"
#include"Fireball.h"


Fireball :: Fireball (){
     affectDamage =1; 
    mPosX = 40;
    mPosY = DEFAULT_PHOENIX_Y + 90;
    status = NONE_CREATED;
    mVelX = 0 ;
    frameFireball = 10 ;
    setSpriteFireball();
}


void Fireball ::  resetFireball (){
     affectDamage =1; 
    mPosX = 40;
    mPosY = DEFAULT_PHOENIX_Y + 90;
    status = NONE_CREATED;
    mVelX = 0 ;
    frameFireball = 10 ;
}

Fireball ::~Fireball(){
    free();
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

    if ( mPosX == SCREEN_WIDTH ){
        mPosX = 2*SCREEN_WIDTH ;
        while ( mPosX < 2*SCREEN_WIDTH + 1000 ){
            mPosX += 0.0000009;
        }
        if (mPosX + FIREBALL_WIDTH >= 2*SCREEN_WIDTH + 1000){
        resetFireball();
        }
    }

    if (mPosX + FIREBALL_WIDTH >= 2*SCREEN_WIDTH ){

        while ( mPosX < 2*SCREEN_WIDTH + 1000 ){
            mPosX += 0.001;
        }
        resetFireball();
    }

    
}

void Fireball :: setSpriteFireball (){
    for(int i=1 ;i<= 30 ;i++){
        spriteOfFireball[i].x= (i-1) * 68; 
        spriteOfFireball[i].y=0;
        spriteOfFireball[i].w=68;
        spriteOfFireball[i].h= 9 ;
    }
}

void Fireball ::  renderFireball (SDL_Renderer * screen ){
    SDL_Rect currentFireball = spriteOfFireball[frameFireball / 10 ];
    render(mPosX , mPosY ,screen ,& currentFireball );
    frameFireball++ ;
     if ( frameFireball >= 10 * 30 ){
            frameFireball = 10 ;
        }    
}

bool Fireball :: loadFireball (SDL_Renderer * screen ){
    if (loadFromFile("img/fireball/fireball.png",screen) == false ){
        std::cout<<"could not load fireball "<<SDL_GetError()<<std::endl;
        return false ;    
    }
    return true;
}
void Fireball ::  manageFireball (SDL_Renderer * screen ){
    renderFireball(screen );
    autoMove();
}

int Fireball ::  getStatusDamage (){
    return affectDamage ; 
}

void Fireball ::  setStatusDamage(int status ){
    affectDamage  = status ;
}