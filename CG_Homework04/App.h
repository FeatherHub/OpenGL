#pragma once

class GLBase;

class App
{
public:
	App() = default;
	~App();

	void Init();

private:
	GLBase* m_glBase;
};
