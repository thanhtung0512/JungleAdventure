#ifndef CHARACTER_H
#define CHARACTER_H
#include"needed.h"
#include"Fireball.h"

 
class Character : public Dot {
    public :
    const int frameWidth = 224;
    const int frameHeight = 112;
    const int CHARACTER_VEL = 1.5 ;

    Character();
    ~Character();
    void handleInputAction(SDL_Event &e , SDL_Renderer *screen ,Mix_Chunk * chunk ,Mix_Chunk * sword ,Mix_Chunk * sword_2,int& frameAttack2 , int & frameAttack, int & frameJumpUp);
    void setClipsRun (int frameNumbers); // set dimensions to clips texture right run 
    
    void setIdleClip ();

    void setAttackClip ();

    void setAttackClip2();

    void setJumpUpClips ();

    void setJumpDownClips ();

    void setDeadClips ();
    //bool loadFromFile ( std ::string path,SDL_Renderer * screen)
    int  getStatus ();

    void movingCharacter ();


    void showCharacter (SDL_Renderer * screen, int frame ,int frameIdle ,int frameIdleLeft, int& frameAttack , int &frameAttack2 , int frameJumpUp, int frameJumpDown , int frameDead   ) ;

    int getCharacterPosX ();
    int getCharacterPosY();

    void getHitFromFireball (Fireball* gFireball );

    protected :

    double mPosX , mPosY;
    
    int mVelCharX ;
    int mVelCharY;
    
    int surfaceWidth ;
    int surfaceHeight ;


    SDL_Rect frame_clips [20];
    SDL_Rect frame_idle  [20];
    SDL_Rect frame_attack [30];
    SDL_Rect frame_attack_2 [30];
    SDL_Rect frame_jump_up [9];
    SDL_Rect frame_jump_down [14];
    SDL_Rect frame_dead [14];


    SDL_Texture * mTexture ;
    // SDL_Rect frame_clip_left  [50];

    

    int frame ; // current frame 
    int status ;
    int jumpControl ; 
    // int frameMainRunning , frameIdle , frameIdleLeft ;

};

#endif 