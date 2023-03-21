#pragma once
#include "Vector3.hpp"
#include "point_mass.hpp"

class Cube : point_mass {
private:
    float size;
    float length;
    
public:
    /* constructor */
    Cube();
    Cube(Vector3 p, Vector3 v, Vector3 a, float m, float r);

    /* setters and getters */
    void setsize(float r);
    float getsize();
    float getlength();
};
