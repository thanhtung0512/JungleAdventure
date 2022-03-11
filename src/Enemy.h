#ifndef ENEMY_H
#define ENEMY_H


#include"needed.h"
#include"Character.h"

#define ALIVE 99
#define DEAD 100 

class Enemy : public Character{
    
    public :
    
    const int enemyVelocity = 1; 

    Enemy();
    ~Enemy();

    void autoMove (int & frameEnemyDead );

    void handleHitFromCharacter (Character* gTestCharacter,  int & frameAttack  );
    
    void setFrameEnemiesRun ();

    void setFrameDead ();

    void ShowEnemie (SDL_Renderer* screen , int frameWalkingEnemie , int frameEnemyDead );


    protected :

    SDL_Rect frame_running [22];
    SDL_Rect frame_dead [34];
    int status ;
    double mPosX  , mPosY; 
    double mVelX ;
    


} ;



#endif 