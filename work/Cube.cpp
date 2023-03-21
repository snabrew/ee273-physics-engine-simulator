#include "Cube.hpp"


Cube::Cube(Vector3 p, Vector3 v, Vector3 a, float m, float r)
: point_mass::point_mass(p,v,a,m),size(r){}


void Cube::setsize(float s){
    this -> size = s;
    length = size / 1.732;
}

float Cube::getsize(){
    return size;
}

float Cube::getlength(){
    return length;
}

