#pragma once

#include <vector>
#include "GraphicTypes.h"

class Character;

class GameManager
{
public:
	GameManager(int winWidth, int winHeight);
	~GameManager();
	void Draw();
	void Update(int deltaTime);

	void WinSizeChanged(int w, int h);
	void SetInput(unsigned char key);
	void DelInput(unsigned char key);

private:
	void ProcessInput();
	void LevelUp();
	void ApplyNewWindow();
	void DarkenWorld();

private:
	enum GameState : int
	{
		PLAY = 0,
		GONG = 1,
	};

private:
	GameState m_gameState;
	unsigned char m_input;
	Character* m_character;
	vec2 m_winSize;
	int m_horizon;
};