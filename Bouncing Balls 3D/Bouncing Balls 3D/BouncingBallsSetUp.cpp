#include "BouncingBallsSetUp.h"
#include "BouncingBalls.h"
#include <iostream>

#include "glut.h"

BouncingBallsSetUp::BouncingBallsSetUp()
{
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
    int nWidth,
    int nHeight)
{
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
	pScreen=new BouncingBalls;
	return pScreen;
	}
	return NULL;
}