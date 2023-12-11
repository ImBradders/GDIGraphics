#pragma once
#include "Bitmap.h"
#include "windows.h"

class Rasteriser
{
public:
	Rasteriser();
	~Rasteriser();

	void Update() const;
	void Render(Bitmap* bitmap) const;
};

