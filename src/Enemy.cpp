#include"needed.h"
#include"Enemy.h"



#define TIME_TO_NEXT_FRAME_WALKING 3 
#define FRAME_WALKING_ENEMY 21 
#define TIME_TO_NEXT_FRAME_DEAD_ENEMY 10 
#define ENEMY_DEAD_FRAME 12



Enemy ::  Enemy (){
    first = 1; 
    status = ALIVE;   
    mVelX =0 ;
    frameEnemyDead = 22 * TIME_TO_NEXT_FRAME_DEAD_ENEMY ;
    frameWalkingEnemie =TIME_TO_NEXT_FRAME_WALKING  ;
    setFrameEnemiesRun();
    setFrameDead();
    mPosX = SCREEN_WIDTH +   rand() % (SCREEN_WIDTH+1);
    mPosY = ENEMY_COORDINATION_Y;
}

Enemy :: Enemy(SDL_Renderer * screen ){
    first = 1; 
    status = ALIVE;   
    mVelX =0 ;
    frameEnemyDead = 22 * TIME_TO_NEXT_FRAME_DEAD_ENEMY ;
    frameWalkingEnemie =TIME_TO_NEXT_FRAME_WALKING  ;
    setFrameEnemiesRun();
    setFrameDead();
    mPosX = SCREEN_WIDTH +   rand() % (SCREEN_WIDTH+1);
    mPosY = ENEMY_COORDINATION_Y;
    loadEnemy(screen);
    
}

void Enemy ::  resetEnemy(){
    first = 1; 
    status = ALIVE;   
    mVelX =0 ;
    frameEnemyDead = 22 * TIME_TO_NEXT_FRAME_DEAD_ENEMY ;
    frameWalkingEnemie =TIME_TO_NEXT_FRAME_WALKING  ;
    mPosX = SCREEN_WIDTH +   rand() % (SCREEN_WIDTH+1);
    mPosY = ENEMY_COORDINATION_Y;
}
void Enemy :: loadEnemy(SDL_Renderer * screen ){
    loadFromFile("img/Enemie/moving_3.png",screen);
}

Enemy :: ~Enemy(){
    free();
}

void Enemy :: handleHitFromCharacter(Character* gTestCharacter , int frameAttack ,int frameAttack2 ){
    if (  (gTestCharacter->getStatus() == ATTACK && frameAttack/ TIME_TO_NEXT_FRAME_ATTACK >=12 && frameAttack/TIME_TO_NEXT_FRAME_ATTACK <=15  ) || ( gTestCharacter->getStatus()==ATTACK_2 && frameAttack2 >= 5*TIME_TO_NEXT_FRAME_ATTACK_2 && frameAttack2 <= 19 * TIME_TO_NEXT_FRAME_ATTACK_2     ) ){
        if ( gTestCharacter->getCharacterPosX()+ 190  >= mPosX + 5 && gTestCharacter->getCharacterPosX() <= mPosX + 52){
            status = DEAD ;  
            if ( first == 1 ){
                first =0 ;
                gTestCharacter->increaseNumsKilledEnemy();
            }
        } 
    }
}


void Enemy :: setFrameEnemiesRun (){
    for (int i =1 ;i<=40; i++){
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
    SDL_Rect* currentFrame=NULL;
    if ( status== ALIVE ){
        currentFrame = &frame_running[frameWalkingEnemie / TIME_TO_NEXT_FRAME_WALKING ];
        render(mPosX,mPosY,screen , currentFrame);
    }
   else if (status == DEAD ){
        currentFrame = & frame_running[frameEnemyDead / TIME_TO_NEXT_FRAME_DEAD_ENEMY ];
        render(mPosX , mPosY , screen , currentFrame);
    }
    frameProcessing();
}

void Enemy ::autoMove ( ){
    mPosX -= enemyVelocity;
    if ( mPosX <= -100  ){
       resetEnemy();
    } 
}

void Enemy::frameProcessing (){
     frameWalkingEnemie ++; 
        if ( frameWalkingEnemie >= FRAME_WALKING_ENEMY * TIME_TO_NEXT_FRAME_WALKING ){
            frameWalkingEnemie = TIME_TO_NEXT_FRAME_WALKING;
        }
        if  (status ==DEAD &&  frameEnemyDead < (ENEMY_DEAD_FRAME + 22)  * TIME_TO_NEXT_FRAME_DEAD_ENEMY ){
            frameEnemyDead ++ ;
        }
        
}

void Enemy ::  getHitFromFireball(Fireball * gFireball){
    if( gFireball ->getXPos ()+ FIREBALL_WIDTH  >= mPosX && gFireball ->getXPos ()+FIREBALL_WIDTH <= mPosX + 80 && status == ALIVE && gFireball->getStatusDamage()==1  ){
        std:: cout << " Fireball vs Enemy "<<std::endl;
        status = DEAD ;
        gFireball->setXPos(SCREEN_WIDTH);
        gFireball->setStatusDamage(0);
    }
}

void Enemy::  collisionWithPhoenix (Phoenix * gPhoenix ){
    if ( gPhoenix->getPhoenixX() + PHOENIX_FRAME_WIDTH == mPosX   ){
        resetEnemy();
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
    if ( gTestCharacter->getCharacterPosX() + 160 >=  mPosX  && gTestCharacter->getCharacterPosX() + 190 <= mPosX + 80 && gTestCharacter->getStatus() != ATTACK && gTestCharacter->getStatus() != JUMP_DOWN  && gTestCharacter->getStatus()!= JUMP_UP  && status ==ALIVE  && gTestCharacter->getStatus()!=DEAD_CHARACTER  && gTestCharacter-> getIsVisible()== true ){
        std::cout<<"Collision enemy "<<std::endl;
        gTestCharacter->setCharacterPosX( gTestCharacter->getCharacterPosX()- 10);
        gTestCharacter->setStatus(DEAD_CHARACTER);
    }
    if(gTestCharacter->getStatus()==JUMP_DOWN  && gTestCharacter->getCharacterPosY()+112 >= mPosY && gTestCharacter->getCharacterPosX() + 160 >=  mPosX  && gTestCharacter->getCharacterPosX() + 190 <= mPosX + 120 && status == ALIVE && gTestCharacter-> getIsVisible() == true){
        std::cout<<"Collision enemy "<<std::endl;
        gTestCharacter->setStatus(DEAD_CHARACTER );
    }
}

void Enemy :: setCoordinate (int X , int Y ){
    mPosX = X;
    mPosY = Y ;

}

void Enemy ::  setVel (double vel ){
    mVelX = vel ;
}