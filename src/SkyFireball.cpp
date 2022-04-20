#include"needed.h"
#include"SkyFireball.h"

SkyFireball :: SkyFireball(){
    mPosX = SCREEN_WIDTH/2 ; 
    mPosY = 0;
    mVel=1 + rand() % 5;
    setFrame();
}

SkyFireball:: ~SkyFireball(){
    free();
}

void SkyFireball ::  resetSkyFireball (){
    mPosX = SCREEN_WIDTH/2 ; 
    mPosY = 0;
    mVel=1 + rand() % 5;
}

void SkyFireball :: setFrame(){
    for (int i=1;i<=60;i++){
        skyFireballFrames[i].x=(i-1)*9;
        skyFireballFrames[i].y=0;   
        skyFireballFrames[i].w=9;
        skyFireballFrames[i].h=25;
    }
}

bool SkyFireball :: loadFireball(SDL_Renderer * screen){
    if ( loadFromFile("img/skyFireball/sfb.png",screen)== false ){
        std::cout<<"Could not load sky fireball "<<std::endl;
        return false ;
    }
    return true ;
}

void SkyFireball:: renderSkyFireball (SDL_Renderer * screen , const int * point  ){
    if ( *point >= 100 )
    {
        render(mPosX,mPosY,screen,&skyFireballFrames[frameSkyfireball/5]);
        frameProcessing();
    }
}
void SkyFireball :: frameProcessing(){
    frameSkyfireball++;
    if ( frameSkyfireball>= 5 * 30 ){
        frameSkyfireball = 5 ;
    }
}

void SkyFireball :: autoMove(){
    
    mPosY+=mVel;
    if ( mPosY > 700 ){
        mPosY=0 ;
        mPosX =  rand() % SCREEN_WIDTH ;
        mVel = 1+ rand () % 3;
    }
}


void SkyFireball :: checkCollisionWithMainCharacter(Character * gTestCharacter){
    if ( mPosY  >= gTestCharacter->getCharacterPosY() + 15 && mPosY  <= gTestCharacter->getPosY() + 40 && mPosX >= gTestCharacter->getCharacterPosX() + 90 && mPosX + 9 <= gTestCharacter->getCharacterPosX() + 160  && gTestCharacter->getStatus()!=DEAD_CHARACTER ){
        std::cout<<"Collision "<<std::endl;
        gTestCharacter->setStatus(DEAD_CHARACTER);
        mPosY=0;
    }   
}

void SkyFireball:: setCoordinate ( double X, double Y){
    mPosX = X;
    mPosY = Y;
}
void SkyFireball ::  setVelocity(double vel ){
    mVel= vel;
}

void SkyFireball:: manageFireball (SDL_Renderer * screen , int * point , Character *gTestCharacter ){
    renderSkyFireball(screen,point);
    autoMove();
    checkCollisionWithMainCharacter(gTestCharacter);
}