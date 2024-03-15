#include "FrameWork.h"

//GDI 엔진
#include "../TSEngine/TSEngine.h"
#include "../TSEngine/TSprite.h"


//수정요망 윈도우 캡션, 클래스네임 세팅 
char* g_ClassName = "TSEngineDemo";
char* g_WindowName = "TSEngineDemo";



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


	// 애플리케이션 초기화를 수행합니다:

	HWND hWnd = CreateWindow(g_ClassName, g_WindowName, WS_OVERLAPPEDWINDOW, 100, 100, 1920, 1080,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);



	if (!hWnd)
	{
		return FALSE;
	}

	/// 그래픽스 엔진 초기화
	/*TSEngine* _pTSEngine = new TSEngine();
	_pTSEngine->Initialize(hInstance, hWnd, 1920, 1080);*/
	TSEngine::GetEngine()->Initialize(hInstance, hWnd, 1920, 1080);

	//data load

	// 테스트로 스프라이트 한 장을 로드
	TSprite* _pTSprite = new TSprite();
	TSEngine::GetEngine()->LoadSprite(_pTSprite, "../Resource/Bitmaps/Hero04.bmp");

	TSprite* _pTSpriteSheet = new TSprite();

	AniInfo tempInfo;
	tempInfo.init(7, 55, 70, 7);
	TSEngine::GetEngine()->LoadSpriteSheet(_pTSpriteSheet, "../Resource/Bitmaps/Hero.bmp", tempInfo);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

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
			/// 여기가 게임 루프
			// 프레임 제어
			TSEngine::GetEngine()->GetEngineTime();

			// 입력을 받는다.
			// 연산을 한다. (물리엔진, 충돌체크)
			TSEngine::GetEngine()->UpdateAll();


			// (백버퍼에) 그린다.
			TSEngine::GetEngine()->BeginRender();

			// (백버퍼에) 테스트용 스프라이트를 그린다.
			//_pTSEngine->DrawSprite(_pTSprite, 400, 400);

			TSEngine::GetEngine()->DrawSpriteOrigin(TSEngine::GetEngine()->GetBackBufferDC(), 100, 100, _pTSprite);
			TSEngine::GetEngine()->DrawSprite(TSEngine::GetEngine()->GetBackBufferDC(), 200, 100, _pTSprite);
			TSEngine::GetEngine()->RotateDrawSprite(TSEngine::GetEngine()->GetBackBufferDC(), 300, 100, _pTSprite, 90);

			


			//_pTSEngine->SpriteAnimation(_pTSpriteSheet);
			TSEngine::GetEngine()->DrawAnimation(TSEngine::GetEngine()->GetBackBufferDC(), 100, 300, _pTSpriteSheet);

			TSEngine::GetEngine()->ShowFPS(1, 1);



			// (더블버퍼링) 백버퍼를 화면에 그린다.
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

