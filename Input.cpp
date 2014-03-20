// set up and maintain view as window sizes change

#include "View.hpp"
#include "Input.hpp"

// Apple's annoying non-standard GL include location
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.1415926
#endif

// GLUT requires data accessed by GLUT callbacks to be global :(
Input g_input;                  // global UI object

//
// called when a mouse button is pressed. 
// Remember where we were, and what mouse button it was.
//
void Input::mousePress(int button, int x, int y)
{
    mouseButton = button;
    oldX = x;
    oldY = y;
}

//
// called when the mouse moves
// use difference between oldX,oldY and x,y to define a rotation
//
void Input::mouseDrag(int x, int y)
{
    if (mouseButton == GLUT_LEFT_BUTTON) {
        // differences from last position
        float dx = float(x - oldX), dy = float(y - oldY);
        oldX = x;              // update stored position
        oldY = y;

        // rotation angle, scaled so across the window = one rotation
        g_view.pan += 360 * dx / g_view.width;
        g_view.tilt += 90 * dy / g_view.height;
//        if (g_view.tilt >  90) g_view.tilt =  90;
//        if (g_view.tilt < -90) g_view.tilt = -90;

        // tell GLUT that something has changed and we must redraw
        glutPostRedisplay();
    }
}

//
// called when any key is pressed
//
void Input::keyPress(int key)
{
    // do any pending updates, and mark current time
    g_view.update();

    switch (key) {
    // reset
    case 'r':
        g_view.pan = g_view.tilt = 0;
        break;
    case 'R':
        g_view.reset();
        break;

    // driving
    case 'a':                   // rotate left
        g_view.rotSpeed = c_rotation;
        break;
    case 'd':                   // rotate right
        g_view.rotSpeed = -c_rotation;
        break;

    case 'w':                   // accelerate
        g_view.speed = c_speed;
        break;
    case 's':                   // decelerate
        g_view.speed = -c_speed;
        break;
            
    case 27:                    // Escape: exit
        exit(0);
    }

    // ask to redraw, based on any updates
    glutPostRedisplay();
}

//
// called when any key is released
//
void Input::keyRelease(int key)
{
    // do any pending updates, and mark current time
    g_view.update();

    switch (key) {
    case 'a': case 'd':         // stop rotating
        g_view.rotSpeed = 0;
        break;

    case 'w': case 's':         // stop accelerating
        g_view.speed = 0;
    }
}

