#pragma once
#include "windows.h"

class Bitmap
{
public: 
	~Bitmap();

	bool Create(HWND window);
	HDC GetDC() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	void Clear(HBRUSH brushHandle) const;
	void Clear(COLORREF colour) const;

private:
	HBITMAP _bitmap{ 0 };
	HBITMAP _oldBitmap{ 0 };
	HDC _innerDC{ 0 };
	unsigned int _width = 0;
	unsigned int _height = 0;

	void DeleteBitmap();
};

