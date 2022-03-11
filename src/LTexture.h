#ifndef LTexture_h
#define LTexture_h
#include"needed.h"
class LTexture {
    public :
        LTexture();
        ~LTexture();
        //load img from specified path
        bool loadFromFile ( std ::string path,SDL_Renderer * screen);

        // create image form font string 
         bool loadFromRenderedText ( std::string textureText, SDL_Color textColor,TTF_Font * des, SDL_Renderer * screen  );
        
        //deallocates textures
        void free();

        // set color modulation
        void setColor (Uint8 red, Uint8 green, Uint8 blue);

        //render textures at given coordinate
        void render(int x, int y , SDL_Renderer * screen , SDL_Rect* clip ,double angle =0.0, SDL_Point * center = NULL, SDL_RendererFlip flip=SDL_FLIP_NONE);
        
        //get image   (surface ) dimensions 
        int getWidth();
        int getHeight();
        
    protected:
    //actual hardware texture 
    SDL_Texture * mTexture;
    //texture dimension information 
    int mWidth;
    int mHeight;
};
#endif