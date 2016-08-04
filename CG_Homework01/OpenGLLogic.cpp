#include "OpenGLLogic.h"
#include "OpenGLData.h"

#include "Square.h"

OpenGLLogic* OpenGLLogic::m_instance = nullptr;

OpenGLLogic* OpenGLLogic::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new OpenGLLogic();

	return m_instance;
}

OpenGLLogic::OpenGLLogic()
{
	m_squres = OpenGLData::CreateSquareData();
}

OpenGLLogic::~OpenGLLogic()
{
	if (m_instance != nullptr)
		delete m_instance;
}

void OpenGLLogic::UpdateSquares()
{
	ConstrainSqares();

	CollisionCheckSqures();
	
	MoveSquares();
}

void OpenGLLogic::MoveSquares()
{
	for (auto& s : *m_squres)
	{
		Point newOrigin = s.GetPosition();
		newOrigin += s.GetMoveDelta();
		s.SetPosition(newOrigin);
	}
}

//�ٸ� �簢���� �ε�����
//�ε��� ���� ����� �̵� ������ �ٲ��ش�
void OpenGLLogic::CollisionCheckSqures()
{
	for (auto& me : *m_squres)
	{
		for (auto& target : *m_squres)
		{
			if(me == target)
				continue;

			Point myPos = me.GetPosition();
			Point targetPos = target.GetPosition();
			int sz = me.GetSize();

			//�浹���� �˻�
			if (me.IntersectRect(target) == true)
			{
				//�翷���� �ε������� �˻�
				if (targetPos.x + sz > myPos.x ||
					myPos.x + sz > targetPos.x)
				{
					me.ReverseDirectionX();
				}

				//���Ʒ����� �ε������� �˻�
				if (targetPos.y + sz > myPos.y ||
					myPos.y + sz > targetPos.y)
				{
					me.ReverseDirectionY();
				}

				me.SetPosition(myPos + me.GetMoveDelta());
			}
		}
	}
}

//ȭ�� ������ �������� 
//ȭ�� �������� �Ű��ְ� �̵� ������ �ٲ��ش�
void OpenGLLogic::ConstrainSqares()
{
	for (auto& s : *m_squres)
	{
		Point pos = s.GetPosition();
		int sz = s.GetSize();

		if (pos.x + sz > m_winSizeWidth)
		{
			s.SetPosition(Point{ (int)m_winSizeWidth - sz - 1, pos.y });
			s.ReverseDirectionX();
		}

		if (pos.x < -m_winSizeWidth)
		{
			s.SetPosition(Point{ (int)-m_winSizeWidth + 1, pos.y });
			s.ReverseDirectionX();
		}
		
		if (pos.y + sz > m_winSizeHeight)
		{
			s.SetPosition(Point{ pos.x, (int)m_winSizeHeight - sz - 1 });
			s.ReverseDirectionY();
		}

		if (pos.y < -m_winSizeHeight)
		{
			s.SetPosition(Point{ pos.x , (int)-m_winSizeHeight + 1 });
			s.ReverseDirectionY();
		}
	}
}

void OpenGLLogic::SetWinSize(float w, float h)
{
	m_winSizeWidth = w;
	m_winSizeHeight = h;
}
