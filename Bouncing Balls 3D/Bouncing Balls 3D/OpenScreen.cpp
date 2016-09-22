#include "OpenScreen.h"
#include "BouncingBallsSetUp.h"
#include "GLUTText.h"
#include <iostream>

#include "glut.h"

OpenScreen::OpenScreen(int nWidthIn, int nHeightIn)
{
	this->SetWidth(nWidthIn);
	this->SetHeight(nHeightIn);
}

// Destructor.
OpenScreen::~OpenScreen()
{
	// As of now there is nothing to do here.
}

////////////////////////////////////////////
//
// Glut functions
//
////////////////////////////////////////////

void OpenScreen::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0,0,0);
	DrawText(10,480,"Main Screen");
	DrawText(10,460,"Click the following");
	
	DrawText(10,440,"b for Bouncing Balls.");
	glutSwapBuffers();
}

Screen *OpenScreen::KeyBoard(
    unsigned char ucKey,
    int           nXVal,
    int           nYVal)
{
	Screen *pScreen=NULL;
	switch (ucKey) 
	{
		case 'b':
			{
			// Open Bouncing Balls.
			int nHeight=this->GetHeight();
			int nWidth=this->GetWidth();
			pScreen=new BouncingBallsSetUp(nWidth,nHeight);

			break;
			}
	}
	return pScreen;
}

void OpenScreen::Reshape(
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

Screen *OpenScreen::Mouse(
    int nMouseButton,
    int nState,
    int nXVal,
    int nYVal)
{
	if(nMouseButton==GLUT_LEFT_BUTTON && nState==GLUT_UP) 
	{
	Screen *pScreen;
	int nHeight=this->GetHeight();
	int nWidth=this->GetWidth();
	pScreen=new BouncingBallsSetUp(nWidth,nHeight);
	return pScreen;
	}
	return NULL;
}