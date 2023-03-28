#include "Vector3.h"
#include "point_mass.h"
	
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
void point_mass::setForce(Vector3 f) {
	this->force = f;
}
Vector3 point_mass::getForce() {
	return force;
}
void point_mass::setMass(float m) {
	this->mass = m;
}
float point_mass::getMass() {
	return mass;
}

/* eulers method integration */
void point_mass::integrate(float time) {
	if ((position.getY()) <= 0.0f) {
		acceleration.setY(0);
	}
	else {
		acceleration.setY(-9.81f);
	}
	Vector3 gravity = Vector3(0, -9.81f, 0);
	force = gravity * mass;
	acceleration = force / mass;
	Vector3 at = acceleration * time;
	velocity += at;
	Vector3 vt = velocity * time;
	position += vt;
	force = Vector3(0, 0, 0);
}