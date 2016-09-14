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

BouncingBalls::BouncingBalls()
{
	pEnviroment=new BouncingBallsEnvironment;
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
    int nWidth,
    int nHeight)
{
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