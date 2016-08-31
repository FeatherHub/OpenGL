#include "glut.h"
#include "math.h"

//loop : end connects to start
//strip : first three points make triangle
//then last two points of triangle and new point make triangle
//fan : first point fixed, and last point, new point make triangle

//Consideration in drawing triangle
//clockwise / counter-clockwise winding rule
//-> differ in normal vector direction
//(openGL : right hand coord.)

const int WIN_WIDTH = 512;
const int WIN_HEIGHT = 512;

bool RunCulling = false;
bool RunDepthTest = false;
bool RunOutline = false;
enum class MENUID 
{
	DEPTH = 1,
	CULLING = 2,
	OUTLINE = 3,
};

const float PI = 3.1415f;
GLfloat gXRot = 0.0f;
GLfloat gYRot = 0.0f;

void ProcessMenu(int menueId);
void RenderScene();
void ChangeSize(int w, int h);
void KeyControl(int key, int x, int y);
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

	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("깊이 테스트", (int)MENUID::DEPTH);
	glutAddMenuEntry("은면 제거", (int)MENUID::CULLING);
	glutAddMenuEntry("뒷면 라인 그리기", (int)MENUID::OUTLINE);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(KeyControl);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}

void ProcessMenu(int menueId)
{
	switch (menueId)
	{
	case (int)MENUID::DEPTH:
		RunDepthTest = !RunDepthTest;
		break;
	case (int)MENUID::CULLING:
		RunCulling = !RunCulling;
		break;	
	case (int)MENUID::OUTLINE:
		RunOutline = !RunOutline;
		break;	
	}

	glutPostRedisplay();
}

void RenderScene()
{
	int pivot = 1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
		GLfloat x = 50.f * sin(angle);
		GLfloat y = 50.f * cos(angle);

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
		angle < (2.f * PI);
		angle += (PI / 8.f))
	{
		GLfloat x = 50.f * sin(angle);
		GLfloat y = 50.f * cos(angle);

		if (pivot == 0)
			glColor3f(0.f, 1.f, 0.f);
		else
			glColor3f(1.f, 0.f, 0.f);

		glVertex2f(x, y);

		pivot = (++pivot) % 2;
	}
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
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

	//Call render callback
	glutPostRedisplay();
}

void SetupRC()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glColor3f(0.f, 1.f, 0.f);
	glShadeModel(GL_FLAT);
	glFrontFace(GL_CW);
}
