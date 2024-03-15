#include "stdafx.h"
#include "CSceneManager.h"

CSceneManager* CSceneManager::m_Instance = nullptr;



CSceneManager::CSceneManager(void)
{
}

CSceneManager::~CSceneManager(void)
{
}

CSceneManager* CSceneManager::GetInstance(void)
{
	//½Ì±ÛÅæ
	if (m_Instance == nullptr)
	{
		m_Instance = new CSceneManager;
	}
	return m_Instance;
}

void CSceneManager::FreeInststance(void)
{
	if (m_Instance != nullptr)
	{
		if (m_pcScene != nullptr)
		{
			m_pcScene->Release(); // ¾ÀÀÌ ÆÄ±«µÇ±â Àü¿¡ ÇØ´ç¾ÀÀ» ÇÒ´çÇØÁ¦ÇØÁÜ
			delete m_pcScene;
			m_pcScene = nullptr;
		}
		delete m_Instance;
		m_Instance = nullptr;
	}
}

void CSceneManager::Init()
{
	m_bSceneChage = false;
	m_bGameEnd = false;
	m_pcScene = new GameIntro; // Ã¹¹øÂ° ¾ÀÀ» ÀÎÆ®·Î·Î
	m_NowScene = GAMEINTRO; // Ã¹¹øÂ° ¾ÀÀ» ÀÎÆ®·Î·Î
    //m_pcScene = new InGame;
    //m_NowScene = INGAME; // Ã¹¹øÂ° ¾ÀÀ» ÀÎÆ®·Î·Î
	m_pcScene->Init();           // ¾À ÃÊ±âÈ­


    ynSndPlay(SoundManager::GetInstance()->GetBGMList(0), 1, 1);
    //timer
    m_timer = new CTimeController();
    m_timer->Initialize();

    m_timer->StartTimeStamp();
   
}

void CSceneManager::SceneChange(SCENESTATE State)
{
    if (m_pcScene != nullptr)
    {
        m_pcScene->Release();           // ¾À ÇØÁ¦
        delete m_pcScene;
        m_pcScene = nullptr;
    }
    
    switch (State)
    {
        case GAMEINTRO:
        {
            m_pcScene = new GameIntro;
            m_NowScene = GAMEINTRO;
            break;
        }
        case INGAME:
        {
            m_pcScene = new InGame;
            m_NowScene = INGAME;
            break;
        }
        case WINFIRE:
        {
            m_pcScene = new WinFire;
            m_NowScene = WINFIRE;
            break;
        }   
        case WINICE:
        {
            m_pcScene = new WinIce;
            m_NowScene = WINICE;
            break;
        }
        case ENDINGCREDIT:
        {
            m_pcScene = new EndingCredit;
            m_NowScene = ENDINGCREDIT;
            break;
        }
    }

    m_pcScene->Init();           // ¾À ÃÊ±âÈ­
    m_bSceneChage = false;

    SoundManager::GetInstance()->PlayBackGround();
    
}

void CSceneManager::Update(void)
{
    m_dtime = m_timer->GetElaspedTimeSec();

    ynMMedia_Update(m_dtime);

    if (m_timer->FPSCheck() == false)
    {
        return;
    }

    m_pcScene->Update(m_dtime);
}

void CSceneManager::Render(void)
{
    m_pcScene->Render();
}

