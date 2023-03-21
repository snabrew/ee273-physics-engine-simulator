#include "Rotation.hpp"


Rot3::Rot3() : x(0),y(0),z(0) {}

Rot3::Rot3(float x,float y,float z) : x(x),y(y),z(z) {}

void Rot3::setX(float x){
    if (valid(x) == 1){
        this-> x = x;
        std::cout << "small" << std::endl;
    }
    else if(valid(x) == 2){
        this -> x = conv(x);
        std::cout << "large" << std::endl;
    }
    else{
        std::cout << "error entering angle" << x;
    }
}

float Rot3::getX(){
    return x;
}

void Rot3::setY(float y){
    if (valid(y) == 1){
    this-> y = y;
    }
    else if(valid(y) == 2){
        this -> y = conv(y);
    }
    else{
        std::cout << "error entering angle" << y;
    }
}


float Rot3::getY(){
    return y;
}

void Rot3::setZ(float z){
    if (valid(z) == 1){
    this-> z = z;
    }
    else if(valid(z) == 2){
        this -> z = conv(z);
    }
    else{
        std::cout << "error entering angle" << z;
    }
}

float Rot3::getZ(){
    return z;
}
float Rot3::conv(float arg){
    float rad(0);
    rad  = (pi * arg)/180;
    return rad;
}

int Rot3::valid(float arg){
    if (arg >= 0 && arg < 2*pi){
        std::cout << "small" << std::endl;
        return 1;
    }
    
    else if( conv(arg) >= 0 && conv(arg) < 2*pi){
        std::cout << "error entering angle" << x;
        return 2;
    }
    
    
    return 0;
}
/*
Rot3 operator+(Rot3& other){
    
}
void operator+=(Rot3& other){
    
}
Rot3 operator-(Rot3& other){
    
}
void operator-=(Rot3& other){
    
}
*/
