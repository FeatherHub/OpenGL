#include "Character.h"
#include "LoadObj.h"
#include "glut.h"
#include <cstdlib>
#include <ctime>

enum Config
{
	JUMP_TIME = 1500,
};

enum Speed : unsigned char
{
	INIT_MOVE_SPEED = 10,
};

Character::Character() :
	m_jumpState(JUMP_END),
	m_moveSpeed(INIT_MOVE_SPEED),
	m_lookRight(0.5f)
{
	srand((unsigned)time(nullptr));
}

void Character::Init()
{
	bool res = LoadObj("hero.obj", m_vertices, m_uvs, m_normals);
	if (res == false)
	{
		printf("Load character failed \n");
		return;
	}
	else
	{
		printf("Load character success \n");
	}

	ResetColor();
}

void Character::Draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(m_position.x, m_position.y, m_position.z);
	glRotatef(25.f + m_lookRight, 0.f, 1.f, 0.f);

	glBegin(GL_POLYGON);

	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		auto v = m_vertices[i];
		auto n = m_normals[i];
		auto c = m_colors[i];

		glColor3f(c.x, c.y, c.z);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(v.x, v.y, v.z);
	}

	glEnd();
}

void Character::Update(int deltaTime)
{
	if (m_jumpState != JUMP_END)
	{
		ProcessJump(deltaTime);
	}
}

void Character::Move(DIRECTION dir)
{
	switch (dir)
	{
	case FORWARD:
		printf("move forward \n");

		m_position.z -= m_moveSpeed;
		break;
	case BACKWARD:
		printf("move backward \n");

		m_position.z += m_moveSpeed;
		break;
	case RIGHT:
		printf("move right \n");

		m_position.x += m_moveSpeed;
		break;
	case LEFT:
		printf("move left \n");

		m_position.x -= m_moveSpeed;
		break;
	}
}

void Character::ProcessJump(int deltaTime)
{
	static unsigned int miliCounter = 0;
	
	switch (m_jumpState)
	{
	case JUMP_START:
		printf("jump start \n");

		m_jumpState = JUMP_UP;
		break;
	case JUMP_UP:
		printf("jump up \n");

		m_position.y += 0.001 * (miliCounter/20)*(miliCounter / 20);
		if (miliCounter > JUMP_TIME)
		{
			miliCounter = 0;
			m_jumpState = JUMP_DOWN;
		}
		break;
	case JUMP_DOWN:
		printf("jump down \n");

		m_position.y -= 0.001 * (miliCounter / 20)*(miliCounter / 20);
		if (miliCounter > JUMP_TIME)
		{
			printf("jump end \n");

			miliCounter = 0;
			m_jumpState = JUMP_END;
		}
		break;
	}

	miliCounter += deltaTime;

	printf("jump mili %u \n", miliCounter);
}

void Character::Jump()
{
	if (m_jumpState == JUMP_END)
	{
		m_jumpState = JUMP_START;
	}
}

void Character::ResetColor()
{
	static float rLimit = 375.f;
	static float gLimit = 340.f;
	static float bLimit = 300.f;

	m_colors.clear();

	for (size_t i = 0; i < m_vertices.size(); i++)
	{
		float r = (rand() % 100) / rLimit;
		float g = (rand() % 100) / gLimit;
		float b = (rand() % 100) / bLimit;
		m_colors.emplace_back(vec3{ r,g,b });
	}

	rLimit -= 10.f;
	gLimit -= 5.f;
	bLimit -= 7.5f;

	m_lookRight += 2.75f;
}
