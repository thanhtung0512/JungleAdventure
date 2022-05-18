#include"needed.h"
#include "Character.h"

#define FRAME_OF_RUNNING 8 
#define FRAME_OF_IDLE 8 
#define FRAME_OF_ATTACK 18 
#define FRAME_OF_ATTACK_2 28
#define FRAME_JUMP_UP 7
#define FRAME_JUMP_DOWN 13
#define FRAME_DEAD 13

#define MAX_HEIGHT_JUMP  DEFAULT_MAIN_CHARACTER_Y  - 135

#define TIME_TO_NEXT_FRAME_RUNNING_CHARACTER 6 
#define TIME_TO_NEXT_FRAME_IDLE 15 
#define TIME_TO_NEXT_FRAME_ATTACK 4
#define TIME_TO_NEXT_FRAME_ATTACK_2 3
#define TIME_TO_NEXT_FRAME_JUMP_UP 7 
#define TIME_TO_NEXT_FRAME_JUMP_DOWN 13 
#define TIME_TO_NEXT_FRAME_DEAD 13

#define LEFT_LIMIT_X 0 
const double jumpVelocity  = 2.5; 
const int fontSize = 12 ;

Character :: Character ( ){
       
}

Character :: Character(SDL_Renderer * screen ){
    loadFromFile("img/mainChar/allBehaFinish.png",screen);
    numsKilledEnemy=0;
    isVisible = true ; 
    mPosX =SCREEN_WIDTH / 2 -  140 ;
    mPosY=DEFAULT_MAIN_CHARACTER_Y ;
    mVelCharX =0;
    mVelCharY =0; 
    frame = 0 ; // current frame 
    status = RUN_RIGHT;
    setClipsRunRight(MAIN_CHAR_FRAME_RUN);
    setClipsRunLeft(MAIN_CHAR_FRAME_RUN);
    setIdleClip();
    setAttackClip();
    setAttackClip2();
    setJumpUpClips();
    setJumpDownClips();
    setDeadClips();
    setAllClipsForInvisibleMode(MAIN_CHAR_FRAME_RUN);
    frameMainRunning = 10;
    frameIdle = 15; 
    frameIdleLeft = 15;
    frameAttack = 6; frameAttack2 = 6 ; frameJumpUp = 14; frameJumpDown = 26 ; frameDead = 13 ;
    runningSound= NULL;
}

Character :: ~Character (){
    free();
}

void Character :: handleInputAction(SDL_Event &e , SDL_Renderer *screen,Mix_Chunk * sword ,Mix_Chunk * sword_2  ){
    if ( e.type == SDL_KEYDOWN  && e.key.repeat == 0 ){
        switch ( e.key.keysym.sym  ){
            case SDLK_RIGHT :{
                if ( status != JUMP_DOWN && status != JUMP_UP && status !=DEAD_CHARACTER  ){
                  
                    status = RUN_RIGHT ;
                }
                mVelCharX  += CHARACTER_VEL ;
                break;
            }

            case SDLK_LEFT :{
                if (status != JUMP_DOWN && status != JUMP_UP && status !=DEAD_CHARACTER )
                {
                    
                    status =RUN_LEFT ;
                }
                mVelCharX -=CHARACTER_VEL;
                break;
            }


            case SDLK_t:{
                frameAttack = 8; 
                if ( status != JUMP_DOWN  && status !=JUMP_UP && status != DEAD_CHARACTER )
                {
                    Mix_PlayChannel(-1,sword,-1);  
                    status = ATTACK;
                }
                break;
            }

            case SDLK_y :{
                if ( status != JUMP_DOWN  && status !=JUMP_UP && status !=DEAD_CHARACTER )
                {
                    Mix_PlayChannel(-1,sword_2,-1);
                    status = ATTACK_2 ;   
                }
                frameAttack2 = 6 ;
                break;
            
            }

            case SDLK_UP:{
                frameJumpUp = 7 ;
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
                if (status != JUMP_DOWN && status != JUMP_UP  )
                {   
                    Mix_HaltChannel(-1);
                    status = RUN_RIGHT;
                }
                mVelCharX  -= CHARACTER_VEL ;
                break;
            }
            case SDLK_LEFT :{
                Mix_HaltChannel(-1);
                playRunningSound();
                if (status != JUMP_DOWN && status != JUMP_UP  )
                status = RUN_RIGHT ;
                mVelCharX +=CHARACTER_VEL;
                break;
            }

            case SDLK_t:{
                Mix_HaltChannel(-1);
                playRunningSound();
                if (status != JUMP_DOWN && status != JUMP_UP  )
                status = RUN_RIGHT ;
                break;
            }

            case SDLK_y :{
                
                Mix_HaltChannel(-1);
                playRunningSound();
                if (status != JUMP_DOWN && status != JUMP_UP  )
                status = RUN_RIGHT;
                break;
            }
            case SDLK_UP:{
                Mix_Pause(-1);
                status = JUMP_DOWN ;
                break; 
            }
        }
    }

}

void Character :: movingCharacter (){
    mPosX += mVelCharX;
    if (mPosX< LEFT_LIMIT_X  || (mPosX + frameWidth >SCREEN_WIDTH )){
        mPosX -= mVelCharX;
    }
 
 // jump processing 
    if ( status ==  JUMP_UP ){
        if (mPosY > MAX_HEIGHT_JUMP  ){
                mPosY -= jumpVelocity ;
        }
        if ( mPosY == MAX_HEIGHT_JUMP ){
            status = JUMP_DOWN;
        } 
    }
    if ( status == JUMP_DOWN )  {
        if(mPosY < DEFAULT_MAIN_CHARACTER_Y ){
            mPosY += jumpVelocity ;
        }
        if ( mPosY == DEFAULT_MAIN_CHARACTER_Y ){
            status = RUN_RIGHT ;
            playRunningSound();
        }
    }
}

void Character :: showCharacter (SDL_Renderer * screen  ){

   
    SDL_Rect * currentFrame;

    if ( isVisible ){
        if ( status == IDLE || status == IDLE_LEFT){
            frameIdle ++;
            currentFrame = & frame_idle[frameIdle/TIME_TO_NEXT_FRAME_IDLE];
            render(mPosX , mPosY, screen , currentFrame );
            if ( frameIdle >= TIME_TO_NEXT_FRAME_IDLE*8 ){
                frameIdle = TIME_TO_NEXT_FRAME_IDLE;
            }
        }
        if ( status == RUN_RIGHT || status == RUN_LEFT){
            currentFrame = & frame_clips_run_right[frameMainRunning/TIME_TO_NEXT_FRAME_RUNNING_CHARACTER ];
            render(mPosX  , mPosY, screen , currentFrame );
        }
        if ( status == ATTACK){
            currentFrame = & frame_attack[frameAttack/TIME_TO_NEXT_FRAME_ATTACK];
            render(mPosX , mPosY, screen , currentFrame ); 
        }
        if ( status ==ATTACK_2 ){ 
            currentFrame = & frame_attack_2[frameAttack2 /TIME_TO_NEXT_FRAME_ATTACK_2 ];
            render(mPosX,mPosY ,screen,currentFrame);
        }
        if(status == JUMP_UP ){
            currentFrame = &frame_jump_up[ frameJumpUp/ TIME_TO_NEXT_FRAME_JUMP_UP ];
            render(mPosX , mPosY , screen, currentFrame);
        }
        if ( status == JUMP_DOWN ){
            currentFrame =  & frame_jump_down [frameJumpDown/ TIME_TO_NEXT_FRAME_JUMP_DOWN];
            render(mPosX , mPosY , screen ,currentFrame );
        }
        
        if (status == DEAD_CHARACTER){
            currentFrame=  & frame_dead [frameDead / TIME_TO_NEXT_FRAME_DEAD] ;
            render(mPosX , mPosY ,screen ,currentFrame);
        }
    }
    else {
        if ( status == IDLE || status == IDLE_LEFT){
            frameIdle ++;
            currentFrame = & i_frame_idle[frameIdle/TIME_TO_NEXT_FRAME_IDLE];
            render(mPosX , mPosY, screen , currentFrame );
            if ( frameIdle >= TIME_TO_NEXT_FRAME_IDLE*8 ){
                frameIdle = TIME_TO_NEXT_FRAME_IDLE;
            }
        }
        if ( status == RUN_RIGHT || status == RUN_LEFT){
            currentFrame = & i_frame_clips_run_right[frameMainRunning/TIME_TO_NEXT_FRAME_RUNNING_CHARACTER ];
            render(mPosX  , mPosY, screen , currentFrame );
        }
        if ( status == ATTACK){
            currentFrame = & i_frame_attack[frameAttack/TIME_TO_NEXT_FRAME_ATTACK];
            render(mPosX , mPosY, screen , currentFrame ); 
        }
        if ( status ==ATTACK_2 ){ 
            currentFrame = & i_frame_attack_2[frameAttack2 /TIME_TO_NEXT_FRAME_ATTACK_2 ];
            render(mPosX,mPosY ,screen,currentFrame);
        }
        if(status == JUMP_UP ){
            currentFrame = &i_frame_jump_up[ frameJumpUp/ TIME_TO_NEXT_FRAME_JUMP_UP ];
            render(mPosX , mPosY , screen, currentFrame);
        }
        if ( status == JUMP_DOWN ){
            currentFrame =  & i_frame_jump_down [frameJumpDown/ TIME_TO_NEXT_FRAME_JUMP_DOWN];
            render(mPosX , mPosY , screen ,currentFrame );
        }
        
        if (status == DEAD_CHARACTER){
            currentFrame=  & i_frame_dead [frameDead / TIME_TO_NEXT_FRAME_DEAD] ;
            render(mPosX , mPosY ,screen ,currentFrame);
        }
    }
    frameProcessing();
}

void Character :: setClipsRunRight (int frameNumbers ){
    for(int i=1;i<= frameNumbers ;i++){
        frame_clips_run_right [i].x = (i-1)* 224  ;
        frame_clips_run_right [i].y = 8*112 ;
        frame_clips_run_right [i].w = 224;
        frame_clips_run_right [i].h = 112;
        
    }
}

void Character ::  setClipsRunLeft(int frameNumbers){
    for(int i=1;i<= frameNumbers ;i++){
        frame_clips_run_left [i].x = (i-1)* 224  ;
        frame_clips_run_left [i].y = 7*112 ;
        frame_clips_run_left [i].w = 224;
        frame_clips_run_left [i].h = 112;
        
    }
}

int  Character :: getStatus (){
    return status ;
}

void Character :: setIdleClip (){
    for(int i=1 ;i<=IDLE_CLIPS ;i++){
        frame_idle [i].x=(i-1) * 224  ;
        frame_idle [i].y=3*112;
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
    
    for(int i=1 ;i<=FRAME_OF_ATTACK_2 ;i++){
        frame_attack_2[i].x = (i-1)* 224;
        frame_attack_2[i].y = 112;
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
    for(int i=1 ;i<=FRAME_JUMP_UP ;i++){
        frame_jump_up[i].x=(i-1)*224 ;
        frame_jump_up[i].y= 6*112 ;
        frame_jump_up[i].w = 224 ;
        frame_jump_up[i].h = 112 ;
    }
}

void Character :: setJumpDownClips(){
    for(int i=1;i<=FRAME_JUMP_DOWN;i++){
        frame_jump_down[i].x = (i-1)*224 ;
        frame_jump_down[i].y = 5*112 ;
        frame_jump_down[i].w = 224 ; 
        frame_jump_down[i].h = 112;

    }
}

void Character :: getHitFromFireball ( Fireball* gFireball ){
    if( gFireball ->getXPos ()+FIREBALL_WIDTH  >= mPosX+ 80 && gFireball ->getXPos ()+FIREBALL_WIDTH <= mPosX + MAIN_CHAR_WIDTH  && status !=DEAD_CHARACTER && isVisible == true ){
        if (DEFAULT_PHOENIX_Y + 90 >= mPosY && DEFAULT_PHOENIX_Y + 90 <= mPosY + MAIN_CHAR_HEIGHT ){
            status = DEAD_CHARACTER;
            gFireball->setXPos(SCREEN_WIDTH * 2  );
        }
    }
        
}

void Character :: setDeadClips (){
    for(int i=1 ;i<=FRAME_DEAD;i++){
        frame_dead[i].x=(i-1) * 224;  
        frame_dead[i].y= 2*112; 
        frame_dead[i].w= 224 ;
        frame_dead[i].h= 112;

    }
}

void Character :: frameProcessing (){
        frameMainRunning ++;
        frameIdle ++; 
        frameIdleLeft ++;
        frameAttack++;
        frameAttack2 ++;
        frameJumpUp ++; 
        frameJumpDown ++ ;

        if ( frameMainRunning  >= FRAME_OF_RUNNING * TIME_TO_NEXT_FRAME_RUNNING_CHARACTER  ){
            frameMainRunning = TIME_TO_NEXT_FRAME_RUNNING_CHARACTER ;
        } 
        if ( frameIdle >= TIME_TO_NEXT_FRAME_IDLE * FRAME_OF_IDLE){
            frameIdle = TIME_TO_NEXT_FRAME_IDLE;
        }
        if  ( frameAttack >= FRAME_OF_ATTACK * TIME_TO_NEXT_FRAME_ATTACK ){
             frameAttack  =TIME_TO_NEXT_FRAME_ATTACK ;
         }
        if ( frameAttack2 >= FRAME_OF_ATTACK_2  *TIME_TO_NEXT_FRAME_ATTACK_2  ){
            frameAttack2 = TIME_TO_NEXT_FRAME_ATTACK_2 ;
        }
       
        if (frameJumpUp >= FRAME_JUMP_UP* TIME_TO_NEXT_FRAME_JUMP_UP){
            frameJumpUp = 2 * TIME_TO_NEXT_FRAME_JUMP_UP ;
        }
        if (frameJumpDown >= FRAME_JUMP_DOWN* TIME_TO_NEXT_FRAME_JUMP_DOWN  ){
            frameJumpDown = 2 * TIME_TO_NEXT_FRAME_JUMP_DOWN ; 
        }
        if (frameDead <= FRAME_DEAD * TIME_TO_NEXT_FRAME_DEAD  ){
            frameDead ++ ;
        }
}

int Character :: getFrameAttack(){
    return frameAttack ;
}

 void Character ::   setStatus (int statusS ){
     status = statusS ;
 }

 void Character ::  setCharacterPosX(int posX){
     mPosX = posX ;
 }

 int Character ::  getFrameAttack2 (){
     return frameAttack2; 
 }

 void Character :: resetCharacter(){
    numsKilledEnemy=0;
    isVisible = true ;
    mPosX =SCREEN_WIDTH / 2 -  140 ;
    mPosY=DEFAULT_MAIN_CHARACTER_Y ;
    mVelCharX =0;
    mVelCharY =0; 
    frame = 0 ; // current frame 
    status = RUN_RIGHT;
    frameMainRunning = 10;
    frameIdle = 15; 
    frameIdleLeft = 15;
    frameAttack = 6; frameAttack2 = 6 ; frameJumpUp = 14; frameJumpDown = 26 ; frameDead = 13 ;

 }

 void Character ::  manageCharacter ( SDL_Renderer * screen ,Fireball *gFireball , int * point , int* recentPointVisible  ){
     
     if ( (numsKilledEnemy % 10 == 0 || numsKilledEnemy % 10 == 1 )  && numsKilledEnemy >= 2   ){
         isVisible = false   ;
         * recentPointVisible = *point; 
     }
     if ( * point == * recentPointVisible + 30  ){
         isVisible = true ;
     }
     if ( !isVisible   ){
        int countDownTime =  * recentPointVisible + 30 - * point;
        visibleNoti.showTextt(SCREEN_WIDTH - 300 , SCREEN_HEIGHT - 40  ,"Time invisible : ",screen,fontSize);
        countDount.showText(SCREEN_WIDTH - 50 , SCREEN_HEIGHT - 40 , &countDownTime, screen ,fontSize );
     }
     else {
        gScore.showText(SCREEN_WIDTH - 50 , SCREEN_HEIGHT - 40,point,screen,fontSize);
        pointText.showTextt(SCREEN_WIDTH - 300 , SCREEN_HEIGHT - 40  ,"Your score is ",screen,fontSize);
     }
     getHitFromFireball (gFireball);
     movingCharacter();
     showCharacter(screen);
 }

 void Character ::  playRunningSound (){
     Mix_PlayChannel(0,runningSound,-1);
 }  

void  Character :: loadRunningSound (){
    runningSound  = Mix_LoadWAV("sound/running.mp3");
    if ( runningSound  == NULL) {
        std::cout<<"Could not load chunk "<<SDL_GetError()<<std::endl;
    }
}

void Character ::  pauseRunningSound(){
    Mix_HaltChannel(-1);
}

bool Character :: getIsVisible (){
    return isVisible ;
}

void Character ::  setIsVisible ( bool isVisiblee  ){
    isVisible = isVisiblee ; 
}

int Character ::  getNumsKilledEnemy (){
    return numsKilledEnemy; 
}
void Character ::  increaseNumsKilledEnemy (){
    numsKilledEnemy ++; 
}

void Character ::  setAllClipsForInvisibleMode (int frameNumbers ){
    //1 . run right 
    for(int i=1;i<= frameNumbers ;i++){
        i_frame_clips_run_right [i].x = (i-1)* 224  ;
        i_frame_clips_run_right [i].y = (8+9)*112 ;
        i_frame_clips_run_right [i].w = 224;
        i_frame_clips_run_right [i].h = 112;
    }

    //2 . run left 
    for(int i=1;i<= frameNumbers ;i++){
        i_frame_clips_run_left [i].x = (i-1)* 224  ;
        i_frame_clips_run_left [i].y = (7+9)*112 ;
        i_frame_clips_run_left [i].w = 224;
        i_frame_clips_run_left [i].h = 112;
    }

    //3.idle  
    for(int i=1 ;i<=IDLE_CLIPS ;i++){
        i_frame_idle [i].x=(i-1) * 224  ;
        i_frame_idle [i].y=(3+9)*112;
        i_frame_idle [i].w=224;
        i_frame_idle [i].h=112; 
    }

    //4. attack 
    for(int i=1 ;i <= FRAME_OF_ATTACK;i++){
        i_frame_attack[i].x=(i-1)* 224 ;
        i_frame_attack[i].y=(0+9) * 112;
        i_frame_attack[i].w=224;
        i_frame_attack[i].h=112;
    }

    //5. attack2
    for(int i=1 ;i<=FRAME_OF_ATTACK_2 ;i++){
        i_frame_attack_2[i].x = (i-1)* 224;
        i_frame_attack_2[i].y = (1+9)*112;
        i_frame_attack_2[i].w = 224 ;
        i_frame_attack_2[i].h = 112;
    }

    //6. jump up  
    for(int i=1 ;i<=FRAME_JUMP_UP ;i++){
        i_frame_jump_up[i].x=(i-1)*224 ;
        i_frame_jump_up[i].y= (6+9)*112 ;
        i_frame_jump_up[i].w = 224 ;
        i_frame_jump_up[i].h = 112 ;
    }

    //7. jump down 
    for(int i=1;i<=FRAME_JUMP_DOWN;i++){
        i_frame_jump_down[i].x = (i-1)*224 ;
        i_frame_jump_down[i].y = (5+9)*112 ;
        i_frame_jump_down[i].w = 224 ; 
        i_frame_jump_down[i].h = 112;
    }

    //8. dead 
    for(int i=1 ;i<=FRAME_DEAD;i++){
        i_frame_dead[i].x=(i-1) * 224;  
        i_frame_dead[i].y= (2+9)*112; 
        i_frame_dead[i].w= 224 ;
        i_frame_dead[i].h= 112;
    }
}   