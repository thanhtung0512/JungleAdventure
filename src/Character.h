#ifndef CHARACTER_H
#define CHARACTER_H
#include"needed.h"
#include"Fireball.h"

 
class Character : public Dot {
    public :
    const int frameWidth = 224;
    const int frameHeight = 112;
    const int CHARACTER_VEL = 2 ;

    Character();
    ~Character();

    
    void setCharacterPosX(int posX);


    void handleInputAction(SDL_Event &e , SDL_Renderer *screen ,Mix_Chunk * chunk ,Mix_Chunk * sword ,Mix_Chunk * sword_2);
    
    void setClipsRun (int frameNumbers); // set dimensions to clips texture right run 
    
    void setIdleClip ();

    void setAttackClip ();

    void setAttackClip2();

    void setJumpUpClips ();

    void setJumpDownClips ();

    void setDeadClips ();
    //bool loadFromFile ( std ::string path,SDL_Renderer * screen)
    int  getStatus ();

    void  setStatus (int status );

    void movingCharacter ();


    void showCharacter (SDL_Renderer * screen   ) ;

    int getCharacterPosX ();
    int getCharacterPosY();

    void getHitFromFireball (Fireball* gFireball );

   

    void frameProcessing ();

    int getFrameAttack();
    int getFrameAttack2 ();

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
    int frameMainRunning , frameIdle , frameIdleLeft ;
    int frameAttack ,  frameAttack2  , frameJumpUp , frameJumpDown , frameDead  ;

};

#endif 