#ifndef _BOUNCINGBALLS_H_
#define _BOUNCINGBALLS_H_
#include "Screen.h"
#include "BouncingBallsEnvironment.h"

class BouncingBalls : public Screen
{
public:
    BouncingBalls(int nWidth, int nHeight);

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

	virtual ScreenType GetScreenType() {return BouncingBalls_Screen;}

private:
	BouncingBallsEnvironment *pEnviroment;
};

#endif /* _BOUNCINGBALLS_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */