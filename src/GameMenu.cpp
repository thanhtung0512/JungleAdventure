#include"needed.h"
#include"GameMenu.h" 

gameMenu :: gameMenu(){
    setMenuFrame();
    confirmSound= NULL;
}

gameMenu :: ~gameMenu (){
    free();   
}

void gameMenu:: setMenuFrame(){
    for (int i=1;i<=6;i++){
        currentMenu[i].x=(i-1)*SCREEN_WIDTH;
        currentMenu[i].y=0;
        currentMenu[i].w=SCREEN_WIDTH;
        currentMenu[i].h=SCREEN_HEIGHT;
    }
}

bool  gameMenu:: loadMenu ( SDL_Renderer * screen ){
    confirmSound = Mix_LoadWAV("sound/confirm.wav");
    if ( loadFromFile("img/mainmenu/menu4.jpg",screen) == false ){
        std::cout<<"could not load Menu "<<std::endl;
        return false ;
    }
    else return true ;
}

bool gameMenu::  isClickPlayButton(SDL_Event& gEvent ){
    if(gEvent.button.button== SDL_BUTTON_LEFT ){
        int mouseX = gEvent.button.x;
        int mouseY = gEvent.button.y;
        std::cout << mouseX <<" "<<mouseY <<std::endl;
        if(  isOnPlayArea(mouseX , mouseY ) ){
            return true ;
        }
    }
    return false;
}

bool gameMenu:: motionOnPlayButton(SDL_Event & gEvent){
    if ( gEvent.type==SDL_MOUSEMOTION ){
        int mouseX=gEvent.motion.x;
        int mouseY =gEvent.motion.y;
        if(  isOnPlayArea(mouseX,mouseY) ){
            return true ;
        }
        return false ;
        
    }
    return false;
}

bool gameMenu:: motionOnExitButton (SDL_Event & gEvent){
    if ( gEvent.type==SDL_MOUSEMOTION ){
        int x=gEvent.motion.x;
        int y =gEvent.motion.y;
        if(  isOnExitArea(x,y) ){
            return true ;
        }
        return false ;
        
    }
    return false;
}

bool gameMenu:: motionOnInfoButton (SDL_Event & gEvent){
    if ( gEvent.type==SDL_MOUSEMOTION ){
        int x=gEvent.motion.x;
        int y =gEvent.motion.y;
        if(  isOnInfoArea(x,y) ){
            return true ;
        }
        return false ;
    }    
    return false;
}


void gameMenu:: menuControl (SDL_Renderer * screen , SDL_Event & gEvent, Mix_Chunk * button,LTexture *gBackgroundTexture, TTF_Font * gFont,SDL_Window * gWindow){
    int isPlay=0, isExit =0 ,isInfo =0;
        while( isPlay == 0   ){
            while (SDL_PollEvent(&gEvent)){
                if (gEvent.type == SDL_MOUSEBUTTONDOWN){
                    if (isClickPlayButton(gEvent)== true ){
                        Mix_PlayChannel(-1,confirmSound,0);
                        isPlay =1 ;
                    }
                     if(isClickExitButton(gEvent)== true ){
                        Mix_PlayChannel(-1,confirmSound,0);
                        gBackgroundTexture->free();
                        SDL_DestroyRenderer(screen);
                        TTF_CloseFont ( gFont );
                        gFont = NULL;
                        screen=NULL;
                        SDL_DestroyWindow(gWindow);
                        gWindow=NULL;
                        TTF_Quit();
                        SDL_Quit();
                        IMG_Quit();
                        isExit=1;
                    }
                     if ( isClickInfoButton(gEvent)== true ){
                        Mix_PlayChannel(-1,confirmSound,0);
                        isInfo = 1 ;
                    }   
                    if ( isClickReturnButton(gEvent)== true ){
                        render(0,0,screen,NULL);
                        isInfo=0;
                    }
                }
                else if ( gEvent.type == SDL_MOUSEMOTION){
                    if ( motionOnPlayButton(gEvent)== true ){
                        renderPlay(screen);
                    }
                    else if (motionOnExitButton(gEvent)==true ){
                        renderExit(screen);
                    }
                    else if (motionOnInfoButton(gEvent)== true ){
                        renderInfor(screen);
                    }
                    else {
                        Mix_HaltChannel(-1);
                        render(0,0,screen,NULL);
                    }
                }
                else if (gEvent.type==SDL_QUIT){
                    gBackgroundTexture->free();
                    SDL_DestroyRenderer(screen);
                    TTF_CloseFont ( gFont );
                    gFont = NULL;
                    screen=NULL;
                    SDL_DestroyWindow(gWindow);
                    gWindow=NULL;
                    TTF_Quit();
                    SDL_Quit();
                    IMG_Quit();
                }
                if ( isInfo == 1 ){
                    render(0,0,screen,&currentMenu[6]);
                }
                

            }
            SDL_RenderPresent(screen);
        }
}


void gameMenu :: renderPlay(SDL_Renderer * screen ){
    render(0,0,screen,&currentMenu[2]);
}

void gameMenu::renderExit ( SDL_Renderer * screen ){
    render(0,0,screen,&currentMenu[3]);
}
void gameMenu:: renderInfor(SDL_Renderer * screen ){
    render(0,0,screen,&currentMenu[4]);
}


void gameMenu::  renderWhenDead(SDL_Renderer * screen ){
    render(0,0,screen,&currentMenu[5]);
}
bool gameMenu:: isClickExitButton(SDL_Event & gEvent){
    if(gEvent.button.button== SDL_BUTTON_LEFT ){
        int mouseX = gEvent.button.x;
        int mouseY = gEvent.button.y;
        if(  isOnExitArea(mouseX,mouseY) ){
            Mix_PlayChannel(-1,confirmSound,0);
            std::cout<<"Clicking on exit button "<<std::endl;
            return true ;
        }
    }
    return false;

}


bool gameMenu::  isClickInfoButton(SDL_Event & gEvent){
    if(gEvent.button.button== SDL_BUTTON_LEFT ){
            int mouseX = gEvent.button.x;
            int mouseY = gEvent.button.y;
            if(  isOnInfoArea(mouseX,mouseY) ){
                std::cout<<"Clicking on info button "<<std::endl;
                Mix_PlayChannel(-1,confirmSound,0);
                return true ;
            }
        }
        return false;
}

bool gameMenu ::  isClickReturnButton ( SDL_Event & gEvent){
    if(gEvent.button.button== SDL_BUTTON_LEFT ){
            int mouseX = gEvent.button.x;
            int mouseY = gEvent.button.y;
            if(  isOnReturnArea(mouseX,mouseY) ){
                std::cout<<"Clicking on return button "<<std::endl;
                return true ;
            }
        }
        return false;
}

void gameMenu ::  renderMainMenu ( SDL_Renderer * screen ){
    render(0,0,screen,&currentMenu[4]);
}

void gameMenu :: renderInsideInfor ( SDL_Renderer  * screen ){
    render(0,0,screen,&currentMenu[6]);
}

bool gameMenu :: isOnPlayArea  ( int mouseX, int mouseY )  {
    return mouseX >= 344 && mouseX <=552 && mouseY >= 384 && mouseY<= 590 ;

}
bool gameMenu :: isOnExitArea  ( int mouseX, int mouseY )  {
    return mouseX >= 346 && mouseX <=421 && mouseY >=599 && mouseY <= 670;
}
bool gameMenu :: isOnInfoArea  ( int mouseX, int mouseY )  {
    return mouseX >=464 && mouseX <=542 && mouseY >= 602 && mouseY <= 666;

}

bool gameMenu::  isOnReturnArea ( int mouseX, int mouseY) {
    return mouseX >= 6 && mouseX <=73 && mouseY >=5 && mouseY<= 70 ;
}