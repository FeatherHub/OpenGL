#include <windows.h>

#include <glut.h>

//gl : openGL �Լ�
//gl-u : gl�� �Լ� �� ���� ������ ������ ���ִٷΰ� �ϳ��� �Լ��� ����(union)
//gl-ut : ���̺귯���� ������ OS�� �°� ����ȭ

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.f, 0.f, 0.);
	glRectf(0.f, 0.f, 50.f, 30.f);

	glFlush();
}

void SetupRC(void)
{
   glClearColor(0.8f, 0.5f,1.0f,1.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	if (w <= h)
	{
		glOrtho(-100.f, 100.f, -100.f*h / w, 100.f*h / 2, 1.f, -1.f);
	}
	else
	{
		glOrtho(-100.f*w / h, 100.f*w / h, -100.f, 100.f, 1.f, -1.f);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(void)
{ 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Complex");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
}