#ifndef GAME_H
#define GAME_H

#include"needed.h" 

#define SCREEN_WIDTH 928
#define SCREEN_HEIGHT 793

#define SCREEN_BPP 32

#define COLOR_KEY_R 113
#define COLOR_KEY_G 102
#define COLOR_KEY_B 79

#define MAIN_CHAR_WIDTH 224
#define MAIN_CHAR_HEIGHT 112

#define DEFAULT_PHOENIX_Y 600
#define DEFAULT_MAIN_CHARACTER_Y 620

#define Render_Draw_Color 0xFF

#define PHOENIX_FRAME_WIDTH 228
#define PHOENIX_FRAME_HEIGHT 189

#define FIREBALL_WIDTH 68 
#define NUMBER_OF_FIREBALLS 100

#define FRAME_PER_SECOND 80

#define MAX_HEIGHT_JUMP DEFAULT_MAIN_CHARACTER_Y  - 135

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
        int  point ; 
        bool returnGame ;
        double  currentTime  ; 
        bool isUpdateScore  ;
        int firstCoordinate;
        
       
    public : 
        Game();
        ~Game();
        void loadSplashScreen (LTexture * , SDL_Renderer ** );
        void waitUntilKeyPressed (LTexture * , SDL_Renderer ** );
        int  playGame();
        void resetGame (Boss * boss,Phoenix * phoenix , Character * mainCharacter , Fireball * phoenixFireball) ;
        bool loadSkyFireball( SDL_Renderer ** mRenderer);
        bool loadFireball(Fireball*phoenixFireball , SDL_Renderer ** mRenderer);
        bool loadPhoenix( SDL_Renderer ** screen);
        bool initData(SDL_Renderer ** mRenderer , SDL_Window ** mWindow);
        bool loadAudio();
        void close ( SDL_Renderer ** mRenderer,SDL_Window ** mWindow);
        bool loadAllNeeded (LTexture * splashScreen , Fireball *  phoenixFireball,SDL_Renderer ** mRenderer,SDL_Window ** mWindow);
        void playBGMusic (Character  * mainCharacter );
        void pointManage();
        void fpsManage();
        bool isOnReturnGameArea ( const int& x , const int& y );
        bool isOnExitArea( const int &x, const int & y) ;
        void pauseAllMusic (Boss * boss , Character * mainCharacter  )  ;
        void manageEnemy (Phoenix * phoenix , Fireball * phoenixFireball , Character * mainCharacter, SDL_Renderer ** mRenderer );

};

#endif 