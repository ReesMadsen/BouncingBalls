#ifndef _BOUNCINGBALLSPHERE_H_
#define _BOUNCINGBALLSPHERE_H_

class BouncingBallSphere
{
public:
	// Constructor.
	BouncingBallSphere(
		const double x_in,
		const double y_in,
		const double z_in,
		const double radius_in,
		const double dx_in,
		const double dy_in,
		const double dz_in,
		const double r_in,
		const double g_in,
		const double b_in);

	//operator overloading >, ==
	bool operator>(const BouncingBallSphere& rhs);
	bool operator==(const BouncingBallSphere& rhs);

	//other methods
	void paint(const double V, const double screen_x, const double screen_y) const;
	void paint_shadow(const double V, const double screen_x, const double screen_y) const;
	//get methods
	double GetRadius() const;
	double GetCenterX() const;
	double GetCenterY() const;
	double GetCenterZ() const;
	double Get_dx() const;
	double Get_dy() const;
	double Get_dz() const;
	double GetRed() const;
	double GetGreen() const;
	double GetBlue() const;
	bool get_solid() const;

	//set methods
	void SetRadius(const double dRadiusIn);
	void SetCenterX(const double dXCenterIn);
	void SetCenterY(const double dYCenterIn);
	void SetCenterZ(const double dZCenterIn);
	void Set_dx(const double dxIn);
	void Set_dy(const double dyIn);
	void Set_dz(const double dzIn);
	void Set_rgb(const double dRed_in, const double dGreen_in, const double dBlue_in);
	void SetSolid(const bool bState);

private:
	double dRadius;
	double dCenterX,dCenterY,dCenterZ; //center of circle
	double d_dx,d_dy,d_dz;		       //velocity
	double r,g,b;					   //color
	bool   bSolid;
};

struct vectortype
{
	double x;
	double y;
	double z;
};

#endif /* _BOUNCINGBALLSPHERE_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */