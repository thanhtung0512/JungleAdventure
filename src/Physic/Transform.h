#ifndef TRANSFORM_H
#define TRANSFORM_H

#include"Vector2D.h"
class Transform{
    private :
        float X,Y;

    public :
        Transform(float x=0, float y=0){
           X=x;
           Y=y; 
        }       
        ~Transform(){}
        void Log ( std::string v){
            std::cout<<v.c_str()<<":(X,Y)=("<<X<<","<<Y<<")";
        }
    public  :
        inline void translate_X(float x){X+=x;}
        inline void translate_Y(float y){Y+=y;}
        inline void translate_vector ( Vector2D v){
            X+=v.X;
            Y+=v.Y;
        } 
};



#endif