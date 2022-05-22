#ifndef POINT_H
#define POINT_H
#include"needed.h"
class Point : public LTexture {
    public :
        Point();
        Point( SDL_Renderer ** screen );
        ~Point();
        void showPointInGame(int * numsKilledEnemy, int * point, int * recentPointVisible  , SDL_Renderer ** screen, Character *mainCharacter );
        void showPointGameOver ( int * point , SDL_Renderer ** screen );
        void loadPoint(SDL_Renderer ** screen);
        void setFrame();
    private :
    SDL_Rect eachNum [10];
    SDL_Rect eachNumOver [10];
    LTexture textNumsKilledEnemy ;
    LTexture textYourPointIs;  
    LTexture textYourAreInvisible ;

};


#endif