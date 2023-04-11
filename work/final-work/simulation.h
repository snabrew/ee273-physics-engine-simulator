#pragma once
#include "sphere.h"

class simulation {

private:
	static sphere* s[1];

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
	static void drawPlane(); // draw ground
	static void drawSphere(sphere* s); // draw sphere
	static void display(); // draw and display
	void light(); // lighting
	static void reshape(int w, int h); // set viewport to match window size
	static void idle(); // update display continuously
	void run_sim();	// runs simulation
};
