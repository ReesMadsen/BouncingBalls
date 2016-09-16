#include "BouncingBallsSetUp.h"
#include "BouncingBalls.h"
#include <iostream>

#include "glut.h"

BouncingBallsSetUp::BouncingBallsSetUp(int nWidthIn, int nHeightIn)
{
	this->SetHeight(nHeightIn);
	this->SetWidth(nWidthIn);
}

// Outputs a string of text at the specified location.
static void DrawText(double x, double y, char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}

    glDisable(GL_BLEND);
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
	DrawText(290,390,"Bouncing Balls");
	DrawText(280,300,"Click to continue");
	glutSwapBuffers();
}

Screen *BouncingBallsSetUp::KeyBoard(
    unsigned char ucKey,
    int           nXVal,
    int           nYVal)
{
	return NULL;
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