#pragma once

namespace gl
{
	void RenderScene();
	void OnTimeTick(int val);
	void OnChangeSize(int w, int h);
	void OnKeyPressed(int key, int x, int y);
	void Init();
}
