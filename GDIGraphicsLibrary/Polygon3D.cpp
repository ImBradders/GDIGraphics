#include "Polygon3D.h"

Polygon3D::Polygon3D()
{
	_indices[0] = -1;
	_indices[1] = -1;
	_indices[2] = -1;
}

Polygon3D::Polygon3D(int i0, int i1, int i2)
{
	_indices[0] = i0;
	_indices[1] = i1;
	_indices[2] = i2;
}

Polygon3D::Polygon3D(const Polygon3D& other)
{
	Copy(other);
}

Polygon3D& Polygon3D::operator=(const Polygon3D& other)
{
	Copy(other);
	return *this;
}

int Polygon3D::GetIndex(int index) const
{
	return _indices[index];
}

void Polygon3D::Copy(const Polygon3D& other)
{
	_indices[0] = other.GetIndex(0);
	_indices[1] = other.GetIndex(1);
	_indices[2] = other.GetIndex(2);
}
