#pragma once
#include "sphere.h"

// static mean can be called without instance of class

class simulation {

private:
	static sphere* s1;
	static sphere* s2;

public:
	/* constructor */
	simulation();
	/* destructor  */
	~simulation();
	/* setters and getters */
	void setS1(sphere* s1);
	sphere* getS1();
	void setS2(sphere* s2);
	sphere* getS2();
	/* simulation functions*/
	static void drawPlane(); // draw ground //static
	static void display();
	void light(); // lighting
	static void reshape(int w, int h); 
	static void idle();
	void run_sim();	// runs simulation
};
