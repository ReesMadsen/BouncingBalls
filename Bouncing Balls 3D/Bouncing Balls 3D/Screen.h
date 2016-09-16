#ifndef _SCREEN_H_
#define _SCREEN_H_

enum ScreenType
{
	BouncingBalls_Screen,
	BouncingBallsSetUp_Screen,
	Environment_Screen,
	OpenScreen_Screen,

	NotSet_Screen
};

class Screen
{
public:
	virtual void Display()=0;

	// KeyBoard may return a screen
	// if manuvering from  one
	// screen instance to another.
    virtual Screen *KeyBoard(
        unsigned char ucKey,
        int           nXVal,
        int           nYVal)=0;

    virtual void Reshape(
        int nWidth,
        int nHeight)=0;

	// Mouse may return a screen
	// if manuvering from  one
	// screen instance to another.
    virtual Screen *Mouse(
        int nMouseButton,
        int nState,
        int nXVal,
        int nYVal)=0;

	virtual ScreenType GetScreenType()=0;
	
	virtual void SetHeight(int nHeightIn) {nHeight=nHeightIn;}
	virtual void SetWidth(int nWidthIn) {nWidth=nWidthIn;}

	virtual int GetHeight() {return this->nHeight;}
	virtual int GetWidth() {return this->nWidth;}

private:
	// nHeight and nWidth need to be initalized
	// in every instance of a screen.
	int nHeight;
	int nWidth;
};

#endif /* _SCREEN_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */