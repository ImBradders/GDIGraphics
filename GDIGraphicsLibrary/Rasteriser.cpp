#include "Rasteriser.h"

Rasteriser::Rasteriser()
{
	_x = 0;
	_y = 0;
	_size = 50;
}

Rasteriser::~Rasteriser()
{
}

void Rasteriser::Update(const Bitmap* bitmap)
{
	_x += _size;
	if (_x + _size >= bitmap->GetWidth())
	{
		_x = 0;
		_y += _size;
		if (_y + _size >= bitmap->GetHeight())
		{
			_y = 0;
		}
	}
}

void Rasteriser::Render(Bitmap* bitmap) const
{
	bitmap->Clear(RGB(0, 0, 0));
	HDC deviceContext = bitmap->GetDC();
	COLORREF colour = RGB(rand() % 256, rand() % 256, rand() % 256);
	HBRUSH brush = CreateSolidBrush(colour);
	RECT rect{ _x, _y, _x + _size, _y + _size };
	FillRect(deviceContext, &rect, brush);
}
