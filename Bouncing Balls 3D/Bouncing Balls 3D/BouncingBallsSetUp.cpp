#include "BouncingBallsSetUp.h"
#include "BouncingBalls.h"
#include "GLUTText.h"
#include "OpenScreen.h"
#include <iostream>

#include "glut.h"

BouncingBallsSetUp::BouncingBallsSetUp(int nWidthIn, int nHeightIn)
{
	this->SetHeight(nHeightIn);
	this->SetWidth(nWidthIn);
}

// Destructor.
BouncingBallsSetUp::~BouncingBallsSetUp()
{
	// As of now there is nothing to do here.
}

////////////////////////////////////////////
//
// Glut functions
//
////////////////////////////////////////////

void BouncingBallsSetUp::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0,0,0);
	DrawText(10,480,"Bouncing Balls");
	DrawText(10,460,"Press 'b' to go back.");
	DrawText(10,440,"Press 'r' to restart.");
	DrawText(10,420,"Press 'Enter' or left click to continue");

	glutSwapBuffers();
}

Screen *BouncingBallsSetUp::KeyBoard(
    unsigned char ucKey,
    int           nXVal,
    int           nYVal)
{
	Screen *pScreen=NULL;
	switch(ucKey)
	{
		case 'b': // Back to the open screen.
			{
			int nHeight=this->GetHeight();
			int nWidth=this->GetWidth();
			pScreen=new OpenScreen(nWidth,nHeight);

			break;
			}
		case 13: // Enter open an instance of bouncing balls.
			{
			int nWidth=this->GetWidth();
			int nHeight=this->GetHeight();
			pScreen=new BouncingBalls(nWidth,nHeight);

			break;
			}
	}
	return pScreen;
}

void BouncingBallsSetUp::Reshape(
    int nWidthIn,
    int nHeightIn)
{
	this->SetWidth(nWidthIn);
	this->SetHeight(nHeightIn);

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, nWidthIn, nHeightIn);

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// We will maintain the idea of a 700 by 500 screen.
	gluOrtho2D(0, 700, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

Screen *BouncingBallsSetUp::Mouse(
    int nMouseButton,
    int nState,
    int nXVal,
    int nYVal)
{
	if(nMouseButton==GLUT_LEFT_BUTTON && nState==GLUT_UP) 
	{
	Screen *pScreen;
	int nWidth=this->GetWidth();
	int nHeight=this->GetHeight();
	pScreen=new BouncingBalls(nWidth,nHeight);
	return pScreen;
	}
	return NULL;
}