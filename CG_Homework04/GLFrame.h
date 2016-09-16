#pragma once

class GameManager;

class GLFrame
{
public:
	GLFrame(int winWidth, int winHeight);
	~GLFrame();

	void Init(void(*updateCallback)(int));
	void RenderScene();
	void Update();
	void OnKeyPressed(unsigned char key);
	void OnKeyReleased(unsigned char key);
	void OnChangeSize(int w, int h);

public:
	enum 
	{ 
		FRAME_UPDATE_DELTA = 17, 
	};

private:
	GameManager* m_gm;
	void(*m_updateCallback)(int);
};