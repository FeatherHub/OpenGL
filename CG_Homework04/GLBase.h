#pragma once

class GLFrame;

class GLBase
{
public:
	GLBase();
	~GLBase();
	void Init();

private:
	const char* APP_TITLE = "wasd : move | j : jump";
	enum Config : int
	{ 
		WIN_WIDTH = 640, 
		WIN_HEIGHT = 480,
		APP_INIT_POS_X = 60,
		APP_INIT_POS_Y = 60
	};

private:
	static GLFrame* m_glFrame;
};