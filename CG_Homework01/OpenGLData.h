#pragma once

#include <vector>
class Square;

class OpenGLData
{
public:
	static std::vector<Square>* CreateSquareData();

private:
	enum 
	{
		MAX_SQUARE_NUM = 20,
		MAX_X = 800,
		MAX_Y = 600,
		SQUARE_SIZE = 10,
		MAX_SQUARE_SPEED = 5
	};
};