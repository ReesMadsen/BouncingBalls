#include "BouncingBalls.h"

#include <iostream>

#ifdef _WIN32
  #include "glut.h"
#else
  #ifdef __APPLE__
    #include <GLUT/glut.h>
  #else
    #include <GL/glut.h>
  #endif
#endif

BouncingBalls::BouncingBalls(int nWidthIn, int nHeightIn)
{
	this->SetHeight(nHeightIn);
	this->SetWidth(nWidthIn);
	pEnviroment=new BouncingBallsEnvironment(nWidthIn,nHeightIn);
}

////////////////////////////////////////////
//
// Glut functions
//
////////////////////////////////////////////

void BouncingBalls::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	this->pEnviroment->Display();
	glutSwapBuffers();
}

Screen *BouncingBalls::KeyBoard(
    unsigned char ucKey,
    int           nXVal,
    int           nYVal)
{
	return NULL;
}

void BouncingBalls::Reshape(
    int nWidthIn,
    int nHeightIn)
{
	this->SetWidth(nWidthIn);
	this->SetHeight(nHeightIn);
	this->pEnviroment->Reshape(nWidthIn,nHeightIn);

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, nWidthIn, nHeightIn);
	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, nWidthIn, 0, nHeightIn);
	glMatrixMode(GL_MODELVIEW);
}

Screen *BouncingBalls::Mouse(
    int nMouseButton,
    int nState,
    int nXVal,
    int nYVal)
{
	this->pEnviroment->Mouse(nMouseButton,nState,nXVal,nYVal);
	return NULL;
}