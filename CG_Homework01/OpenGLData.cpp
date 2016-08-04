#include "OpenGLData.h"
#include "Square.h"
#include <random>
#include <ctime>

std::vector<Square>* OpenGLData::CreateSquareData()
{
	std::vector<Square>* squares = new std::vector<Square>();
	
	srand((unsigned int)time(NULL));
	
	for (int i = 0; i < MAX_SQUARE_NUM; i++)
	{
		squares->emplace_back(Square{ 
			Point{rand()%MAX_X - (MAX_X / 2), rand()%MAX_Y - (MAX_Y / 2)},
			SQUARE_SIZE, 
			RGBA{(rand() % 100) / 100.f, (rand() % 100) / 100.f, (rand() % 100) / 100.f, 1.0f},
			rand() % MAX_SQUARE_SPEED + 1 });
	}

	return squares;
}

