// GDIGraphicsLibrary.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "GDIGraphicsLibrary.h"

#define MAX_LOADSTRING 100
#define DEFAULT_FRAMERATE 60

GDIGraphicsLibrary* _this = NULL;

// Global Variables:
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GDIGRAPHICSLIBRARY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    _this = new GDIGraphicsLibrary(hInstance);
    if (!_this->Init(hInstance, nCmdShow))
        return -1;

    int returnValue = _this->ProgramLoop();
    //perform shutdown here if necessary

    return returnValue;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDIGRAPHICSLIBRARY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (_this != NULL)
    {
        return _this->MsgProc(hWnd, message, wParam, lParam);
    }
    else 
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 
// Class Stuff
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

GDIGraphicsLibrary::GDIGraphicsLibrary(HINSTANCE hInstance)
{
    _hInstance = hInstance;
    _windowHandle = NULL;
    _rasteriser = NULL;
    _timeSpan = 0;
}

GDIGraphicsLibrary::~GDIGraphicsLibrary()
{
    if (_rasteriser != NULL)
        delete _rasteriser;
}

bool GDIGraphicsLibrary::Init(HINSTANCE hInstance, int nCmdShow)
{
    //Perform default windows behaviour
    _hInstance = hInstance; // Store instance handle in our ~~global~~ class variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
        return false;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    
    // Added for Class stuff
    _windowHandle = hWnd;

    return true;
}

int GDIGraphicsLibrary::ProgramLoop()
{
    HACCEL hAccelTable = LoadAccelerators(_hInstance, MAKEINTRESOURCE(IDC_GDIGRAPHICSLIBRARY));
    MSG msg;

    LARGE_INTEGER counterFrequency;
    LARGE_INTEGER nextTime;
    LARGE_INTEGER currentTime;
    LARGE_INTEGER lastTime;
    bool updateFlag = true;

    // Initialise timer
    QueryPerformanceFrequency(&counterFrequency);
    DWORD msPerFrame = static_cast<DWORD>(counterFrequency.QuadPart / DEFAULT_FRAMERATE);
    double timeFactor = 1.0 / counterFrequency.QuadPart;
    QueryPerformanceCounter(&nextTime);
    lastTime = nextTime;

    // Main message loop:
    msg.message = WM_NULL;
    while (msg.message != WM_QUIT) {
        if (updateFlag)
        {
            QueryPerformanceCounter(&currentTime);
            _timeSpan = (currentTime.QuadPart - lastTime.QuadPart) * timeFactor;
            lastTime = currentTime;
            Update();
            updateFlag = false;
        }
        QueryPerformanceCounter(&currentTime);
        // Is it time to render the frame?
        if (currentTime.QuadPart > nextTime.QuadPart)
        {
            Render();
            // Make sure that the window gets repainted
            InvalidateRect(_windowHandle, NULL, FALSE);
            // Set time for next frame
            nextTime.QuadPart += msPerFrame;
            // If we get more than a frame ahead, allow one to be dropped
            // Otherwise, we will never catch up if we let the error accumulate
            // and message handling will suffer
            if (nextTime.QuadPart < currentTime.QuadPart)
            {
                nextTime.QuadPart = currentTime.QuadPart + msPerFrame;
            }
            updateFlag = true;
        }

        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            //TODO find out why this is needed.
            if (msg.message == WM_QUIT)
                break;
        }
    }
    return static_cast<int>(msg.wParam);
}

LRESULT GDIGraphicsLibrary::MsgProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), windowHandle, About);
            break;
        case IDM_EXIT:
            DestroyWindow(windowHandle);
            break;
        default:
            return DefWindowProc(windowHandle, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(windowHandle, &ps);
        //BitBlt(hdc, 0, 0, _bitmap.GetWidth(), _bitmap.GetHeight(), _bitmap.GetDC(), 0, 0, SRCCOPY);
        EndPaint(windowHandle, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(windowHandle, message, wParam, lParam);
    }
    return 0;
}

void GDIGraphicsLibrary::Update()
{
}

void GDIGraphicsLibrary::Render()
{
}


