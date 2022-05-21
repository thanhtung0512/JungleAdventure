#ifndef ENEMY_H
#define ENEMY_H


#include"needed.h"


enum EnemyStatus {
     ALIVE, 
     DEAD,
};

class Enemy : public Character {
    
    public :

    const double enemyVelocity = 2; 
    Enemy();
    ~Enemy();
    void autoMove ( );
    void loadEnemy(SDL_Renderer ** screen );
    void handleHitFromCharacter (Character* gTestCharacter,  int  frameAttack , int frameAttack2  );
    void setFrameEnemiesRun ();
    void ShowEnemie (SDL_Renderer* screen );
    void frameProcessing ();
    void getHitFromFireball(Fireball * gFireball );
    void collisionWithPhoenix (Phoenix * gPhoenix );
    void collisionWithMainCharacter ( Character * gTestCharacter);
    void checkCollision ( Phoenix  *gPhoenix , Fireball *gFireball, Character * gTestCharacter);
    void setCoordinate (int X , int Y );
    double getEnemyPosX ();
    void setVel (double vel );
    void resetEnemy();

    private:

    SDL_Rect frame_running [41];
    EnemyStatus status ;
    double mPosX  , mPosY; 
    double mVelX ;
    int frameEnemyDead , frameWalkingEnemie ; 
    int first ; 
} ;



#endif 