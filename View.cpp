// set up and maintain view as window sizes change

#include "View.hpp"
#include "Marker.hpp"

// Apple's annoying non-standard GL include location
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <iostream>

////// GLUT requires data accessed by GLUT callbacks to be global :(
View g_view;                    // global view object

// speed
const float c_speed = 0.05f;
// view offset from terrain
static const Vec<3> c_viewOffset = {{0,0,5}};

// create with initial window size and location
View::View()
    : width(800), height(600), updateTime(0)
{
    reset();
}

//
// Reset view to default
//
void View::reset()
{
    position[0] = position[1] = 0;
    speed = rotSpeed = pan = tilt = 0;
    scale = 0.5;
}

//
// Update view based on elapsed time in milliseconds
//
void View::update() 
{
    int now = glutGet(GLUT_ELAPSED_TIME), elapsed = now - updateTime;
    if (scale_accelerate != 0) {
        if (scale < 0.1)
        {
            scale = 0.1;
        }
        if (scale > 1.0)
        { 
            scale = 1.0;
        }
        else
        {
            scale += scale_accelerate * elapsed * 0.003;
        }
        glutPostRedisplay();
    }
    if (move_x != 0 || move_y != 0)
    {
        position[0] += move_x * elapsed * 0.1;
        position[1] += move_y * elapsed * 0.1;
        glutPostRedisplay();
    }

    updateTime = now;
}

//
// New view from current position, pointing in current direction
// Height interpolated from terrain
//
void View::view() const
{
    // fixed position 
    Vec<3> worldPos = c_viewOffset;

    // orient view to normal
    Vec<3> worldDir = {{0, 0, 0}};
    Vec<3> normal = {{0,0,1}};

    Vec<3> atPos = worldPos + worldDir;
    glLoadIdentity();
    
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT);  
    glColor3f(0, 1, 0);

    glLineWidth(1);
    glRotatef(tilt, 1,0,0);
    glRotatef(pan, 0,1,0);
     
    //glScalef(0.5,0.5,0.5);
    glScalef(scale,scale,scale);
    glTranslatef(position[0], position[1], 0.0);
    //glTranslatef(position[0], 0, position[1]);

    glRotatef(90, 1,0,0);
    glutWireSphere(0.99,19,19);
    glColor3f(0, 0.5, 0.8);
    glutSolidSphere(0.98,19,19);

    //draw marker
    glColor3f(0.0, 0.0, 1.0);
    Marker *equator = new Marker(PARALLEL, 0.0, 0.0);
    equator->draw();
    
    glColor3f(1.0, 0.0, 0.0);
    Marker *prime_meridian = new Marker(MERIDIAN, 0.0, 0.0);
    prime_meridian->draw();

    glColor3f(1.0, 1.0, 0.0);
    Marker *tropic_of_cancer = new Marker(PARALLEL, 23.5, 0.0);
    tropic_of_cancer->draw();

    glColor3f(1.0, 1.0, 0.0);
    Marker *tropic_of_capricorn = new Marker(PARALLEL, -23.5, 0.0);
    tropic_of_capricorn->draw();

    glColor3f(1.0, 0.0, 0.0);
    Marker *arctic_circle = new Marker(PARALLEL, 66.5, 0.0);
    arctic_circle->draw();

    glColor3f(1.0, 0.0, 0.0);
    Marker *antarctic_circle = new Marker(PARALLEL, -66.5, 0.0);
    antarctic_circle->draw();

    
    glColor3f(0.8, 0.5, 0.0);
    Marker *point = new Marker(POINT, 51.50013, -0.126305);
    point->draw();

    gluLookAt(worldPos[0], worldPos[1], worldPos[2],
          atPos[0], atPos[1], atPos[2],
          normal[0], normal[1], normal[2]);

    glPopMatrix();
}

//
// This is called when window is created or resized
// Adjust projection accordingly.
//
void View::viewport(int width, int height)
{
    // this viewport makes a 1 to 1 mapping of physical pixels to GL
    // "logical" pixels
    glViewport(0, 0, (GLint) width, (GLint) height);

    // adjust 3D projection into this window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.,                 // vertical field of view
                   (float)width/height, // ratio of height & width
                   1, // near clipping plane
                   1000); // far clipping plane

    // switch back to "normal" transformation mode
    glMatrixMode(GL_MODELVIEW);
}
