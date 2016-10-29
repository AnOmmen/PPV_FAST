// FAST_RTA main.cpp
//Authors: David Scarlett, Josh Ronek, Collin Ommen







///////////////////////////////////////////////////////////////////
//						Includes and Defines
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>
#include <windows.h>
#include "ResourceManager.h"



#define _WIDTH	1000
#define _HEIGHT	750




///////////////////////////////////////////////////////////////////
//						Windows App Setup
///////////////////////////////////////////////////////////////////
class DEMO_APP
{
	HINSTANCE app;
	WNDPROC wp;
	HWND HWindow;
	ResourceManager* manager;
public:
	DEMO_APP(HINSTANCE h, WNDPROC wp);

	bool Loop();
	bool CleanUp();
};








///////////////////////////////////////////////////////////////////
//						Setup
///////////////////////////////////////////////////////////////////

DEMO_APP::DEMO_APP(HINSTANCE hinst, WNDPROC proc)
{
	app = hinst;
	wp = proc;
	//make our window object
	WNDCLASSEX wclass;
	//zero out for safety
	ZeroMemory(&wclass, sizeof(wclass));
	//set properties aka fill out data
	wclass.cbSize = sizeof(WNDCLASSEX);
	wclass.lpfnWndProc = wp;
	wclass.lpszClassName = L"DirectXApplication";
	wclass.hInstance = app;
	wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wclass.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	//register window
	RegisterClassEx(&wclass);
	//define window size and attributes
	RECT window_size = { 0, 0, _WIDTH, _HEIGHT };
	AdjustWindowRect(&window_size, WS_OVERLAPPEDWINDOW, false);
	HWindow = CreateWindow(L"DirectXApplication", L"FAST_RTA", WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, window_size.right - window_size.left, window_size.bottom - window_size.top,
		NULL, NULL, app, this);
	ShowWindow(HWindow, SW_SHOW);

	//once we have our window, initialize any objects we need
	manager = new ResourceManager();
	manager->Init(_WIDTH, _HEIGHT, false, HWindow, false, 100.0, .01);
}








///////////////////////////////////////////////////////////////////
//						Application Loop
///////////////////////////////////////////////////////////////////

bool DEMO_APP::Loop()
{
	//input


	//update
	manager->Update();

	//render every 1/30s if we handle fps
	manager->Render();
	return true;
}




///////////////////////////////////////////////////////////////////
//						Application Cleanup
///////////////////////////////////////////////////////////////////

bool DEMO_APP::CleanUp()
{
	
	return true;
}






///////////////////////////////////////////////////////////////////
//						Windows Code
///////////////////////////////////////////////////////////////////
//Reference: Lari Nori, Full Sail Graphics 1 Hardware Project
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	//create DEMO_APP instance
	DEMO_APP myApp(hInstance, (WNDPROC)WndProc);
	//create message buffer
	MSG message; 
	ZeroMemory(&message, sizeof(message));
	//check the message for WM_QUIT and call Run() to check for runtime error
	while (message.message != WM_QUIT && myApp.Loop())
	{
		//grab message, if any, and store it for loop condition
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	//cleanup method
	myApp.CleanUp();
	//return success
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//make app close on escape button
	if (GetAsyncKeyState(VK_ESCAPE))
		message = WM_DESTROY;
	switch (message)
	{
	case (WM_DESTROY): 
	{
		PostQuitMessage(0);

		break;
	}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}