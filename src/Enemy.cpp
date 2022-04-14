#include"Enemy.h"
#include"needed.h"

#include"Character.h"

#define TIME_TO_NEXT_FRAME_WALKING 3 
#define FRAME_WALKING_ENEMY 21 
#define TIME_TO_NEXT_FRAME_DEAD_ENEMY 5 
#define ENEMY_DEAD_FRAME 30 



Enemy ::  Enemy (  ){
    status = ALIVE;   
    mVelX =0 ;
    frameEnemyDead = 20 ;
    frameWalkingEnemie =TIME_TO_NEXT_FRAME_WALKING  ;
    setFrameEnemiesRun();
    setFrameDead();
    mPosX = ENEMY_COORDINATION_X;
    mPosY = ENEMY_COORDINATION_Y;
}

Enemy :: ~Enemy(){
    free();
}

void Enemy :: handleHitFromCharacter(Character* gTestCharacter , int frameAttack ,int frameAttack2 ){
    if (  (gTestCharacter->getStatus() == ATTACK && frameAttack/ TIME_TO_NEXT_FRAME_ATTACK >=12 && frameAttack/TIME_TO_NEXT_FRAME_ATTACK <=15  ) || ( gTestCharacter->getStatus()==ATTACK_2 && frameAttack2 >= 5*TIME_TO_NEXT_FRAME_ATTACK_2 && frameAttack2 <= 18 * TIME_TO_NEXT_FRAME_ATTACK_2     ) ){
        if ( gTestCharacter->getCharacterPosX()+ 190  >= mPosX + 5 && gTestCharacter->getCharacterPosX() <= mPosX + 52){
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
        frame_dead[i].x=(i-1)* 80; 
        frame_dead[i].y=  0;
        frame_dead[i].w= 80;
        frame_dead[i].h= 52;

    }
}

void Enemy :: ShowEnemie (SDL_Renderer* screen ){
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
        currentFrame = &frame_running[frameWalkingEnemie / TIME_TO_NEXT_FRAME_WALKING ];
        render(mPosX,mPosY,screen , currentFrame);
    }
    if (status == DEAD ){
        currentFrame = & frame_dead[frameEnemyDead / TIME_TO_NEXT_FRAME_DEAD_ENEMY ];
        render(mPosX , mPosY , screen , currentFrame);
    }
    frameProcessing();
}

void Enemy ::autoMove ( ){
    mPosX -= enemyVelocity;
    if ( mPosX <= -100  ){
        mPosX = SCREEN_WIDTH  + rand () % ( 900 );
        status = ALIVE;
        frameEnemyDead = 20 ;
    } 
}

void Enemy::frameProcessing (){
     frameWalkingEnemie ++; 
        if ( frameWalkingEnemie >= FRAME_WALKING_ENEMY * TIME_TO_NEXT_FRAME_WALKING ){
            frameWalkingEnemie = TIME_TO_NEXT_FRAME_WALKING;
        }
        if  ( frameEnemyDead <=ENEMY_DEAD_FRAME  * TIME_TO_NEXT_FRAME_DEAD_ENEMY ){
            frameEnemyDead ++ ;
        }
}

void Enemy ::  getHitFromFireball(Fireball * gFireball){
    if( gFireball ->getXPos ()+ FIREBALL_WIDTH  >= mPosX && gFireball ->getXPos ()+FIREBALL_WIDTH <= mPosX + 80 && status == ALIVE ){
        status = DEAD ;
        gFireball->setXPos(SCREEN_WIDTH);
    }
}

void Enemy::  collisionWithPhoenix (Phoenix * gPhoenix ){
    if ( gPhoenix->getPhoenixX() + PHOENIX_FRAME_WIDTH == mPosX  ){
        status = DEAD;
    }
    
}

void Enemy :: checkCollision ( Phoenix  *gPhoenix , Fireball *gFireball, Character* gTestCharacter){
    getHitFromFireball(gFireball);
    collisionWithPhoenix(gPhoenix);
    collisionWithMainCharacter(gTestCharacter);
}

double Enemy :: getEnemyPosX (){
    return mPosX ;
}

void Enemy ::  collisionWithMainCharacter ( Character * gTestCharacter){
    if ( gTestCharacter->getCharacterPosX() + 160 >=  mPosX  && gTestCharacter->getCharacterPosX() + 190 <= mPosX + 80 && gTestCharacter->getStatus() != ATTACK && gTestCharacter->getStatus() != JUMP_DOWN  && gTestCharacter->getStatus()!= JUMP_UP  && status != DEAD ){
        gTestCharacter->setCharacterPosX( gTestCharacter->getCharacterPosX()- 10);
        gTestCharacter->setStatus(DEAD_CHARACTER);
    }
    if(gTestCharacter->getStatus()==JUMP_DOWN  && gTestCharacter->getCharacterPosY()+112 >= mPosY && gTestCharacter->getCharacterPosX() + 160 >=  mPosX  && gTestCharacter->getCharacterPosX() + 190 <= mPosX + 120 && status == ALIVE){
        gTestCharacter->setStatus(DEAD_CHARACTER );
    }
}

void Enemy :: setCoordinate (int X , int Y ){
    mPosX = X;
    mPosY = Y ;

}

void Enemy ::  setVel (double vel ){
    
}