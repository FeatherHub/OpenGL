#pragma once

class ColorCube;

class GLManager
{
public:
	GLManager() = default;
	~GLManager();
	void Init();
	void Run();
	
private:
	//Add static for registering GL callback
	static void RenderScene();
	static void OnWindowChange(int w, int h);
	static void OnKeyPressed(int key, int x, int y);

private:
	//Add static for using in GL callback
	static ColorCube* m_colorCube;
	static float m_rotX;
	static float m_rotY;
};