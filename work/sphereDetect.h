#pragma once
#include "sphere.h"
#include "Vector3.h"

class sphereDetect {
public:
	/* constructor */
	sphereDetect();

	/* collision between two spheres */
	bool detect(sphere& s1, sphere& s2);
	bool detect(sphere& s, float ground);
};