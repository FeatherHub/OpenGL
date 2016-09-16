#pragma once

#include <vector>
#include "GraphicTypes.h"

enum DIRECTION : unsigned char
{
	FORWARD = 0,
	BACKWARD = 1,
	RIGHT = 2,
	LEFT = 3,
};

class Character
{
public:
	Character();
	~Character() = default;

	void Init();
	void Draw();
	void Update(int deltaTime);
	void Move(DIRECTION dir);
	void Jump();

	const vec3& GetPosition() { return m_position; }
	void SetPosition(const vec3& pos) { m_position = pos; }
	void IncreaseMoveSpeed(const int& spd) { m_moveSpeed += spd; }
	void ResetColor();

private:
	void ProcessJump(int deltaTime);

private:
	enum JumpState : unsigned char
	{
		JUMP_START,
		JUMP_UP,
		JUMP_DOWN,
		JUMP_END,
	};

private:
	float m_lookRight;
	vec3 m_position;
	JumpState m_jumpState;
	int m_moveSpeed;
	std::vector<vec3> m_vertices;
	std::vector<vec3> m_normals;
	std::vector<vec2> m_uvs;
	std::vector<vec3> m_colors;
};