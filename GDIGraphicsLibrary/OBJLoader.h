#pragma once
#include <vector>

class VertexWorld;
class VertexTexture;
class Polygon3D;

class OBJLoader
{
public:
	bool LoadOBJ(const char* path, 
		std::vector<VertexWorld>& out_verts, 
		std::vector<VertexTexture>& out_uvs,
		std::vector<Polygon3D>& out_polys);
};

