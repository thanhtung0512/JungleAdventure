#include"needed.h"

Enemy gEnemy ; 
// load 2gRenderder 

bool loadMainMenu (){
    if ( gMainMenu.loadFromFile("img/mainmenu/mainmenu.png",gRenderer ) == false ){
        std::cout<<"Could not load main menu "<<std::endl;
        return false ;
    }
    return true ;
}

bool  loadFireball (){
            if (gFireball.loadFromFile("img/fireball/fireball.png",gRenderer) == false ){
                std::cout<<"could not load fireball "<<SDL_GetError()<<std::endl;
                return false ;    
            }
        return true;
}

void setSpriteFireball (){
    for(int i=1 ;i<= 30 ;i++){
        spriteOfFireball[i].x= (i-1) * 68; 
        spriteOfFireball[i].y=0;
        spriteOfFireball[i].w=68;
        spriteOfFireball[i].h= 9 ;
    }
}

void setSpritePhoenix (){
    for(int i=1;i<= 12;i++){
        spriteOfPhoenix[i].x= (i-1)* 228 ;
        spriteOfPhoenix[i].y=0;
        spriteOfPhoenix[i].w=228;
        spriteOfPhoenix[i].h=189;
    }
}

bool loadPhoenix (){
    if ( gPhoenix.loadFromFile("img/phoenix/phoenix.png",gRenderer) == false ){
        std::cout<<"Could not load Phoenix "<<SDL_GetError()<<std::endl;
        return false;
    }
    return true;
}

void setScrolling(){
    int first = 0;
    for(int i=1;i<=12;i++){
        scrollingOffset[i]=first;
    }
}

void minusScrolling (){
    double  minus = 0.8;
    for(int i=1;i<=12;i++){
        scrollingOffset[i] -= minus ;
        if (scrollingOffset[i] < - gBackgroundTexture.getWidth()){
            scrollingOffset[i]=0;
        }
        minus -= (0.8/12);
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
    gWindow = SDL_CreateWindow ("Tung Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
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

bool loadFont (){
    bool success = true; 
    // open font 
    gFont = TTF_OpenFont("fonts/test.ttf",28);
    if ( gFont == NULL){
        std::cout<<"Could not load font ";
        success = false;
    }
    else {
        // render text 
        SDL_Color textColor={0,0,0};
        if (gtextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog", textColor , gFont,gRenderer)== false){
            success =false;
            std::cout<<"Could not render text "<<SDL_GetError()<<std::endl;
        }
        else {
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


    return true;    
}

void renderLayers(){

    for(int i=12;i>=1;i--){
        bgl[i].render(scrollingOffset[i],0,gRenderer,NULL);
        bgl[i].render(scrollingOffset[i]+gBackgroundTexture.getWidth(),0,gRenderer,NULL);
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
    double minus = 0.8;
    scrollingOffset[1] -= minus ;
    if (scrollingOffset[1] < - gBackgroundTexture.getWidth()){
        scrollingOffset[1]=0;
    }
    bgl[1].render(scrollingOffset[1],0,gRenderer,NULL);
    bgl[1].render(scrollingOffset[1]+gBackgroundTexture.getWidth(),0,gRenderer,NULL);
    
}

void frameProcessing (){
        frameMainRunning ++;
        frameIdle ++; 
        frameIdleLeft ++;
        frameAttack++;
        framePhoenix++;
        frameAttack2 ++;
        frameFireball++;
        frameJumpUp ++; 
        frameJumpDown ++ ;
        frameWalkingEnemie ++ ; 
   
        if(framePhoenix >= 12* 15){
            framePhoenix= 15;
        }
        if ( frameMainRunning  >= 8*10 ){
            frameMainRunning = 10;
        } 
        if ( frameIdle >= 15 * 8){
            frameIdle = 15;
        }
        if ( frameAttack >= 18 * 6 ){
             frameAttack =  6;
         }
        if ( frameAttack2 >= 28 *6 ){
            frameAttack2 = 6;
        }
        if ( frameFireball >= 10 * 30 ){
            frameFireball = 10 ;
        }
        if (frameJumpUp >= 7 * 7){
            frameJumpUp = 14 ;
        }
        if (frameJumpDown >= 13* 13 ){
            frameJumpDown = 26; 
        }
        if (frameDead <= 13*13 ){
            frameDead ++ ;
        }
        if ( frameWalkingEnemie >= 21*10 ){
            frameWalkingEnemie = 10;
        }
        if  ( frameEnemyDead <= 20 * 30 ){
            frameEnemyDead ++ ;
        }
}

bool loadAllNeeded (){
    
    if(initData()==false){
       return false;
    }
    if(loadAudio()== false ){
        return false ;
    }
    if (loadPhoenix()== false){
        return false;
    }
    if (loadlayer()==false){
        return false;
    }
    if ( loadFireball() == false ){
        return false ;
    }
    if ( loadBG()== false) {
        return false;
    }
    if ( loadFont()==false ){
        return false;
    }
  
    
    if ( loadMainMenu() == false  ) return false ; 
    return true;
}

void playBGMusic (){
    
    Mix_PlayMusic(music,-1);
    Mix_PlayMusic(phoenixWing, -1 );
}


int main(int argc, char * agrv[]){
    if(loadAllNeeded()==false){
        return -1;
    }

    bool stop = false;
    // SET SPRITE ALL CHARACTERS -------------------------------------------------------
    setSpriteFireball();
    setSpritePhoenix();
    setScrolling();
   
    // ----------------------------------------------------------------------------------
    playBGMusic();
    
    while (stop == false ){  
        fpsTimer.start(); 
       while ( SDL_PollEvent(&gEvent)){
            if(gEvent.type == SDL_QUIT ){
               stop=1;
            }
     
            gTestCharacter.handleInputAction(gEvent,gRenderer,chunk,sword,sword_2,frameAttack2,frameAttack,frameJumpUp );
            // gPhoenix.handleInputAction(gEvent,gRenderer,NULL,NULL,NULL,frameAttack2);
        }
        
        SDL_SetRenderDrawColor(gRenderer,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color);
        SDL_RenderClear(gRenderer);
        
        // FOR PARALLAX BACKGROUNDDD ------------------------------------------------------------------------------------------------------------------------
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        
        SDL_Rect * currentFrame = &spriteMainCharacter[frame/10];
        SDL_Rect * currentFramePhoenix = &spriteOfPhoenix[framePhoenix /15 ];

        minusScrolling();
        renderLayers();

                
        // FOR FIREBALL ---------------------------------------------------------------------------------------------------------------------------------------
        
        SDL_Rect  * currentFireball = & spriteOfFireball [frameFireball / 10 ];

            //INSIDE RENDERFIREBALL FUNCTION, IT HAS TO CHECK THE STATE OF FIREBALL IS BE CREATED  OR NOT --------------------------------- 
            gFireball.render(gFireball.getXPos() , gFireball.getYPos() , gRenderer, currentFireball);
            gFireball.autoMove();
            
        // FOR FIREBALL -------------------------------------------------------------- 
        
        // gPhoenix.movingCharacter();
        gPhoenix.render(0 , DEFAULT_PHOENIX_Y  ,gRenderer , currentFramePhoenix);
        
        // FOR MAIN CHARACTER ----------------------------------------------------------------------------------------------------------------------------------
        gTestCharacter.getHitFromFireball(&gFireball);
        gTestCharacter.movingCharacter();
        gTestCharacter.showCharacter(gRenderer,frame,frameIdle,frameIdleLeft,frameAttack,frameAttack2,frameJumpUp ,frameJumpDown, frameDead);

        loadFirstLayer();
        
        gEnemy.autoMove(frameEnemyDead);
        gEnemy.ShowEnemie(gRenderer,frameWalkingEnemie,frameEnemyDead );
        gEnemy.handleHitFromCharacter(&gTestCharacter,frameAttack );

        frameProcessing();
        SDL_RenderPresent(gRenderer);  
        int realImpTime = fpsTimer.getTicks();
        int timeOneFrame = (1000/FRAME_PER_SECOND ); // ms 
        if ( realImpTime < timeOneFrame ){
            int delayTime = timeOneFrame -  realImpTime ; 
            if ( delayTime > 0 )
            SDL_Delay(delayTime);
        }
    }
  
    close();
    return 0;
}