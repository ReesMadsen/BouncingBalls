#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include "Screen.h"

class Environment
{
public:
    // Constructor
    Environment(int nWidth, int nHeight);
	// Destructor
	~Environment();

    ////////////////////////////////////////////
    //
    // Glut functions
    //
    ////////////////////////////////////////////

    void Display();

    void KeyBoard(
        unsigned char ucKey,
        int           nXVal,
        int           nYVal);

    void Reshape(
        int nWidth,
        int nHeight);

    void Mouse(
        int nMouseButton,
        int nState,
        int nXVal,
        int nYVal);

	virtual ScreenType GetScreenType() {return Environment_Screen;}

private:
	Screen     *pScreen;
	// The current screen dimensions.
    int         nWidth, nHeight;

protected:
};

#endif /* _ENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */

