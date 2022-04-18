#ifndef needed_h
#define needed_h

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include<ctime>
#include<cstdlib>

#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <string>
#include <string.h>
#include <bits/stdc++.h>

#include <SDL_image.h>
#include "Physic/Vector2D.h"
#include "Physic/Transform.h"
#include "LTexture.h"
#include "Dot.h"
#include "Character.h"
#include "Fireball.h"
#include "impTimer.h" 
#include"Phoenix.h"
#include "Enemy.h"
#include "Character.h"
#include"GameMenu.h"
#include"Boss.h"
#include"SkyFireball.h"

#define SCREEN_WIDTH 928
#define SCREEN_HEIGHT 793

#define SCREEN_BPP 32

#define COLOR_KEY_R 113
#define COLOR_KEY_G 102
#define COLOR_KEY_B 79

#define MAIN_CHAR_FRAME_RUN 8
#define MAIN_CHAR_WIDTH 224
#define MAIN_CHAR_HEIGHT 112

#define DEFAULT_PHOENIX_Y 600
#define DEFAULT_MAIN_CHARACTER_Y 620

#define Render_Draw_Color 0xFF

#define SPRITE_MAIN_WITDH 96
#define SPRITE_MAIN_HEIGHT 64

#define PHOENIX_FRAME_WIDTH 228
#define PHOENIX_FRAME_HEIGHT 189

#define FIREBALL_WIDTH 68 
#define NUMBER_OF_FIREBALLS 100

#define FRAME_PER_SECOND 90

#define RUN_RIGHT 1
#define RUN_LEFT 0
#define IDLE -1
#define IDLE_LEFT -2 
#define ATTACK 4 
#define IDLE_CLIPS 8
#define ATTACK_2 -3
#define JUMP_UP 10
#define JUMP_DOWN 13  
#define ON_GROUND 11 
#define DEAD_CHARACTER  -9 


// CHARACTER FRAME DEFINE 
#define FRAME_OF_RUNNING 8 
#define FRAME_OF_IDLE 8 
#define FRAME_OF_ATTACK 18 
#define FRAME_OF_ATTACK_2 28
#define FRAME_JUMP_UP 7
#define FRAME_JUMP_DOWN 13
#define FRAME_DEAD 13

#define MAX_HEIGHT_JUMP DEFAULT_MAIN_CHARACTER_Y  - 135

#define TIME_TO_NEXT_FRAME_RUNNING_CHARACTER 6 
#define TIME_TO_NEXT_FRAME_IDLE 15 
#define TIME_TO_NEXT_FRAME_ATTACK 4
#define TIME_TO_NEXT_FRAME_ATTACK_2 3
#define TIME_TO_NEXT_FRAME_JUMP_UP 7 
#define TIME_TO_NEXT_FRAME_JUMP_DOWN 13 
#define TIME_TO_NEXT_FRAME_DEAD 13
#define NUMS_OF_SKY_FIREBALL 7
#define NUMS_OF_ENEMY 3

#define LEFT_LIMIT_X 0 

///////////////////////////////

#define ENEMY_COORDINATION_X  (double)SCREEN_WIDTH - 130
#define ENEMY_COORDINATION_Y  (double )DEFAULT_MAIN_CHARACTER_Y+70 

static SDL_Window *gWindow = NULL;
static SDL_Renderer *gRenderer = NULL;
static SDL_Event gEvent;
static SDL_Texture *gCurrentImage = NULL;

static TTF_Font *gFont = NULL;

static LTexture bgl[13];
static LTexture gBackgroundTexture;
static LTexture gScore;
static LTexture gDotTexture;


static Phoenix gPhoenix;

static Character gMainCharacterTexture;
static Character gTestCharacter;

 

static SDL_Rect spriteMainCharacter[9];
static SDL_Rect spriteOfPhoenix [50];


static double scrollingOffset[14];

static Fireball gFireball  ; 

static Mix_Chunk *chunk = NULL;
static Mix_Music *music = NULL;
static Mix_Music *phoenixWing = NULL;
static Mix_Chunk *sword = NULL;
static Mix_Chunk *sword_2 = NULL;
static Mix_Chunk *fireball = NULL;
static Mix_Chunk * button = NULL ;

static gameMenu gGameMenu ; 
static impTimer fpsTimer ; 

static Boss gBoss ; 
static SkyFireball gSkyFireball[11];

static int originXFireball = 0 , originYFireball  = 0 ;
static int countFireball = 0;

static Uint64 NOW = SDL_GetPerformanceCounter();
static Uint64 LAST = 0;
static double deltaTime = 0;

static  int point=0 ; 
static bool returnGame = false;
static double  currentTime = 0 ; 

static bool isUpdateScore = true ;


// static Enemy gEnemy ; 



#endif