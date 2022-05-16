#include"needed.h"
#include "LTexture.h"

LTexture::LTexture(){
    mTexture = NULL;
    mWidth  = 0;
    mHeight = 0;
    arcadeFont = nullptr;
    
}

LTexture ::~LTexture(){
    free();
}

bool LTexture :: loadFromFile(std::string path ,SDL_Renderer * screen ){
    free();
    SDL_Texture * newTexture = NULL;
    SDL_Surface * tSurface = IMG_Load(path.c_str());
    if (tSurface != NULL) {
        //color key image 
        SDL_SetColorKey( tSurface, SDL_TRUE, SDL_MapRGB( tSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B ) );
        newTexture= SDL_CreateTextureFromSurface(screen,tSurface);
        if ( newTexture==NULL){
            std::cout<<"Could not load texture from surface"<<SDL_GetError()<<std::endl;

        }
        else {
            mWidth = tSurface->w;
            mHeight = tSurface->h;
        }
        SDL_FreeSurface(tSurface);
    }
    else {
        std::cout<<"Could not intialize Surface "<<std::endl;
    }
    mTexture = newTexture;
    if (mTexture != NULL) return true;
    else return false;

}

bool LTexture :: loadFromRenderedText ( std::string textureText, SDL_Color textColor , SDL_Renderer * screen , const int sizeText   ){
    // render text surface 
    this->arcadeFont = TTF_OpenFont ("fonts/ARCADE_R.ttf",sizeText);
    SDL_Surface  * textSurface = TTF_RenderText_Solid( arcadeFont ,textureText.c_str(), textColor);
    if ( textSurface == NULL ){
        std::cout<<"Could not load text surface "<< SDL_GetError()<<std::endl;
    }
    else {
        mTexture = SDL_CreateTextureFromSurface(screen, textSurface);
        if(mTexture == NULL){
            std::cout<<"Could not create texture from rendered text "<<SDL_GetError()<<std::endl;
        }
        else {
            // get dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface( textSurface);
    }
    return mTexture != NULL;

}

void LTexture :: free(){
    if ( mTexture != NULL ){
        SDL_DestroyTexture ( mTexture);
        mWidth=0;
        mHeight=0;
        mTexture=NULL;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
    SDL_SetTextureColorMod(mTexture,red,green,blue);
}

void LTexture::render(int x, int y , SDL_Renderer * screen , SDL_Rect* clip ,double angle , SDL_Point * center , SDL_RendererFlip flip  ){
    //set rendering space and render to screen 
    SDL_Rect renderQuad ={x,y,mWidth,mHeight};
    //set clip rendering dimensions 
    if (clip != NULL){
        renderQuad.w= clip->w;
        renderQuad.h= clip->h;
    }
    if ( SDL_RenderCopyEx(screen,mTexture,clip,&renderQuad,angle,center,flip) !=0 ){
        std::cout<<"Could not RenderCopy "<<SDL_GetError()<<std::endl;
    }
}

int LTexture :: getWidth(){
    return mWidth;
}

int LTexture::getHeight(){
    return mHeight;
}

void LTexture ::  showText(int x, int y ,const int * point , SDL_Renderer * screen, int textSize){
    loadFromRenderedText(std::to_string(*point),{84,153,32},screen, textSize );
    render(x,y,screen,NULL);
}

void LTexture ::  showTextt(int x, int y ,const std::string inpText , SDL_Renderer * screen, int textSize){
    loadFromRenderedText(inpText,{84,153,32},screen , textSize );
    render(x,y,screen,NULL);
}

void LTexture :: loadFont (){
    this->arcadeFont = TTF_OpenFont ("fonts/ARCADE_R.ttf",28);
}