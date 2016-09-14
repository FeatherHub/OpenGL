#include "GLManager.h"
#include "ColorCube.h"
#include "glut.h"

//Init static members
ColorCube* GLManager::m_colorCube = nullptr;
float GLManager::m_rotX = 0.f;
float GLManager::m_rotY = 0.f;

GLManager::~GLManager()
{
	if (m_colorCube != nullptr)
		delete m_colorCube;
}

void GLManager::Init()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Color Cube");
	
	glutDisplayFunc(GLManager::RenderScene);
	glutReshapeFunc(GLManager::OnWindowChange);
	glutSpecialFunc(GLManager::OnKeyPressed);

	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);

	m_colorCube = new ColorCube();
	m_colorCube->Init();
}

void GLManager::Run()
{
	glutMainLoop();
}

void GLManager::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glRotatef(m_rotX, 1.f, 0.f, 0.f);
	glRotatef(m_rotY, 0.f, 1.f, 0.f);

	m_colorCube->Draw();

	glPopMatrix();

	glFlush();
}

void GLManager::OnWindowChange(int w, int h)
{
	GLfloat range = 2.5f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	if (w <= h)
		glOrtho(-range, range, -range*h / w, range*h / w, -range, range);
	else
		glOrtho(-range*w / h, range*w / h, -range, range, -range, range);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void GLManager::OnKeyPressed(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		m_rotX += 5.f;
		break;
	case GLUT_KEY_DOWN:
		m_rotX -= 5.f;
		break;
	case GLUT_KEY_RIGHT:
		m_rotY += 5.f;
		break;
	case GLUT_KEY_LEFT:
		m_rotY -= 5.f;
		break;
	}

	glutPostRedisplay();
}