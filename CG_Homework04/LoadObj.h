#pragma once

#include "GraphicTypes.h"
#include <vector>

bool LoadObj(
	const char * path,
	std::vector <vec3>& out_vertices,
	std::vector <vec2>& out_uvs,
	std::vector <vec3>& out_normals
);