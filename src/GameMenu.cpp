#include"needed.h"
#include"GameMenu.h" 

gameMenu :: gameMenu(){
    setMenuFrame();
    confirmSound= NULL;
}

gameMenu :: gameMenu(SDL_Renderer * screen ){
    setMenuFrame();
    confirmSound= NULL;
    loadMenu(screen);
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

bool gameMenu:: loadMenu ( SDL_Renderer * screen ){
    for (int i=1;i<=2;i++){
        mp3Rect[i].x=(i-1)* 200 ;
        mp3Rect[i].y=0;
        mp3Rect[i].w=200;
        mp3Rect[i].h=50;

    }
 
    confirmSound = Mix_LoadWAV("sound/confirm.wav");
   
    if ( loadFromFile("img/mainmenu/menu4.jpg",screen) == false ){
        std::cout<<"could not load Menu "<<std::endl;
        return false ;
    }
  
    else return true ;
}

bool gameMenu::  isClickPlayButton( ){
    int mouseX, mouseY ;
    SDL_GetMouseState(&mouseX, &mouseY);
    if ( isOnPlayArea(mouseX,mouseY)){
           
            return true ;
    }
    return false ;
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
    if ( gEvent.type == SDL_MOUSEMOTION ){
        int x=gEvent.motion.x;
        int y =gEvent.motion.y;
        if( isOnInfoArea(x,y)  ){
            return true ;
        }
        return false ;
    }    
    return false;
}

void gameMenu::  playConfirmSound (){
    Mix_PlayChannel(2,confirmSound,0);
}


void gameMenu:: menuControl (SDL_Renderer * screen , SDL_Event & gEvent, Mix_Chunk * button , TTF_Font * gFont,SDL_Window * gWindow,bool * isStop,bool * returnGame,int * continueToPlay ){
    int * isContinue = new int (0);
    int * isExit = new int (0);
    int * isInfo= new int (0);
    int * isPlayMusic = new int (1);
    
    while( *isContinue == 0   ){
        while (SDL_PollEvent(&gEvent)){
            if (gEvent.type == SDL_MOUSEBUTTONDOWN){
                if ( isClickPlayButton()== true && *isContinue ==0 && *isInfo ==0  ){
                    std :: cout << "PLAY "<<std::endl;
                    *isContinue =1 ;
                    *continueToPlay=1;
                }
                    if( isClickExitButton()== true && *isContinue == 0 && *isInfo ==0   ){
                    *isStop = true ;
                    *returnGame = false ;
                    *isContinue =1 ;
                    * continueToPlay = 0 ;
                }
                if ( isClickInfoButton()== true && *isInfo == 0  ){
                    *isInfo = 1 ;
                }   
                if ( isClickReturnButton()== true && *isInfo == 1  ){
                    render(0,0,screen,NULL);
                    *isInfo=0;
                }
                
            }
            else if ( gEvent.type == SDL_MOUSEMOTION){
                if ( isClickPlayButton()== true ){
                    renderPlay(screen);
                }
                else if (isClickExitButton()==true ){
                    renderExit(screen);
                }
                else if (isClickInfoButton()== true ){
                    renderInfor(screen);
                }
                else {
                    Mix_HaltChannel(-1);
                    render(0,0,screen,NULL);
                }
            }
            else if (gEvent.type==SDL_QUIT){
                    *isStop = true ;
                    *returnGame = false ;
                    *isContinue = 1; 
            }
        }
        if ( *isInfo == 1 ){
            render(0,0,screen,&currentMenu[6]);
        }
        SDL_RenderPresent(screen);
        SDL_Delay(10);
    }
    playConfirmSound();
    delete isContinue ;
    delete isExit  ;
    delete isInfo ; 
    delete isPlayMusic ; 
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

bool gameMenu:: isClickExitButton(){
    int mouseX, mouseY ;
    SDL_GetMouseState(&mouseX, &mouseY);
    if ( isOnExitArea(mouseX,mouseY)){
        return true ;
    }
    return false ;
}

bool gameMenu::  isClickInfoButton(){
    int mouseX, mouseY ;
    SDL_GetMouseState(&mouseX, &mouseY);
    if ( isOnInfoArea (mouseX,mouseY) ){
            return true ;
    }
    return false ;
}

bool gameMenu ::  isClickReturnButton ( ){
    int mouseX, mouseY ;
    SDL_GetMouseState(&mouseX, &mouseY);
    if ( isOnReturnArea(mouseX,mouseY)){
            
            return true ;
    }
    return false ;
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

