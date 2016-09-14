#include "ColorCube.h"
#include "glut.h"

enum : int
{
	//F: Front	B: Back
	//L: Left	R: Right
	//T: Top	B: Bottom

	//Naming protocol : ZXY
	//Ex) BRT means Back(z) Right(x) Top(y)

	FLB = 0, FLT = 1, FRB = 2, FRT = 3,
	BLB = 4, BLT = 5, BRB = 6, BRT = 7,
	X = 0, Y = 1, Z = 2,

	R = 0, G = 1, B = 2
};

void ColorCube::Init()
{
	//Init Vertices 
	m_vs[BRB][X] = m_vs[BRT][X] = m_vs[FRB][X] = m_vs[FRT][X] = 1.f;
	m_vs[BLB][X] = m_vs[BLT][X] = m_vs[FLB][X] = m_vs[FLT][X] = -1.f;
	 
	m_vs[BLT][Y] = m_vs[BRT][Y] = m_vs[FLT][Y] = m_vs[FRT][Y] = 1.f;
	m_vs[BLB][Y] = m_vs[BRB][Y] = m_vs[FLB][Y] = m_vs[FRB][Y] = -1.f;

	m_vs[FLB][Z] = m_vs[FLT][Z] = m_vs[FRB][Z] = m_vs[FRT][Z] = 1.f;
	m_vs[BLB][Z] = m_vs[BLT][Z] = m_vs[BRB][Z] = m_vs[BRT][Z] = -1.f;

	//Init Colors
	m_cs[BRB][R] = m_cs[BRT][R] = m_cs[FRB][R] = m_cs[FRT][R] = 1.f;
	m_cs[BLB][R] = m_cs[BLT][R] = m_cs[FLB][R] = m_cs[FLT][R] = -1.f;
	 
	m_cs[BLT][G] = m_cs[BRT][G] = m_cs[FLT][G] = m_cs[FRT][G] = 1.f;
	m_cs[BLB][G] = m_cs[BRB][G] = m_cs[FLB][G] = m_cs[FRB][G] = -1.f;

	m_cs[FLB][B] = m_cs[FLT][B] = m_cs[FRB][B] = m_cs[FRT][B] = 1.f;
	m_cs[BLB][B] = m_cs[BLT][B] = m_cs[BRB][B] = m_cs[BRT][B] = -1.f;
}

void ColorCube::Draw()
{
	//Front Face Rule : Clockwise

	glBegin(GL_QUADS);

	//draw face : cw
	glColor3fv(m_cs[FLB]);
	glVertex3fv(m_vs[FLB]);

	glColor3fv(m_cs[FLT]);
	glVertex3fv(m_vs[FLT]);
	
	glColor3fv(m_cs[FRT]);
	glVertex3fv(m_vs[FRT]);
	
	glColor3fv(m_cs[FRB]);
	glVertex3fv(m_vs[FRB]);

	//draw back : ccw
	glColor3fv(m_cs[BLT]);
	glVertex3fv(m_vs[BLT]);

	glColor3fv(m_cs[BLB]);
	glVertex3fv(m_vs[BLB]);

	glColor3fv(m_cs[BRB]);
	glVertex3fv(m_vs[BRB]);
	
	glColor3fv(m_cs[BRT]);
	glVertex3fv(m_vs[BRT]);

	//draw top : cw
	glColor3fv(m_cs[FRT]);
	glVertex3fv(m_vs[FRT]);

	glColor3fv(m_cs[FLT]);
	glVertex3fv(m_vs[FLT]);

	glColor3fv(m_cs[BLT]);
	glVertex3fv(m_vs[BLT]);

	glColor3fv(m_cs[BRT]);
	glVertex3fv(m_vs[BRT]);

	//draw bottom : ccw
	glColor3fv(m_cs[FLB]);
	glVertex3fv(m_vs[FLB]);

	glColor3fv(m_cs[FRB]);
	glVertex3fv(m_vs[FRB]);

	glColor3fv(m_cs[BRB]);
	glVertex3fv(m_vs[BRB]);

	glColor3fv(m_cs[BLB]);
	glVertex3fv(m_vs[BLB]);

	//draw right side : cw
	glColor3fv(m_cs[FRB]);
	glVertex3fv(m_vs[FRB]);

	glColor3fv(m_cs[FRT]);
	glVertex3fv(m_vs[FRT]);

	glColor3fv(m_cs[BRT]);
	glVertex3fv(m_vs[BRT]);

	glColor3fv(m_cs[BRB]);
	glVertex3fv(m_vs[BRB]);

	//draw left side : ccw
	glColor3fv(m_cs[FLT]);
	glVertex3fv(m_vs[FLT]);

	glColor3fv(m_cs[FLB]);
	glVertex3fv(m_vs[FLB]);

	glColor3fv(m_cs[BLB]);
	glVertex3fv(m_vs[BLB]);

	glColor3fv(m_cs[BLT]);
	glVertex3fv(m_vs[BLT]);

	glEnd();
}