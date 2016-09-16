#include "Environment.h"
#include "OpenScreen.h"
#include "Error.h"

#include "glut.h"

// Constructor
Environment::Environment(int nWidthIn, int nHeightIn)
	: nWidth(nWidthIn), nHeight(nHeightIn)
{
    // The first initilazation will be of the openscreen.
    pScreen=new OpenScreen(nWidthIn,nHeightIn);
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
    int nWidthIn,
    int nHeightIn)
{
	this->nWidth =nWidthIn;
	this->nHeight=nHeightIn;
    if(this->pScreen)
    {
        pScreen->Reshape(nWidthIn,nHeightIn);
		pScreen->SetHeight(nHeightIn);
		pScreen->SetWidth(nWidthIn);
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
