// FAST_RTA main.cpp
//Authors: David Scarlett, Josh Ronek, Collin Ommen







///////////////////////////////////////////////////////////////////
//						Includes and Defines
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>
#include <windows.h>
///////////////////////////////////////////////////////////////////
//						Windows App Setup
///////////////////////////////////////////////////////////////////
class DEMO_APP
{
	HINSTANCE app;
	WNDPROC wp;
	HWND HWindow;

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

}








///////////////////////////////////////////////////////////////////
//						Application Loop
///////////////////////////////////////////////////////////////////

bool DEMO_APP::Loop()
{

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