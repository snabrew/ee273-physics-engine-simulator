#pragma once
#include "Vector3.h"
#include "point_mass.h"

class sphere : point_mass {
private:
	float radius;
public:
	/* constructor */
	sphere(Vector3 p, Vector3 v, Vector3 a, float m, float r);

    /* setters and getters */
	void setRadius(float r);
    float getRadius();
};