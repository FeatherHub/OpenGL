#include "OpenGLRenderer.h"
#include <glut.h>

#include "OpenGLLogic.h"
#include "Square.h"

OpenGLRenderer* OpenGLRenderer::m_instance = nullptr;

OpenGLRenderer* OpenGLRenderer::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new OpenGLRenderer();
	
	return m_instance;
}

OpenGLRenderer::~OpenGLRenderer()
{
	if (m_instance != nullptr)
		delete m_instance;
}

OpenGLRenderer::OpenGLRenderer()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(Config::DefaultWidth, Config::DefaultHegiht);

	glutCreateWindow(TITLE);

	glutDisplayFunc(Callback::OnDisplayCall);

	glutReshapeFunc(Callback::OnWindowChanged);

	glutTimerFunc(Config::OnTickInterval, Callback::OnTickCall, Config::OnTickVal);

	glClearColor(CLEAR_R, CLEAR_G, CLEAR_B, CLEAR_A);
}

void OpenGLRenderer::Init()
{
	OpenGLLogic::GetInstance()->SetWinSize(Config::DefaultWidth, Config::DefaultHegiht);
}

void OpenGLRenderer::Run()
{
	glutMainLoop();
}

namespace Callback
{
	void OnDisplayCall()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		auto squres = OpenGLLogic::GetInstance()->GetSquares();
		
		for (auto& s : *squres)
		{
			auto& c = s.GetRGBA();
			glColor3f(c.red, c.green, c.blue);

			Point& pos = s.GetPosition();
			int sz = s.GetSize();
			glRectf(pos.x, pos.y, pos.x+sz, pos.y+sz);
		}
		
		glutSwapBuffers();
	}

	void OnTickCall(int val)
	{
		glutPostRedisplay();

		OpenGLLogic::GetInstance()->UpdateSquares();

		glutTimerFunc(33, OnTickCall, Config::OnTickVal);
	}

	void OnWindowChanged(int w, int h)
	{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float newWidth, newHeight;

		if (w <= h)
		{
			newWidth = 100.f;
			newHeight = 100.f * h / w;

			glOrtho(-100.f, 100.f, -100.f * h / w, 100.f*h / w, 1.f, -1.f);
		}
		else
		{
			newWidth = 100.f * w / h;
			newHeight = 100.f;

			glOrtho(-100.f * w / h, 100.f*w / h, -100.f, 100.f, 1.f, -1.f);
		}

		OpenGLLogic::GetInstance()->SetWinSize(newWidth, newHeight);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}