#pragma once

#include <vector>
class Square;

class OpenGLLogic
{
public:
	static OpenGLLogic* GetInstance();
	~OpenGLLogic();

	void UpdateSquares();

	std::vector<Square>* GetSquares() { return m_squres; }
	void SetWinSize(float w, float h);

private:
	void ConstrainSqares();
	void CollisionCheckSqures();
	void MoveSquares();

private:
	OpenGLLogic();
	static OpenGLLogic* m_instance;

	std::vector<Square>* m_squres;
	
	float m_winSizeWidth;
	float m_winSizeHeight;
};