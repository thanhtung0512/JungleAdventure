#ifndef BACKGROUND_H
#define BACKGROUND_H
#include"needed.h"


#define NUMS_OF_LAYERS 12
using namespace std;
class Background  {
    private : 
    double scrollingOffset[14];

    LTexture * bgl = new LTexture [13];


    public :
    Background ();
    Background ( SDL_Renderer * screen );
    ~Background();
    void minusScrolling ();
    bool loadlayer(SDL_Renderer * screen );
    void renderLayers(Boss * gBoss,SDL_Renderer * screen, int * point   );
    void loadFirstLayer(SDL_Renderer * screen );
    void manageBGWhenRunning(Boss * gBoss,SDL_Renderer * screen , int * point  );
    void setSrolling();

};

#endif