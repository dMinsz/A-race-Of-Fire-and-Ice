#include "stdafx.h"
#include "WinFire.h"

WinFire::WinFire()
{
}

WinFire::~WinFire(void)
{
}

void WinFire::Init(void)
{
	//엔딩화면 테스트
	TSprite* Back = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Back, "../Resource/Bitmaps/win_fire.bmp");
	m_BackGround = Back;

	//fire win 
	TSprite* FireWin = new TSprite();
	TSEngine::GetEngine()->LoadSprite(FireWin, "../Resource/Bitmaps/cha_fire_win.bmp");

	AniInfo FireWinAni;
	FireWinAni.init(8, 200, 200);
	FireWin->m_AniInfo = FireWinAni;

	m_motion = FireWin;
}

void WinFire::Update(float dtime)
{

	KeyState::KeyUpdate();


	//애니메이션
	HDC backbuffer = TSEngine::GetEngine()->GetBackBufferDC();
	TSEngine::GetEngine()->DrawAnimation(backbuffer, 354, 680, m_motion, dtime * 1.2f);

	TSEngine::GetEngine()->EndRender();

	if (KeyState::InputKeyDown(VK_F5)) 
	{
		CSceneManager::GetInstance()->SceneChange(ENDINGCREDIT);
	}

}

void WinFire::Render(void)
{
	TSEngine::GetEngine()->BeginRender();

	TSEngine::GetEngine()->DrawSpriteOrigin(TSEngine::GetEngine()->GetBackBufferDC(), 0, 0, m_BackGround);



}

void WinFire::Release(void)
{
	TSEngine::GetEngine()->SpriteRelease(m_BackGround);
	TSEngine::GetEngine()->SpriteRelease(m_motion);
}
