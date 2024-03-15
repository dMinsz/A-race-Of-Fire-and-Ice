#include "stdafx.h"
#include "WinIce.h"


WinIce::WinIce()
{
}

WinIce::~WinIce(void)
{
}

void WinIce::Init(void)
{
	//엔딩화면 테스트
	TSprite* Back = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Back, "../Resource/Bitmaps/win_ice.bmp");
	m_BackGround = Back;


	//ICE WIN
	TSprite* IceWin = new TSprite();
	TSEngine::GetEngine()->LoadSprite(IceWin, "../Resource/Bitmaps/cha_ice_win.bmp");

	AniInfo IceWinAni;
	IceWinAni.init(8, 200, 200);
	IceWin->m_AniInfo = IceWinAni;

	m_motion = IceWin;

}

void WinIce::Update(float dtime)
{
	

	KeyState::KeyUpdate();


	//애니메이션
	HDC backbuffer = TSEngine::GetEngine()->GetBackBufferDC();
	TSEngine::GetEngine()->DrawAnimation(backbuffer, 1325, 680, m_motion, dtime *1.2f );

	TSEngine::GetEngine()->EndRender();

	if (KeyState::InputKeyDown(VK_F5))
	{
		CSceneManager::GetInstance()->SceneChange(ENDINGCREDIT);
	}

}

void WinIce::Render(void)
{
	TSEngine::GetEngine()->BeginRender();

	TSEngine::GetEngine()->DrawSpriteOrigin(TSEngine::GetEngine()->GetBackBufferDC(), 0, 0, m_BackGround);

}

void WinIce::Release(void)
{
	TSEngine::GetEngine()->SpriteRelease(m_BackGround);
	TSEngine::GetEngine()->SpriteRelease(m_motion);
}
