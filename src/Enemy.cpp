#include"Enemy.h"
#include"needed.h"

#include"Character.h"

Enemy ::Enemy (){
    status = ALIVE; 
    mPosX = SCREEN_WIDTH - 130;
    mPosY = DEFAULT_MAIN_CHARACTER_Y+70;
    mVelX =0 ;
    setFrameEnemiesRun();
    setFrameDead();
   
}

Enemy :: ~Enemy(){

}

void Enemy :: handleHitFromCharacter(Character* gTestCharacter , int & frameAttack  ){
    if (gTestCharacter->getStatus() == ATTACK && frameAttack/ 6 >=12 && frameAttack/6 <=15   ){
        if ( gTestCharacter->getCharacterPosX()+ 216  >= mPosX + 5 && gTestCharacter->getCharacterPosX() <= mPosX + 52){
            status = DEAD ;
        }
    }
    
}


void Enemy :: setFrameEnemiesRun (){
    for (int i =1 ;i<=21; i++){
        frame_running[i].x= (i-1)* 80 ; 
        frame_running[i].y= 0;
        frame_running[i].w= 80; 
        frame_running[i].h= 52; 

    }
}


void Enemy :: setFrameDead (){
    for(int i=1 ;i<= 30;i++){
        frame_dead[i].x=(i-1)* 80 ; 
        frame_dead[i].y=  0 ;
        frame_dead[i].w= 80;
        frame_dead[i].h= 52 ;

    }
}

void Enemy :: ShowEnemie (SDL_Renderer* screen , int frameWalkingEnemie , int frameEnemyDead){
    if ( status == ALIVE ){
        if (loadFromFile("img/Enemie/moving.png",screen)== false ){
            std::cout<<"could not load enemy walkiing "<<std::endl;
        }
    }
    else if (status == DEAD) {
        if (loadFromFile("img/Enemie/dead.png",screen)== false ){
            std::cout<<"could not load enemy walkiing "<<std::endl;
        }
    }

    SDL_Rect* currentFrame;

    if ( status== ALIVE ){
        currentFrame = &frame_running[frameWalkingEnemie / 10];
        render(mPosX,mPosY,screen , currentFrame);
    }
    if (status == DEAD ){
        currentFrame = & frame_dead[frameEnemyDead / 20 ];
        render(mPosX , mPosY , screen , currentFrame);
    }

}

void Enemy ::autoMove (int & frameEnemyDead ){
    mPosX -= enemyVelocity;
    if ( mPosX <= -500  ){
        mPosX = SCREEN_WIDTH  + 100;
        status = ALIVE;
        frameEnemyDead = 0 ;
    } 
}

