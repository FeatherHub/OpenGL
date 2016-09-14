#pragma once

class GLLogic;

class GLInterface
{
public:
	GLInterface() = default;
	~GLInterface();
	void Init();
	void Run();

private:
	static GLLogic* m_glLogic;
};