#include "Vector3.h"
#include "point_mass.h"
#include "sphere.h"
#include <iostream>

using namespace std;


int main() {
    // boucning ball
    Vector3 s_pos(0, 10, 0);
    Vector3 s_vel(0, 0, 0);
    Vector3 s_acc(0, 0, 0);
    float s_mass = 5.0;
    float s_rad = 1.0;
    sphere s(s_pos, s_vel, s_acc, s_mass, s_rad); 
    Vector3 ground_normal(0, 1, 0);
    float ground_level = 0.0f;
    // set the simulation parameters
    float timeStep = 0.01f;
    float endTime = 100.0f;

    // simulate the sphere
    for (float t = 0; t < endTime; t += timeStep) {
 
        if (s.detect(ground_level) == 1) {
            s.res(ground_normal);
            cout << "COLLISION" << endl;
        }
        s.integrate(timeStep);
        // print the sphere's position
        cout << "t = " << t << ", position = (" << s.getPosition().getX()
            << ", " << s.getPosition().getY() << ", " << s.getPosition().getZ() << ")" << endl;
    }

}



/*
int main() {
	// simulating particle and gravity 
	// create a particle
	point_mass p(Vector3(0, 1, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0);

	// set the simulation parameters
	float timeStep = 0.01f;
	float endTime = 10.0f;

	// simulate the particle
	for (float t = 0; t < endTime; t += timeStep) {
		p.integrate(timeStep);

		// print the particle's position
		cout << "t = " << t << ", position = (" << p.getPosition().getX()
			<< ", " << p.getPosition().getY() << ", " << p.getPosition().getZ() << ")" << endl;
	}

	return 0;
}
*/

/*
int main() {

    // create two point masses
    Vector3 pos1(1, 1, 1);
    Vector3 vel1(0, 0, 0);
    Vector3 acc1(0, 0, 0);
    float mass1 = 1;
    point_mass pm1(pos1, vel1, acc1, mass1);

    Vector3 pos2(1, 1, 1);
    Vector3 vel2(0, 0, 0);
    Vector3 acc2(0, 0, 0);
    float mass2 = 1;
    point_mass pm2(pos2, vel2, acc2, mass2);

    // create detector object
    pmDetect detector;

    // test pmDetect::detect(pm1, pm2)
    bool result = detector.detect(pm1, pm2);
    cout << "pmDetect::detect(pm1, pm2) result: " << result << endl;

    // test pmDetect::detect(pm, ground)
    Vector3 pos3(5, 0, 0);
    Vector3 vel3(0, 0, 0);
    Vector3 acc3(0, 0, 0);
    float mass3 = 1;
    point_mass pm3(pos3, vel3, acc3, mass3);

    float ground = 0;
    result = detector.detect(pm3, ground);
    cout << "pmDetect::detect(pm3, ground) result: " << result << endl;

    return 0;
}
*/