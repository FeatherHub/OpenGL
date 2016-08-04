#pragma once

class OpenGLRenderer
{
public:
	static OpenGLRenderer* GetInstance();
	~OpenGLRenderer();
	void Init();
	void Run();

private:
	static OpenGLRenderer* m_instance;
	OpenGLRenderer();

	const char* TITLE = "Bouncing rectangles";

	const float CLEAR_R = 0.3f;
	const float CLEAR_G = 0.3f;
	const float CLEAR_B = 0.3f;
	const float CLEAR_A = 1.0f;
};

namespace Callback
{
	void OnDisplayCall();
	void OnTickCall(int val);
	void OnWindowChanged(int w, int h);
}

enum Config : int
{
	DefaultWidth = 800,
	DefaultHegiht = 600,
	OnTickInterval = 1000,
	OnTickVal = 1
};
