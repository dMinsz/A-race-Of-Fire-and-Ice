#include "stdafx.h"



//������� ������ ĸ��, Ŭ�������� ���� 
char* g_ClassName = "AROFNIDemo";
char* g_WindowName = "A Race of Fire and Ice";

CTimeController* g_timer;

// ���� ���ν����� ���漱��
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/// ������ ����Ѵ�.
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);		//�۾����� ���� ����.	
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_ClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);

	RegisterClassEx(&wc);



	int Titlebar = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYEDGE);




	// ���ø����̼� �ʱ�ȭ�� �����մϴ�:

	HWND hWnd = CreateWindow(g_ClassName, g_WindowName, WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX), 0, 0, 1920, (1080+Titlebar),
		GetDesktopWindow(), NULL, wc.hInstance, NULL);

	//WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),//  <-(âũ�� ��ȭ �ɼ� ����)WS_OVERLAPPEDWINDOW,

	if (!hWnd)
	{
		return FALSE;
	}


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//������ ���� �Լ��� ���� ������
	srand(GetTickCount64());

	//�����ʱ�ȭ
	TSEngine::GetEngine()->Initialize(hInstance, hWnd, 1920, 1080);

	//���� �Ŵ���
	ynMMedia_Initial(hWnd);
	SoundManager::GetInstance()->LoadData();
	


	//���Ŵ���
	CSceneManager::GetInstance()->Init();

	MSG msg;
	// �⺻ �޽��� �����Դϴ�:
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

