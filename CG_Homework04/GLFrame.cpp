#include "GLFrame.h"
#include "GameManager.h"
#include "glut.h"

GLFrame::GLFrame(int winWidth, int winHeight)
{
	m_gm = new GameManager(winHeight, winHeight);
}

GLFrame::~GLFrame()
{
	if (m_gm != nullptr)
	{
		delete m_gm;
	}
}

void GLFrame::Init(void(*updateCallback)(int))
{
	m_updateCallback = updateCallback;

	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.8f, 0.8f, 0.8f, 1.f);
}

void GLFrame::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_gm->Draw();

	glutSwapBuffers();
}

void GLFrame::Update()
{
	m_gm->Update(FRAME_UPDATE_DELTA);

	glutTimerFunc(FRAME_UPDATE_DELTA, m_updateCallback, 0);
	glutPostRedisplay();
}

void GLFrame::OnKeyPressed(unsigned char key)
{
	m_gm->SetInput(key);
}

void GLFrame::OnKeyReleased(unsigned char key)
{
	m_gm->DelInput(key);
}

void GLFrame::OnChangeSize(int w, int h)
{
	m_gm->WinSizeChanged(w, h);
}