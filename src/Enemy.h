#ifndef ENEMY_H
#define ENEMY_H


#include"needed.h"
#include"Character.h"

#define ALIVE 99
#define DEAD 100 

class Enemy : public Character{
    
    public :
    
    const double enemyVelocity = 2; 

    
    
    Enemy();
    
    ~Enemy();

    void autoMove ( );

    void handleHitFromCharacter (Character* gTestCharacter,  int  frameAttack , int frameAttack2  );
    
    void setFrameEnemiesRun ();

    void setFrameDead ();

    void ShowEnemie (SDL_Renderer* screen );

    void frameProcessing ();

    void getHitFromFireball(Fireball * gFireball );

    void collisionWithPhoenix (Phoenix * gPhoenix );

    void collisionWithMainCharacter ( Character * gTestCharacter);

    void checkCollision ( Phoenix  *gPhoenix , Fireball *gFireball, Character * gTestCharacter);

    void setCoordinate (int X , int Y );

    double getEnemyPosX ();
    
    void setVel (double vel );

    protected :

    SDL_Rect frame_running [22];
    SDL_Rect frame_dead [34];
    int status ;
    double mPosX  , mPosY; 
    double mVelX ;
    int frameEnemyDead , frameWalkingEnemie ; 
    


} ;



#endif 