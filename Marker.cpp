#include "Marker.hpp"
#include <cmath>

// Apple's annoying non-standard GL include location
#if defined(__APPLE__) || defined(MACOSX)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Marker::Marker (int m, double lati, double longi) {
	mode = m;
    latitude = lati;
    longitude = longi;

}

void Marker::draw() {

	float *vertices;
	int iFactor = 18;
	double theta, phi;
	theta = phi = 0.0;
	glEnableClientState(GL_VERTEX_ARRAY);
 
	switch(mode)
	{
		case MERIDIAN:
			vertices = new float[iFactor*6];
			phi = longitude;
			for (int i = 0; i < iFactor*2; ++i)
			{
				theta = (2*M_PI*i)/iFactor;
				vertices[i*3] = (float)(sin(theta)*cos(phi));
				vertices[i*3+1] = (float)(sin(theta)*sin(phi));
				vertices[i*3+2] = (float)(cos(theta));
			}
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glLineWidth(10);
	    	glDrawArrays(GL_LINE_STRIP, 0, iFactor*2);  //count
		    break;

		case PARALLEL:
			vertices = new float[iFactor*6];
			theta = M_PI/2 - latitude;
			for (int i = 0; i < iFactor*2; ++i)
			{
				phi = (2*M_PI*i)/iFactor;
				vertices[i*3] = (float)(sin(theta)*cos(phi));
				vertices[i*3+1] = (float)(sin(theta)*sin(phi));
				vertices[i*3+2] = (float)(cos(theta));
			}
			glVertexPointer(3, GL_FLOAT, 0, vertices);
			glLineWidth(10);
	    	glDrawArrays(GL_LINE_STRIP, 0, iFactor*2);  //count
			break;

		case POINT:
			vertices = new float[3];
			theta = M_PI/2 - latitude;
		    phi = longitude;
			vertices[0] = (float)(sin(theta)*cos(phi));
			vertices[1] = (float)(sin(theta)*sin(phi));
			vertices[2] = (float)(cos(theta));	
			glVertexPointer(3, GL_FLOAT, 0, vertices);
		    glPointSize(20);
	    	glDrawArrays(GL_POINTS, 0, 1);
			break;
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	delete vertices;

}


