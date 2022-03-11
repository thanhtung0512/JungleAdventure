#ifndef needed_h
#define needed_h

#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <string>
#include <string.h>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <SDL_image.h>
#include "Physic/Vector2D.h"
#include "Physic/Transform.h"
#include "LTexture.h"
#include "Dot.h"
#include "Character.h"
#include "Fireball.h"
#include "impTimer.h" 

#include "Enemy.h"

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


static SDL_Window *gWindow = NULL;
static SDL_Renderer *gRenderer = NULL;
static SDL_Event gEvent;
static SDL_Texture *gCurrentImage = NULL;
static TTF_Font *gFont = NULL;

static LTexture bgl[13];
static LTexture gBackgroundTexture;
static LTexture gtextTexture;
static LTexture gDotTexture;
static LTexture gMainMenu ; 

static Character gPhoenix;
static Character gMainCharacterTexture;
static Character gTestCharacter;

 

static SDL_Rect spriteMainCharacter[9];
static SDL_Rect spriteOfPhoenix [50];
static SDL_Rect spriteOfFireball [32];


static double scrollingOffset[14];

static Fireball gFireball  ; 

static Mix_Chunk *chunk = NULL;
static Mix_Music *music = NULL;
static Mix_Music *phoenixWing = NULL;
static Mix_Chunk *sword = NULL;
static Mix_Chunk *sword_2 = NULL;
static Mix_Chunk * fireball = NULL;


static impTimer fpsTimer ; 

static int frameMainRunning = 10, frameIdle = 15, frameIdleLeft = 15;
static int frameAttack = 6, framePhoenix = 15, frameAttack2 = 6, frameFireball = 10 , frameJumpUp = 14, frameJumpDown = 26 , frameDead = 13 ;
static int frameEnemyDead = 10 ;

static int frameWalkingEnemie = 10; 

static int originXFireball = 0 , originYFireball  = 0 ;
static int countFireball = 0;




#endif