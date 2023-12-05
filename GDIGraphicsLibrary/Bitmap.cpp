#include "Bitmap.h"

Bitmap::~Bitmap()
{
	DeleteBitmap();
}

bool Bitmap::Create(HWND windowHandle)
{
	HDC deviceContext;

	//delete old bitmap
	DeleteBitmap();

	//Gets the context of the window rather than calling the fucntion in this class.
	deviceContext = ::GetDC(windowHandle);

	//attempt to get width and height
	RECT rect;
	if (!GetWindowRect(windowHandle, &rect))
		return false;

	_width = rect.right - rect.left;
	_height = rect.bottom - rect.top;

	//attempt to create compatible window
	_innerDC = CreateCompatibleDC(deviceContext);
	if (_innerDC == 0)
		return false;

	//attempt to create compatible bitmap
	_bitmap = CreateCompatibleBitmap(deviceContext, _width, _height);
	if (_bitmap == 0)
		return false;

	//keep hold of the old bitmap before we assign the new one!
	_oldBitmap = static_cast<HBITMAP>(SelectObject(_innerDC, _bitmap));

	//release temporary device context
	ReleaseDC(windowHandle, deviceContext);
	return true;
}

HDC Bitmap::GetDC() const
{
	return _innerDC;
}

unsigned int Bitmap::GetWidth() const
{
	return _width;
}

unsigned int Bitmap::GetHeight() const
{
	return _height;
}

void Bitmap::Clear(HBRUSH brushHandle) const
{
	RECT rect;

	rect.left = 0;
	rect.right = _width;
	rect.top = 0;
	rect.bottom = _height;
	FillRect(_innerDC, &rect, brushHandle);
}

void Bitmap::Clear(COLORREF colour) const
{
	HBRUSH brush = CreateSolidBrush(colour);
	Clear(brush);
	DeleteObject(brush);
}

void Bitmap::DeleteBitmap()
{
	// Select any default bitmap that existed for the device context
	if (_oldBitmap != 0 && _innerDC != 0)
	{
		SelectObject(_innerDC, _oldBitmap);
		_oldBitmap = 0;
	}
	// Delete any existing bitmap
	if (_bitmap != 0)
	{
		DeleteObject(_bitmap);
		_bitmap = 0;
	}
	// Delete any existing bitmap device context
	if (_innerDC != 0)
	{
		DeleteDC(_innerDC);
		_innerDC = 0;
	}
}
