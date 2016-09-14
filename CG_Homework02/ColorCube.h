#pragma once

class ColorCube
{
public:
	ColorCube() = default;
	~ColorCube() = default;
	void Init();
	void Draw();

private:
	enum : int
	{
		CUBE_VERTEX_NUM = 8,
		DIMENSION_NUM = 3,
	};
	
private:
	float m_vs[CUBE_VERTEX_NUM][DIMENSION_NUM];
	float m_cs[CUBE_VERTEX_NUM][DIMENSION_NUM];
};