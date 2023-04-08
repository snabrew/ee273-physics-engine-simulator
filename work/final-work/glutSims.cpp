#include "glutSims.h"
#include "glut.h"

using namespace std;


sphere* simulation::s1 = nullptr;
sphere* simulation::s2 = nullptr;

/* constructors */
simulation::simulation() {

    s1 = new sphere();
    s2 = new sphere();
}

simulation::~simulation() {

    delete s1;
    delete s2;
}


/* setters and getters */
void simulation::setS1(sphere* s1) {

    this->s1 = s1;
}

void simulation::setS2(sphere* s2) {

    this->s2 = s2;
}

sphere* simulation::getS1() {

    return s1;
}

sphere* simulation::getS2() {

    return s2;
}



/* simulation functions */
void simulation::drawPlane() {

    glTranslatef(0.0f, 0.0f, 0.0f); // set ground height
    glBegin(GL_QUADS); // draw ground using quad
    glNormal3f(0.0f, 1.0f, 0.0f); // set the normal vector for lighting

    /* cooridinates of ground vertexs */
    glVertex3f(-20.0f, 0.0f, -20.0f);
    glVertex3f(-20.0f, 0.0f, 20.0f);
    glVertex3f(20.0f, 0.0f, 20.0f);
    glVertex3f(20.0f, 0.0f, -20.0f);

    glColor3f(0.0, 1.0, 0.0); // set the color of the plane
    glEnd();
}


void simulation::display(){

    // clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100); // setup perspective projection

    // set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 10, 40, 0, 0, 0, 0, 1, 0); // camera position and orientation


    drawPlane();
    Vector3 ground_normal(0, 1, 0);
    // Integrate the sphere
    if (s1->detect(0) == 1) { // detect collision sphere 1
        s1->res(ground_normal); // resolve collision sphere 1
    }
    if (s1->detect((*s2)) == 1) {
        s1->res((*s2));
    }
    // integrate the sphere position and velocity
    s1->integrate(0.01);

    if (s2->detect(0) == 1) { // detect collision sphere 2
        s2->res(ground_normal); // resolve collision sphere 2
    }
    if (s2->detect((*s1)) == 1) {
        s2->res((*s1));
    }

    s2->integrate(0.01);


    // Draw sphere 1
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(s1->getPosition().getX(), s1->getPosition().getY(), s1->getPosition().getZ());
    glutSolidSphere(s1->getRadius(), 50, 50);
    glPopMatrix();

    // Draw sphere 2
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(s2->getPosition().getX(), s2->getPosition().getY(), s2->getPosition().getZ());
    glutSolidSphere(s2->getRadius(), 50, 50);
    glPopMatrix();

    /* push and pop matrix so spheres are drawn independently
    so they dont appear to overlap or intersect */ 

    glutSwapBuffers();

    // flush the graphics pipeline
    glFlush();
}


void simulation::light(){

    // set the material and lighting properties

    /* material properties */
    // amount of light relfected by material
    GLfloat material_ambience[] = { 0.2, 0.2, 0.2, 1.0 }; 
    // amount of light scattered by material
    GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };


    /* light properites */
    // normal light source
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; 
    // ambient light source 
    GLfloat light_ambience[] = { 0.8, 0.8, 0.8, 0.8 }; 
    // diffuse of source
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; 
    // shininess of light 
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    /* enabling and setting up the light */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambience);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambience);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);


    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // background colour

}


void simulation::reshape(int w, int h){

    // set viewport to match window size 
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // position camera 
}

void simulation::idle(){

    /* updates display continuously for
     smooth simulation in another function
     because needed to be static */
    glutPostRedisplay();
    
}

void simulation::run_sim() {

    /* creating window */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Simulation");

    /* apply functions */
    light();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    /* program stops when window is closed */
    glutMainLoop();

}
