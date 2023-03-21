#pragma once
#include <iostream>

class Rot3 {

private:
    /* x, y and z coordiantes */
    float x;
    float y;
    float z;
    const float pi = 355/113;
public:
    /* constructors */
    Rot3();
    Rot3(float x, float y, float z);

    /* setters and getters */
    void setX(float x);
    float getX();
    void setY(float y);
    float getY();
    void setZ(float z);
    float getZ();

    /* calculations */
    float conv(float arg);
    int valid(float arg);
    Rot3 operator+(Rot3& other);
    void operator+=(Rot3& other);
    Rot3 operator-(Rot3& other);
    void operator-=(Rot3& other);

};
