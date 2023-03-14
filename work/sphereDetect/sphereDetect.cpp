#include "Vector3.h"
#include "sphere.h"
#include "sphereDetect.h"
#include "point_mass.h"
#include <iostream>

using namespace std;

sphereDetect::sphereDetect() {}

bool sphereDetect::detect(sphere& s1, sphere& s2) {

	Vector3 s1Pos = s1.getPosition();
	Vector3 s2Pos = s2.getPosition();
	float r1 = s1.getRadius();
	float r2 = s2.getRadius();
	Vector3 d = s1Pos - s2Pos;
	float d_mag = d.magnitude();
	return (d_mag <= r1 + r2);
} 

bool sphereDetect::detect(sphere& s, float ground){

	Vector3 s_pos = s.getPosition();
	float d = s_pos.getY() - ground;
	return(d <= s.getRadius());
}
