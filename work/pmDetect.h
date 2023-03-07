#pragma once
#include "Vector3.h"
#include "point_mass.h"

class pmDetect {

public:
	/* constructors */
	pmDetect();

	/* detection between two point masses */
	bool detect(point_mass& pm1, point_mass& pm2);
	/* detection between point mass and plane */
	bool detect(point_mass& pm, float ground);
};