#pragma once
#include "cube.h"

struct ground;

class simulation {

private:
	static vector<sphere*> s;
	static vector<cube*> c;
	static ground g;

public:
	/* constructor */
	simulation();
	/* destructor  */
	~simulation();
	/* setters and getters */	
	void addSphere(sphere* s);
	vector<sphere*> getSpheres();
	void addCube(cube* c);
	vector<cube*> getCubes();
	/* simulation functions*/
	static void drawPlane(); // draw ground
	static void collisions(sphere*& s1, sphere*& s2); // collisions for spheres
	static void collisions(cube*& c1, cube*& c2, sphere*& s1, sphere*& s2); // collisions for cubes
	static void drawSphere(sphere* s); // draw sphere
	static void drawCube(cube* c);
	static void display(); // draw and display
	void light(); // lighting
	static void reshape(int w, int h); // set viewport to match window size
	static void idle(); // update display continuously
	void run_sim();	// runs simulation
};

struct ground {
public:
	Vector3 ground_normal = Vector3(0, 1, 0);
	float ground_level = 0.0f;

};