#pragma once
class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int i0, int i1, int i2);
	Polygon3D(const Polygon3D& other);
	Polygon3D& operator= (const Polygon3D& other);

	int GetIndex(int index) const;
	void Copy(const Polygon3D& other);
private:
	int _indices[3];
};

