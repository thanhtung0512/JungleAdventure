#ifndef _GAMEMENU_H
#define _GAMEMENU_H
#include"needed.h"

class gameMenu : public LTexture {
    public :    
    gameMenu();
    ~gameMenu();
    
    bool  loadMenu ( SDL_Renderer * screen );
    bool isClickPlayButton(SDL_Event& gEvent );
    bool isClickExitButton(SDL_Event & gEvent);
    bool isClickInfoButton(SDL_Event & gEvent);
    bool isClickReturnButton ( SDL_Event & gEvent);

    bool motionOnPlayButton(SDL_Event & gEvent);
    bool motionOnExitButton (SDL_Event & gEvent);
    bool motionOnInfoButton (SDL_Event & gEvent);
    

    void menuControl (SDL_Renderer * screen , SDL_Event & gEvent,Mix_Chunk * button,LTexture *gBackgroundTexture, TTF_Font * gFont,SDL_Window * gWindow );
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


    private :
    
    SDL_Rect currentMenu[8];
    Mix_Chunk  * confirmSound ;


} ;


#endif 