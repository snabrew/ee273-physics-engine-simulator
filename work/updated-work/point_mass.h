#pragma once
#include "Vector3.h"

using namespace std;

/* point mass is the most basic thing that can be simulated it is a point in space*/

class point_mass {

protected:
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	Vector3 force;
	float mass;

public:

	/* constructors */
	point_mass(Vector3 p, Vector3 v, Vector3 a, float m);

	/* setters and getters */
	void setPosition(Vector3 p);
	Vector3 getPosition();
	void setVelocity(Vector3 v);
	Vector3 getVelocity();
	void setAcceleration(Vector3 a);
	Vector3 getAcceleration();
	void setForce(Vector3 f);
	Vector3 getForce();
	void setMass(float m);
	float getMass();
	/* eulers method */
	void integrate(float time);
};