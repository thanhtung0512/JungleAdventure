#include"needed.h" 
#include"Game.h"


int  Game:: playGame(){
    
    srand(time(0));
    static SDL_Renderer * mRenderer = NULL;
    static SDL_Window *mWindow = NULL;
    static LTexture splashScreen ;
    static Fireball phoenixFireball ;
    if( loadAllNeeded( &splashScreen , &phoenixFireball , &mRenderer, &mWindow )==false ){
        return -1;
    }
    static Point gamePoint(&mRenderer) ;
    static LTexture gameScore ;
    static LTexture textNumsOfKilledEnemyIs; 
    static LTexture numsKilledEnemy ;
    static Character mainCharacter(mRenderer);
    mainCharacter.loadRunningSound();
    static gameMenu myMenu ( mRenderer  );
    static Background  scrollingBackground (mRenderer);
    static Boss boss(&mRenderer);
    static Phoenix phoenix(&mRenderer);
    static int bossPlaySound  = 1 ;
    static int continueToPlay = 0 ;
    static bool stop = false;
    static int recentPointVisible = 0 ;


    myMenu.menuControl(mRenderer,gEvent,button,gFont,mWindow,&stop,&returnGame, &continueToPlay );
    if ( continueToPlay ) waitUntilKeyPressed(&splashScreen,&mRenderer); 
    playBGMusic(&mainCharacter);
    
    while (stop == false  || returnGame == true ){  
        fpsTimer.start(); 
        if (mainCharacter.getStatus()!=DEAD_CHARACTER ){
            if ( returnGame ==  true ){
                returnGame = false ; 
                playBGMusic(&mainCharacter);
            }
            while ( SDL_PollEvent(&gEvent)){
                if(gEvent.type == SDL_QUIT ){
                    stop=true ;
                    returnGame= false ;
                }
                mainCharacter.handleInputAction(gEvent,mRenderer,sword,sword_2 );
            }
            SDL_SetRenderDrawColor(mRenderer,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color);
            SDL_RenderClear(mRenderer);
            scrollingBackground.manageBGWhenRunning(&boss , mRenderer, &point);
        
            if( point >= TO_RENDER_BOSS_POINT ){
                for (int i=1;i<=NUMS_OF_SKY_FIREBALL;i++){
                    gSkyFireball[i].manageFireball(mRenderer,&point,&mainCharacter);
                }
                if ( bossPlaySound == 1 ){
                    bossPlaySound = 0 ;
                    boss.playSound();
                }
            }

            for (int i=0;i<NUMS_OF_ENEMY;i++)
            {
                gEnemy[i].autoMove();
                gEnemy[i].ShowEnemie(mRenderer);
                gEnemy[i].checkCollision(&phoenix,&phoenixFireball,&mainCharacter);
                gEnemy[i].handleHitFromCharacter(&mainCharacter,mainCharacter.getFrameAttack(),mainCharacter.getFrameAttack2());   
            }

            phoenixFireball.manageFireball(mRenderer);
            phoenix.renderPhoenix(mRenderer);
            // textNumsOfKilledEnemyIs.showTextt(SCREEN_WIDTH - 300 , SCREEN_HEIGHT - 20  ,"NUMS OF KILLED ENEMY",mRenderer,12);
            int numsKilledEnemyy = mainCharacter.getNumsKilledEnemy();
            // numsKilledEnemy.showText(SCREEN_WIDTH - 50 , SCREEN_HEIGHT - 20, &numsKilledEnemyy , mRenderer,12);
            
            gamePoint.showPointInGame(&numsKilledEnemyy,&point,&recentPointVisible,&mRenderer,&mainCharacter);
            mainCharacter.manageCharacter(mRenderer,&phoenixFireball,&point,&recentPointVisible );
        }
        // else if  (mainCharacter.getStatus() == DEAD_CHARACTER ){
        //         pauseAllMusic(&boss, &mainCharacter);
        //         isUpdateScore=false ;
        //         myMenu.renderWhenDead(mRenderer);
        //         gamePoint.showText(SCORE_X ,SCORE_Y ,&point,mRenderer,28);
        //         while( SDL_PollEvent (&gEvent) ){
        //             if ( gEvent.type == SDL_MOUSEBUTTONDOWN ){
        //                 int x = gEvent.button.x;
        //                 int y = gEvent.button.y;
        //                 if ( isOnReturnGameArea(x,y) ){
        //                     bossPlaySound=1; 
        //                     returnGame =  true ;
        //                     resetGame(&boss,&phoenix,&mainCharacter,&phoenixFireball);
        //                 }
        //                 else if ( isOnExitArea(x,y) ){
        //                     stop= true ;
        //                     returnGame= false;
        //                 }
        //             }
        //              if  ( gEvent.type == SDL_QUIT ){
        //                 stop= true ;
        //                 returnGame = false;
        //             }
        //         }
        // }
        pointManage();
        SDL_RenderPresent(mRenderer); 
        fpsManage();
    }
    
    close(&mRenderer,&mWindow);
    return 0;

}

void Game ::  fpsManage(){
    int *  realImpTime = new int (fpsTimer.getTicks());
        int *timeOneFrame = new int  (1000/FRAME_PER_SECOND ); // ms 
        if ( *realImpTime < *timeOneFrame )
        {
            int * delayTime = new int ( * timeOneFrame - *realImpTime ); 
            if ( * delayTime > 0 )
            {
                SDL_Delay( * delayTime );
            }
            delete delayTime ; 
        }
        
    delete timeOneFrame ; 
    delete realImpTime;
}

void Game:: resetGame (Boss * boss,Phoenix * phoenix , Character * mainCharacter , Fireball * phoenixFireball ){
    int first = ENEMY_COORDINATION_X + rand() % 200 ;
    for (int i=0;i<3;i++){
        gEnemy[i].setCoordinate( first ,  ENEMY_COORDINATION_Y );
        first += 400;
    }
    mainCharacter->resetCharacter();
    boss->resetBoss();
    phoenix->resetPhoenix();
    phoenixFireball->resetFireball();
    for(int i=1;i<=NUMS_OF_SKY_FIREBALL;i++){
        gSkyFireball[i].resetSkyFireball();
    }
    for (int i=1;i<=NUMS_OF_ENEMY;i++){
        gEnemy[i].resetEnemy();
    }
    point=0;
    isUpdateScore=true ;
}


bool Game:: loadSkyFireball( SDL_Renderer ** mRenderer  ){
    for (int i=1;i<=NUMS_OF_SKY_FIREBALL;i++){
        if ( gSkyFireball[i].loadFireball(*mRenderer)== false ){
        std:: cout<<"Could not load sky fireball "<<SDL_GetError()<<std::endl;
        return false ;
        }
    }
    return true ;
}




bool Game:: loadFireball(Fireball *phoenixFireball, SDL_Renderer ** mRenderer ){
    if ( phoenixFireball->loadFireball(*mRenderer)== false ){
        std::cout<<"Could not load Fireball "<<std::endl;
        return false ;
    }
    return true ;
}


bool Game:: initData(SDL_Renderer ** mRenderer , SDL_Window ** mWindow ){
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
    *mWindow = SDL_CreateWindow ("The Jungle Adventure _ Thanh Tung UET   ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (*mWindow!=NULL){
        *mRenderer=SDL_CreateRenderer ( *mWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if ( *mRenderer == NULL){
            success=0;
        }else {
            SDL_SetRenderDrawColor(*mRenderer,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color);
            int imgFlags = IMG_INIT_PNG;
            if ( !(IMG_Init(imgFlags) && imgFlags)){
                success =0;
            }
        }
    }

    else success = 0;
    return success;
}




bool Game:: loadAudio(){
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



void Game:: close (SDL_Renderer ** mRenderer,SDL_Window ** mWindow){
    SDL_DestroyRenderer(*mRenderer);
    TTF_CloseFont ( gFont );
    gFont = NULL;
    *mRenderer=NULL;
    SDL_DestroyWindow(*mWindow);
    *mWindow=NULL;
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}


bool Game:: loadAllNeeded (LTexture * splashScreen,Fireball* phoenixFireball, SDL_Renderer ** mRenderer,SDL_Window ** mWindow ){
    
    if(initData(mRenderer, mWindow)==false){
       return false;
    }


    if(loadAudio()== false ){
        return false ;
    }
    
    if ( loadFireball(phoenixFireball,mRenderer)== false ) return false;
    if ( loadSkyFireball(mRenderer)== false ) return false ;
    loadSplashScreen( splashScreen,mRenderer);
    for (int i=0;i<NUMS_OF_ENEMY;i++){
        gEnemy[i].loadEnemy(mRenderer);
    }

    for (int i=0;i<3;i++){
        gEnemy[i].setCoordinate(firstCoordinate,ENEMY_COORDINATION_Y );
        firstCoordinate += 800 ;
    }
    return true; 
}


void Game:: playBGMusic (Character * mainCharacter ){
    Mix_PlayMusic(music,-1);
    Mix_PlayMusic(phoenixWing, -1 );
    mainCharacter->playRunningSound();
}

Game :: ~Game(){

}

Game:: Game (){
    firstCoordinate  = ENEMY_COORDINATION_X ;
    originXFireball = 0 , originYFireball  = 0 ;
    countFireball = 0;
    NOW = SDL_GetPerformanceCounter();
    LAST = 0;
    deltaTime = 0;
    point=0 ; 
    returnGame = false;
    currentTime = 0 ; 
    isUpdateScore = true ;
    music = NULL;
    phoenixWing = NULL;
    sword = NULL;
    sword_2 = NULL;
    fireball = NULL;
    button = NULL ;
    
}

void Game ::  pointManage(){
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

}


bool Game:: isOnReturnGameArea ( const int& x , const int& y ){
    return x>= 334 && x<= 400 && y>=518 && y<=579;
}

bool Game :: isOnExitArea( const int &x, const int & y) {
    return x>=471 && x<= 539 && y>=515 && y<= 578;
}

void Game ::  pauseAllMusic (Boss * boss, Character * mainCharacter  ){
    boss->pauseSound();
    mainCharacter->pauseRunningSound();
}

void Game ::  waitUntilKeyPressed (LTexture  *  splashScreen, SDL_Renderer ** mRenderer){
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        splashScreen->render(0,0,*mRenderer,NULL);
        SDL_RenderPresent(*mRenderer);
        SDL_Delay(100);
    }
}

void Game ::  loadSplashScreen (LTexture * splashScreen, SDL_Renderer ** mRenderer){
    splashScreen->loadFromFile("img/bg/waitKey.jpg",*mRenderer);
}