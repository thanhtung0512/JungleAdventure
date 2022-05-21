#ifndef _GAMEMENU_H
#define _GAMEMENU_H
#include"needed.h"

enum Track {KHONG_BANG };

class gameMenu : public LTexture {
    public :    
    gameMenu();
    gameMenu(SDL_Renderer * screen );
    ~gameMenu();
    
    

    bool  loadMenu ( SDL_Renderer * screen );
    bool isClickPlayButton( );
    bool isClickExitButton();
    bool isClickInfoButton();
    bool isClickReturnButton ( );

    bool motionOnPlayButton(SDL_Event & gEvent);
    bool motionOnExitButton (SDL_Event & gEvent);
    bool motionOnInfoButton (SDL_Event & gEvent);
    

    void menuControl (SDL_Renderer * screen , SDL_Event & gEvent,Mix_Chunk * button , TTF_Font * gFont,SDL_Window * gWindow, bool * isStop , bool * returnGame , int * continueToPlay  );
    void setMenuFrame();
    
    void renderPlay(SDL_Renderer * screen );
    void renderExit ( SDL_Renderer * screen );
    void renderInfor(SDL_Renderer * screen );
    void renderInsideInfor ( SDL_Renderer  * screen );
    void renderWhenDead(SDL_Renderer * screen );    
    void renderMainMenu ( SDL_Renderer * screen );

    bool isOnPlayArea  (  int mouseX, int mouseY )  ;
    bool isOnExitArea  (  int mouseX, int mouseY )  ;
    bool isOnInfoArea  (  int mouseX, int mouseY )  ;
    bool isOnReturnArea ( int mouseX, int mouseY) ;

    bool isClickPlayMusicButton(SDL_Event& gEvent );
    bool isOnPlayMusicArea  (  int mouseX, int mouseY )  ;

    void playConfirmSound ();




    private :
    
    SDL_Rect currentMenu[7];
    Mix_Chunk  * confirmSound ;
    Mix_Music  * track1 ;
  
    SDL_Rect mp3Rect [3];
  
   


} ;


#endif 