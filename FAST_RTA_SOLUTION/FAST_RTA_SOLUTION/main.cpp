//// FAST_RTA main.cpp
////Authors: David Scarlett, Josh Ronek, Collin Ommen
/////////////////////////////////////////////////////////////////////
////						Includes and Defines
/////////////////////////////////////////////////////////////////////
//#include <iostream>
//#include <ctime>
//#include <windows.h>
//#include "ResourceManager.h"
//#define _WIDTH	1000
//#define _HEIGHT	750
/////////////////////////////////////////////////////////////////////
////						Windows App Setup
/////////////////////////////////////////////////////////////////////
//class DEMO_APP
//{
//	HINSTANCE app;
//	WNDPROC wp;
//	HWND HWindow;
//	ResourceManager* manager;
//	bool keys[16];
//public:
//	DEMO_APP(HINSTANCE h, WNDPROC wp);
//	void inputCheck();
//	bool Loop();
//	bool CleanUp();
//};
/////////////////////////////////////////////////////////////////////
////						Setup
/////////////////////////////////////////////////////////////////////
//DEMO_APP::DEMO_APP(HINSTANCE hinst, WNDPROC proc)
//{
//	app = hinst;
//	wp = proc;
//	//make our window object
//	WNDCLASSEX wclass;
//	//zero out for safety
//	ZeroMemory(&wclass, sizeof(wclass));
//	//set properties aka fill out data
//	wclass.cbSize = sizeof(WNDCLASSEX);
//	wclass.lpfnWndProc = wp;
//	wclass.lpszClassName = L"DirectXApplication";
//	wclass.hInstance = app;
//	wclass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wclass.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
//	//register window
//	RegisterClassEx(&wclass);
//	//define window size and attributes
//	RECT window_size = { 0, 0, _WIDTH, _HEIGHT };
//	AdjustWindowRect(&window_size, WS_OVERLAPPEDWINDOW, false);
//	HWindow = CreateWindow(L"DirectXApplication", L"FAST_RTA", WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
//		CW_USEDEFAULT, CW_USEDEFAULT, window_size.right - window_size.left, window_size.bottom - window_size.top,
//		NULL, NULL, app, this);
//	ShowWindow(HWindow, SW_SHOW);
//	//once we have our window, initialize any objects we need
//	manager = new ResourceManager();
//	manager->Init(_WIDTH, _HEIGHT, false, HWindow, false, 1.0, .01);
//}
//void DEMO_APP::inputCheck()
//{
//	if (GetAsyncKeyState('w'))
//		keys[0] = true;
//	else
//		keys[0] = false;
//	if (GetAsyncKeyState('a'))
//		keys[1] = true;
//	else
//		keys[1] = false;
//	if (GetAsyncKeyState('s'))
//		keys[2] = true;
//	else
//		keys[2] = false;
//	if (GetAsyncKeyState('d'))
//		keys[3] = true;
//	else
//		keys[3] = false;
//	if (GetAsyncKeyState('q'))
//		keys[4] = true;
//	else
//		keys[4] = false;
//	if (GetAsyncKeyState('e'))
//		keys[5] = true;
//	else
//		keys[5] = false;
//	if (GetAsyncKeyState('1'))
//		keys[6] = true;
//	else
//		keys[6] = false;
//	if (GetAsyncKeyState('2'))
//		keys[7] = true;
//	else
//		keys[7] = false;
//	if (GetAsyncKeyState('3'))
//		keys[8] = true;
//	else
//		keys[8] = false;
//	if (GetAsyncKeyState('4'))
//		keys[9] = true;
//	else
//		keys[9] = false;
//	if (GetAsyncKeyState('5'))
//		keys[10] = true;
//	else
//		keys[10] = false;
//	if (GetAsyncKeyState('6'))
//		keys[11] = true;
//	else
//		keys[11] = false;
//	if (GetAsyncKeyState('7'))
//		keys[12] = true;
//	else
//		keys[12] = false;
//	if (GetAsyncKeyState('8'))
//		keys[13] = true;
//	else
//		keys[13] = false;
//	if (GetAsyncKeyState('9'))
//		keys[14] = true;
//	else
//		keys[14] = false;
//	if (GetAsyncKeyState(VK_RBUTTON))
//		keys[15] = true;
//	else
//		keys[15] = false;
//}
/////////////////////////////////////////////////////////////////////
////						Application Loop
/////////////////////////////////////////////////////////////////////
//bool DEMO_APP::Loop()
//{
//	//input
//	inputCheck();
//	//update
//	manager->Update();
//	//render every 1/30s if we handle fps
//	manager->Render();
//	return true;
//}
/////////////////////////////////////////////////////////////////////
////						Application Cleanup
/////////////////////////////////////////////////////////////////////
//bool DEMO_APP::CleanUp()
//{
//	delete manager;
//	return true;
//}
/////////////////////////////////////////////////////////////////////
////						Windows Code
/////////////////////////////////////////////////////////////////////
////Reference: Lari Nori, Full Sail Graphics 1 Hardware Project
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
//{
//	//create DEMO_APP instance
//	DEMO_APP myApp(hInstance, (WNDPROC)WndProc);
//	//create message buffer
//	MSG message;
//	ZeroMemory(&message, sizeof(message));
//	//check the message for WM_QUIT and call Run() to check for runtime error
//	while (message.message != WM_QUIT && myApp.Loop())
//	{
//		//grab message, if any, and store it for loop condition
//		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&message);
//			DispatchMessage(&message);
//		}
//	}
//	//cleanup method
//	myApp.CleanUp();
//	//return success
//	return 0;
//}
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	//make app close on escape button
//	if (GetAsyncKeyState(VK_ESCAPE))
//		message = WM_DESTROY;
//	switch (message)
//	{
//	case (WM_DESTROY):
//	{
//		PostQuitMessage(0);
//		break;
//	}
//	}
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}





// FAST_RTA main.cpp
//Authors: David Scarlett, Josh Ronek, Collin Ommen







///////////////////////////////////////////////////////////////////
//						Includes and Defines
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>
#include <windows.h>
#include "ResourceManager.h"
#include "Input.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>



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
	Input* m_Input;
	bool keys[16];
public:
	
	DEMO_APP(HINSTANCE h, WNDPROC wp);
	void inputCheck();
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
	manager->Init(_WIDTH, _HEIGHT, false, HWindow, false, 100.0f, .01f);
}


void DEMO_APP::inputCheck()
{
	if (GetAsyncKeyState('W'))
		keys[0] = true;
	else
		keys[0] = false;
	if (GetAsyncKeyState('A'))
		keys[1] = true;
	else
		keys[1] = false;
	if (GetAsyncKeyState('S'))
		keys[2] = true;
	else
		keys[2] = false;
	if (GetAsyncKeyState('D'))
		keys[3] = true;
	else
		keys[3] = false;
	if (GetAsyncKeyState('Q'))
		keys[4] = true;
	else
		keys[4] = false;
	if (GetAsyncKeyState('E'))
		keys[5] = true;
	else
		keys[5] = false;
	if (GetAsyncKeyState('1'))
		keys[6] = true;
	else
		keys[6] = false;
	if (GetAsyncKeyState('2'))
		keys[7] = true;
	else
		keys[7] = false;
	if (GetAsyncKeyState('3'))
		keys[8] = true;
	else
		keys[8] = false;
	if (GetAsyncKeyState('4'))
		keys[9] = true;
	else
		keys[9] = false;
	if (GetAsyncKeyState('5'))
		keys[10] = true;
	else
		keys[10] = false;
	if (GetAsyncKeyState('6'))
		keys[11] = true;
	else
		keys[11] = false;
	if (GetAsyncKeyState(VK_RIGHT))
		keys[12] = true;
	else
		keys[12] = false;
	if (GetAsyncKeyState(VK_LEFT))
		keys[13] = true;
	else
		keys[13] = false;
	if (GetAsyncKeyState(VK_DOWN))
		keys[14] = true;
	else
		keys[14] = false;
	if (GetAsyncKeyState(VK_UP))
		keys[15] = true;
	else
		keys[15] = false;
}




///////////////////////////////////////////////////////////////////
//						Application Loop
///////////////////////////////////////////////////////////////////

bool DEMO_APP::Loop()
{
	//input
	inputCheck();

	//update
	manager->Update(keys, .1f);


	manager->Render();
	return true;
}




///////////////////////////////////////////////////////////////////
//						Application Cleanup
///////////////////////////////////////////////////////////////////

bool DEMO_APP::CleanUp()
{
	delete manager;
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
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);
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