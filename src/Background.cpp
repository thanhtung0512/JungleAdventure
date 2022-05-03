#include"needed.h" 
#include"Background.h"

bool Background:: loadlayer(SDL_Renderer * screen){
    bool success = 1;
    for (int i=1;i<=NUMS_OF_LAYERS; i++){
        std::string path = "img/bg/" + std::to_string(i) + ".png"; 
        std::cout<<path<<std::endl;
        if ( bgl[i].loadFromFile(path , screen)==false ){
                std::cout<<"Could not load image "<<SDL_GetError()<<std::endl;
                success=0;   
        }
    }
    return success;
}

 void Background ::  minusScrolling (){
    double  minus = 1.8;
    for(int i=1;i<=NUMS_OF_LAYERS;i++){
        scrollingOffset[i] -= minus ;
        if (scrollingOffset[i] < -SCREEN_WIDTH){
            scrollingOffset[i]=0;
        }
        minus -= (1.8/NUMS_OF_LAYERS);
    }
 }


 void Background ::  renderLayers(Boss * gBoss,SDL_Renderer * screen , int * point  ){
      for(int i=NUMS_OF_LAYERS;i>=1;i--){
        bgl[i].render(scrollingOffset[i],0,screen,NULL);
        bgl[i].render(scrollingOffset[i]+SCREEN_WIDTH,0,screen,NULL);
        if( i==5  && *point >= TO_RENDER_BOSS_POINT ){
            {   
                gBoss->renderBoss(screen);    
            }
        }
    }
 }

Background :: Background (){
    setSrolling();

}
Background :: Background (SDL_Renderer * screen ){
    setSrolling();
    loadlayer(screen);
}
void Background:: loadFirstLayer (SDL_Renderer * screen){
    double minus = 1.8;
    scrollingOffset[1] -= minus ;
    if (scrollingOffset[1] < -SCREEN_WIDTH){
        scrollingOffset[1]=0;
    }
    bgl[1].render(scrollingOffset[1],0,screen,NULL);
    bgl[1].render(scrollingOffset[1]+SCREEN_WIDTH,0,screen,NULL);
}

void Background :: manageBGWhenRunning(Boss * gBoss,SDL_Renderer * screen , int * point  ){
    minusScrolling();
    renderLayers(gBoss,screen, point );
    loadFirstLayer(screen);
}

Background :: ~Background(){
    
}
void Background ::  setSrolling(){
    int first = 0;
    for(int i=1;i<=NUMS_OF_LAYERS;i++){
        scrollingOffset[i]=first;
    }
}