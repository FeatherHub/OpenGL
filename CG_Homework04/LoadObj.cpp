#include "LoadObj.h"
#include <windows.h>
#include <vector>
#include "glut.h"

bool LoadObj(
	const char * path,
	std::vector <vec3>& out_vertices,
	std::vector <vec2>& out_uvs,
	std::vector <vec3>& out_normals
)
{
	std::vector<UINT> vertexIndices, uvIndices, normalIndices;
	std::vector<vec3> tmpVertieces, tmpNormals;
	std::vector<vec2> tmpUvs;

	FILE* file = fopen(path, "r");
	if (file == nullptr)
	{
		return false;
	}

	while (true)
	{
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			vec3 vertex;
			fscanf_s(file, "%f %f %f \n", &vertex.x, &vertex.y, &vertex.z);
			tmpVertieces.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			vec2 uv;
			fscanf_s(file, "%f %f \n", &uv.x, &uv.y);
			tmpUvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			vec3 normal;
			fscanf_s(file, "%f %f %f \n", &normal.x, &normal.y, &normal.z);
			tmpNormals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			UINT vertexIndex[3], uvIndex[3], normalIndex[3];
			int matchNum = fscanf_s(
				file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matchNum != 9)
			{
				return false;
			}
			
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	} //end while loop

	for (UINT i = 0; i < vertexIndices.size(); i++)
	{
		UINT vIdx = vertexIndices[i];
		vec3 vertex = tmpVertieces[vIdx - 1];
		out_vertices.push_back(vertex);
	}

	for (UINT i = 0; i < normalIndices.size(); i++)
	{
		UINT nIdx = normalIndices[i];
		vec3 normal = tmpNormals[nIdx - 1];
		out_normals.push_back(normal);
	}

	for (UINT i = 0; i < uvIndices.size(); i++)
	{
		UINT uIdx = uvIndices[i];
		vec2 uv = tmpUvs[uIdx - 1];
		out_uvs.push_back(uv);
	}

	return true;
}