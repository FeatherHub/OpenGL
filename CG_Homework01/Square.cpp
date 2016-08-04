#include "Square.h"

unsigned int Square::m_serial = 0;

Square::Square(Point origin, int size, RGBA rgba, int speed) :
	m_pos(origin), m_size(size), m_rgba(rgba), m_spd(speed), m_dirX(1), m_dirY(1), m_id(m_serial++)
{
}

bool Square::IntersectRect(const Square& other)
{
	if (m_pos.x > other.m_pos.x + other.m_size ||
		m_pos.x + m_size < other.m_pos.x ||
		m_pos.y > other.m_pos.y + other.m_size ||
		m_pos.y + m_size < other.m_pos.y)
		return false;
	else
		return true;
}

bool Square::operator==(const Square& other)
{
	if (m_id == other.m_id)
		return true;
	else
		return false;
}
