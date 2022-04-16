#include"needed.h"
#include"Boss.h"
#define TIME_TO_NEXT_FRAME_BOSS 3 
Boss::Boss(){
    setClipsWalk();
    mPosX = SCREEN_WIDTH/2- 80 ;
    mPosY = 530  ;
    frameOfWalk = 120 ;
    
}

void Boss ::  resetBoss(){
    mPosX = SCREEN_WIDTH/2- 80 ;
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
        if (i==4 ){
            for (int j=1;j<=4;j++){
            frameWalk[c].x=(j-1)*212;
            frameWalk[c].y=first;
            frameWalk[c].w=212;
            frameWalk[c].h=209;
            c++;
        }

        }
        else 
        {
        for (int j=1;j<=5;j++){
            frameWalk[c].x=(j-1)*212;
            frameWalk[c].y=first;
            frameWalk[c].w=212;
            frameWalk[c].h=209;
            c++;
        }
        }
        first+=209;
    }
}


void Boss :: renderBoss ( SDL_Renderer * screen ){
    
    SDL_Rect* currentFrame = &frameWalk[frameOfWalk/TIME_TO_NEXT_FRAME_BOSS];
    render(mPosX,mPosY,screen,currentFrame);
    frameProcessing();
}   

void Boss::frameProcessing(){
    frameOfWalk++;
    if (frameOfWalk >= 19 * TIME_TO_NEXT_FRAME_BOSS  ){
        frameOfWalk = TIME_TO_NEXT_FRAME_BOSS ;
    }

}

bool Boss:: loadBoss(SDL_Renderer * screen ){
    if (loadFromFile("img/Boss/Walk3.png",screen)== false ){
        std::cout<<"Could not load Boss "<<std::endl;
    }
    return true ;

}




