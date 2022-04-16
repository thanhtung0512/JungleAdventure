#include"needed.h"

Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;
double deltaTime = 0;

int point=0 ; 
bool returnGame = false;
double  currentTime = 0 ; 

bool isUpdateScore = true ;

Enemy gEnemy[NUMS_OF_ENEMY];

void resetGame (){
    int first = ENEMY_COORDINATION_X ;
    for (int i=0;i<3;i++){
        gEnemy[i].setCoordinate( first ,  ENEMY_COORDINATION_Y );
        first += 400;
    }
    gTestCharacter.resetCharacter();
    gBoss.resetBoss();
    gPhoenix.resetPhoenix();
    gFireball.resetFireball();
    for(int i=1;i<=NUMS_OF_SKY_FIREBALL;i++){
        gSkyFireball[i].resetSkyFireball();
    }
    for (int i=1;i<=NUMS_OF_ENEMY;i++){
        gEnemy[i].resetEnemy();
    }
    point=0;
    isUpdateScore=true ;
}

bool loadSkyFireball (){
    for (int i=1;i<=NUMS_OF_SKY_FIREBALL;i++){
        if ( gSkyFireball[i].loadFireball(gRenderer)== false ){
        std:: cout<<"Could not load sky fireball "<<SDL_GetError()<<std::endl;
        return false ;
        }
    }
    return true ;
}

bool loadFireball(){
    if ( gFireball.loadFireball(gRenderer)== false ){
        std::cout<<"Could not load Fireball "<<std::endl;
        return false ;
    }
    return true ;
}

bool loadPhoenix(){
    if ( gPhoenix.loadPhoenix(gRenderer)== false ){
        std::cout<<"Could not load Phoenix"<<SDL_GetError()<<std::endl;
        return false ;

    }
    return true ;
}

bool loadBoss(){
    if (gBoss.loadBoss(gRenderer)== false ){
        std::cout<<"Could not load boss "<<SDL_GetError()<<std::endl;
        return false;
    }
    return true ;
}

bool loadMainMenu (){
    if(gGameMenu.loadMenu(gRenderer)== true ){
        return true ;
    }
    else return false ;
}

void setScrolling(){
    int first = 0;
    for(int i=1;i<=12;i++){
        scrollingOffset[i]=first;
    }
}

void minusScrolling (){
    double  minus = 1.8;
    for(int i=1;i<=12;i++){
        scrollingOffset[i] -= minus ;
        if (scrollingOffset[i] < - gBackgroundTexture.getWidth()){
            scrollingOffset[i]=0;
        }
        minus -= (1.8/12);
    }
}

bool initData(){
    bool success =1;
     if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING )<0){
        return false;
    }
    else {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gWindow = SDL_CreateWindow ("The Jungle Adventure _ Thanh Tung UET   ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (gWindow!=NULL){
        gRenderer=SDL_CreateRenderer ( gWindow,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        if ( gRenderer == NULL){
            success=0;
        }else {
            SDL_SetRenderDrawColor(gRenderer,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color);
            int imgFlags = IMG_INIT_PNG;
            if ( !(IMG_Init(imgFlags) && imgFlags)){
                success =0;
            }
        }
    }

    else success = 0;
    return success;
}

bool loadlayer (){
    bool success = 1;
    for (int i=1;i<=12; i++){
        std::string path = "img/bg/" + std::to_string(i) + ".png"; 
        std::cout<<path<<std::endl;
       if ( bgl[i].loadFromFile(path ,gRenderer)==false ){
            std::cout<<"Could not load image "<<SDL_GetError()<<std::endl;
            success=0;   
       }
    }
    
    return success;
}

bool loadAudio(){
    chunk =Mix_LoadWAV("sound/running.wav");
    if ( chunk == NULL) {
        std::cout<<"Could not load chunk "<<SDL_GetError()<<std::endl;
        return false;
    }

    sword = Mix_LoadWAV("sound/sword.wav");
    if(sword == NULL){
        std::cout<<"could not load sword eff "<<SDL_GetError()<<std::endl;
        return false ;
    }
    music=Mix_LoadMUS("sound/bgmusic.mp3");
    if(music == NULL ){
        std::cout<<"could not load music "<<SDL_GetError()<<std::endl;
        return false;
    }
    phoenixWing = Mix_LoadMUS ("sound/wingsound.mp3");
    if ( phoenixWing == NULL){
        std::cout<<"Could not load wing sound "<<SDL_GetError()<<std::endl;
        return false;
    }
    sword_2 = Mix_LoadWAV("sound/sword2.wav");
    if ( sword_2 == NULL){
        std::cout<<"Could not get sw2 sound effect "<<SDL_GetError()<<std::endl;
        return false ;
    }

    fireball = Mix_LoadWAV("sound/fireball.wav");
    if ( fireball == NULL){
        std::cout<<"Could not load fireball sound "<<SDL_GetError()<<std::endl;
        return false ;
    }

    button= Mix_LoadWAV("img/mainmenu/buttonEFF3.wav");
    if ( button== NULL){
        std::cout<<"could not load button sound eff "<<SDL_GetError()<<std::endl;
        return false;
    }

    return true;    
}

void renderLayers(){
    for(int i=12;i>=1;i--){
        bgl[i].render(scrollingOffset[i],0,gRenderer,NULL);
        bgl[i].render(scrollingOffset[i]+gBackgroundTexture.getWidth(),0,gRenderer,NULL);
        if( i==5  && point >= 100 ){
            {   
                gBoss.renderBoss(gRenderer);    
            }
        }
    }
}

bool loadBG(){
    if(gBackgroundTexture.loadFromFile ( "img/bg/Background.png",gRenderer)==false){
        std::cout<<"Could not load BG "<<SDL_GetError()<<std::endl;
        return 0;
    }
    return 1;
}

void close (){
    gBackgroundTexture.free();
    SDL_DestroyRenderer(gRenderer);
    TTF_CloseFont ( gFont );
    gFont = NULL;
    gRenderer=NULL;
    SDL_DestroyWindow(gWindow);
    gWindow=NULL;
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}

void loadFirstLayer(){
    double minus = 1.8;
    scrollingOffset[1] -= minus ;
    if (scrollingOffset[1] < -gBackgroundTexture.getWidth()){
        scrollingOffset[1]=0;
    }
    bgl[1].render(scrollingOffset[1],0,gRenderer,NULL);
    bgl[1].render(scrollingOffset[1]+gBackgroundTexture.getWidth(),0,gRenderer,NULL);
    
}

bool loadAllNeeded (){
    if(initData()==false){
       return false;
    }
    if(loadAudio()== false ){
        return false ;
    }

    if (loadlayer()==false){
        return false;
    }
  
    if ( loadBG()== false) {
        return false;
    }

    if ( loadMainMenu() == false  ) return false ; 
    if (loadBoss()== false ) return false ;
    if ( loadFireball()== false ) return false;
    if ( loadPhoenix()== false ) return false;
    if ( loadSkyFireball()== false ) return false ;
    return true; 
}

void playBGMusic (){
    Mix_PlayMusic(music,-1);
    Mix_PlayMusic(phoenixWing, -1 );
}


int main(int argc, char * agrv[]){
    // load all texture before going to game loop

    srand(time(0));

    int first = ENEMY_COORDINATION_X ;
    for (int i=0;i<3;i++){
        gEnemy[i].setCoordinate( first ,  ENEMY_COORDINATION_Y );
        first += 400;
    }

    if(loadAllNeeded()==false){
        return -1;
    }

    bool stop = false;
    // SET FOR PARRALAX BACKGROUND ALL VELOCITY = 0 
    setScrolling();
    // ----------------------------------------------------------------------------------
    gGameMenu.render(0,0,gRenderer,NULL);
    gGameMenu.menuControl(gRenderer,gEvent,button,gBackgroundTexture,gFont,gWindow);

    playBGMusic();

    
    while (stop == false  || returnGame == true ){  
        
        fpsTimer.start(); 
        
        while ( SDL_PollEvent(&gEvent)){
            if(gEvent.type == SDL_QUIT ){
               stop=true ;
               returnGame= false ;
            }
            gTestCharacter.handleInputAction(gEvent,gRenderer,chunk,sword,sword_2 );
        }
        
        SDL_SetRenderDrawColor(gRenderer,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color);
        SDL_RenderClear(gRenderer);
        
        // FOR PARALLAX BACKGROUNDDD ------------------------------------------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        minusScrolling();
        renderLayers();
    
        // FOR FIREBALL ---------------------------------------------------------------------------------------------------------------------------------------
            //INSIDE RENDERFIREBALL FUNCTION, IT HAS TO CHECK THE STATE OF FIREBALL IS BE CREATED  OR NOT --------------------------------- 
            
        gFireball.renderFireball(gRenderer);
        gFireball.autoMove();
        // FOR FIREBALL -------------------------------------------------------------- 
        
     
        
        
        // FOR MAIN CHARACTER ----------------------------------------------------------------------------------------------------------------------------------
        gTestCharacter.getHitFromFireball(&gFireball);
        gTestCharacter.movingCharacter();
        gTestCharacter.showCharacter(gRenderer);

        loadFirstLayer();

        if(point>=100 ){
        for (int i=1;i<=NUMS_OF_SKY_FIREBALL;i++){
            gSkyFireball[i].renderSkyFireball(gRenderer,&point);
            gSkyFireball[i].autoMove();
            gSkyFireball[i].checkCollisionWithMainCharacter(&gTestCharacter);
        }
        }
        
        

        for (int i=0;i<NUMS_OF_ENEMY;i++){
            gEnemy[i].autoMove();
            gEnemy[i].ShowEnemie(gRenderer);
            gEnemy[i].checkCollision(&gPhoenix,&gFireball,&gTestCharacter);
            gEnemy[i].handleHitFromCharacter(&gTestCharacter,gTestCharacter.getFrameAttack(),gTestCharacter.getFrameAttack2());
        }
        
        
        if  (gTestCharacter.getStatus() == DEAD_CHARACTER ){
                isUpdateScore=false ;
                gGameMenu.renderWhenDead(gRenderer);
                gScore.showText(430,466,&point,gRenderer);
                while( SDL_PollEvent (&gEvent) ){
                    if ( gEvent.type == SDL_MOUSEBUTTONDOWN ){
                        int x = gEvent.button.x;
                        int y = gEvent.button.y;
                        if ( x>= 334 && x<= 400 && y>=518 && y<=579 ){
                            returnGame =  true ;
                            resetGame();
                        }
                        if ( x>=471 && x<= 539 && y>=515 && y<= 578 ){
                            stop= true ;
                            returnGame= false;
                        }
                    }
                    else if  ( gEvent.type == SDL_QUIT){
                        stop= true ;
                        returnGame= false;
                    }

                }
            
        }
        if ( gTestCharacter.getStatus()!=DEAD_CHARACTER){
        gScore.showText(0,0,&point,gRenderer);
        }
        gPhoenix.renderPhoenix(gRenderer);
        SDL_RenderPresent(gRenderer); 


        
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );

        currentTime += deltaTime;
        // std::cout<<currentTime<<std::endl;
        if ( currentTime >= 200 ){
            // std::cout<<currentTime<<std::endl;
            currentTime =0;
            if(isUpdateScore == true ){
                point++ ; 
            }
        }

        int realImpTime = fpsTimer.getTicks();
        
        int timeOneFrame = (1000/FRAME_PER_SECOND ); // ms 
        if ( realImpTime < timeOneFrame ){
            int delayTime = timeOneFrame - realImpTime ; 
            if ( delayTime > 0 )
            {
                SDL_Delay(delayTime);
            }
        }
    }
    
    close();
    return 0;
}