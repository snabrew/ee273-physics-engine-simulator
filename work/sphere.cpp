#include "Vector3.h"
#include "point_mass.h"
#include "sphere.h"

sphere::sphere(Vector3 p, Vector3 v, Vector3 a, float m, float r) : 
   point_mass(p, v, a, m), radius(r) {}

void sphere::setRadius(float r) {
    this->radius = r;
}
float sphere::getRadius() {
    return radius;
}