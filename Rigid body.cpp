

#include "Vector3.hpp"
#include "point_mass.hpp"

Vector3 normal (Vector3 force, Vector3 norm){
    Vector3 uF = force;
    Vector3 un = norm;
    
    uF.normalise();
    un.normalise();
    
    float m = uF.dot(un);
    //normalised dot products are basically cos theta.
    
    return force * m * -1;
}

Vector3 weight ( point_mass* p){
    Vector3 g{0,0,-9.81};
    //assigning gravity, we can change this to mess with gravity? (create a scene class for these numbers maybe?
    return g * (p->getMass()) ;
}

//Vector3 friction ( float coef,Vector3 norm){}

float torque ( Vector3 force, Vector3 r){
    // r is the vector from the center of geometry to the contact point.
    return (force.cross(r)).magnitude();
    
}

