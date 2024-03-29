#include "Vector3.h"
#include "point_mass.h"
#include "cube.hpp"


cube::cube() : point_mass(), radius(0.0f) {
    setreference();
}

cube::cube(Vector3 p, Vector3 v, Vector3 a, float m, float r) :
   point_mass(p, v, a, m), radius(r) {}

void cube::setRadius(float r) {
    this->radius = r;
    length = r/1.732;
    
}

float cube::getRadius() {
    return radius;
}

Vector3 cube::drawposition (){
    const int test1 = 1;
    const int test2 = 1;
    
    Vector3 radiusv {};
    Vector3 dpos {};
    switch (test1){
            /* one of these should work if not then choose 3 4 5 to show which axis is y or z  and let me know*/
        case 1:
            radiusv = Vector3(length/2,length/2,-length/2);
            break;
        case 2:
            radiusv = Vector3(length/2,-length/2,length/2);
            break;
            /* chcks for which axis is x y and z.*/
        case 3:
            radiusv = Vector3(1,0,0);
            break;
        case 4:
            radiusv = Vector3(0,1,0);
            break;
        case 5:
            radiusv = Vector3(0,0,1);
            break;
            
            
    }
    switch (test2){
            /* test to see whether if were wrong in adding or subtracting. (pretty sure its subtracting.)*/
        case 1:
            dpos = position - radiusv;
            break;
            
        case 2:
            dpos = position + radiusv;
            break;
    }
    //GLUT draws a cube from the bottm left corner, where the code assumes position is in the center.
    // this affects position before the simulation is run so the user will not see this.
    
    return dpos; //returns a vector that replaces position when drawn.
}

void cube::setreference(){
    const Vector3 ndefinition[6] = {Vector3(1,0,0),Vector3(-1,0,0),Vector3(0,1,0),Vector3(0,-1,0),Vector3(0,0,1),Vector3(0,0,-1)}; // normals of a cube defined
    
    for (int i = 0; i < 6; i++){
        normals.push_back(ndefinition[i]);
    }
    
}

bool cube::detect(float ground) {

    // if cube is touching ground detection
    //since orientation will always in -z normal, so use radius from -z normal (0,0,-1)
    float d = position.getY() - ground;
    return(d <= length/2);
}

bool cube::detect(sphere& s2) {
    // if cubes are touching detection
    Vector3 s2Pos = s2.getPosition();
    float r2 = s2.getRadius();
    Vector3 d = position - s2Pos;
    
    Vector3 d_dir = d;
    d_dir.normalise();
    
    float colr = 0; // collision radius
    
    for (int i = 0; i < 6; i++){
        float ndot = normals[i].dot(d_dir);
        if (ndot >= 0.5) {
            colr = length/2;
        }
        else if (ndot < 0.5){
            colr = radius;
        }
        // checking whether direction of  distance vector is along the normal or the vertices to determine the collision radius so that it is represented as a sphere
    }
    
    
    float d_mag = d.magnitude();
    return (d_mag <= colr + r2);
}

bool cube::detect(cube& c2) {
    // if cubes are touching detection
    Vector3 c2Pos = c2.getPosition();
    float r2 = c2.getRadius();
    Vector3 d = position - c2Pos;
    
    Vector3 d_dir = d;
    d_dir.normalise();
    
    float colr = 0; // collision radius
    
    for (int i = 0; i < 6; i++){
        float ndot = normals[i].dot(d_dir);
        if (ndot >= 0.5) {
            colr = length/2;
        }
        else if (ndot < 0.5){
            colr = radius;
        }
    }
    
    float d_mag = d.magnitude();
    return (d_mag <= colr + r2);
}


void cube::res(Vector3 ground_normal) {
    
    /* splits into parallel and perpindicular components
    and    changes perpindulcar component reduces perpindicular component */

    Vector3 velPerp = velocity;
    velPerp.dot(ground_normal);    // vertical velocity
    Vector3 s_velParallel = velocity - velPerp; // horizontal velocity
    velPerp = velPerp * (-0.5f); // energy loss constant
    Vector3 set = velPerp + s_velParallel;
    velocity = set;
}

void cube::res(sphere& s2) {
    
    Vector3 unit_vec = s2.getPosition() - position;
    unit_vec.normalise(); // unit vector at point of collision
    Vector3 velBetween = s2.getVelocity() - velocity; // calculate velocity between two cubes
    float vel = velBetween.dot(unit_vec); // mag of velocity perpindicular to collision unit vector
    
    if (vel > 0) {
        return;    // cubes are moving away no collisiomn
    }
    
    float impulse_mag =  -(0.5f * vel) * s2.getMass(); //0.5 is energy loss p=mv
    
    // update cubes velocity using impulse
    Vector3 impulse = unit_vec * impulse_mag; // impulse as a vector using unit vector
    Vector3 v1_lost = impulse / mass;    // p=mv
    velocity -= v1_lost; // being slowed down by other cube
    Vector3 v2_gained = impulse / s2.getMass(); // p=mv
    s2.setVelocity(s2.getVelocity() + v2_gained); // being pushed
}

void cube::res(cube& c2) {

    Vector3 unit_vec = c2.getPosition() - position;
    unit_vec.normalise(); // unit vector at point of collision
    Vector3 velBetween = c2.getVelocity() - velocity; // calculate velocity between two cubes
    float vel = velBetween.dot(unit_vec); // mag of velocity perpindicular to collision unit vector

    if (vel > 0) {
       return;    // cubes are moving away no collisiomn
    }

    float impulse_mag =  -(0.5f * vel) * c2.getMass(); //0.5 is energy loss p=mv

    // update cubes velocity using impulse
    Vector3 impulse = unit_vec * impulse_mag; // impulse as a vector using unit vector
    Vector3 v1_lost = impulse / mass;    // p=mv
    velocity -= v1_lost; // being slowed down by other cube
    Vector3 v2_gained = impulse / c2.getMass(); // p=mv
    c2.setVelocity(c2.getVelocity() + v2_gained); // being pushed
}

void cube::integrate(float time) {

    // if on floor stop accelerating downwards
    if ((position.getY() - radius) <= 0.0f) {
        acceleration.setY(0);
    }
    // gravity
    else {
        acceleration.setY(-9.81f);
    }

    // eulers method

    Vector3 at = acceleration * time;
    velocity += at;
    Vector3 vt = velocity * time;
    position += vt;

}

