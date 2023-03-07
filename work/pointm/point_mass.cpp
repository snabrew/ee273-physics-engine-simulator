#include "Vector3.h"
#include "point_mass.h"
#include <iostream>

	
using namespace std;

/* constructors */
point_mass::point_mass(Vector3 p, Vector3 v, Vector3 a, float m) :
	position(p), velocity(v), acceleration(a), mass(m) {}


/* setters and getters */
void point_mass::setPosition(Vector3 p) {
	this->position = p;
}
Vector3 point_mass::getPosition() {
	return position;
}
void point_mass::setVelocity(Vector3 v) {
	this->velocity = v;
}
Vector3 point_mass::getVelocity() {
	return velocity;
}
void point_mass::setAcceleration(Vector3 a) {
	this->acceleration = a;
}
Vector3 point_mass::getAcceleration() {
	return acceleration;
}
void point_mass::setMass(float m) {
	this->mass = m;
}
float point_mass::getMass() {
	return mass;
}

/* sets force to 0 */

/* eulers method integration */
void point_mass::integrate(float time) {
	
	Vector3 gravity = Vector3(0, -9.81, 0);
	force = gravity * mass;
	acceleration = force / mass;
	Vector3 at = acceleration * time;
	velocity += at;
	Vector3 vt = velocity * time;
	position += vt;
	force = Vector3(0, 0, 0);
}


int main() {
	/* simulating particle and gravity */

	// create a particle
	point_mass p(Vector3(0, 1, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0);

	// set the simulation parameters
	float timeStep = 0.01;
	float endTime = 10.0;

	// simulate the particle
	for (float t = 0; t < endTime; t += timeStep) {
		p.integrate(timeStep);

		// print the particle's position
		cout << "t = " << t << ", position = (" << p.getPosition().getX()
			<< ", " << p.getPosition().getY() << ", " << p.getPosition().getZ() << ")" << endl;
	}

	return 0;
}
