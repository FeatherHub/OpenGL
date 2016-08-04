#pragma once

class RGBA
{
public:
	RGBA() = delete;
	RGBA(float r, float g, float b, float a);

public:
	float red;
	float green;
	float blue;
	float alpha;
};


