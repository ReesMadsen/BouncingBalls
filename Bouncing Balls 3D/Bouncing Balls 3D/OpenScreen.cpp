#include "OpenScreen.h"
#include "BouncingBallsSetUp.h"
#include <iostream>

#include "glut.h"

OpenScreen::OpenScreen()
{
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, char *string)
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

void OpenScreen::Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(0,0,0);
	DrawText(300,390,"Main Screen");
	DrawText(280,300,"Click to continue");
	glutSwapBuffers();
}

Screen *OpenScreen::KeyBoard(
    unsigned char ucKey,
    int           nXVal,
    int           nYVal)
{
	return NULL;
}

void OpenScreen::Reshape(
    int nWidth,
    int nHeight)
{
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
	pScreen=new BouncingBallsSetUp;
	return pScreen;
	}
	return NULL;
}