#ifndef _BOUNCINGBALLSSETUP_H_
#define _BOUNCINGBALLSSETUP_H_
#include "Screen.h"

class BouncingBallsSetUp : public Screen
{
public:
    BouncingBallsSetUp(int nWidth, int nHeight);

    ////////////////////////////////////////////
    //
    // Glut functions
    //
    ////////////////////////////////////////////

    void Display();

    Screen *KeyBoard(
        unsigned char ucKey,
        int           nXVal,
        int           nYVal);

    void Reshape(
        int nWidth,
        int nHeight);

    Screen *Mouse(
        int nMouseButton,
        int nState,
        int nXVal,
        int nYVal);

	virtual ScreenType GetScreenType() {return BouncingBallsSetUp_Screen;}
};

#endif /* _BOUNCINGBALLSSETUP_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */