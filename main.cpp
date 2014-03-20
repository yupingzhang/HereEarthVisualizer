// Yuping Zhang
// Thesis: Real-time Realistic Rendering of Sunrise and Sunset at Seaside


#include <iostream>
#include "Input.hpp"
#include "View.hpp"
#include <GL/gl.h>

// Apple's annoying non-standard GL include location
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

///////
// GLUT callbacks must use extern "C"
extern "C" {

  //
  // called every time the screen needs to be redrawn 
  //
  void draw()
  {
    g_view.update();
      
    glClearColor(0.5, 0.5, 1.0, 1.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, 1000, 800);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
      
    // draw something
    g_view.view();
      
    glEnable(GL_DEPTH_TEST);
    // tell OpenGL to finish drawing and show what we've done
    glutSwapBuffers();
  }
}

//
// called whenever the window size changes
//
void reshape(int width, int height)
{
    g_view.viewport(width, height);
}
//
// called when mouse button is pressed
//
void mousePress(int button, int state, int x, int y)
{
    g_input.mousePress(button,x,y);
}

//
// called when mouse is moved with any button down
//
void mouseDrag(int x, int y)
{
    g_input.mouseDrag(x,y);
}

//
// called on any keypress
//
void keyPress(unsigned char k, int x, int y)
{
    g_input.keyPress(k);
}

//
// called on any key release
//
void keyRelease(unsigned char k, int x, int y)
{
    g_input.keyRelease(k);
}

// initialize GLUT - windows and interaction
void initGLUT(int *argcp, char *argv[])
{
    // ask for a window with dimensions from g_view
    // need color, depth (for 3D drawing) and double buffer (smooth display)
    glutInit(argcp, argv);
    glutInitWindowSize(1000, 800);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Demo");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyRelease);
    glutMouseFunc(mousePress);
    glutMotionFunc(mouseDrag);
    
}

// initialize OpenGL - rendering state
void initGL()
{
    // enable some GL features
    glEnable(GL_DEPTH_TEST);      // tell OpenGL to handle overlapping surfaces
    glEnable(GL_COLOR_MATERIAL);  // map glColor to surface colors for lighting
    glEnable(GL_NORMALIZE);       // tell GL to auto-normalize normals
}

int main(int argc, char *argv[])
{
    // set up GLUT and OpenGL
    initGLUT(&argc, argv);
    initGL();
    
    g_view.view();
    glutMainLoop();
    
    //delete
    return 0;
}


