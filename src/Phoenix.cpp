#include"needed.h"
#include"Phoenix.h"

#define TIME_TO_NEXT_FRAME_PHOENIX 14
#define FRAMES_PHOENIX 12
  
Phoenix :: Phoenix(){
    mPosX = 0 ;
    mPosY = DEFAULT_PHOENIX_Y; 
    setSpritePhoenix();
    framePhoenix = 10; 

}


Phoenix :: ~Phoenix(){
    free();
}

bool Phoenix :: loadPhoenix (SDL_Renderer * screen ){
     if ( loadFromFile("img/phoenix/phoenix.png",screen) == false ){
        std::cout<<"Could not load Phoenix "<<SDL_GetError()<<std::endl;
        return false;
    }
    return true;
}

void Phoenix :: setSpritePhoenix (){
    for(int i=1;i<= 12;i++){
        spriteOfPhoenix[i].x= (i-1)* 228 ;
        spriteOfPhoenix[i].y=0;
        spriteOfPhoenix[i].w=228;
        spriteOfPhoenix[i].h=189;
    }
}

void Phoenix ::  renderPhoenix ( SDL_Renderer  * screen ){
    SDL_Rect  currentPhoenix = spriteOfPhoenix [ framePhoenix / TIME_TO_NEXT_FRAME_PHOENIX   ];
    framePhoenix ++ ;
    render(mPosX , mPosY , screen , &currentPhoenix );
    if(framePhoenix >= FRAMES_PHOENIX * TIME_TO_NEXT_FRAME_PHOENIX){
        framePhoenix= TIME_TO_NEXT_FRAME_PHOENIX;
    }  

}

int Phoenix  :: getPhoenixX (){
     return mPosX ; 
}