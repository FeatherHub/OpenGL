#pragma once

class GLUquadric;

class GLLogic
{
	friend class GLInterface;
private: //core methods
	GLLogic();
	~GLLogic() = default;
	void Init(void(*updateCallback)(int));
	void RenderScene();
	void Update();
	void OnKeyPressed(int key);
	void OnWindowChanged(int w, int h);

private: //sub methods
	void InitLighting();
	unsigned int LoadTexture(const char* filePath);
	void DrawPlanet(GLUquadric* quad, unsigned char texId, int radius);

private:
	const float PI = 3.14159f;
	enum Config : int
	{
		UPDATE_DELTA = 34, /* 30fps */
		EARTH_IDX = 0,
		VENUS_IDX = 1,
		SILVA_IDX = 2,
		PLANET_NUM = 3,
	};

private:
	void(*m_updateCallback)(int);
	unsigned int m_texIds[PLANET_NUM];
	GLUquadric* m_planets[PLANET_NUM];
	float m_rotX;
	float m_rotY;
	float m_rotPlanet;
};