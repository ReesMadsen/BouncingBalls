#include "BouncingBallsEnvironment.h"
#include <time.h>

#ifdef _WIN32
  #include "glut.h"
#else
  #ifdef __APPLE__
    #include <GLUT/glut.h>
  #else
    #include <GL/glut.h>
  #endif
#endif

BouncingBallsEnvironment::BouncingBallsEnvironment()
	: dSizeX(700),
	  dSizeY(500),
	  dSizeZ(700),
	  dViewDistance(1000),
	  nCircles(6),
	  dMax_dx(.3),
	  dMax_dy(.3),
	  dMax_dz(.3),
	  dGravity_x(0),
	  dGravity_y(0.0004),
	  dGravity_z(0)
{
		//circles[i]= Circle(200,200,50,.2,.1,0,0,0);
	srand(time(0));
	double X,Y,Z,R,DX,DY,DZ,r,g,b;
	//ind = rand()%count;
	int i;
	int j;
	bool flag;
	for(i=0; i<nCircles; i++)
	{
		R=rand()%(nMaxRadius-nMinRadius)+nMinRadius;
		X=rand()%int(dSizeX-2*(R+1))+R+1;
		Y=rand()%int(dSizeY-2*(R+1))+R+1;
		Z=rand()%int(dSizeZ-2*(R+1))+R+1;
		DX=double(rand()%int(dMax_dx*200))/100-dMax_dx;
		DY=double(rand()%int(dMax_dy*200))/100-dMax_dy;
		DZ=double(rand()%int(dMax_dz*200))/100-dMax_dz;
		r=double(rand()%100)/100;
		g=double(rand()%100)/100;
		b=double(rand()%100)/100;

		// These are cleaned up in the destructor of BouncingBallsEnviornment.
		BouncingBallSphere *pBBSphere=
			new BouncingBallSphere(X,Y,Z,R,DX,DY,DZ,r,g,b);

		aSpheres.push_back(pBBSphere);

		if(i==0)
		{
			aSpheres[i]->SetSolid(true);
		}
		else
		{
			flag = true;
			for(j=0; j<i; j++)
			{
				if(*(aSpheres[j])==*(aSpheres[i]))
				{
					flag = false;
				}
			}
			aSpheres[i]->SetSolid(flag);
		}
	}
	SortBalls();
}

// Destructor.
BouncingBallsEnvironment::~BouncingBallsEnvironment()
{
	int nBallIndex;
	for(nBallIndex=0; nBallIndex < nCircles; nBallIndex++)
	{
		delete aSpheres[nBallIndex];
	}
}

////////////////////////////////////////////
//
// Draw functionality
//
////////////////////////////////////////////

void BouncingBallsEnvironment::DrawWalls()
{
	double x1 = dSizeZ*dSizeX/(2*dViewDistance+2*dSizeZ);
	double y1 = dSizeZ*dSizeY/(2*dViewDistance+2*dSizeZ);
	double x2 = dSizeX-x1;
	double y2 = dSizeY-y1;

	//background
	glColor3d(.6, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x1,y2);
	glVertex2d(x2,y2);
	glVertex2d(x2,y1);
	glEnd();

	//walls
	glColor3d(.7, 0, 0);//left wall
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x1,y2);
	glVertex2d(0,dSizeY);
	glVertex2d(0,0);
	glEnd();

	glColor3d(.7, .1, 0);//bottom wall
	glBegin(GL_QUADS);
	glVertex2d(0,0);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(dSizeX,0);
	glEnd();

	glColor3d(.6, .1, 0);//right wall
	glBegin(GL_QUADS);
	glVertex2d(dSizeX,0);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(dSizeX,dSizeY);
	glEnd();

	glColor3d(.5, 0, 0);//right wall
	glBegin(GL_QUADS);
	glVertex2d(x2,y2);
	glVertex2d(dSizeX,dSizeY);
	glVertex2d(0,dSizeY);
	glVertex2d(x1,y2);
	glEnd();
}

void BouncingBallsEnvironment::DrawShadows()
{
	int nBallIndex;
	for(nBallIndex=0; nBallIndex < nCircles; nBallIndex++)
	{
		aSpheres[nBallIndex]->paint_shadow(dViewDistance,dSizeX,dSizeY);
	}

}

void BouncingBallsEnvironment::DrawBalls()
{
	int nBallIndex;
	for(nBallIndex=0; nBallIndex < nCircles; nBallIndex++)
	{
		aSpheres[nBallIndex]->paint(dViewDistance,dSizeX,dSizeY);
	}
}

void BouncingBallsEnvironment::DrawBouncingBalls()
{
	DrawWalls();
	DrawShadows();
	DrawBalls();
}

////////////////////////////////////////////
//
// Move functionality.
//
////////////////////////////////////////////

void BouncingBallsEnvironment::MoveBalls()
{
	int i;
	for(i=0; i < this->nCircles; i++)
	{
		aSpheres[i]->SetCenterX(aSpheres[i]->GetCenterX()+aSpheres[i]->Get_dx());
		aSpheres[i]->SetCenterY(aSpheres[i]->GetCenterY()+aSpheres[i]->Get_dy());
		aSpheres[i]->SetCenterZ(aSpheres[i]->GetCenterZ()+aSpheres[i]->Get_dz());
	}
}

static void TestSolid(int index, 
					  int nCircles,
					  std::vector<BouncingBallSphere *> &aSpheres)
{
	int i;
	bool flag = true;
	for(i=0;i<nCircles && i!=index; i++)
	{
		if(*(aSpheres[i])==*(aSpheres[index]))
		{
			flag = false;
		}
	}
	aSpheres[index]->SetSolid(flag);
}

static double DotProduct(vectortype a,
					     vectortype b)
{
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

static void Collide(int p1,
				    int p2,
					std::vector<BouncingBallSphere *> &aSpheres)
{
	//std::cout << "collide " << p1 << p2 << std::endl;
	vectortype en;   // dirction of impulse vector
	vectortype u[2]; // initial velocities of two particles
	vectortype I;    //impulse felt by each particle
	vectortype v[2]; // final velocities of two particles
	double m[2];	 // mass of two particles
	double k;
	int i;

	en.x=aSpheres[p1]->GetCenterX() - aSpheres[p2]->GetCenterX();
	en.y=aSpheres[p1]->GetCenterY() - aSpheres[p2]->GetCenterY();
	en.z=aSpheres[p1]->GetCenterZ() - aSpheres[p2]->GetCenterZ();
	//size = sqrt(xdif*xdif+ydif*ydif+zdif*zdif);
	//en.x= xdif/size;
	//en.y= ydif/size;
	//en.z= zdif/size;
	// set u values
	u[0].x=aSpheres[p1]->Get_dx();
	u[0].y=aSpheres[p1]->Get_dy();
	u[0].z=aSpheres[p1]->Get_dz();
	m[0]=aSpheres[p1]->GetRadius()*aSpheres[p1]->GetRadius()*aSpheres[p1]->GetRadius();
	u[1].x=aSpheres[p2]->Get_dx();
	u[1].y=aSpheres[p2]->Get_dy();
	u[1].z=aSpheres[p2]->Get_dz();
	m[1]=aSpheres[p2]->GetRadius()*aSpheres[p2]->GetRadius()*aSpheres[p2]->GetRadius();
	//k=30000;
	//double E1 =0;
	//for(i=0;i<2;i++)
	//	E1+=m[i]*(u[i].x*u[i].x+u[i].y*u[i].y+u[i].z*u[i].z);
	k=2*(DotProduct(u[1],en)-DotProduct(u[0],en))*m[1]*m[0]/((m[0]+m[1])*DotProduct(en,en));
	//std::cout << k << std::endl;
	I.x = en.x*k;
	I.y = en.y*k;
	I.z = en.z*k;
	// set v values
	for(i=0;i<2;i++)
	{
		v[i].x = u[i].x +(1-2*i)*I.x/m[i]*dCollisionFriction;
		v[i].y = u[i].y +(1-2*i)*I.y/m[i]*dCollisionFriction;
		v[i].z = u[i].z +(1-2*i)*I.z/m[i]*dCollisionFriction;
	}
	//double E2 =0;
	//for(i=0;i<2;i++)
	//	E2+=m[i]*(v[i].x*v[i].x+v[i].y*v[i].y+v[i].z*v[i].z);
	//std::cout << "E1 = " << E1 << ", E2 = "<< E2 << ", percent loss = " << (E1-E2)/E1*100 << std::endl;
	// reset particle values
	aSpheres[p1]->Set_dx(v[0].x);
	aSpheres[p1]->Set_dy(v[0].y);
	aSpheres[p1]->Set_dz(v[0].z);
	aSpheres[p2]->Set_dx(v[1].x);
	aSpheres[p2]->Set_dy(v[1].y);
	aSpheres[p2]->Set_dz(v[1].z);
	aSpheres[p1]->SetSolid(false);
	aSpheres[p2]->SetSolid(false);
} /* Collide */

void BouncingBallsEnvironment::HandleCollisions()
{
	int i;
	double x,y,z,r,dx,dy,dz;
	for(i = 0; i<nCircles; i++)
	{
		//get info on circle
		r = aSpheres[i]->GetRadius();
		x = aSpheres[i]->GetCenterX();
		y = aSpheres[i]->GetCenterY();
		z = aSpheres[i]->GetCenterZ();
		dx = aSpheres[i]->Get_dx();
		dy = aSpheres[i]->Get_dy();
		dz = aSpheres[i]->Get_dz();
		//check for collision with wall
		if(x-r<0)//wall
		{
			if(dx>0)
			{
				dx*=-1;
			}
			//bring it back a step
			aSpheres[i]->Set_dx(-dx*dWallFriction);
			aSpheres[i]->Set_dy(dy*dWallFriction);
			aSpheres[i]->Set_dz(dz*dWallFriction);
			aSpheres[i]->SetCenterX(x-dx);
		}
		if(x+r>dSizeX)//wall
		{
			if(dx<0)
				dx*=-1;
			//bring it back a step
			aSpheres[i]->Set_dx(-dx*dWallFriction);
			aSpheres[i]->Set_dy(dy*dWallFriction);
			aSpheres[i]->Set_dz(dz*dWallFriction);
			aSpheres[i]->SetCenterX(x-dx);
		}
		if(y-r<0)//wall
		{
			if(dy>0)
				dy*=-1;
			if(dy == 0)
			{
				//no wall fricion
				aSpheres[i]->Set_dx(dx*dWallFriction);
				aSpheres[i]->Set_dy(-dy);
				aSpheres[i]->Set_dz(dz*dWallFriction);
				aSpheres[i]->SetCenterY(y-dy);
			}
			else
			{
				//bring it back a step
				aSpheres[i]->Set_dx(dx*dWallFriction);
				aSpheres[i]->Set_dy(-dy*dWallFriction);
				aSpheres[i]->Set_dz(dz*dWallFriction);
				aSpheres[i]->SetCenterY(y-dy);
			}
		}
		if(y+r>dSizeY)//wall
		{
			if(dy<0)
				dy*=-1;
			//bring it back a step
			aSpheres[i]->Set_dx(dx*dWallFriction);
			aSpheres[i]->Set_dy(-dy*dWallFriction);
			aSpheres[i]->Set_dz(dz*dWallFriction);
			aSpheres[i]->SetCenterY(y-dy);
		}
		if(z-r<0)//wall
		{
			if(dz>0)
				dz*=-1;
			//bring it back a step
			aSpheres[i]->Set_dx(dx*dWallFriction);
			aSpheres[i]->Set_dy(dy*dWallFriction);
			aSpheres[i]->Set_dz(-dz*dWallFriction);
			aSpheres[i]->SetCenterZ(z-dz);
		}
		if(z+r>dSizeZ)//wall
		{
			if(dz<0)
				dz*=-1;
			//bring it back a step
			aSpheres[i]->Set_dx(dx*dWallFriction);
			aSpheres[i]->Set_dy(dy*dWallFriction);
			aSpheres[i]->Set_dz(-dz*dWallFriction);
			aSpheres[i]->SetCenterZ(z-dz);
		}
	}

	int j;
	for(i=0; i < nCircles; i++)
	{
		if(aSpheres[i]->get_solid())
		{
			for(j=0; j<i; j++)
			{
				if(*(aSpheres[i])==*(aSpheres[j]) && aSpheres[j]->get_solid())
				{
					Collide(i,j, aSpheres);
					//double ri=circles[i].get_r();
					//double gi=circles[i].get_g();
					//double bi=circles[i].get_b();
					//circles[i].set_rgb(circles[j].get_r(),circles[j].get_g(),circles[j].get_b());
					//circles[j].set_rgb(ri,gi,bi);
					j=i;
				}
			}
		}
		else
		{
			TestSolid(i,nCircles,aSpheres);
		}
	}
}

void BouncingBallsEnvironment::SortBalls()
{
	int i,j;
	bool flag = true;
	BouncingBallSphere *pTemp;
	for(i=1; i<=this->nCircles && flag; i++)
	{
		flag = false;
		for(j=0; j<this->nCircles-1; j++)
		{
			if(*this->aSpheres[j+1] > *this->aSpheres[j])
			{
				pTemp = aSpheres[j];
				this->aSpheres[j]=this->aSpheres[j+1];
				this->aSpheres[j+1] = pTemp;
				flag = true;
			}
		}
	}
}

void BouncingBallsEnvironment::HandleGravity()
{
	int i;
	for(i = 0; i<nCircles; i++)
	{
		aSpheres[i]->Set_dx((aSpheres[i]->Get_dx()-dGravity_x)*dWindResistance);
		aSpheres[i]->Set_dy((aSpheres[i]->Get_dy()-dGravity_y)*dWindResistance);
		aSpheres[i]->Set_dz((aSpheres[i]->Get_dz()-dGravity_z)*dWindResistance);
	}	
}

void BouncingBallsEnvironment::UpdateBouncingBalls()
{
	MoveBalls();
	HandleCollisions();
	SortBalls();
	HandleGravity();
}

///////////////////////////////
//
// GLUT based function calls.
//
///////////////////////////////

void BouncingBallsEnvironment::Display()
{
	DrawBouncingBalls();
	UpdateBouncingBalls();
	glutPostRedisplay();
}

void BouncingBallsEnvironment::Mouse(int nMouseButton,
									 int nState,
									 int nXVal,
									 int nYVal)
{
	if(nMouseButton == GLUT_LEFT_BUTTON && nState == GLUT_DOWN) 
	{
		double X,Y,Z,R,DX,DY,DZ,r,g,b;
		R=rand()%(nMaxRadius-nMinRadius)+nMinRadius;
		X=rand()%int(dSizeX-2*(R+1))+R+1;
		Y=rand()%int(dSizeY-2*(R+1))+R+1;
		Z=rand()%int(dSizeZ-2*(R+1))+R+1;
		DX=double(rand()%int(dMax_dx*200))/100-dMax_dx;
		DY=double(rand()%int(dMax_dy*200))/100-dMax_dy;
		DZ=double(rand()%int(dMax_dz*200))/100-dMax_dz;
		r=double(rand()%100)/100;
		g=double(rand()%100)/100;
		b=double(rand()%100)/100;

		BouncingBallSphere *pBBSphere = 
			new BouncingBallSphere(X,
								   Y,
								   Z,
								   (R+nMaxRadius)/2,
								   (DX+dMax_dx)*5,
								   (DY+dMax_dy)*5,
								   (DZ+dMax_dz)*5,
								   r,
								   g,
								   b);

		aSpheres.push_back(pBBSphere);
		bool flag = true;
		int j;
		for(j=0; j<nCircles; j++)
		{
			if(*(aSpheres[j])==*(aSpheres[nCircles]))
			{
				flag = false;
			}
		}
		aSpheres[nCircles]->SetSolid(flag);
		nCircles+=1;
	}
	if (nMouseButton == GLUT_LEFT_BUTTON && nState == GLUT_UP) 
	{
	}
	if (nMouseButton == GLUT_MIDDLE_BUTTON && nState == GLUT_DOWN) 
	{
	}
	if (nMouseButton == GLUT_MIDDLE_BUTTON && nState == GLUT_UP) 
	{
	}
}