#include "App.h"
#include "GLBase.h"

App::~App()
{
	if (m_glBase != nullptr)
	{
		delete m_glBase;
	}
}

void App::Init()
{
	m_glBase = new GLBase();
	
	m_glBase->Init();
}