#ifndef GAME_H
#define GAME_H

#include"needed.h" 

#define SCREEN_WIDTH 928
#define SCREEN_HEIGHT 793

#define SCREEN_BPP 32

#define COLOR_KEY_R 113
#define COLOR_KEY_G 102
#define COLOR_KEY_B 79

#define MAIN_CHAR_FRAME_RUN 8
#define MAIN_CHAR_WIDTH 224
#define MAIN_CHAR_HEIGHT 112

#define DEFAULT_PHOENIX_Y 600
#define DEFAULT_MAIN_CHARACTER_Y 620

#define Render_Draw_Color 0xFF

#define SPRITE_MAIN_WITDH 96
#define SPRITE_MAIN_HEIGHT 64

#define PHOENIX_FRAME_WIDTH 228
#define PHOENIX_FRAME_HEIGHT 189

#define FIREBALL_WIDTH 68 
#define NUMBER_OF_FIREBALLS 100

#define FRAME_PER_SECOND 90

#define RUN_RIGHT 1
#define RUN_LEFT 0
#define IDLE -1
#define IDLE_LEFT -2 
#define ATTACK 4 
#define IDLE_CLIPS 8
#define ATTACK_2 -3
#define JUMP_UP 10
#define JUMP_DOWN 13  
#define ON_GROUND 11 
#define DEAD_CHARACTER  -9 


// CHARACTER FRAME DEFINE 
#define FRAME_OF_RUNNING 8 
#define FRAME_OF_IDLE 8 
#define FRAME_OF_ATTACK 18 
#define FRAME_OF_ATTACK_2 28
#define FRAME_JUMP_UP 7
#define FRAME_JUMP_DOWN 13
#define FRAME_DEAD 13

#define MAX_HEIGHT_JUMP DEFAULT_MAIN_CHARACTER_Y  - 135

#define TIME_TO_NEXT_FRAME_RUNNING_CHARACTER 6 
#define TIME_TO_NEXT_FRAME_IDLE 15 
#define TIME_TO_NEXT_FRAME_ATTACK 4
#define TIME_TO_NEXT_FRAME_ATTACK_2 3
#define TIME_TO_NEXT_FRAME_JUMP_UP 7 
#define TIME_TO_NEXT_FRAME_JUMP_DOWN 13 
#define TIME_TO_NEXT_FRAME_DEAD 13
#define NUMS_OF_SKY_FIREBALL 7
#define NUMS_OF_ENEMY 5

#define LEFT_LIMIT_X 0 


#define ENEMY_COORDINATION_X  ( double ) SCREEN_WIDTH - 130
#define ENEMY_COORDINATION_Y  ( double ) DEFAULT_MAIN_CHARACTER_Y+70 

#define SCORE_X 430
#define SCORE_Y 466

#define TO_RENDER_BOSS_POINT 100
#define NUMS_OF_SKYFIREBALL 11 
class Game {

    private :
        SDL_Window *gWindow = NULL;
        SDL_Renderer *gRenderer = NULL;
        SDL_Event gEvent;
        SDL_Texture *gCurrentImage = NULL;
        TTF_Font *gFont = NULL;
        Mix_Music *music ;
        Mix_Music *phoenixWing;
        Mix_Chunk *sword ;
        Mix_Chunk *sword_2 ;
        Mix_Chunk *fireball ;
        Mix_Chunk * button  ;
        
        impTimer fpsTimer ; 
        Enemy gEnemy [NUMS_OF_ENEMY];
        SkyFireball gSkyFireball[NUMS_OF_SKYFIREBALL];

        int originXFireball , originYFireball  ;
        int countFireball ;
        Uint64 NOW ;
        Uint64 LAST ;
        double deltaTime ;
        int point ; 
        bool returnGame ;
        double  currentTime  ; 
        bool isUpdateScore  ;
        int firstCoordinate;
        
        
        

       

    public : 
        Game();
        ~Game();
        void loadSplashScreen (LTexture * splashScreen);
        void waitUntilKeyPressed (LTexture * splashScreen);
        int  playGame();
        void resetGame (Boss * gBoss,Phoenix * gPhoenix , Character * mainCharacter , Fireball * gFireball) ;
        bool loadSkyFireball();
        bool loadFireball(Fireball*gFireball );
        bool loadPhoenix();
        bool loadBoss();
        bool loadMainMenu ();
        bool initData();
        bool loadAudio();
        void close ();
        bool loadAllNeeded (LTexture * splashScreen , Fireball *  gFireball );
        void playBGMusic (Character  * gTestCharacter );
        void pointManage();
        void fpsManage();
        bool isOnReturnGameArea ( const int& x , const int& y );
        bool isOnExitArea( const int &x, const int & y) ;
        void pauseAllMusic (Boss * gBoss , Character * gTestCharacter  );

};

#endif 