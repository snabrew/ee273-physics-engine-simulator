#include "glutSims.h"
#include "glut.h"
#include "Vector3.h"
#include "point_mass.h"
#include "sphere.h"





// declare two spheres for collision 
Vector3 s_pos(-10, 300, 0);
Vector3 s_vel(0, 0, 0);
Vector3 s_acc(0, 0, 0);
float s_mass = 5.0;
float s_rad = 3.0f;
sphere s1(s_pos, s_vel, s_acc, s_mass, s_rad);
Vector3 ground_normal(0, 1, 0);
float ground_level = 0.0f;


Vector3 s_pos2(8, 100, 0);
Vector3 s_vel2(0, 0, 0);
Vector3 s_acc2(0, 0, 0);
float s_rad2 = 1.0f;
float s_mass2 = 1;
sphere s2(s_pos2, s_vel2, s_acc2, s_mass2, s_rad2);



// declare two spheres for collision 
Vector3 s_pos3(-10, 3, 0);
Vector3 s_vel3(10, 0, 0);
Vector3 s_acc3(50, 0, 0);
float s_mass3 = 5.0;
float s_rad3 = 3.0f;
sphere s3(s_pos3, s_vel3, s_acc3, s_mass3, s_rad3);

Vector3 s_pos4(8, 1, 0);
Vector3 s_vel4(0, 0, 0);
Vector3 s_acc4(0, 0, 0);
float s_rad4 = 1.0f;
float s_mass4 = 1;
sphere s4(s_pos4, s_vel4, s_acc4, s_mass4, s_rad4);



void drawPlane() {
    glTranslatef(0.0f, 0.0f, 0.0f); // move the ground to the right height
    glBegin(GL_QUADS); // draw a quad to represent the ground
    glNormal3f(0.0f, 1.0f, 0.0f); // set the normal vector for lighting
    glVertex3f(-20.0f, 0.0f, -20.0f);
    glVertex3f(-20.0f, 0.0f, 20.0f);
    glVertex3f(20.0f, 0.0f, 20.0f);
    glVertex3f(20.0f, 0.0f, -20.0f);
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
    gluLookAt(0, 10, 40, 0, 0, 0, 0, 1, 0); // setup camera position and orientation


    drawPlane();

    // Integrate the sphere
    if (s1.detect(ground_level) == 1) { // detect collision sphere 1
        s1.res(ground_normal);          // resolve collision sphere 1
    }
    if (s1.detect(s2) == 1) {
        s1.res(s2);
    }
    // integrate the sphere's position and velocity
    s1.integrate(0.01);

    if (s2.detect(ground_level) == 1) { // detect collision sphere 2
        s2.res(ground_normal);          // resolve collision sphere 2
    }
    if (s2.detect(s1) == 1) {
        s2.res(s1);
    }

    s2.integrate(0.01);


    // Draw sphere 1
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(s1.getPosition().getX(), s1.getPosition().getY(), s1.getPosition().getZ());
    glutSolidSphere(s1.getRadius(), 50, 50);
    glPopMatrix();

    // Draw sphere 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(s2.getPosition().getX(), s2.getPosition().getY(), s2.getPosition().getZ());
    glutSolidSphere(s2.getRadius(), 50, 50);
    glPopMatrix();



    glutSwapBuffers();

    // flush the graphics pipeline
    glFlush();
}

void display2()
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
    gluLookAt(0, 10, 40, 0, 0, 0, 0, 1, 0); // setup camera position and orientation


    drawPlane();

    // Integrate the sphere
    if (s3.detect(ground_level) == 1) { // detect collision sphere 1
        s3.res(ground_normal);          // resolve collision sphere 1
    }
    if (s3.detect(s4) == 1) {
        s3.res(s4);
    }
    // integrate the sphere's position and velocity
    s3.integrate(0.01);

    if (s4.detect(ground_level) == 1) { // detect collision sphere 2
        s4.res(ground_normal);          // resolve collision sphere 2
    }
    if (s4.detect(s3) == 1) {
        s4.res(s3);
    }

    s4.integrate(0.01);


    // Draw sphere 1
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(s3.getPosition().getX(), s3.getPosition().getY(), s3.getPosition().getZ());
    glutSolidSphere(s3.getRadius(), 50, 50);
    glPopMatrix();

    // Draw sphere 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(s4.getPosition().getX(), s4.getPosition().getY(), s4.getPosition().getZ());
    glutSolidSphere(s4.getRadius(), 50, 50);
    glPopMatrix();



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

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}



void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // position camera upwards
}

void idle()
{
    glutPostRedisplay();
}

void bouncing_ball() {


    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Bouncing Ball");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();


}

void collision_balls() {

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Collision Between 2 Balls");

    init();

    glutDisplayFunc(display2);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    glutMainLoop();


}