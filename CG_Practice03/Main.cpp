#include "glut.h"
#include "math.h"

//gl model

//start(push) mark : put datas(queue) : end(pop) mark
//loop : end connects to start
//strip : first three points make triangle
//then last two points of triangle and new point make triangle
//fan : first point fixed, and last point, new point make triangle

//How to draw triangle
//clockwise / counter-clockwise winding rule
//- differ in normal vector direction
//(right hand coord.)

const int WIN_WIDTH = 512;
const int WIN_HEIGHT = 512;

const bool RunCulling = true;
const bool RunDepthTest = false;
const bool RunOutline = true;

const float PI = 3.1415f;
GLfloat gXRot = 0.0f;
GLfloat gYRot = 0.0f;

void ChangeSize(int w, int h);
void KeyControl(int key, int x, int y);
void RenderScene();
void SetupRC();

int main()
{
	glutInitDisplayMode(
		GLUT_DOUBLE |
		GLUT_RGB |
		GLUT_DEPTH);
	glutInitWindowPosition(WIN_WIDTH, 
							WIN_HEIGHT);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Spring Vertex");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	if (w <= h)
		glOrtho(-nRange, nRange,
			-nRange * h / w, nRange * h / w,
			-nRange, nRange);
	else
		glOrtho(-nRange* w / h, nRange * w / h,
			-nRange, nRange,
			-nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void KeyControl(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		gXRot -= 5.f;
		break;
	case GLUT_KEY_DOWN:
		gXRot += 5.f;
		break;
	case GLUT_KEY_LEFT:
		gYRot -= 5.f;
		break;
	case GLUT_KEY_RIGHT:
		gYRot += 5.f;
		break;
	}

	glutPostRedisplay();
}

void RenderScene()
{
	int pivot = 1;

	glClear(GL_COLOR_BUFFER_BIT);
	
	if (RunCulling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
	if (RunDepthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	if (RunOutline)
		glPolygonMode(GL_BACK, GL_LINE);
	else
		glPolygonMode(GL_BACK, GL_FILL);

	glPushMatrix();
	glRotatef(gXRot, 1.f, 0.f, 0.f);
	glRotatef(gYRot, 0.f, 1.f, 0.f);

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.f, 0.f, 75.f);
	for (GLfloat angle = 0.f;
		angle < 2.f * PI;
		angle += PI / 8.f)
	{
		GLfloat x, y;

		x = 50.f * sin(angle);
		y = 50.f * cos(angle);

		if (pivot == 0)
			glColor3f(0.f, 1.f, 0.f);
		else
			glColor3f(1.f, 0.f, 0.f);

		pivot = (++pivot) % 2;

		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.f, 0.f);
	for (GLfloat angle = 0.f;
		angle < 2.f * PI;
		angle += PI / 8.f)
	{
		GLfloat x, y;
		x = 50.f * sin(angle);
		y = 50.f * cos(angle);

		if (pivot == 0)
			glColor3f(0.f, 1.f, 0.f);
		else
			glColor3f(1.f, 0.f, 0.f);

		pivot = (++pivot) % 2;
		
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glColor3f(0.f, 1.f, 0.f);
	glShadeModel(GL_FLAT);
	glFrontFace(GL_CW);
}
