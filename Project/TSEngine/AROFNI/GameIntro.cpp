#include "stdafx.h"
#include "GameIntro.h"

GameIntro::GameIntro()
{
}

GameIntro::~GameIntro(void)
{
}

void GameIntro::Init(void)
{
	TSprite* Back = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Back, "../Resource/Bitmaps/main_title.bmp");

	m_BackGround = Back;

	//Fire motion 
	TSprite* FireMotion = new TSprite();
	TSEngine::GetEngine()->LoadSprite(FireMotion, "../Resource/Bitmaps/cha_fire_jump_r.bmp");

	AniInfo FireMotionAni;
	FireMotionAni.init(6, 200, 200);
	FireMotion->m_AniInfo = FireMotionAni;

	m_motion1 = FireMotion;

	//Fire motion 
	TSprite* IceMotion = new TSprite();
	TSEngine::GetEngine()->LoadSprite(IceMotion, "../Resource/Bitmaps/cha_ice_jump_l.bmp");

	AniInfo ICEMotionAni;
	ICEMotionAni.init(5, 200, 200);
	IceMotion->m_AniInfo = ICEMotionAni;

	m_motion2 = IceMotion;


	//press enter
	TSprite* EnterMortion = new TSprite();
	TSEngine::GetEngine()->LoadSprite(EnterMortion, "../Resource/Bitmaps/main_press.bmp");

	AniInfo EnterMortionAni;
	EnterMortionAni.init(7, 477, 45);
	EnterMortion->m_AniInfo = EnterMortionAni;

	m_PressEnter = EnterMortion;



}

void GameIntro::Update(float dtime)
{

	HDC backbuffer = TSEngine::GetEngine()->GetBackBufferDC();
	//fire 234 335
	TSEngine::GetEngine()->DrawAnimation(backbuffer, 390, 620, m_motion1, dtime * 2.0f);
	//ice
	TSEngine::GetEngine()->DrawAnimation(backbuffer, 1345, 620, m_motion2, dtime * 2.0f);
	//ฟฃลอ 742 774
	TSEngine::GetEngine()->DrawAnimation(backbuffer, 722, 782, m_PressEnter, dtime);
	

	TSEngine::GetEngine()->EndRender();
	

	KeyState::KeyUpdate();

	if (KeyState::InputKeyDown(VK_RETURN)) 
	{
		CSceneManager::GetInstance()->SceneChange(INGAME);
	}


}

void GameIntro::Render(void)
{

	TSEngine::GetEngine()->BeginRender();

	TSEngine::GetEngine()->DrawSpriteOrigin(TSEngine::GetEngine()->GetBackBufferDC(), 0, 0, m_BackGround);
}

void GameIntro::Release(void)
{
	TSEngine::GetEngine()->SpriteRelease(m_BackGround);
	TSEngine::GetEngine()->SpriteRelease(m_motion1);
	TSEngine::GetEngine()->SpriteRelease(m_motion2);
}
