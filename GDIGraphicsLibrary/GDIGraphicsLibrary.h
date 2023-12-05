#pragma once

#include "resource.h"
#include "Bitmap.h"
#include "Rasteriser.h"

class GDIGraphicsLibrary 
{
public:
	GDIGraphicsLibrary(HINSTANCE hInstance);
	~GDIGraphicsLibrary();
	bool Init();
	int ProgramLoop();
	LRESULT MsgProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
private:
	Rasteriser* _rasteriser{ 0 };
	HINSTANCE _hInstance;
};
