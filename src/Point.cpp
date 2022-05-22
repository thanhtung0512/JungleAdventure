#include"needed.h"
#include"Point.h"

Point :: Point(){

}

Point :: Point( SDL_Renderer ** screen ){
    setFrame();
    loadPoint(screen);
    textNumsKilledEnemy.loadFromRenderedText("NUMS OF KILLED ENEMY :",{84,153,32},*screen,12);
    textYourPointIs.loadFromRenderedText("your point is ",{84,153,32},*screen,12);
    textYourAreInvisible.loadFromRenderedText("you are invisible  ",{84,153,32},*screen,12);
}   

Point :: ~Point(){
    free();
}

void Point :: showPointInGame(int * numsKilledEnemy ,int * point , int * recentPointVisible ,  SDL_Renderer ** screen , Character *mainCharacter  ){
    if ( mainCharacter->getIsVisible() ){
        textYourPointIs.render(SCREEN_WIDTH - 300 , SCREEN_HEIGHT - 40 , *screen , NULL);
        string s1= to_string ( *point );
        short f= SCREEN_WIDTH - 50 ;
        for (auto x : s1 ){
            render ( f , SCREEN_HEIGHT - 40,*screen , &eachNum[x-'0']);
            f+=10;
        }
    }
    else {
        short countDownTime =  * recentPointVisible + 30 - * point;
        string s3= to_string (countDownTime);
        textYourAreInvisible.render(SCREEN_WIDTH - 300 , SCREEN_HEIGHT - 40 , *screen , NULL);
        short z=  SCREEN_WIDTH - 50 ; 
        for (auto x : s3 ){
            render ( z , SCREEN_HEIGHT - 40,*screen , &eachNum[x-'0']);
            z+=10;
        }

        
    }
    textNumsKilledEnemy.render(SCREEN_WIDTH - 300 , SCREEN_HEIGHT - 20,*screen,NULL);
    string s= to_string( *numsKilledEnemy );
    short firstX = SCREEN_WIDTH - 50;
    for (auto x : s ){
        render(firstX , SCREEN_HEIGHT - 25 , *screen , &eachNum[x-'0']);
        firstX += 10 ;
    }


}

// SCREEN_WIDTH - 50 , SCREEN_HEIGHT - 20
void Point :: showPointGameOver ( int * point ,SDL_Renderer ** screen){

}

void Point :: loadPoint(SDL_Renderer ** screen){
    loadFromFile ( "img/point/point1.png",*screen);
}

void Point :: setFrame(){
    for (int i=0;i<=9;i++){
        eachNum[i].x= i* 39;
        eachNum[i].y = 0 ; 
        eachNum[i].w = 39;
        eachNum[i].h = 22 ; 
    }
}