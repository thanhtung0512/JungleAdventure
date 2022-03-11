#include"needed.h"
#include "Character.h"

#define MAX_HEIGHT_JUMP DEFAULT_MAIN_CHARACTER_Y  - 130
const int jumpVelocity  = 1.95; 

Character ::Character (){
    mPosX =SCREEN_WIDTH / 2 -  140 ;
    mPosY=DEFAULT_MAIN_CHARACTER_Y ;
    mVelCharX =0;
    mVelCharY =0; 
    frame = 0 ; // current frame 
    status = RUN_RIGHT;
    setClipsRun(MAIN_CHAR_FRAME_RUN);
    setIdleClip();
    setAttackClip();
    setAttackClip2();
    setJumpUpClips();
    setJumpDownClips();
    setDeadClips();

    // frameMainRunning = 10;
    // frameIdle = 15; 
    // frameIdleLeft = 15;

    
}

Character :: ~Character (){

}

void Character :: handleInputAction(SDL_Event &e , SDL_Renderer *screen, Mix_Chunk * chunk,Mix_Chunk * sword ,Mix_Chunk * sword_2 ,int& frameAttack2 , int &frameAttack , int & frameJump ){
    if ( e.type == SDL_KEYDOWN  && e.key.repeat == 0 ){
        switch ( e.key.keysym.sym  ){
            case SDLK_RIGHT :{
                Mix_PlayChannel(-1,chunk ,0);
                if (status != JUMP_DOWN && status != JUMP_UP  ){
                status = RUN_RIGHT ;
                }
                mVelCharX  += CHARACTER_VEL ;
                break;
            }
            case SDLK_LEFT :{
                Mix_PlayChannel(-1,chunk ,0);
                if (status != JUMP_DOWN && status != JUMP_UP)
                status =RUN_LEFT ;
                mVelCharX -=CHARACTER_VEL;
                break;
            }
            case SDLK_t:{
                Mix_PlayChannel(-1,sword,-1);  
                frameAttack = 8; 
                status = ATTACK;
                break;
            }
            case SDLK_y :{
                Mix_PlayChannel(-1,sword_2,-1);
                status = ATTACK_2 ;
                frameAttack2 = 6 ;
                break;
            
            }
            case SDLK_UP:{
                frameJump = 7 ;
                mVelCharY -= 50; 
                if ( mPosY == DEFAULT_MAIN_CHARACTER_Y )
                status = JUMP_UP;
                break;
            }
            
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat ==0  ){
        switch ( e.key.keysym.sym ){
            case SDLK_RIGHT :{
                Mix_HaltChannel(-1);
                if (status != JUMP_DOWN && status != JUMP_UP  )
                status = RUN_RIGHT;
                mVelCharX  -= CHARACTER_VEL ;
                break;
            }
            case SDLK_LEFT :{
                Mix_HaltChannel(-1);
                if (status != JUMP_DOWN && status != JUMP_UP  )
                status = IDLE_LEFT ;
                mVelCharX +=CHARACTER_VEL;
                break;
            }
            case SDLK_t:{
                Mix_HaltChannel(-1);
                if (status != JUMP_DOWN && status != JUMP_UP  )
                status = IDLE ;
                break;
            }
            case SDLK_y :{
                frameAttack2 = 6 ;
                Mix_HaltChannel(-1);
                if (status != JUMP_DOWN && status != JUMP_UP  )
                status = IDLE;
                break;
            }
            case SDLK_UP:{
                status = JUMP_DOWN ;
                break; 
            }
            
        }
    }

}

void Character :: movingCharacter (){
    mPosX += mVelCharX;
    if (mPosX<0 || (mPosX + frameWidth >SCREEN_WIDTH )){
        mPosX -= mVelCharX;
    }

    if ( status ==  JUMP_UP ){
        if (mPosY > MAX_HEIGHT_JUMP  ){
                mPosY -= 1.95 ;
        }
        if ( mPosY == MAX_HEIGHT_JUMP ){
            status = JUMP_DOWN;
        } 
    }
    if ( status == JUMP_DOWN )  {
        if(mPosY < DEFAULT_MAIN_CHARACTER_Y ){
            mPosY += 1.95;
        }
        if ( mPosY == DEFAULT_MAIN_CHARACTER_Y ){
            status = RUN_RIGHT ;
        }
    }
}

void Character :: showCharacter (SDL_Renderer * screen, int frame , int frameIdle ,int frameIdleLeft  ,int& frameAttack , int& frameAttack2  , int frameJumpUp , int frameJumpDown, int frameDead  ){

    if ( status == RUN_RIGHT){
       if ( loadFromFile("img/mainChar/toright.png",screen) == false ){
           std::cout<<"could not load right animation "<<std::endl;
       }
    }
    else if ( status == RUN_LEFT ){
       if ( loadFromFile("img/mainChar/toleft.png",screen) == false ){
           std::cout<<"coudl not load left animation "<<std::endl;
       }
    }
    else if ( status == IDLE){
        if ( loadFromFile("img/mainChar/idle.png",screen) ==false ){
            std::cout<<"coudl not load idle right  animation "<<std::endl;
        }
    }
    else if (status == IDLE_LEFT){
        if ( loadFromFile("img/mainChar/idlemirror.png",screen) ==false ){
            std::cout<<"coudl not load idle left animation "<<std::endl;
        }
    }
    else if ( status == ATTACK){
        if ( loadFromFile("img/mainChar/attack.png",screen) ==false ){
            std::cout<<"coudl not load attack  animation "<<std::endl;
        }
    }
    else if ( status == ATTACK_2 ){
        if ( loadFromFile("img/mainChar/attack2.png",screen) ==false ){
            std::cout<<"coudl not load attack2  animation "<<std::endl;
        }
    }
    else  if ( status == JUMP_UP){
        if ( loadFromFile("img/mainChar/jumpUp.png",screen) == false ){
            std::cout<<"could not load jump png "<<SDL_GetError()<<std::endl;
        }
    }
    else if ( status == JUMP_DOWN ){
        if ( loadFromFile("img/mainChar/jumpDown.png",screen) == false ){
            std::cout<<"could not load jump Down "<<SDL_GetError()<<std::endl;
        }
    }
    else if ( status == DEAD_CHARACTER){
        if ( loadFromFile("img/mainChar/dead.png",screen) == false ){
            std::cout<<"could not load dead "<<SDL_GetError()<<std::endl;
        }
    }
    SDL_Rect * currentFrame;

    if ( status == IDLE || status == IDLE_LEFT){
         frameIdle ++;
         currentFrame = & frame_idle[frameIdle/15];
         render(mPosX , mPosY, screen , currentFrame );
         if ( frameIdle >= 15*8 ){
             frameIdle = 15;
         }
    }
    if ( status == RUN_RIGHT || status == RUN_LEFT){
        currentFrame = & frame_clips[frame/10];
        render(mPosX  , mPosY, screen , currentFrame );
    }
    if ( status == ATTACK){
        // de y cai frame clip =)))) aaaaaaaaaaaaaaaaaaaaaaaaaaaaa cay vaiii
         currentFrame = & frame_attack[frameAttack/6];
         render(mPosX , mPosY, screen , currentFrame ); 
    }
    if ( status ==ATTACK_2 ){ 
        currentFrame = & frame_attack_2[frameAttack2 /6];
        render(mPosX,mPosY ,screen,currentFrame);
    }
    if(status == JUMP_UP ){
        currentFrame = &frame_jump_up[ frameJumpUp/ 7 ];
        render(mPosX , mPosY , screen, currentFrame);
    }
    if ( status == JUMP_DOWN ){
        currentFrame =  & frame_jump_down [frameJumpDown/ 13];
        render(mPosX , mPosY , screen ,currentFrame );
    }
    
    if (status == DEAD_CHARACTER){
        currentFrame=  & frame_dead [frameDead / 13] ;
        render(mPosX , mPosY ,screen ,currentFrame);
    }

}

void Character :: setClipsRun (int frameNumbers ){
    for(int i=1;i<= frameNumbers ;i++){
        frame_clips [i].x = (i-1)* 224  ;
        frame_clips [i].y = 0;
        frame_clips [i].w = 224;
        frame_clips [i].h = 112;
        
    }
}

int  Character :: getStatus (){
    return status ;
}

void Character :: setIdleClip (){
    
    for(int i=1 ;i<=IDLE_CLIPS ;i++){
        frame_idle [i].x=(i-1) * 224  ;
        frame_idle [i].y=0;
        frame_idle [i].w=224;
        frame_idle [i].h=112;
        
    }
}


void Character :: setAttackClip (){
    for(int i=1 ;i <= 18;i++){
        frame_attack[i].x=(i-1)* 224 ;
        frame_attack[i].y=0;
        frame_attack[i].w=224;
        frame_attack[i].h=112;
    }

}

void Character :: setAttackClip2(){
    for(int i=1 ;i<=28 ;i++){
        frame_attack_2[i].x = (i-1)* 224;
        frame_attack_2[i].y = 0;
        frame_attack_2[i].w = 224 ;
        frame_attack_2[i].h = 112;
    }
}

int Character :: getCharacterPosX (){
    return mPosX ;
}

int  Character ::getCharacterPosY(){
    return mPosY;
}

void Character ::  setJumpUpClips (){
    for(int i=1 ;i<=7 ;i++){
        frame_jump_up[i].x=(i-1)*224 ;
        frame_jump_up[i].y= 0 ;
        frame_jump_up[i].w = 224 ;
        frame_jump_up[i].h = 112 ;
    }
}

void Character :: setJumpDownClips(){
    for(int i=1;i<=13;i++){
        frame_jump_down[i].x = (i-1)*224 ;
        frame_jump_down[i].y = 0 ;
        frame_jump_down[i].w = 224 ; 
        frame_jump_down[i].h = 112;

    }
}

void Character :: getHitFromFireball (Fireball* gFireball ){
    if( gFireball ->getXPos ()+FIREBALL_WIDTH  >= mPosX+ 80 && gFireball ->getXPos ()+FIREBALL_WIDTH <= mPosX + MAIN_CHAR_WIDTH ){
        if (DEFAULT_PHOENIX_Y + 90 >= mPosY && DEFAULT_PHOENIX_Y + 90 <= mPosY + MAIN_CHAR_HEIGHT ){
            status = DEAD_CHARACTER;
        }
    }
        
    
}

void Character :: setDeadClips (){
    for(int i=1 ;i<=13;i++){
        frame_dead[i].x=(i-1) * 224;  
        frame_dead[i].y= 0; 
        frame_dead[i].w= 224 ;
        frame_dead[i].h= 112;

    }
}