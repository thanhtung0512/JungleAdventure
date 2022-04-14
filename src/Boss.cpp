#include"needed.h"
#include"Boss.h"

Boss::Boss(){
    setClipsWalk();
    mPosX = SCREEN_WIDTH/2- 50 ;
    mPosY = 530  ;
    frameOfWalk = 120 ;
    
}

Boss::~Boss(){
    free();
}

void Boss::setClipsWalk(){
    int first=0;
    int c=1;
    for (int i=1;i<=4;i++){
        for (int j=1;j<=30;j++){
            frameWalk[c].x=(j-1)*221;
            frameWalk[c].y=first;
            frameWalk[c].w=221;
            frameWalk[c].h=224;
            c++;
        }
        first+=224;
    }
}


void Boss :: renderBoss ( SDL_Renderer * screen ){
    
    SDL_Rect* currentFrame = &frameWalk[frameOfWalk/5];
    render(mPosX,mPosY,screen,currentFrame);
    frameProcessing();
}   

void Boss::frameProcessing(){
    frameOfWalk++;
    if (frameOfWalk >= 120*5 ){
        frameOfWalk = 5;
    }

}

bool Boss:: loadBoss(SDL_Renderer * screen ){
    if (loadFromFile("img/Boss/Walk2.png",screen)== false ){
        std::cout<<"Could not load Boss "<<std::endl;
    }
    return true ;

}




