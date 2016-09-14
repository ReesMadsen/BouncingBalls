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
	
	void SetHeight(int nHeightIn) {nHeight=nHeightIn;}
	void SetWidth(int nWidthIn) {nWidth=nWidth;}

	int GetHeight() {return this->nHeight;}
	int GetWidth() {return this->nWidth;}

private:
	int nHeight;
	int nWidth;
};

#endif /* _SCREEN_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */