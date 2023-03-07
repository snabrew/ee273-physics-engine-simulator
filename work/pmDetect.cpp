#include <iostream>
#include "Vector3.h"
#include "point_mass.h"
#include "pmDetect.h"

using namespace std;


pmDetect::pmDetect() {}

bool pmDetect::detect(point_mass& pm1, point_mass& pm2) {
	Vector3 pos1 = pm1.getPosition();
	Vector3 pos2 = pm2.getPosition();
	return (pos1.getX() == pos2.getX()) && (pos1.getY() == pos2.getY()) 
			&& (pos1.getZ() == pos2.getZ());
}

bool pmDetect::detect(point_mass& pm, float ground) {
	Vector3 pos = pm.getPosition();
	return pos.getY() == ground;
}
