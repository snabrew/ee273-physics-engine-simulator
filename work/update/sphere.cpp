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

bool sphere::detect(float ground) {

	
	float d = this->position.getY() - ground;
	return(d <= this->radius);
}

bool sphere::detect(sphere& s2) {

	Vector3 s2Pos = s2.getPosition();
	float r2 = s2.getRadius();
	Vector3 d = this->position - s2Pos;
	float d_mag = d.magnitude();
	return (d_mag <= this->radius + r2);
}


void sphere::res(Vector3 ground_normal) {

	Vector3 s_velPerp = this->velocity;
	s_velPerp.dot(ground_normal);
	Vector3 s_velParallel = this->velocity - s_velPerp;
	s_velPerp = s_velPerp * (-0.5f); // energy loss constant
	Vector3 s_set = s_velPerp + s_velParallel;
	this->velocity = s_set;
}

void sphere::res(sphere& s2) {

	s2.getRadius();
}

void sphere::integrate(float time) {

	
	if ((position.getY() - radius) <= 0.0f) {
		acceleration.setY(0);
	}
	else {
		acceleration.setY(-9.81f);	
	}
	force = acceleration * mass;
	acceleration = force / mass;
	Vector3 at = acceleration * time;
	velocity += at;
	Vector3 vt = velocity * time;
	position += vt;
	force = Vector3(0, 0, 0);
}