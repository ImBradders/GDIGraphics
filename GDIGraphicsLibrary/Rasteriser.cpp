#include "Rasteriser.h"

Rasteriser::Rasteriser()
{
}

Rasteriser::~Rasteriser()
{
}

void Rasteriser::Update() const
{
	//update the things
}

void Rasteriser::Render(Bitmap* bitmap) const
{
	bitmap->Clear(RGB(255, 255, 255));
}
