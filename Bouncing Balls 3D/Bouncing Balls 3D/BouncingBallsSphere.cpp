#include "BouncingBallSphere.h"
#include <cmath>
#ifdef _WIN32
  #include "glut.h"
#else
  #ifdef __APPLE__
    #include <GLUT/glut.h>
  #else
    #include <GL/glut.h>
  #endif
#endif
// Constructors.
BouncingBallSphere::BouncingBallSphere(
	const double x_in, 
	const double y_in, 
	const double z_in,
	const double radius_in,
	const double dx_in,
	const double dy_in, 
	const double dz_in,
	const double r_in, 
	const double g_in, 
	const double b_in)
	: dCenterX(x_in),
	  dCenterY(y_in), 
	  dCenterZ(z_in), 
	  dRadius(radius_in), 
	  d_dx(dx_in), 
	  d_dy(dy_in), 
	  d_dz(dz_in), 
	  r(r_in), 
	  g(g_in), 
	  b(b_in), 
	  bSolid(false)
{
}

//operator overloading
bool BouncingBallSphere::operator>(const BouncingBallSphere &rhs)
{
	// For complete accuracy this
	// should test to see which
	// ball has a center that is
	// closer to the eyes position,
	// but this works well enough.
	return this->dCenterZ > rhs.GetCenterZ();
}
bool BouncingBallSphere::operator==(const BouncingBallSphere& rhs)
{
	double dX=this->dCenterX-rhs.GetCenterX();
	double dY=this->dCenterY-rhs.GetCenterY();
	double dZ=this->dCenterZ-rhs.GetCenterZ();
	double dRadiusSum=this->dRadius+rhs.GetRadius();
	return dX*dX+dY*dY+dZ*dZ < dRadiusSum*dRadiusSum;
}

//other methods
void BouncingBallSphere::paint(const double V, const double screen_x, const double screen_y) const
{
	/*
	the process to draw the sphere.
	when looking at a sphere you do not see exaclty half of the sphere, you see a little less.
	take a plane along the curve of the boundery of what would be visible to the viewer and cut the sphere.
	the result is a circle.
	the center of this circle has been given the valus AC(X,Y,Z). for apparent center and AR for apparent radius
	this plane is repersented by U and W, both of which are orthoganal to the viewers eye to the center of the circle that will be drawn.
	*/
  glColor3d(this->r, this->g, this->b);
  double U,ux,uy,uz, W,wx,wy,wz,   x,y,z,  px,py,theta;
  double D = sqrt((V+this->dCenterZ)*(V+this->dCenterZ)+
				  (screen_x/2-this->dCenterX)*(screen_x/2-this->dCenterX)+
				  (screen_y/2-this->dCenterZ)*(screen_y/2-this->dCenterY));

  double AR = this->dRadius*sqrt(D*D-this->dRadius*this->dRadius)/D;
  double AD = D - sqrt(this->dRadius*this->dRadius-AR*AR);
  double ACX = AD*(this->dCenterX-screen_x/2)/D+screen_x/2;
  double ACY = AD*(this->dCenterY-screen_y/2)/D+screen_y/2;
  double ACZ = AD*(this->dCenterZ+V)/D-V;
  //get vector field set up

  //U
  double size;
  ux = 1;
  uy = 0;
  uz = -(ACX - screen_x)/(ACZ + V);
  size = sqrt(ux*ux+uy*uy+uz*uz);
  ux /= size;
  uy /= size;
  uz /= size;

  //W
  wx = 0;
  wy = 1;
  wz = -(ACY - screen_y)/(ACZ + V);
  size = sqrt(wx*wx+wy*wy+wz*wz);
  wx /= size;
  wy /= size;
  wz /= size;

	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		theta = (double)i/32.0 * 2.0 * 3.1415926;
		U = AR * cos(theta); // u = (1,0,
		W = AR * sin(theta);
		x = U*ux+W*wx + ACX;
		y = U*uy+W*wy + ACY;
		z = U*uz+W*wz + ACZ;
		//(x,y,z) = a*u+b*v
		//z = this->CZ;
		px = (x+z*(screen_x/2-x)/(V+z));
		py = (y+z*(screen_y/2-y)/(V+z));
		glVertex2d(px, py);
	}
	glEnd();
}

void BouncingBallSphere::paint_shadow(const double V, const double screen_x, const double screen_y) const
{
	double R= this->dRadius;
	double CX = this->dCenterX;
	double y = 0;
	double CZ = this->dCenterZ;
	glColor3d(.5, 0.09, 0.04);
  
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = CX + R * cos(theta);
		double z = CZ + R * sin(theta);
		double ax = (x+z*(screen_x/2-x)/(V+z));
		double ay = (y+z*(screen_y/2-y)/(V+z));
		glVertex2d(ax, ay);
	}
	glEnd();
}

//set methods
void BouncingBallSphere::SetRadius(const double R){this->dRadius=R;}
void BouncingBallSphere::SetCenterX(const double CX){this->dCenterX=CX;}
void BouncingBallSphere::SetCenterY(const double CY){this->dCenterY=CY;}
void BouncingBallSphere::SetCenterZ(const double CZ){this->dCenterZ=CZ;}
void BouncingBallSphere::Set_dx(const double DX){this->d_dx=DX;}
void BouncingBallSphere::Set_dy(const double DY){this->d_dy=DY;}
void BouncingBallSphere::Set_dz(const double DZ){this->d_dz=DZ;}
void BouncingBallSphere::Set_rgb(const double r_in, const double g_in, const double b_in)
{
	this->r=r_in;
	this->g=g_in;
	this->b=b_in;
}
void BouncingBallSphere::SetSolid(const bool state){this->bSolid = state;}

//get methods
double BouncingBallSphere::GetRadius() const{return this->dRadius;}
double BouncingBallSphere::GetCenterX() const{return this->dCenterX;}
double BouncingBallSphere::GetCenterY() const{return this->dCenterY;}
double BouncingBallSphere::GetCenterZ() const{return this->dCenterZ;}
double BouncingBallSphere::Get_dx() const{return this->d_dx;}
double BouncingBallSphere::Get_dy() const{return this->d_dy;}
double BouncingBallSphere::Get_dz() const{return this->d_dz;}
double BouncingBallSphere::GetRed() const{return this->r;}
double BouncingBallSphere::GetGreen() const{return this->g;}
double BouncingBallSphere::GetBlue() const{return this->b;}
bool   BouncingBallSphere::get_solid() const{return this->bSolid;}
