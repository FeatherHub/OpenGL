#include "glut.h"
#include <math.h>

const float PI = 3.1415f;
static float gRotX = 0.f;
static float gRotY = 0.f;

constexpr bool ISKEY(int inputKey, int glutKeyCode) { 
	return inputKey == glutKeyCode ? true : false;
}

void RenderScene();
//void OnTimeTick(int val);
void OnChangeSize(int w, int h);
void OnKeyPressed(int key, int x, int y);
void Init();

void main()
{
	//������ �ֿ� �ɼǵ�***
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	//â��ġ ����
	glutInitWindowPosition(0, 0);
	//âũ�� ����
	glutInitWindowSize(512, 512);
	//â ����***
	glutCreateWindow("SpringVertex");

	//������ �ݹ� ���
	glutDisplayFunc(RenderScene);
	//������Ʈ �ݹ� ���
//	glutTimerFunc(33, OnTimeTick, 1);
	//â���� �ݹ� ���
	glutReshapeFunc(OnChangeSize);
	//Ű�Է� �ݹ� ���
	glutSpecialFunc(OnKeyPressed);

	Init();

	//openGL �Լ��� �ݺ��Ѵ�
	glutMainLoop();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glRotatef(gRotX, 1.f, 0.f, 0.f);
	glRotatef(gRotY, 0.f, 1.f, 0.f);
	glBegin(GL_POINTS);

	GLfloat z = -50.f;

	GLfloat ae = 3.f;
	GLfloat pe = 30.f;
	GLfloat ze = 1.2f;

	for (GLfloat angle = 0.f;
		angle <= 2.0f * PI * ae;
		angle += 0.1f)
	{
		GLfloat x = pe * sin(angle);
		GLfloat y = pe * cos(angle);
		glVertex3f(x, y, z);

		z += ze;
	}

	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

/*
void OnTimeTick(int val)
{

}
*/

void OnChangeSize(int w, int h)
{
	GLfloat range = 100.f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	if (w <= h) //Ȧ��
		glOrtho(-range, range, 
			-range*h/w, range*h/w, 
			-range, range);
	else //������
		glOrtho(-range*w/h, range*w/h,
			-range, range,
			-range, range);

	//���󺹱�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void OnKeyPressed(int key, int x, int y)
{
	if (ISKEY(key, GLUT_KEY_UP))
		gRotX -= 5.0f;

	if (ISKEY(key, GLUT_KEY_DOWN))
		gRotX += 5.0f;

	if (ISKEY(key, GLUT_KEY_LEFT))
		gRotY -= 5.0f;

	if (ISKEY(key, GLUT_KEY_RIGHT))
		gRotY += 5.0f;

	//Render �Լ��� **
	glutPostRedisplay();
}

void Init()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glColor3f(0.f, 1.f, 0.f);
}
