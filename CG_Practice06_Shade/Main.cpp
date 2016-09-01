#include <glut.h>

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glShadeModel(GL_SMOOTH);

	glBegin(GL_TRIANGLES);

	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(0.0f, 1.f, 0.f);

	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(-1.f, -1.f, 0.f);

	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(1.f, -1.f, 0.f);

	glEnd();

	glFlush();
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(512, 512);
	glutInitWindowPosition(220, 220);

	glutCreateWindow("Smooth Shade");

	glutDisplayFunc(RenderScene);

	glClearColor(0.1f, 0.1f, 0.1f, 1.f);

	glutMainLoop();
}