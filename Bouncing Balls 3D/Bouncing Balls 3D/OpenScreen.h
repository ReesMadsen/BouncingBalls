#ifndef _OPENSCREEN_H_
#define _OPENSCREEN_H_
#include "Screen.h"

class OpenScreen : public Screen
{
public:
    OpenScreen(int nWidth, int nHeight);

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

	virtual ScreenType GetScreenType() {return OpenScreen_Screen;}
};

#endif /* _OPENSCREEN_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */