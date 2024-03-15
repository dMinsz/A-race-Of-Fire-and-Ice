#include "stdafx.h"
#include "EndingCredit.h"

EndingCredit::EndingCredit()
{
}

EndingCredit::~EndingCredit(void)
{
}

void EndingCredit::Init(void)
{
	TSprite* Back = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Back, "../Resource/Bitmaps/ending_credit.bmp");
	
	m_BackGround = Back;

	//Fire motion 
	TSprite* FireMotion = new TSprite();
	TSEngine::GetEngine()->LoadSprite(FireMotion, "../Resource/Bitmaps/cha_fire_credit.bmp");

	AniInfo FireMotionAni;
	FireMotionAni.init(5, 200, 200);
	FireMotion->m_AniInfo = FireMotionAni;

	m_motion1 = FireMotion;

	//Fire motion 
	TSprite* IceMotion = new TSprite();
	TSEngine::GetEngine()->LoadSprite(IceMotion, "../Resource/Bitmaps/cha_ice_credit.bmp");

	AniInfo ICEMotionAni;
	ICEMotionAni.init(5, 200, 200);
	IceMotion->m_AniInfo = ICEMotionAni;

	m_motion2 = IceMotion;



}

void EndingCredit::Update(float dtime)
{



	KeyState::KeyUpdate();


	HDC backbuffer = TSEngine::GetEngine()->GetBackBufferDC();
	//fire
	TSEngine::GetEngine()->DrawAnimation(backbuffer, 86, 200, m_motion1, dtime * 2.0f);
	//ice
	TSEngine::GetEngine()->DrawAnimation(backbuffer, 1610, 452, m_motion2, dtime * 2.0f);

	TSEngine::GetEngine()->EndRender();

	if (KeyState::InputKeyDown(VK_F5))
	{
		CSceneManager::GetInstance()->SceneChange(GAMEINTRO);
	}

}

void EndingCredit::Render(void)
{
	TSEngine::GetEngine()->BeginRender();

	TSEngine::GetEngine()->DrawSpriteOrigin(TSEngine::GetEngine()->GetBackBufferDC(), 0, 0, m_BackGround);
}

void EndingCredit::Release(void)
{
}
