

// FAST_RTA main.cpp
//Authors: David Scarlett, Josh Ronek, Collin Ommen







///////////////////////////////////////////////////////////////////
//						Includes and Defines
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>
#include <windows.h>
#include <shellapi.h>
#include "ResourceManager.h"
#include "Input.h"
#include "../FAST_BINARY_IO/FASTBinaryIO.h"
#include "../FAST_FBX_LOADER/FASTFBXLoader.h"
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
	DragAcceptFiles(HWindow, true);

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
	manager->Update(keys, .01f, HWindow);


	manager->Render();
	return true;
}

char *binFilePath;
bool loadBinFile;


///////////////////////////////////////////////////////////////////
//						Application Cleanup
///////////////////////////////////////////////////////////////////

bool DEMO_APP::CleanUp()
{
	delete[] binFilePath;
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
	case (WM_DROPFILES):
	{
		TCHAR *filePath;
		HDROP hDrop = (HDROP)wParam;
		uint32_t numFiles = DragQueryFile(hDrop, -1, NULL, NULL);
		if (numFiles == 1)
		{
			delete[] binFilePath;
			binFilePath = nullptr;

			uint32_t filePathSize = DragQueryFile(hDrop, 0, NULL, NULL) + 1;
			filePath = new TCHAR[filePathSize];
			DragQueryFile(hDrop, 0, filePath, filePathSize);
			
			char searchExt[4] = "fbx";
			int32_t extCount = 3;
			bool extSearchOn = true;
			for (int32_t i = filePathSize - 1; i > -1; --i)
			{
				if (extSearchOn)
				{
					if (extCount > 0 && filePath[i] != searchExt[extCount--])
						break;
					if (filePath[i] == '.')
						extSearchOn = false;
				}

				if (filePath[i] == '\\')
				{
					uint32_t binFilePathSize = filePathSize - i - 6;
					binFilePath = new char[binFilePathSize + 5];

					uint32_t j;
					for (j = 0; j < binFilePathSize; ++j)
						binFilePath[j] = filePath[i + j + 1];

					binFilePath[j + 0] = '.';
					binFilePath[j + 1] = 'b';
					binFilePath[j + 2] = 'i';
					binFilePath[j + 3] = 'n';
					binFilePath[j + 4] = '\0';

					break;
				}
			}

			if (binFilePath)
			{
				FASTBinaryIO::FASTFile *fastFile = FASTBinaryIO::Create(FASTBinaryIO::READ);
				if (!FASTBinaryIO::Open(fastFile, binFilePath))
				{
					char *tempPath = new char[filePathSize];
					for (uint32_t i = 0; i < filePathSize; ++i)
						tempPath[i] = filePath[i];

					FASTFBXLoader::Init();
					FASTFBXLoader::Load(tempPath);
					FASTFBXLoader::Export(binFilePath);
					FASTFBXLoader::Clean();
					delete tempPath;
				}
				else
					FASTBinaryIO::Close(fastFile);
				FASTBinaryIO::Destroy(fastFile);

				loadBinFile = true;
			}

			delete filePath;
		}
		break;
	}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}