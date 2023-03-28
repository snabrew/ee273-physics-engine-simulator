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

	// if sphere is toucnhing ground detection
	float d = position.getY() - ground;
	return(d <= radius);
}

bool sphere::detect(sphere& s2) {
	// if spheres are touching detection
	Vector3 s2Pos = s2.getPosition();
	float r2 = s2.getRadius();
	Vector3 d = position - s2Pos;
	float d_mag = d.magnitude();
	return (d_mag <= radius + r2);
}


void sphere::res(Vector3 ground_normal) {
	
	/* splits into parallel and perpindicular components 
	and	changes perpindulcar component reduces perpindicular component */

	Vector3 s_velPerp = velocity; 
	s_velPerp.dot(ground_normal);	// vertical velocity 
	Vector3 s_velParallel = velocity - s_velPerp; // horizontal velocity
	s_velPerp = s_velPerp * (-0.5f); // energy loss constant
	Vector3 s_set = s_velPerp + s_velParallel;
	velocity = s_set;	
}

void sphere::res(sphere& s2) {
		
    /* Calculate the unit vector perpindicular to surface 
	that is at the point between the two spheres */
	Vector3 unit_vec = s2.getPosition() - position;
	unit_vec.normalise();

    // Calculate the relative velocity between the two spheres
    Vector3 vel_between = s2.getVelocity() - velocity;

    /*Calculate the velocity component along the collision normal vector 
	which is the perpindicular velocity */ 
    float vel_perp = vel_between.dot(unit_vec);

    // If the spheres are moving away from each other there is no collision to resolve
    if (vel_perp > 0) {
       return;
    }


	/*  calculate amount of energy needed to stop spheres and 
	then apply velocity in opposite direction (helped by chatGPT) */
	
	float mass_sum = mass + s2.getMass();
	float inverse_mass_sum = 1 / s2.getMass();
    float impulse_mag = ( - (1.0f + 0.5f) * vel_perp) / inverse_mass_sum;
	//0.5 is energy loss (coefficeient of restitution)
	

    // update spheres velocity
    Vector3 impulse = unit_vec * impulse_mag; // impulse as a vector using normal
	Vector3 v1_lost = impulse / mass;	// impulse formula
    velocity -= v1_lost;	// being slown down by other sphere
	Vector3 v2_gained = impulse / s2.getMass(); //// impulse formula
    s2.setVelocity(s2.getVelocity() + v2_gained); // being pushed 
}

void sphere::integrate(float time) {

	// if on floor stop accelerating downwards
	if ((position.getY() - radius) <= 0.0f) {
		acceleration.setY(0);
	}
	// gravity 
	else {
		acceleration.setY(-9.81f);	
	}

	// eulers method

	force = acceleration * mass;
	acceleration = force / mass;
	Vector3 at = acceleration * time;
	velocity += at;
	Vector3 vt = this->velocity * time;
	position += vt;
	force = Vector3(0, 0, 0);
}