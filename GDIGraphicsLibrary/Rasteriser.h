#pragma once
#include "Bitmap.h"
#include "windows.h"

class Rasteriser
{
public:
	Rasteriser();
	~Rasteriser();

	void Update(const Bitmap* bitmap);
	void Render(Bitmap* bitmap) const;

private:
	int _x;
	int _y;
	int _size;
};

