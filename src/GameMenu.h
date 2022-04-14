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

    bool motionOnPlayButton(SDL_Event & gEvent);
    bool motionOnExitButton (SDL_Event & gEvent);
    bool motionOnInfoButton (SDL_Event & gEvent);

    void menuControl (SDL_Renderer * screen , SDL_Event & gEvent,Mix_Chunk * button,LTexture &gBackgroundTexture, TTF_Font * gFont,SDL_Window * gWindow );
    void setMenuFrame();
    void renderPlay(SDL_Renderer * screen );
    void renderExit ( SDL_Renderer * screen );
    void renderInfor(SDL_Renderer * screen );
    

    private :
    
    SDL_Rect currentMenu[6];


} ;


#endif 