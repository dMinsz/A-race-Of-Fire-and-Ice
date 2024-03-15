#include "FrameWork.h"

//GDI ����
#include "../TSEngine/TSEngine.h"
#include "../TSEngine/TSprite.h"


//������� ������ ĸ��, Ŭ�������� ���� 
char* g_ClassName = "TSEngineDemo";
char* g_WindowName = "TSEngineDemo";



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


	// ���ø����̼� �ʱ�ȭ�� �����մϴ�:

	HWND hWnd = CreateWindow(g_ClassName, g_WindowName, WS_OVERLAPPEDWINDOW, 100, 100, 1920, 1080,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);



	if (!hWnd)
	{
		return FALSE;
	}

	/// �׷��Ƚ� ���� �ʱ�ȭ
	/*TSEngine* _pTSEngine = new TSEngine();
	_pTSEngine->Initialize(hInstance, hWnd, 1920, 1080);*/
	TSEngine::GetEngine()->Initialize(hInstance, hWnd, 1920, 1080);

	//data load

	// �׽�Ʈ�� ��������Ʈ �� ���� �ε�
	TSprite* _pTSprite = new TSprite();
	TSEngine::GetEngine()->LoadSprite(_pTSprite, "../Resource/Bitmaps/Hero04.bmp");

	TSprite* _pTSpriteSheet = new TSprite();

	AniInfo tempInfo;
	tempInfo.init(7, 55, 70, 7);
	TSEngine::GetEngine()->LoadSpriteSheet(_pTSpriteSheet, "../Resource/Bitmaps/Hero.bmp", tempInfo);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

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
			/// ���Ⱑ ���� ����
			// ������ ����
			TSEngine::GetEngine()->GetEngineTime();

			// �Է��� �޴´�.
			// ������ �Ѵ�. (��������, �浹üũ)
			TSEngine::GetEngine()->UpdateAll();


			// (����ۿ�) �׸���.
			TSEngine::GetEngine()->BeginRender();

			// (����ۿ�) �׽�Ʈ�� ��������Ʈ�� �׸���.
			//_pTSEngine->DrawSprite(_pTSprite, 400, 400);

			TSEngine::GetEngine()->DrawSpriteOrigin(TSEngine::GetEngine()->GetBackBufferDC(), 100, 100, _pTSprite);
			TSEngine::GetEngine()->DrawSprite(TSEngine::GetEngine()->GetBackBufferDC(), 200, 100, _pTSprite);
			TSEngine::GetEngine()->RotateDrawSprite(TSEngine::GetEngine()->GetBackBufferDC(), 300, 100, _pTSprite, 90);

			


			//_pTSEngine->SpriteAnimation(_pTSpriteSheet);
			TSEngine::GetEngine()->DrawAnimation(TSEngine::GetEngine()->GetBackBufferDC(), 100, 300, _pTSpriteSheet);

			TSEngine::GetEngine()->ShowFPS(1, 1);



			// (������۸�) ����۸� ȭ�鿡 �׸���.
			TSEngine::GetEngine()->EndRender();
		}
	}

	return (int)msg.wParam;
}


LRESULT CALLBACK MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

