#ifndef CHARACTER_H
#define CHARACTER_H
#include"needed.h"
#include"Fireball.h"

 
class Character : public Dot {
    public :
    const int frameWidth = 224;
    const int frameHeight = 112;
    const int CHARACTER_VEL = 3 ;

    Character();
    Character(SDL_Renderer * screen );
    ~Character();

    
    void setCharacterPosX(int posX);


    void handleInputAction(SDL_Event &e , SDL_Renderer *screen  ,Mix_Chunk * sword ,Mix_Chunk * sword_2);
    
    void setClipsRunRight (int frameNumbers); // set dimensions for clips texture run right 

    void setClipsRunLeft(int frameNumbers);
    
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
    void resetCharacter();
    void playRunningSound ();
    void pauseRunningSound();
    void loadRunningSound ();
    void manageCharacter ( SDL_Renderer * screen ,Fireball *gFireball , int * point, int* recentPointVisible   );

    bool getIsVisible ();
    void setIsVisible ( bool isVisiblee  );


    int getNumsKilledEnemy ();
    void increaseNumsKilledEnemy ();

    void setAllClipsForInvisibleMode (int frameNumbers);





    private :

    double mPosX , mPosY;
    
    int mVelCharX ;
    int mVelCharY;
    
    int surfaceWidth ;
    int surfaceHeight ;


    SDL_Rect frame_clips_run_right [20];
    SDL_Rect frame_clips_run_left [20];
    SDL_Rect frame_idle  [20];
    SDL_Rect frame_attack [30];
    SDL_Rect frame_attack_2 [30];
    SDL_Rect frame_jump_up [9];
    SDL_Rect frame_jump_down [14];
    SDL_Rect frame_dead [14];

    SDL_Rect i_frame_clips_run_right [20];
    SDL_Rect i_frame_clips_run_left [20];
    SDL_Rect i_frame_idle  [20];
    SDL_Rect i_frame_attack [30];
    SDL_Rect i_frame_attack_2 [30];
    SDL_Rect i_frame_jump_up [9];
    SDL_Rect i_frame_jump_down [14];
    SDL_Rect i_frame_dead [14];


    SDL_Texture * mTexture ;
    // SDL_Rect frame_clip_left  [50];

    

    int frame ; // current frame 
    int status ;

    bool isVisible ; 

    int jumpControl ; 
    int frameMainRunning , frameIdle , frameIdleLeft ;
    int frameAttack ,  frameAttack2  , frameJumpUp , frameJumpDown , frameDead  ;

    Mix_Chunk * runningSound  ;

    int numsKilledEnemy ; 
    LTexture visibleNoti ; 

};

#endif 