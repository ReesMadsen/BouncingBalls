#include "Environment.h"
#include "OpenScreen.h"
#include "Error.h"

// Constructor
Environment::Environment()
{
    // The first initilazation will be of the openscreen.
    pScreen=new OpenScreen;
}

////////////////////////////////////////////
//
// Glut functions
//
////////////////////////////////////////////

void Environment::Display()
{
    if(this->pScreen)
    {
        pScreen->Display();
    }
    else
    {
        throw ShouldNeverBeHere;
    }
}

void Environment::KeyBoard(
    unsigned char ucKey,
    int           nXVal,
    int           nYVal)
{
    if(this->pScreen)
    {
        pScreen->KeyBoard(ucKey,nXVal,nYVal);
    }
    else
    {
        throw ShouldNeverBeHere;
    }
}

void Environment::Reshape(
    int nWidth,
    int nHeight)
{
    if(this->pScreen)
    {
        pScreen->Reshape(nWidth,nHeight);
		pScreen->SetHeight(nHeight);
		pScreen->SetWidth(nWidth);
    }
    else
    {
        throw ShouldNeverBeHere;
    }
}

void Environment::Mouse(
    int nMouseButton,
    int nState,
    int nXVal,
    int nYVal)
{
    if(this->pScreen)
    {
        if(Screen *pNewScreen=pScreen->Mouse(nMouseButton,nState,nXVal,nYVal))
		{
			// We are moving from one screen to the next.
			// Delete the current screen and replace it
			// with the new screen.
			delete pScreen;
			pScreen=pNewScreen;
		}
    }
    else
    {
        throw ShouldNeverBeHere;
    }
}
