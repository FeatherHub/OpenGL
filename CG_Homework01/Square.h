#pragma once

#include "Point.h"
#include "RGBA.h"

//origin : bottom-left
class Square
{
public:
	Square() = default;
	Square(Point origin, int size, RGBA rgba, int speed);

	Point GetPosition() { return m_pos; }
	int GetSize() { return m_size; }
	Point GetMoveDelta() { return Point{ m_dirX * m_spd, m_dirY * m_spd }; }
	RGBA GetRGBA() { return m_rgba; }

	void SetPosition(Point pos) { m_pos = pos; }
	void SetRGBA(const RGBA rgba) { m_rgba = rgba; }
	
	void ReverseDirectionX() { m_dirX *= -1; }
	void ReverseDirectionY() { m_dirY *= -1; }

	bool IntersectRect(const Square& other);

	bool operator==(const Square& other);

private:
	static unsigned int m_serial;
	int m_id;

	Point m_pos; //origin = top-left
	int m_size;
	RGBA m_rgba;

	int m_dirX;
	int m_dirY;
	int m_spd;
};