// OpenGL/GLUT 
// Rees Madsen
// 8/31/2016
// Bouncing Balls 3D from 2D geometry.
#include <cmath>
#include <cstring>
#include "glut.h"

#include "Error.h"
#include "Environment.h"

// GLUT is not thread safe so all of the environment
// will be handled through a single instance of a
// class called Universe.

Environment TheEnvironment(700,500);

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	try
	{
		TheEnvironment.Display();
	}
    catch(ErrorType Error)
    {
		PrintError(Error);
    }
	catch(...)
	{
		PrintError(NullError);
	}
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char ucKey,
              int           nXVal,
              int           nYVal)
{
    try
    {
		TheEnvironment.KeyBoard(ucKey, nXVal, nYVal);
    }
    catch(ErrorType Error)
    {
		PrintError(Error);
    }
	catch(...)
	{
		PrintError(NullError);
	}
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int nWidth,
             int nHeight)
{
    try
    {
		TheEnvironment.Reshape(nWidth,nHeight);
    }
    catch(ErrorType Error)
    {
		PrintError(Error);
    }
	catch(...)
	{
		PrintError(NullError);
	}
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int nMouseButton,
           int nState,
           int nXVal,
           int nYVal)
{
    try
    {
		TheEnvironment.Mouse(nMouseButton,nState,nXVal,nYVal);
    }
    catch(ErrorType Error)
    {
		PrintError(Error);
    }
	catch(...)
	{
		PrintError(NullError);
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(50, 50);

    int fullscreen = 0;
    if (fullscreen) 
    {
        glutGameModeString("800x600:32");
        glutEnterGameMode();
    } 
    else 
    {
        glutCreateWindow("GLUT Projects");
    }

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    glColor3d(0,0,0); // forground color
    glClearColor(1, 1, 1, 0); // background color

    glutMainLoop();

    return 0;
}
