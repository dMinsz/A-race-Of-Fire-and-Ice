#include "stdafx.h"



//수정요망 윈도우 캡션, 클래스네임 세팅 
char* g_ClassName = "AROFNIDemo";
char* g_WindowName = "A Race of Fire and Ice";

CTimeController* g_timer;

// 윈도 프로시저의 전방선언
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/// 윈도를 등록한다.
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);		//작업영역 색상 변경.	
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_ClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);

	RegisterClassEx(&wc);



	int Titlebar = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYEDGE);




	// 애플리케이션 초기화를 수행합니다:

	HWND hWnd = CreateWindow(g_ClassName, g_WindowName, WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), 0, 0, 1920, (1080+Titlebar),
		GetDesktopWindow(), NULL, wc.hInstance, NULL);

	//WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),//  <-(창크기 변화 옵션 제거)WS_OVERLAPPEDWINDOW,

	if (!hWnd)
	{
		return FALSE;
	}


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//아이템 랜덤 함수를 위해 설정함
	srand(GetTickCount64());

	//엔진초기화
	TSEngine::GetEngine()->Initialize(hInstance, hWnd, 1920, 1080);

	//사운드 매니저
	ynMMedia_Initial(hWnd);
	SoundManager::GetInstance()->LoadData();
	


	//씬매니저
	CSceneManager::GetInstance()->Init();

	MSG msg;
	// 기본 메시지 루프입니다:
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
		
			CSceneManager::GetInstance()->Render();
			CSceneManager::GetInstance()->Update();
		}
	}

	return (int)msg.wParam;
}


LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:

		ynMMedia_Release();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

