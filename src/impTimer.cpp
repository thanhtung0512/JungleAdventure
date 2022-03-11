#include"needed.h"
#include"impTimer.h" 

impTimer :: impTimer (){
    startTick = pauseTick =0 ;
    isPaused = isStarted = false ; 
}

impTimer :: ~impTimer(){
    
}


void impTimer::start(){
    isStarted = true ;
    isPaused = false ; 
    startTick = SDL_GetTicks();

}

void impTimer:: stop (){
    isStarted = false; 
    isPaused = false ;

}
void impTimer::paused (){
    if ( isStarted == true && isPaused == false){
        isPaused = true ;
        pauseTick = SDL_GetTicks() -  startTick ;
    }
}
void impTimer :: resume(){
    if ( isPaused == true ){
        isPaused = false;
        startTick = SDL_GetTicks ()- pauseTick ;
        pauseTick = 0;
    }
}
int  impTimer ::   getTicks(){
    if(isStarted == true){
        if ( isPaused == true ){
            return pauseTick ; 
        }
        else return SDL_GetTicks()- startTick;
    }
}   

bool impTimer:: isStarted_(){
    return isStarted ; 
}

bool impTimer:: isPaused_(){
    return isPaused ; 
}