#include "GLInterface.h"
#include "GLLogic.h"
#include "glut.h"

GLLogic* GLInterface::m_glLogic = nullptr;

GLInterface::~GLInterface()
{
	if (m_glLogic != nullptr)
		delete m_glLogic;
}

void GLInterface::Init()
{
	if (m_glLogic != nullptr) //Prevent init multiple times
	{
		return;
	}

	auto updateCallback = [](int val) { m_glLogic->Update(); };

	m_glLogic = new GLLogic();
	m_glLogic->Init(updateCallback);
	
	glutDisplayFunc([]() { m_glLogic->RenderScene(); });
	glutTimerFunc(GLLogic::UPDATE_DELTA, updateCallback, 0);
	glutReshapeFunc([](int w, int h) { m_glLogic->OnWindowChanged(w, h); });
	glutSpecialFunc([](int key, int x, int y) { m_glLogic->OnKeyPressed(key); });
}

void GLInterface::Run()
{
	glutMainLoop();
}