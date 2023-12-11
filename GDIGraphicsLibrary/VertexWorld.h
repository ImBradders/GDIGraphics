#pragma once
class VertexWorld
{
public:
	VertexWorld();
	VertexWorld(const float x, const float y, const float z);
	VertexWorld(const VertexWorld& other);
	VertexWorld& operator= (const VertexWorld& other);
	
	void SetX(const float value);
	void SetY(const float value);
	void SetZ(const float value);
	void SetW(const float value);
	void SetXYZ(const float x, const float y, const float z);
	void SetXYZW(const float x, const float y, const float z, const float w);

	float GetX() const;
	float GetY() const;
	float GetZ() const;
	float GetW() const;
	
private:
	float _x;
	float _y;
	float _z;
	float _w;
};

