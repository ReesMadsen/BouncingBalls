#ifndef _BOUNCINGBALLSENVIRONMENT_H_
#define _BOUNCINGBALLSENVIRONMENT_H_

#include <vector>
#include "BouncingBallSphere.h"

// Global Constants
const int    nMinRadius=30;
const int    nMaxRadius=50;

const double dWindResistance=.9998;
const double dCollisionFriction=.95;
const double dWallFriction=.9502;

class BouncingBallsEnvironment
{
public:
    BouncingBallsEnvironment();
	~BouncingBallsEnvironment();

	void DrawBouncingBalls();
	void DrawWalls();
	void DrawShadows();
	void DrawBalls();

	void UpdateBouncingBalls();
	void MoveBalls();
	void HandleCollisions();
	void SortBalls();
	void HandleGravity();

	void Display();
	void Mouse(int nMouseButton,
			   int nState,
			   int nXVal,
			   int nYVal);

private:
	// The dimensions of the box.
	double dSizeX;
	double dSizeY;
	double dSizeZ;

	double dViewDistance;

	int nCircles;

	// Max start speed.
	// Should be put in a vector.
	double dMax_dx;
	double dMax_dy;
	double dMax_dz;

	// Gravity direction.
	// Sould be put in a vector.
	double dGravity_x;
	double dGravity_y;
	double dGravity_z;

	std::vector<BouncingBallSphere *> aSpheres;
};

#endif /* _BOUNCINGBALLSENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */