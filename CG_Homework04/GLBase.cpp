#include "GLBase.h"
#include "GLFrame.h"
#include "glut.h"

GLFrame* GLBase::m_glFrame = nullptr;

GLBase::GLBase()
{
	m_glFrame = new GLFrame(WIN_WIDTH, WIN_HEIGHT);
}

GLBase::~GLBase()
{
	if (m_glFrame != nullptr)
		delete m_glFrame;
}

void GLBase::Init()
{
	//init glut display options
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
	glutInitWindowPosition(APP_INIT_POS_X, APP_INIT_POS_Y);
	glutCreateWindow(APP_TITLE);

	//init openGL frame
	void(*updateCallback)(int) = [](int val) { m_glFrame->Update(); };
	m_glFrame->Init(updateCallback);

	//register callbacks
	glutDisplayFunc([]() {m_glFrame->RenderScene(); });
	glutTimerFunc(GLFrame::FRAME_UPDATE_DELTA, updateCallback, 0);
	glutReshapeFunc([](int w, int h) {m_glFrame->OnChangeSize(w, h); });
	glutKeyboardFunc([](unsigned char key, int x, int y) {m_glFrame->OnKeyPressed(key); });
	glutKeyboardUpFunc([](unsigned char key, int x, int y) {m_glFrame->OnKeyReleased(key); });

	//start
	glutMainLoop();
}