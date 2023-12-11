#include "VertexWorld.h"

VertexWorld::VertexWorld()
{
	SetXYZW(0, 0, 0, 0);
}

VertexWorld::VertexWorld(const float x, const float y, const float z)
{
	SetXYZ(x, y, z);
	SetW(0);
}

VertexWorld::VertexWorld(const VertexWorld& other)
{
	SetXYZW(other.GetX(), other.GetY(), other.GetZ(), other.GetW());
}

VertexWorld& VertexWorld::operator=(const VertexWorld& other)
{
	SetXYZW(other.GetX(), other.GetY(), other.GetZ(), other.GetW());
	return *this;
}

void VertexWorld::SetX(const float value)
{
	_x = value;
}

void VertexWorld::SetY(const float value)
{
	_y = value;
}

void VertexWorld::SetZ(const float value)
{
	_z = value;
}

void VertexWorld::SetW(const float value)
{
	_w = value;
}

void VertexWorld::SetXYZ(const float x, const float y, const float z)
{
	SetX(x);
	SetY(y);
	SetZ(z);
}

void VertexWorld::SetXYZW(const float x, const float y, const float z, const float w)
{
	SetXYZ(x, y, z);
	SetW(w);
}

float VertexWorld::GetX() const
{
	return _x;
}

float VertexWorld::GetY() const
{
	return _y;
}

float VertexWorld::GetZ() const
{
	return _z;
}

float VertexWorld::GetW() const
{
	return _w;
}

