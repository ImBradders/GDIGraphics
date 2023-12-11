#pragma once

#include "resource.h"
#include "Bitmap.h"
#include "Rasteriser.h"

class GDIGraphicsLibrary 
{
public:
	GDIGraphicsLibrary(HINSTANCE hInstance);
	~GDIGraphicsLibrary();
	bool Init(HINSTANCE hInstance, int nCmdShow);
	int ProgramLoop();
	LRESULT MsgProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
	void Update();
	void Render();
private:
	Bitmap* _bitmap{ 0 };
	Rasteriser* _rasteriser{ 0 };
	HINSTANCE _hInstance;
	HWND _windowHandle;
	double _timeSpan;
};
