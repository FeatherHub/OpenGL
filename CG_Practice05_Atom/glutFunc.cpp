#include "glutFunc.h"
#include "glut.h"

const float PI = 3.1415f;

GLfloat rotX = 0.f;
GLfloat rotY = 0.f;

GLfloat elect = 0.f;

void gl::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.f, 0.f, -100.f);
	glColor3ub(255, 0, 0);
	glutSolidSphere(10.f, 15, 15);

	glPushMatrix();
	glRotatef(elect, 0.f, 1.f, 0.f);
	glTranslatef(90.f, 0.f, 0.f);
	glColor3ub(255, 255, 0);
	glutSolidSphere(6.f, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(elect, 0.f, 1.f, 0.f);
	glTranslatef(90.f, 0.f, 0.f);
	glColor3ub(255, 255, 0);
	glutSolidSphere(6.f, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45.f, 0.f, 0.f, 1.f);
	glRotatef(elect, 0.f, 1.f, 0.f);
	glTranslatef(-70.f, 0.f, 0.f);
	glutSolidSphere(6.f, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90.f, 0.f, 0.f, 1.f);
	glRotatef(elect, 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, 60.f);
	glutSolidSphere(6.f, 15, 15);
	glPopMatrix();

	elect += 10.f;
	if (elect > 360.f)
		elect = 0.f;

	glutSwapBuffers();
}

void gl::OnTimeTick(int val)
{
	glutPostRedisplay();
	glutTimerFunc(33, OnTimeTick, 0);
}

void gl::OnChangeSize(int w, int h)
{
	GLfloat range = 100.f;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-range, range,
			-range*h / w, range*h / w,
			-range*2.f, range*2.f);
	else
		glOrtho(-range*w / h, range*w / h,
			-range, range,
			-range*2.f, range*2.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void gl::OnKeyPressed(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotX += 5.f;
		break;
	case GLUT_KEY_DOWN:
		rotX -= 5.f;
		break;
	case GLUT_KEY_RIGHT:
		rotY += 5.f;
		break;
	case GLUT_KEY_LEFT:
		rotY -= 5.f;
		break;
	}
}

void gl::Init()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}