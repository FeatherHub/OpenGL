#include "OpenGLRenderer.h"

int main()
{
	auto openGL = OpenGLRenderer::GetInstance();

	openGL->Init();

	openGL->Run();

	return 0;
}