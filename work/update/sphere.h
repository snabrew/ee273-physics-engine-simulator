#pragma once
#include "Vector3.h"
#include "point_mass.h"

class sphere : public point_mass {
private:
	float radius;
public:
	/* constructor */
	sphere(Vector3 p, Vector3 v, Vector3 a, float m, float r);

    /* setters and getters */
	void setRadius(float r);
    float getRadius();

	/* collisions */
	/* detection between sphere and ground */
	bool detect(float ground);
	/* detection between two spheres */
	bool detect(sphere& s2);
	/* resolution between sphere and ground */
	void res(Vector3 ground_normal);
	/* resolution between two spheres */
	void res(sphere& s2);

	/* integrate eulers method */
	void integrate(float time);
};