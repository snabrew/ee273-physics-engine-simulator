#include <iostream>
#include <glut.h>
#include "C:\Users\uwais\source\repos\EE273_Project\Vector3.h"
#include "C:\Users\uwais\source\repos\EE273_Project\Vector3.cpp"
#include "C:\Users\uwais\source\repos\EE273_Project\point_mass.h"
#include "C:\Users\uwais\source\repos\EE273_Project\point_mass.cpp"
#include "C:\Users\uwais\source\repos\EE273_Project\sphere.h"
#include "C:\Users\uwais\source\repos\EE273_Project\sphere.cpp"


using namespace std;
Vector3 s_pos(0, 100, 0);
Vector3 s_vel(0, 0, 2);
Vector3 s_acc(0, 0, 0); 
float s_mass = 10.0;
float s_rad = 1.0f;
sphere mySphere(s_pos, s_vel, s_acc, s_mass, s_rad);
Vector3 ground_normal(0, 1, 0);
float ground_level = 0.0f;


Vector3 s_pos2(5, 100, 0);
float s_rad2 = 2.0f;
float s_mass2 = 15.0;
sphere mySphere2(s_pos2, s_vel, s_acc, s_mass2, s_rad2);


void drawPlane() {
    glTranslatef(0.0f, -0.5f, 0.0f); // move the ground to the right height
    glBegin(GL_QUADS); // draw a quad to represent the ground
    glNormal3f(0.0f, 1.0f, 0.0f); // set the normal vector for lighting
    glVertex3f(-10.f, 0.0f, -10.f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glColor3f(0.0, 1.0, 0.0); // set the color of the plane
    glEnd();
}


void display()
{

    // clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100); // setup perspective projection

    // set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 10, 30, 0, 0, 0, 0, 1, 0); // setup camera position and orientation

    // Integrate the sphere
    if (mySphere.detect(ground_level) == 1) { // detect collision
        mySphere.res(ground_normal);          // resolve collision 
    }
    // integrate the sphere's position and velocity
    mySphere.integrate(0.01);

    if (mySphere2.detect(ground_level) == 1) { // detect collision
        mySphere2.res(ground_normal);          // resolve collision 
    }

    mySphere2.integrate(0.01);



    // Draw the sphere
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(mySphere.getPosition().getX(), mySphere.getPosition().getY(), mySphere.getPosition().getZ());
    glutSolidSphere(mySphere.getRadius(), 50, 50);
    glEnd();


    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(mySphere2.getPosition().getX(), mySphere2.getPosition().getY(), mySphere2.getPosition().getZ());
    glutSolidSphere(mySphere2.getRadius(), 50, 50);
    glEnd();


    drawPlane();

    glutSwapBuffers();





    // flush the graphics pipeline
    glFlush();
}

void init()
{
    
    // set the material and lighting properties
     
    
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void idle()
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Sphere");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}


