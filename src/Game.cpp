#include"needed.h" 
#include"Game.h"


int  Game:: playGame(){
    
    srand(time(0));
    static SDL_Renderer * thisRenderer = NULL;
    static SDL_Window *thisWindow = NULL;
    static LTexture splashScreen ;
    static Fireball phoenixFireball ;
    if( loadAllNeeded( &splashScreen , &phoenixFireball , &thisRenderer, &thisWindow )==false ){
        return -1;
    }

    static LTexture gameScore ;
    static LTexture textNumsOfKilledEnemyIs; 
    static LTexture numsKilledEnemy ;
    static Character mainCharacter(thisRenderer);
    mainCharacter.loadRunningSound();
    static gameMenu myMenu ( thisRenderer  );
    static Background  scrollingBackground (thisRenderer);
    static Boss boss(&thisRenderer);
    static Phoenix phoenix(&thisRenderer);
    static int bossPlaySound  = 1 ;
    static int continueToPlay = 0 ;
    static bool stop = false;
    static int recentPointVisible = 0 ;


    myMenu.menuControl(thisRenderer,gEvent,button,gFont,thisWindow,&stop,&returnGame, &continueToPlay );
    if ( continueToPlay ) waitUntilKeyPressed(&splashScreen,&thisRenderer); 
    playBGMusic(&mainCharacter);
    
    while (stop == false  || returnGame == true ){  
        fpsTimer.start(); 
        SDL_SetRenderDrawColor(thisRenderer,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color);
        SDL_RenderClear(thisRenderer);
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
                mainCharacter.handleInputAction(gEvent,thisRenderer,sword,sword_2 );
            }
            scrollingBackground.manageBGWhenRunning(&boss , thisRenderer, &point);
        
            if( point >= TO_RENDER_BOSS_POINT ){
                for (int i=1;i<=NUMS_OF_SKY_FIREBALL;i++){
                    gSkyFireball[i].manageFireball(thisRenderer,&point,&mainCharacter);
                }
                if ( bossPlaySound == 1 ){
                    bossPlaySound = 0 ;
                    boss.playSound();
                }
            }

            for (int i=0;i<NUMS_OF_ENEMY;i++)
            {
                gEnemy[i].autoMove();
                gEnemy[i].ShowEnemie(thisRenderer);
                gEnemy[i].checkCollision(&phoenix,&phoenixFireball,&mainCharacter);
                gEnemy[i].handleHitFromCharacter(&mainCharacter,mainCharacter.getFrameAttack(),mainCharacter.getFrameAttack2());   
            }

            phoenixFireball.manageFireball(thisRenderer);
            phoenix.renderPhoenix(thisRenderer);
            textNumsOfKilledEnemyIs.showTextt(SCREEN_WIDTH - 300 , SCREEN_HEIGHT - 20  ,"NUMS OF KILLED ENEMY",thisRenderer,12);
            int numsKilledEnemyy = mainCharacter.getNumsKilledEnemy();
            numsKilledEnemy.showText(SCREEN_WIDTH - 50 , SCREEN_HEIGHT - 20, &numsKilledEnemyy , thisRenderer,12);
            mainCharacter.manageCharacter(thisRenderer,&phoenixFireball,&point,&recentPointVisible );
        }
        else if  (mainCharacter.getStatus() == DEAD_CHARACTER ){
                pauseAllMusic(&boss, &mainCharacter);
                isUpdateScore=false ;
                myMenu.renderWhenDead(thisRenderer);
                gameScore.showText(SCORE_X ,SCORE_Y ,&point,thisRenderer,28);
                while( SDL_PollEvent (&gEvent) ){
                    if ( gEvent.type == SDL_MOUSEBUTTONDOWN ){
                        int x = gEvent.button.x;
                        int y = gEvent.button.y;
                        if ( isOnReturnGameArea(x,y) ){
                            bossPlaySound=1; 
                            returnGame =  true ;
                            resetGame(&boss,&phoenix,&mainCharacter,&phoenixFireball);
                        }
                        else if ( isOnExitArea(x,y) ){
                            stop= true ;
                            returnGame= false;
                        }
                    }
                     if  ( gEvent.type == SDL_QUIT ){
                        stop= true ;
                        returnGame = false;
                    }
                }
        }
        pointManage();
        SDL_RenderPresent(thisRenderer); 
        fpsManage();
    }
    
    close(&thisRenderer,&thisWindow);
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
                SDL_Delay( * delayTime);
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


bool Game:: loadSkyFireball( SDL_Renderer ** thisRenderer  ){
    for (int i=1;i<=NUMS_OF_SKY_FIREBALL;i++){
        if ( gSkyFireball[i].loadFireball(*thisRenderer)== false ){
        std:: cout<<"Could not load sky fireball "<<SDL_GetError()<<std::endl;
        return false ;
        }
    }
    return true ;
}




bool Game:: loadFireball(Fireball *phoenixFireball, SDL_Renderer ** thisRenderer ){
    if ( phoenixFireball->loadFireball(*thisRenderer)== false ){
        std::cout<<"Could not load Fireball "<<std::endl;
        return false ;
    }
    return true ;
}


bool Game:: initData(SDL_Renderer ** thisRenderer , SDL_Window ** thisWindow ){
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
    *thisWindow = SDL_CreateWindow ("The Jungle Adventure _ Thanh Tung UET   ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (*thisWindow!=NULL){
        *thisRenderer=SDL_CreateRenderer ( *thisWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if ( *thisRenderer == NULL){
            success=0;
        }else {
            SDL_SetRenderDrawColor(*thisRenderer,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color,Render_Draw_Color);
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



void Game:: close (SDL_Renderer ** thisRenderer,SDL_Window ** thisWindow){
    SDL_DestroyRenderer(*thisRenderer);
    TTF_CloseFont ( gFont );
    gFont = NULL;
    *thisRenderer=NULL;
    SDL_DestroyWindow(*thisWindow);
    *thisWindow=NULL;
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}


bool Game:: loadAllNeeded (LTexture * splashScreen,Fireball* phoenixFireball, SDL_Renderer ** thisRenderer,SDL_Window ** thisWindow ){
    
    if(initData(thisRenderer, thisWindow)==false){
       return false;
    }


    if(loadAudio()== false ){
        return false ;
    }
    
    if ( loadFireball(phoenixFireball,thisRenderer)== false ) return false;
    if ( loadSkyFireball(thisRenderer)== false ) return false ;
    loadSplashScreen( splashScreen,thisRenderer);
    for (int i=0;i<NUMS_OF_ENEMY;i++){
        gEnemy[i].loadEnemy(thisRenderer);
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

void Game ::  waitUntilKeyPressed (LTexture  *  splashScreen, SDL_Renderer ** thisRenderer){
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        splashScreen->render(0,0,*thisRenderer,NULL);
        SDL_RenderPresent(*thisRenderer);
        SDL_Delay(100);
    }
}

void Game ::  loadSplashScreen (LTexture * splashScreen, SDL_Renderer ** thisRenderer){
    splashScreen->loadFromFile("img/bg/waitKey.jpg",*thisRenderer);
}