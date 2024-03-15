#include "stdafx.h"
#include "InGame.h"

InGame::InGame()
{
	m_timeing = 0.0f;
}

InGame::~InGame(void)
{
}

void InGame::Init(void)
{


	//플레이어 1 생성
	LoadSpritesPlayer1();
	MakePlayer1();

	//플레이어 2 생성
	LoadSpritesPlayer2();
	MakePlayer2();

	//맵 생성
	GeneratePattern();
	MakeMap();


	//vs ui 로드
	LoadSpritesVSUi();

	
	m_MapManager->m_Mode = MODE::EASY;

}

void InGame::Update(float dtime)
{

	m_timeing += dtime;

	if (m_timeing >= 10.0f && m_MapManager->m_Info.ScrollDownSize < 400.0f && m_MapManager->m_Mode == MODE::EASY)
	{
		m_MapManager->SetPlusScrollSpeed(100.0f);
		m_timeing = 0.0f;

		m_MapManager->m_Mode = MODE::NORMAL;
		//testcode
		/*m_MapManager->SetScrollSpeed(400.0f);
		m_MapManager->m_Mode = MODE::HELL;*/
	}
	else if (m_timeing >= 10.0f && m_MapManager->m_Info.ScrollDownSize < 400.0f && m_MapManager->m_Mode == MODE::NORMAL)
	{
		m_MapManager->SetPlusScrollSpeed(100.0f);
		m_timeing = 0.0f;

		m_MapManager->m_Mode = MODE::HARD0;
	}
	else if (m_timeing >= 15.0f && m_MapManager->m_Info.ScrollDownSize < 400.0f && m_MapManager->m_Mode == MODE::HARD0)
	{
		//m_MapManager->SetPlusScrollSpeed(100.0f);
		m_timeing = 0.0f;

		m_MapManager->m_Mode = MODE::HARD1;
	}
	else if (m_timeing >= 15.0f && m_MapManager->m_Info.ScrollDownSize < 400.0f && m_MapManager->m_Mode == MODE::HARD1)
	{
		m_MapManager->SetPlusScrollSpeed(50.0f);
		m_timeing = 0.0f;

		m_MapManager->m_Mode = MODE::HARD2;
	}
	else if (m_timeing >= 20.0f && m_MapManager->m_Info.ScrollDownSize < 400.0f && m_MapManager->m_Mode == MODE::HARD2)
	{
		//m_MapManager->SetPlusScrollSpeed(50.0f);
		m_timeing = 0.0f;

		m_MapManager->m_Mode = MODE::HARD3;
	}
	else if (m_timeing >= 20.0f && m_MapManager->m_Info.ScrollDownSize < 400.0f && m_MapManager->m_Mode == MODE::HARD3)
	{
		//m_MapManager->SetPlusScrollSpeed(50.0f);
		m_timeing = 0.0f;

		m_MapManager->m_Mode = MODE::HARD4;
	}
	else if (m_timeing >= 15.0f && m_MapManager->m_Info.ScrollDownSize < 400.0f && m_MapManager->m_Mode == MODE::HARD4)
	{
		m_MapManager->SetPlusScrollSpeed(50.0f);
		m_timeing = 0.0f;

		m_MapManager->m_Mode = MODE::HELL;
	}

	m_MapManager->Update(dtime);

	KeyState::KeyUpdate();
	m_Player1->KeyInput();
	m_Player2->KeyInput();

	m_MapManager->Draw(dtime);


	//m_MapManager->m_Player.Player1->m_gage->Draw();
	//m_MapManager->m_Player.Player2->m_gage->Draw();

	//ui 

	TSEngine::GetEngine()->DrawSpriteOrigin(TSEngine::GetEngine()->GetBackBufferDC(), 89, 25, m_UIFireBar);
	TSEngine::GetEngine()->DrawSpriteOrigin(TSEngine::GetEngine()->GetBackBufferDC(), 1027, 25, m_UIIceBar);


	//960 - (m_UIvs->m_Width / 2) = 850
	//TSEngine::GetEngine()->DrawSprite(TSEngine::GetEngine()->GetBackBufferDC(),960 - (m_UIvs->m_Width / 2), 0, m_UIvs);

	m_Player1->m_gage->Draw();
	m_Player2->m_gage->Draw();

	TSEngine::GetEngine()->DrawSprite(TSEngine::GetEngine()->GetBackBufferDC(), 0, 0, m_UIBackVs);

	TSEngine::GetEngine()->EndRender();

	//test
	if (m_Player1->m_Hp <= 0 || (m_Player1->m_Pos.y >= 1080))
	{
		CSceneManager::GetInstance()->SceneChange(WINICE);
	}
	else if (m_Player2->m_Hp <= 0 || (m_Player2->m_Pos.y >= 1080))
	{
		CSceneManager::GetInstance()->SceneChange(WINFIRE);
	}


}

void InGame::Render(void)
{
	//KeyState::KeyUpdate();

	TSEngine::GetEngine()->BeginRender();

	TSEngine::GetEngine()->DrawSpriteOrigin(TSEngine::GetEngine()->GetBackBufferDC(), 0, 0, m_BackGround);

}

void InGame::Release(void)
{

	m_MapManager->Release();

}

void InGame::LoadSpritesPlayer1()
{
	//배경화면 // 그냥 같이넣어주자
	TSprite* Back = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Back, "../Resource/Bitmaps/background.bmp");

	m_BackGround = Back;

	//플레이어 1
	//좌우이동
	TSprite* CharRight = new TSprite();
	TSEngine::GetEngine()->LoadSprite(CharRight, "../Resource/Bitmaps/cha_fire_move_r.bmp");

	AniInfo MoveRightani;
	MoveRightani.init(6, 200, 200);
	CharRight->m_AniInfo = MoveRightani;



	m_Lodead_Player1_Sprites.push_back(CharRight);

	TSprite* CharLeft = new TSprite();
	TSEngine::GetEngine()->LoadSprite(CharLeft, "../Resource/Bitmaps/cha_fire_move_l.bmp");

	AniInfo CharLeftAni;
	CharLeftAni.init(6, 200, 200);
	CharLeft->m_AniInfo = CharLeftAni;

	m_Lodead_Player1_Sprites.push_back(CharLeft);

	//점프
	TSprite* CharJumpl = new TSprite();
	TSEngine::GetEngine()->LoadSprite(CharJumpl, "../Resource/Bitmaps/cha_fire_jump_l.bmp");

	AniInfo CharJumplAni;
	CharJumplAni.init(7, 200, 200);
	CharJumpl->m_AniInfo = CharJumplAni;

	m_Lodead_Player1_Sprites.push_back(CharJumpl);

	TSprite* CharJumpR = new TSprite();
	TSEngine::GetEngine()->LoadSprite(CharJumpR, "../Resource/Bitmaps/cha_fire_jump_r.bmp");

	AniInfo CharJumpRAni;
	CharJumpRAni.init(7, 200, 200);
	CharJumpR->m_AniInfo = CharJumpRAni;

	m_Lodead_Player1_Sprites.push_back(CharJumpR);

	//먹기 모션
	TSprite* CharGoodEat = new TSprite();
	TSEngine::GetEngine()->LoadSprite(CharGoodEat, "../Resource/Bitmaps/cha_fire_eat.bmp");

	AniInfo CharGoodEatAni;
	CharGoodEatAni.init(5, 200, 200);
	CharGoodEat->m_AniInfo = CharGoodEatAni;



	//eat miss
	TSprite* CharMissEat = new TSprite();
	TSEngine::GetEngine()->LoadSprite(CharMissEat, "../Resource/Bitmaps/cha_fire_miss.bmp");

	AniInfo CharMissEatAni;
	CharMissEatAni.init(4, 200, 200);
	CharMissEat->m_AniInfo = CharMissEatAni;

	m_Lodead_Player1_Sprites.push_back(CharMissEat);
	m_Lodead_Player1_Sprites.push_back(CharGoodEat);

	//gage
	TSprite* SprFireGage = new TSprite();
	TSEngine::GetEngine()->LoadSprite(SprFireGage, "../Resource/Bitmaps/ui_hp_fire.bmp");
	m_SprPlayer1Gage = SprFireGage;

}

void InGame::MakePlayer1()
{
	//주인공 스프라이트 주입
	for (int i = 0; i < m_Lodead_Player1_Sprites.size(); i++)
	{
		m_Player1Arr[i] = m_Lodead_Player1_Sprites[i];
	}
	m_Player1 = new Player();
	m_Player1->Init(50, 800, 10, 240.0f, 0.2f, MOVERIGHT, m_Player1Arr, 6, m_SprPlayer1Gage);
}

void InGame::LoadSpritesPlayer2()
{
	//플레이어 2
	//좌우이동
	TSprite* Char2Right = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Char2Right, "../Resource/Bitmaps/cha_ice_move_r.bmp");

	AniInfo Char2RightAni;
	Char2RightAni.init(5, 200, 200);
	Char2Right->m_AniInfo = Char2RightAni;

	m_Lodead_Player2_Sprites.push_back(Char2Right);

	TSprite* Char2Left = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Char2Left, "../Resource/Bitmaps/cha_ice_move_l.bmp");

	AniInfo Char2LeftAni;
	Char2LeftAni.init(5, 200, 200);
	Char2Left->m_AniInfo = Char2LeftAni;

	m_Lodead_Player2_Sprites.push_back(Char2Left);

	//점프

	TSprite* Char2Jumpl = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Char2Jumpl, "../Resource/Bitmaps/cha_ice_jump_l.bmp");

	AniInfo Char2JumplAni;
	Char2JumplAni.init(8, 200, 200);
	Char2Jumpl->m_AniInfo = Char2JumplAni;

	m_Lodead_Player2_Sprites.push_back(Char2Jumpl);


	TSprite* Char2JumpR = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Char2JumpR, "../Resource/Bitmaps/cha_ice_jump_r.bmp");

	AniInfo Char2JumpRAni;
	Char2JumpRAni.init(8, 200, 200);
	Char2JumpR->m_AniInfo = Char2JumpRAni;

	m_Lodead_Player2_Sprites.push_back(Char2JumpR);

	//먹기 모션

	//good eat
	TSprite* Char2GoodEat = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Char2GoodEat, "../Resource/Bitmaps/cha_ice_eat.bmp");

	AniInfo Char2GoodEatAni;
	Char2GoodEatAni.init(5, 200, 200);
	Char2GoodEat->m_AniInfo = Char2GoodEatAni;



	//eat miss
	TSprite* Char2MissEat = new TSprite();
	TSEngine::GetEngine()->LoadSprite(Char2MissEat, "../Resource/Bitmaps/cha_ice_miss.bmp");

	AniInfo Char2MissEatAni;
	Char2MissEatAni.init(5, 200, 200);
	Char2MissEat->m_AniInfo = Char2MissEatAni;

	m_Lodead_Player2_Sprites.push_back(Char2MissEat);
	m_Lodead_Player2_Sprites.push_back(Char2GoodEat);

	//gage
	TSprite* SprGageIce = new TSprite();
	TSEngine::GetEngine()->LoadSprite(SprGageIce, "../Resource/Bitmaps/ui_hp_ice.bmp");

	m_SprPlayer2Gage = SprGageIce;

}

void InGame::MakePlayer2()
{
	//주인공 스프라이트 주입
	for (int i = 0; i < m_Lodead_Player2_Sprites.size(); i++)
	{
		m_Player2Arr[i] = m_Lodead_Player2_Sprites[i];
	}

	m_Player2 = new Player2();
	//940 50+913
	m_Player2->Init(963, 800, 10, 240.0f, 0.2f, MOVERIGHT, m_Player2Arr, 6, m_SprPlayer2Gage);
}

void InGame::GeneratePattern()
{
	//easy mode
	EASYPattern = new ItemPatern();

	ITEMPROPERTY easy_A01[2] = { {FIREITEM,722},{ICEITEM,1619} };
	ITEMPROPERTY easy_A02[4] = { {FIREITEM,373},{FIREITEM,605},{ICEITEM,1270},{ICEITEM,1502} };
	ITEMPROPERTY easy_A03[4] = { {FIREITEM,231},{FIREITEM,762},{ICEITEM,1128},{ICEITEM,1695} };
	ITEMPROPERTY easy_A04[4] = { {FIREITEM,413},{FIREITEM,645},{ICEITEM,1310},{ICEITEM,1542} };
	ITEMPROPERTY easy_A05[2] = { {FIREITEM,605},{ICEITEM,1502} };
	ITEMPROPERTY easy_A06[4] = { {FIREITEM,423},{FIREITEM,722},{ICEITEM,1320},{ICEITEM,1619} };
	ITEMPROPERTY easy_A07[4] = { {FIREITEM,311},{FIREITEM,525},{ICEITEM,1208},{ICEITEM,1422} };
	ITEMPROPERTY easy_A08[6] = { {FIREITEM,231},{FIREITEM,485},{FIREITEM,762},{ICEITEM,1128},{ICEITEM,1382},{ICEITEM,1659} };
	ITEMPROPERTY easy_A09[2] = { {FIREITEM,413},{ICEITEM,1310} };
	ITEMPROPERTY easy_A10[4] = { {FIREITEM,314},{FIREITEM,503},{ICEITEM,1211},{ICEITEM,1400} };


	std::vector<ITEMPROPERTY> a_pattern1 = EASYPattern->MakeOnePattern(easy_A01, 2);
	std::vector<ITEMPROPERTY> a_pattern2 = EASYPattern->MakeOnePattern(easy_A02, 4);
	std::vector<ITEMPROPERTY> a_pattern3 = EASYPattern->MakeOnePattern(easy_A03, 4);
	std::vector<ITEMPROPERTY> a_pattern4 = EASYPattern->MakeOnePattern(easy_A04, 4);
	std::vector<ITEMPROPERTY> a_pattern5 = EASYPattern->MakeOnePattern(easy_A05, 2);
	std::vector<ITEMPROPERTY> a_pattern6 = EASYPattern->MakeOnePattern(easy_A06, 4);
	std::vector<ITEMPROPERTY> a_pattern7 = EASYPattern->MakeOnePattern(easy_A07, 4);
	std::vector<ITEMPROPERTY> a_pattern8 = EASYPattern->MakeOnePattern(easy_A08, 6);
	std::vector<ITEMPROPERTY> a_pattern9 = EASYPattern->MakeOnePattern(easy_A09, 2);
	std::vector<ITEMPROPERTY> a_pattern10 = EASYPattern->MakeOnePattern(easy_A10, 4);


	EASYPattern->MakePattern(a_pattern1);
	EASYPattern->MakePattern(a_pattern2);
	EASYPattern->MakePattern(a_pattern3);
	EASYPattern->MakePattern(a_pattern4);
	EASYPattern->MakePattern(a_pattern5);
	EASYPattern->MakePattern(a_pattern6);
	EASYPattern->MakePattern(a_pattern7);
	EASYPattern->MakePattern(a_pattern8);
	EASYPattern->MakePattern(a_pattern9);
	EASYPattern->MakePattern(a_pattern10);

	//normal
	NORMALPattern = new ItemPatern();

	ITEMPROPERTY nomal_B01[6] = { {FIREITEM,423},{FIRETRAP,559},{FIREITEM,722},{ICEITEM,1336},{ICETRAP,1472},{ICEITEM,1635}, };
	ITEMPROPERTY nomal_B02[2] = { {FIREITEM,525},{ICEITEM,(525 + 913)}, };
	ITEMPROPERTY nomal_B03[4] = { {FIRETRAP,231},{FIREITEM,485},{ICETRAP,(231 + 913)},{ICEITEM,(485 + 913)} };
	ITEMPROPERTY nomal_B04[2] = { {FIREITEM,623},{ICEITEM,(623 + 913)} };
	ITEMPROPERTY nomal_B05[2] = { {FIREITEM,503},{ICEITEM,(503 + 913)} };
	ITEMPROPERTY nomal_B06[4] = { {FIREITEM,226},{FIREITEM,362},{ICEITEM,(226 + 913)},{ICEITEM,(362 + 913)} };
	ITEMPROPERTY nomal_B07[2] = { {FIREITEM,663},{ICEITEM,(663 + 913)} };
	ITEMPROPERTY nomal_B08[2] = { {FIRETRAP,231},{ICETRAP,(231 + 913)} };
	ITEMPROPERTY nomal_B09[2] = { {FIREITEM,362},{ICEITEM,(362 + 913)} };
	ITEMPROPERTY nomal_B10[2] = { {FIREITEM,683},{ICEITEM,(683 + 913)} };

	std::vector<ITEMPROPERTY> b_pattern1 = EASYPattern->MakeOnePattern(nomal_B01, 6);
	std::vector<ITEMPROPERTY> b_pattern2 = EASYPattern->MakeOnePattern(nomal_B02, 2);
	std::vector<ITEMPROPERTY> b_pattern3 = EASYPattern->MakeOnePattern(nomal_B03, 4);
	std::vector<ITEMPROPERTY> b_pattern4 = EASYPattern->MakeOnePattern(nomal_B04, 2);
	std::vector<ITEMPROPERTY> b_pattern5 = EASYPattern->MakeOnePattern(nomal_B05, 2);
	std::vector<ITEMPROPERTY> b_pattern6 = EASYPattern->MakeOnePattern(nomal_B06, 4);
	std::vector<ITEMPROPERTY> b_pattern7 = EASYPattern->MakeOnePattern(nomal_B07, 2);
	std::vector<ITEMPROPERTY> b_pattern8 = EASYPattern->MakeOnePattern(nomal_B08, 2);
	std::vector<ITEMPROPERTY> b_pattern9 = EASYPattern->MakeOnePattern(nomal_B09, 2);
	std::vector<ITEMPROPERTY> b_pattern10 = EASYPattern->MakeOnePattern(nomal_B10, 2);


	NORMALPattern->MakePattern(b_pattern1);
	NORMALPattern->MakePattern(b_pattern2);
	NORMALPattern->MakePattern(b_pattern3);
	NORMALPattern->MakePattern(b_pattern4);
	NORMALPattern->MakePattern(b_pattern5);
	NORMALPattern->MakePattern(b_pattern6);
	NORMALPattern->MakePattern(b_pattern7);
	NORMALPattern->MakePattern(b_pattern8);
	NORMALPattern->MakePattern(b_pattern9);
	NORMALPattern->MakePattern(b_pattern10);


	//HARD 01

	HARD00Pattern = new ItemPatern();

	ITEMPROPERTY HARD_C01[4] = { {FIREITEM,442},{FIREITEM,708},{ICEITEM,442 + 913},{ICEITEM,708 + 913} };
	ITEMPROPERTY HARD_C02[4] = { {FIREITEM,247},{FIRETRAP,708},{ICEITEM,247 + 913},{ICETRAP,708 + 913} };
	ITEMPROPERTY HARD_C03[2] = { {FIREITEM,442},{ICEITEM,442 + 913} };
	ITEMPROPERTY HARD_C04[4] = { {FIRETRAP,427},{FIREITEM,723},{ICETRAP,427 + 913},{ICEITEM,723 + 913} };
	ITEMPROPERTY HARD_C05[2] = { {FIREITEM,442},{ICEITEM,442 + 913} };
	ITEMPROPERTY HARD_C06[4] = { {FIREITEM,317},{FIREITEM,708},{ICEITEM,317 + 913},{ICEITEM,708 + 913} };
	ITEMPROPERTY HARD_C07[8] = { {FIREITEM,247},{FIRETRAP,357},{FIREITEM,546},{FIRETRAP,708},{ICEITEM,247 + 913},{ICETRAP,357 + 913},{ICEITEM,546 + 913},{ICETRAP,708 + 913} };
	ITEMPROPERTY HARD_C08[2] = { {FIREITEM,317},{ICEITEM,317 + 913} };
	ITEMPROPERTY HARD_C09[4] = { {FIREITEM,467},{FIREITEM,723},{ICEITEM,467 + 913},{ICEITEM,723 + 913} };
	ITEMPROPERTY HARD_C10[4] = { {FIREITEM,207},{FIREITEM,708},{ICEITEM,207 + 913},{ICEITEM,708 + 913} };

	std::vector<ITEMPROPERTY> c_pattern1 = HARD00Pattern->MakeOnePattern(HARD_C01, 4);
	std::vector<ITEMPROPERTY> c_pattern2 = HARD00Pattern->MakeOnePattern(HARD_C02, 4);
	std::vector<ITEMPROPERTY> c_pattern3 = HARD00Pattern->MakeOnePattern(HARD_C03, 2);
	std::vector<ITEMPROPERTY> c_pattern4 = HARD00Pattern->MakeOnePattern(HARD_C04, 4);
	std::vector<ITEMPROPERTY> c_pattern5 = HARD00Pattern->MakeOnePattern(HARD_C05, 2);
	std::vector<ITEMPROPERTY> c_pattern6 = HARD00Pattern->MakeOnePattern(HARD_C06, 4);
	std::vector<ITEMPROPERTY> c_pattern7 = HARD00Pattern->MakeOnePattern(HARD_C07, 8);
	std::vector<ITEMPROPERTY> c_pattern8 = HARD00Pattern->MakeOnePattern(HARD_C08, 2);
	std::vector<ITEMPROPERTY> c_pattern9 = HARD00Pattern->MakeOnePattern(HARD_C09, 4);
	std::vector<ITEMPROPERTY> c_pattern10 = HARD00Pattern->MakeOnePattern(HARD_C10, 4);


	HARD00Pattern->MakePattern(c_pattern1);
	HARD00Pattern->MakePattern(c_pattern2);
	HARD00Pattern->MakePattern(c_pattern3);
	HARD00Pattern->MakePattern(c_pattern4);
	HARD00Pattern->MakePattern(c_pattern5);
	HARD00Pattern->MakePattern(c_pattern6);
	HARD00Pattern->MakePattern(c_pattern7);
	HARD00Pattern->MakePattern(c_pattern8);
	HARD00Pattern->MakePattern(c_pattern9);
	HARD00Pattern->MakePattern(c_pattern10);




	//HARD 02

	HARD01Pattern = new ItemPatern();

	ITEMPROPERTY HARD_D01[6] = { {FIREITEM,209},{FIREITEM,626},{FIREITEM,748},{ICEITEM,209 + 913},{ICEITEM,626 + 913},{ICEITEM,748 + 913} };
	ITEMPROPERTY HARD_D02[6] = { {FIRETRAP,192},{FIREITEM,546},{FIRETRAP,708},{ICETRAP,192 + 913},{ICEITEM,546 + 913},{ICETRAP,708 + 913} };
	ITEMPROPERTY HARD_D03[2] = { {FIREITEM,317},{ICEITEM,317 + 913} };
	ITEMPROPERTY HARD_D04[6] = { {FIREITEM,247},{FIRETRAP,357},{FIREITEM,738},{ICEITEM,247 + 913},{ICETRAP,357 + 913},{ICEITEM,738 + 913} };
	ITEMPROPERTY HARD_D05[2] = { {FIREITEM,357},{ICEITEM,357 + 913} };
	ITEMPROPERTY HARD_D06[4] = { {FIREITEM,209},{FIREITEM,748},{ICEITEM,209 + 913},{ICEITEM,748 + 913} };
	ITEMPROPERTY HARD_D07[6] = { {FIREITEM,287},{FIRETRAP,516},{FIREITEM,641},{ICEITEM,287 + 913},{ICETRAP,516 + 913},{ICEITEM,641 + 913} };
	ITEMPROPERTY HARD_D08[2] = { {FIREITEM,698},{ICEITEM,698 + 913} };
	ITEMPROPERTY HARD_D09[6] = { {FIREITEM,247},{FIRETRAP,571},{FIREITEM,738},{ICEITEM,247 + 913},{ICETRAP,571 + 913},{ICEITEM,738 + 913} };
	ITEMPROPERTY HARD_D10[2] = { {FIREITEM,668},{ICEITEM,668 + 913} };

	std::vector<ITEMPROPERTY> d_pattern1 = HARD01Pattern->MakeOnePattern(HARD_D01, 6);
	std::vector<ITEMPROPERTY> d_pattern2 = HARD01Pattern->MakeOnePattern(HARD_D02, 6);
	std::vector<ITEMPROPERTY> d_pattern3 = HARD01Pattern->MakeOnePattern(HARD_D03, 2);
	std::vector<ITEMPROPERTY> d_pattern4 = HARD01Pattern->MakeOnePattern(HARD_D04, 6);
	std::vector<ITEMPROPERTY> d_pattern5 = HARD01Pattern->MakeOnePattern(HARD_D05, 2);
	std::vector<ITEMPROPERTY> d_pattern6 = HARD01Pattern->MakeOnePattern(HARD_D06, 4);
	std::vector<ITEMPROPERTY> d_pattern7 = HARD01Pattern->MakeOnePattern(HARD_D07, 6);
	std::vector<ITEMPROPERTY> d_pattern8 = HARD01Pattern->MakeOnePattern(HARD_D08, 2);
	std::vector<ITEMPROPERTY> d_pattern9 = HARD01Pattern->MakeOnePattern(HARD_D09, 6);
	std::vector<ITEMPROPERTY> d_pattern10 = HARD01Pattern->MakeOnePattern(HARD_D10, 2);


	HARD01Pattern->MakePattern(d_pattern1);
	HARD01Pattern->MakePattern(d_pattern2);
	HARD01Pattern->MakePattern(d_pattern3);
	HARD01Pattern->MakePattern(d_pattern4);
	HARD01Pattern->MakePattern(d_pattern5);
	HARD01Pattern->MakePattern(d_pattern6);
	HARD01Pattern->MakePattern(d_pattern7);
	HARD01Pattern->MakePattern(d_pattern8);
	HARD01Pattern->MakePattern(d_pattern9);
	HARD01Pattern->MakePattern(d_pattern10);





	//HARD 03
	HARD02Pattern = new ItemPatern();

	ITEMPROPERTY HARD_E01[4] = { {FIREITEM,209},{FIREITEM,571},{ICEITEM,209 + 913},{ICEITEM,571 + 913} };
	ITEMPROPERTY HARD_E02[6] = { {FIREITEM,287},{FIRETRAP,461},{FIREITEM,641},{ICEITEM,287 + 913},{ICETRAP,461 + 913},{ICEITEM,641 + 913} };
	ITEMPROPERTY HARD_E03[6] = { {FIRETRAP,209},{FIREITEM,367},{FIREITEM,698},{ICETRAP,209 + 913},{ICEITEM,367 + 913},{ICEITEM,698 + 913} };
	ITEMPROPERTY HARD_E04[8] = { {FIREITEM,247},{FIREITEM,491},{FIRETRAP,611},{FIREITEM,748},{ICEITEM,247 + 913},{ICEITEM,491 + 913},{ICETRAP,611 + 913},{ICEITEM,748 + 913} };
	ITEMPROPERTY HARD_E05[4] = { {FIREITEM,246},{FIREITEM,411},{ICEITEM,246 + 913},{ICEITEM,411 + 913} };
	ITEMPROPERTY HARD_E06[2] = { {FIREITEM,209},{ICEITEM,209 + 913} };
	ITEMPROPERTY HARD_E07[4] = { {FIREITEM,287},{FIREITEM,778},{ICEITEM,287 + 913},{ICEITEM,778 + 913} };
	ITEMPROPERTY HARD_E08[2] = { {FIREITEM,641},{ICEITEM,641 + 913} };
	ITEMPROPERTY HARD_E09[4] = { {FIREITEM,344},{FIREITEM,748},{ICEITEM,344 + 913},{ICEITEM,748 + 913} };
	ITEMPROPERTY HARD_E10[2] = { {FIREITEM,304},{ICEITEM,304 + 913} };


	std::vector<ITEMPROPERTY> e_pattern1 = HARD02Pattern->MakeOnePattern(HARD_E01, 4);
	std::vector<ITEMPROPERTY> e_pattern2 = HARD02Pattern->MakeOnePattern(HARD_E02, 6);
	std::vector<ITEMPROPERTY> e_pattern3 = HARD02Pattern->MakeOnePattern(HARD_E03, 6);
	std::vector<ITEMPROPERTY> e_pattern4 = HARD02Pattern->MakeOnePattern(HARD_E04, 8);
	std::vector<ITEMPROPERTY> e_pattern5 = HARD02Pattern->MakeOnePattern(HARD_E05, 4);
	std::vector<ITEMPROPERTY> e_pattern6 = HARD02Pattern->MakeOnePattern(HARD_E06, 2);
	std::vector<ITEMPROPERTY> e_pattern7 = HARD02Pattern->MakeOnePattern(HARD_E07, 4);
	std::vector<ITEMPROPERTY> e_pattern8 = HARD02Pattern->MakeOnePattern(HARD_E08, 2);
	std::vector<ITEMPROPERTY> e_pattern9 = HARD02Pattern->MakeOnePattern(HARD_E09, 4);
	std::vector<ITEMPROPERTY> e_pattern10 = HARD02Pattern->MakeOnePattern(HARD_E10, 2);


	HARD02Pattern->MakePattern(e_pattern1);
	HARD02Pattern->MakePattern(e_pattern2);
	HARD02Pattern->MakePattern(e_pattern3);
	HARD02Pattern->MakePattern(e_pattern4);
	HARD02Pattern->MakePattern(e_pattern5);
	HARD02Pattern->MakePattern(e_pattern6);
	HARD02Pattern->MakePattern(e_pattern7);
	HARD02Pattern->MakePattern(e_pattern8);
	HARD02Pattern->MakePattern(e_pattern9);
	HARD02Pattern->MakePattern(e_pattern10);


	//HARD 04
	HARD03Pattern = new ItemPatern();

	ITEMPROPERTY HARD_F01[4] = { {FIREITEM,442},{FIREITEM,708},{ICEITEM,442 + 913},{ICEITEM,708 + 913} };
	ITEMPROPERTY HARD_F02[4] = { {FIREITEM,247},{FIRETRAP,708},{ICEITEM,247 + 913},{ICETRAP,708 + 913} };
	ITEMPROPERTY HARD_F03[2] = { {FIREITEM,442},{ICEITEM,442 + 913} };
	ITEMPROPERTY HARD_F04[4] = { {FIRETRAP,427},{FIREITEM,723},{ICETRAP,427 + 913},{ICEITEM,723 + 913} };
	ITEMPROPERTY HARD_F05[2] = { {FIREITEM,442},{ICEITEM,442 + 913} };
	ITEMPROPERTY HARD_F06[4] = { {FIREITEM,317},{FIREITEM,708},{ICEITEM,317 + 913},{ICEITEM,708 + 913} };
	ITEMPROPERTY HARD_F07[8] = { {FIREITEM,247},{FIRETRAP,357},{FIREITEM,546},{FIRETRAP,708},{ICEITEM,247 + 913},{ICETRAP,357 + 913},{ICEITEM,546 + 913},{ICETRAP,708 + 913} };
	ITEMPROPERTY HARD_F08[2] = { {FIREITEM,317},{ICEITEM,317 + 913} };
	ITEMPROPERTY HARD_F09[4] = { {FIREITEM,467},{FIREITEM,723},{ICEITEM,467 + 913},{ICEITEM,723 + 913} };
	ITEMPROPERTY HARD_F10[4] = { {FIREITEM,207},{FIREITEM,708},{ICEITEM,207 + 913},{ICEITEM,708 + 913} };

	std::vector<ITEMPROPERTY> f_pattern1 = HARD03Pattern->MakeOnePattern(HARD_F01, 4);
	std::vector<ITEMPROPERTY> f_pattern2 = HARD03Pattern->MakeOnePattern(HARD_F02, 4);
	std::vector<ITEMPROPERTY> f_pattern3 = HARD03Pattern->MakeOnePattern(HARD_F03, 2);
	std::vector<ITEMPROPERTY> f_pattern4 = HARD03Pattern->MakeOnePattern(HARD_F04, 4);
	std::vector<ITEMPROPERTY> f_pattern5 = HARD03Pattern->MakeOnePattern(HARD_F05, 2);
	std::vector<ITEMPROPERTY> f_pattern6 = HARD03Pattern->MakeOnePattern(HARD_F06, 4);
	std::vector<ITEMPROPERTY> f_pattern7 = HARD03Pattern->MakeOnePattern(HARD_F07, 8);
	std::vector<ITEMPROPERTY> f_pattern8 = HARD03Pattern->MakeOnePattern(HARD_F08, 2);
	std::vector<ITEMPROPERTY> f_pattern9 = HARD03Pattern->MakeOnePattern(HARD_F09, 4);
	std::vector<ITEMPROPERTY> f_pattern10 = HARD03Pattern->MakeOnePattern(HARD_F10, 4);


	HARD03Pattern->MakePattern(f_pattern1);
	HARD03Pattern->MakePattern(f_pattern2);
	HARD03Pattern->MakePattern(f_pattern3);
	HARD03Pattern->MakePattern(f_pattern4);
	HARD03Pattern->MakePattern(f_pattern5);
	HARD03Pattern->MakePattern(f_pattern6);
	HARD03Pattern->MakePattern(f_pattern7);
	HARD03Pattern->MakePattern(f_pattern8);
	HARD03Pattern->MakePattern(f_pattern9);
	HARD03Pattern->MakePattern(f_pattern10);


	//HARD 05
	HARD04Pattern = new ItemPatern();

	ITEMPROPERTY HARD_G01[6] = { {FIREITEM,209},{FIREITEM,626},{FIREITEM,748},{ICEITEM,209 + 913},{ICEITEM,626 + 913},{ICEITEM,748 + 913} };
	ITEMPROPERTY HARD_G02[6] = { {FIRETRAP,192},{FIREITEM,546},{FIRETRAP,708},{ICETRAP,192 + 913},{ICEITEM,546 + 913},{ICETRAP,708 + 913} };
	ITEMPROPERTY HARD_G03[2] = { {FIREITEM,317},{ICEITEM,317 + 913} };
	ITEMPROPERTY HARD_G04[6] = { {FIREITEM,247},{FIRETRAP,357},{FIREITEM,738},{ICEITEM,247 + 913},{ICETRAP,357 + 913},{ICEITEM,738 + 913} };
	ITEMPROPERTY HARD_G05[2] = { {FIREITEM,357},{ICEITEM,357 + 913} };
	ITEMPROPERTY HARD_G06[4] = { {FIREITEM,209},{FIREITEM,748},{ICEITEM,209 + 913},{ICEITEM,748 + 913} };
	ITEMPROPERTY HARD_G07[6] = { {FIREITEM,287},{FIRETRAP,516},{FIREITEM,641},{ICEITEM,287 + 913},{ICETRAP,516 + 913},{ICEITEM,641 + 913} };
	ITEMPROPERTY HARD_G08[2] = { {FIREITEM,698},{ICEITEM,698 + 913} };
	ITEMPROPERTY HARD_G09[6] = { {FIREITEM,247},{FIRETRAP,571},{FIREITEM,738},{ICEITEM,247 + 913},{ICETRAP,571 + 913},{ICEITEM,738 + 913} };
	ITEMPROPERTY HARD_G10[2] = { {FIREITEM,668},{ICEITEM,668 + 913} };

	std::vector<ITEMPROPERTY> g_pattern1 = HARD04Pattern->MakeOnePattern(HARD_G01, 6);
	std::vector<ITEMPROPERTY> g_pattern2 = HARD04Pattern->MakeOnePattern(HARD_G02, 6);
	std::vector<ITEMPROPERTY> g_pattern3 = HARD04Pattern->MakeOnePattern(HARD_G03, 2);
	std::vector<ITEMPROPERTY> g_pattern4 = HARD04Pattern->MakeOnePattern(HARD_G04, 6);
	std::vector<ITEMPROPERTY> g_pattern5 = HARD04Pattern->MakeOnePattern(HARD_G05, 2);
	std::vector<ITEMPROPERTY> g_pattern6 = HARD04Pattern->MakeOnePattern(HARD_G06, 4);
	std::vector<ITEMPROPERTY> g_pattern7 = HARD04Pattern->MakeOnePattern(HARD_G07, 6);
	std::vector<ITEMPROPERTY> g_pattern8 = HARD04Pattern->MakeOnePattern(HARD_G08, 2);
	std::vector<ITEMPROPERTY> g_pattern9 = HARD04Pattern->MakeOnePattern(HARD_G09, 6);
	std::vector<ITEMPROPERTY> g_pattern10 = HARD04Pattern->MakeOnePattern(HARD_G10, 2);


	HARD04Pattern->MakePattern(g_pattern1);
	HARD04Pattern->MakePattern(g_pattern2);
	HARD04Pattern->MakePattern(g_pattern3);
	HARD04Pattern->MakePattern(g_pattern4);
	HARD04Pattern->MakePattern(g_pattern5);
	HARD04Pattern->MakePattern(g_pattern6);
	HARD04Pattern->MakePattern(g_pattern7);
	HARD04Pattern->MakePattern(g_pattern8);
	HARD04Pattern->MakePattern(g_pattern9);
	HARD04Pattern->MakePattern(g_pattern10);


	//HELL
	HELLPattern = new ItemPatern();

	ITEMPROPERTY HELL_H01[8] = { {FIREITEM,222},{FIREITEM,748},{FIRETRAP,382},{FIRETRAP,530},{ICEITEM,222 + 913},{ICETRAP,382 + 913},{ICETRAP,513 + 913},{ICEITEM,748 + 913} };
	ITEMPROPERTY HELL_H02[8] = { {FIRETRAP,302},{FIREITEM,467},{FIRETRAP,572},{FIRETRAP,723},{ICETRAP,302 + 913},{ICEITEM,467 + 913},{ICETRAP,572 + 913},{ICETRAP,723 + 913} };
	ITEMPROPERTY HELL_H03[8] = { {FIREITEM,209},{FIREITEM,317},{FIRETRAP,613},{FIREITEM,754},{ICEITEM,209 + 913},{ICEITEM,317 + 913},{ICETRAP,613 + 913},{ICEITEM,754 + 913} };
	ITEMPROPERTY HELL_H04[6] = { {FIREITEM,317},{FIRETRAP,450},{FIREITEM,738},{ICEITEM,317 + 913},{ICETRAP,450 + 913},{ICEITEM,738 + 913} };
	ITEMPROPERTY HELL_H05[4] = { {FIREITEM,452},{FIREITEM,585},{ICEITEM,452 + 913},{ICEITEM,585 + 913} };
	ITEMPROPERTY HELL_H06[6] = { {FIREITEM,209},{FIRETRAP,429},{FIREITEM,571},{ICEITEM,209 + 913},{ICETRAP,429 + 913},{ICEITEM,571 + 913} };
	ITEMPROPERTY HELL_H07[6] = { {FIREITEM,287},{FIREITEM,429},{FIREITEM,698},{ICETRAP,287 + 913},{ICEITEM,429 + 913},{ICEITEM,698 + 913} };
	ITEMPROPERTY HELL_H08[4] = { {FIRETRAP,367},{FIREITEM,698},{ICETRAP,367 + 913},{ICEITEM,698 + 913} };
	ITEMPROPERTY HELL_H09[8] = { {FIREITEM,247},{FIRETRAP,429},{FIRETRAP,571},{FIREITEM,738},{ICEITEM,247 + 913},{ICETRAP,429 + 913},{ICETRAP,571 + 913},{ICEITEM,738 + 913} };
	ITEMPROPERTY HELL_H10[4] = { {FIRETRAP,209},{FIREITEM,668},{ICETRAP,209 + 913},{ICEITEM,668 + 913} };

	std::vector<ITEMPROPERTY> h_pattern1 = HELLPattern->MakeOnePattern(HELL_H01, 8);
	std::vector<ITEMPROPERTY> h_pattern2 = HELLPattern->MakeOnePattern(HELL_H02, 8);
	std::vector<ITEMPROPERTY> h_pattern3 = HELLPattern->MakeOnePattern(HELL_H03, 8);
	std::vector<ITEMPROPERTY> h_pattern4 = HELLPattern->MakeOnePattern(HELL_H04, 6);
	std::vector<ITEMPROPERTY> h_pattern5 = HELLPattern->MakeOnePattern(HELL_H05, 4);
	std::vector<ITEMPROPERTY> h_pattern6 = HELLPattern->MakeOnePattern(HELL_H06, 6);
	std::vector<ITEMPROPERTY> h_pattern7 = HELLPattern->MakeOnePattern(HELL_H07, 6);
	std::vector<ITEMPROPERTY> h_pattern8 = HELLPattern->MakeOnePattern(HELL_H08, 4);
	std::vector<ITEMPROPERTY> h_pattern9 = HELLPattern->MakeOnePattern(HELL_H09, 8);
	std::vector<ITEMPROPERTY> h_pattern10 = HELLPattern->MakeOnePattern(HELL_H10, 4);


	HELLPattern->MakePattern(h_pattern1);
	HELLPattern->MakePattern(h_pattern2);
	HELLPattern->MakePattern(h_pattern3);
	HELLPattern->MakePattern(h_pattern4);
	HELLPattern->MakePattern(h_pattern5);
	HELLPattern->MakePattern(h_pattern6);
	HELLPattern->MakePattern(h_pattern7);
	HELLPattern->MakePattern(h_pattern8);
	HELLPattern->MakePattern(h_pattern9);
	HELLPattern->MakePattern(h_pattern10);


}

void InGame::MakeMap()
{
	MAPINFO Minfo;

	Minfo.FInterval = 200; // 플랫폼끼리의 높이 간격
	Minfo.ScrollDownSize = 100.0f; // 1초당 움직일 픽셀

	Minfo.EASYPattern = EASYPattern;// 아이템 생성 패턴
	Minfo.NORMALPattern = NORMALPattern;
	Minfo.HARD00Pattern = HARD00Pattern;
	Minfo.HARD01Pattern = HARD01Pattern;
	Minfo.HARD02Pattern = HARD02Pattern;
	Minfo.HARD03Pattern = HARD03Pattern;
	Minfo.HARD04Pattern = HARD04Pattern;
	Minfo.HELLPattern = HELLPattern;

	Minfo.SprPlatForm = new TSprite();
	Minfo.SprItems[0] = new TSprite;
	Minfo.SprItems[1] = new TSprite;

	Minfo.SprTrap[0] = new TSprite;
	Minfo.SprTrap[1] = new TSprite;

	TSEngine::GetEngine()->LoadSprite(Minfo.SprItems[0], "../Resource/Bitmaps/FireItem0.bmp");
	TSEngine::GetEngine()->LoadSprite(Minfo.SprItems[1], "../Resource/Bitmaps/IceItem0.bmp");
	TSEngine::GetEngine()->LoadSprite(Minfo.SprPlatForm, "../Resource/Bitmaps/PlatForm.bmp");

	TSEngine::GetEngine()->LoadSprite(Minfo.SprTrap[0], "../Resource/Bitmaps/trap_firestorm.bmp");
	TSEngine::GetEngine()->LoadSprite(Minfo.SprTrap[1], "../Resource/Bitmaps/trap_icicle.bmp");



	//Playerinfo 세팅
	PLAYERINFO Pinfo;
	Pinfo.Player1 = m_Player1;
	Pinfo.Player2 = m_Player2;


	m_MapManager = new GameManager;
	m_MapManager->Init(Minfo, Pinfo);
	m_MapManager->GenerateMap();
}

void InGame::LoadSpritesVSUi()
{
	
	m_UIBackVs = new TSprite();
	TSEngine::GetEngine()->LoadSprite(m_UIBackVs, "../Resource/Bitmaps/ui_vs.bmp");


	m_UIFireBar = new TSprite();
	TSEngine::GetEngine()->LoadSprite(m_UIFireBar, "../Resource/Bitmaps/ui_hp_fire_bar.bmp");

	/*m_UIFireHP = new TSprite();
	TSEngine::GetEngine()->LoadSprite(m_UIFireHP, "../Resource/Bitmaps/ui_hp_fire.bmp");*/
	
	
	m_UIIceBar = new TSprite();
	TSEngine::GetEngine()->LoadSprite(m_UIIceBar, "../Resource/Bitmaps/ui_hp_ice_bar.bmp");

	/*m_UIIceHP = new TSprite();
	TSEngine::GetEngine()->LoadSprite(m_UIIceHP, "../Resource/Bitmaps/ui_hp_ice.bmp");*/

	//플레이어에게 주입?
	//m_Player2->m_gage->m_Sprite = m_UIFireHP;

}
