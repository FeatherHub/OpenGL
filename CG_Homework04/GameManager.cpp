#include "GameManager.h"
#include <windows.h>
#include "glut.h"
#include "Character.h"

enum CharacterConfig
{
	CHAR_INIT_X = 0,
	CHAR_INIT_Y = -100,
	CHAR_INIT_Z = -300,
	INCREASE_SPEED = 4,
};

enum GameConfig
{
	INIT_MAX_Z = 1000,
	INCREASE_HORIZON = 300,
};

GameManager::GameManager(int winWidth, int winHeight) :
	m_input('\0'),
	m_horizon(INIT_MAX_Z),
	m_winSize(vec2{ (float)winWidth, (float)winHeight }),
	m_gameState(GameState::PLAY)
{
	m_character = new Character();
	m_character->Init();
	m_character->SetPosition(vec3{CHAR_INIT_X, CHAR_INIT_Y, CHAR_INIT_Z});
}

GameManager::~GameManager()
{
	if (m_character != nullptr)
		delete m_character;
}

void GameManager::Draw()
{
	m_character->Draw();
}

void GameManager::Update(int deltaTime)
{
	static int elapsedTime = 0;

	switch (m_gameState)
	{
	case GameState::PLAY:
	{
		ProcessInput();

		m_character->Update(deltaTime);

		const auto& charPos = m_character->GetPosition();
		if (charPos.z < -m_horizon)
		{
			LevelUp();
			m_gameState = GONG;
		}
	}
		break;
	case GameState::GONG:
	{
		elapsedTime += deltaTime;
		if (elapsedTime > 1200)
		{
			elapsedTime = 0;
			m_gameState = PLAY;
		}
		break;
	}
	}
}

void GameManager::LevelUp()
{
	PlaySound(L"gong.wav", NULL, SND_FILENAME | SND_ASYNC);

	m_character->SetPosition(vec3{ CHAR_INIT_X, CHAR_INIT_Y, CHAR_INIT_Z });
	m_character->IncreaseWalkSpeed(INCREASE_SPEED);
	m_character->ResetColor();
	m_horizon += INCREASE_HORIZON;
	ApplyNewWindow();
	DarkenWorld();
}


void GameManager::WinSizeChanged(int w, int h)
{
	m_winSize.x = w;
	m_winSize.y = h;

	ApplyNewWindow();
}

void GameManager::ApplyNewWindow()
{
	glViewport(0, 0, m_winSize.x, m_winSize.y);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	GLdouble aspect = m_winSize.x / m_winSize.y;
	gluPerspective(45.f, aspect, 1.0, m_horizon * 1.25);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.f, 0.f, -50.f);
}

void GameManager::DarkenWorld()
{
	static float r = 0.75f;
	static float g = 0.75f;
	static float b = 0.75f;

	glClearColor(r, g, b, 1);

	r -= 0.038f;
	g -= 0.038f;
	b -= 0.038f;
}

void GameManager::ProcessInput()
{
	switch (m_input)
	{
	case 'w':
		m_character->Move(FORWARD);
		break;
	case 'a':
		m_character->Move(LEFT);
		break;
	case 's':
		m_character->Move(BACKWARD);
		break;
	case 'd':
		m_character->Move(RIGHT);
		break;
	case 'j':
		m_character->Jump();
		break;
	}
}

void GameManager::SetInput(unsigned char key)
{
	switch (key)
	{
	case 'w': case 'a': case 's':
	case 'd': case 'j': //set of valid inputs
		m_input = key;
		break;
	default: //ignore else
		return;
	}
}

void GameManager::DelInput(unsigned char key)
{
	if (m_input == key)
		m_input = '\0';
}