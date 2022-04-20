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
    for (int i=1;i<=5;i++){
        currentMenu[i].x=(i-1)*SCREEN_WIDTH;
        currentMenu[i].y=0;
        currentMenu[i].w=SCREEN_WIDTH;
        currentMenu[i].h=SCREEN_HEIGHT;
    }
}

bool  gameMenu:: loadMenu ( SDL_Renderer * screen ){
    confirmSound = Mix_LoadWAV("sound/confirm.wav");
    if ( loadFromFile("img/mainmenu/MENU1.png",screen) == false ){
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
        if(  mouseX >= 398 && mouseX <=495 && mouseY >= 527 && mouseY<=630 ){
            return true ;
        }
    }
    return false;
}

bool gameMenu::  motionOnPlayButton(SDL_Event & gEvent){
    if ( gEvent.type==SDL_MOUSEMOTION ){
        int x=gEvent.motion.x;
        int y =gEvent.motion.y;
        if(  x >= 398 && x <=495 && y >= 527 && y<=630 ){
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
        if(  x >= 247 && x <=351 && y >= 638 && y<=743 ){
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
        if(  x >= 553 && x <= 694 && y >= 638 && y<=746 ){
            return true ;
        }
        return false ;
    }    
    return false;
}


void gameMenu:: menuControl (SDL_Renderer * screen , SDL_Event & gEvent, Mix_Chunk * button,LTexture &gBackgroundTexture, TTF_Font * gFont,SDL_Window * gWindow){
    int isPlay=0, isExit =0 ,isInfo =0;
        while( isPlay == 0  && isInfo == 0  ){
            while (SDL_PollEvent(&gEvent)){
                if (gEvent.type == SDL_MOUSEBUTTONDOWN){
                    if (isClickPlayButton(gEvent)== true ){
                        Mix_PlayChannel(-1,confirmSound,0);
                        isPlay =1 ;
                    }
                     if(isClickExitButton(gEvent)== true ){
                        Mix_PlayChannel(-1,confirmSound,0);
                        gBackgroundTexture.free();
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
                    gBackgroundTexture.free();
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
            }
            SDL_RenderPresent(screen);
        }
}


void gameMenu:: renderPlay(SDL_Renderer * screen ){
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
        if(  mouseX >= 247 && mouseX <=351 && mouseY >= 638 && mouseY<=743 ){
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
            if(  mouseX >= 553 && mouseX <= 694 && mouseY >= 638 && mouseY<=746 ){
                std::cout<<"Clicking on info button "<<std::endl;
                Mix_PlayChannel(-1,confirmSound,0);
                return true ;
            }
        }
        return false;
}