#pragma once


enum SCENESTATE // 씬상태를 표시할 enum
{
    GAMEINTRO,
    INGAME,
    WINFIRE,
    WINICE,
    ENDINGCREDIT
};


class CSceneManager
{
private:
    CSceneManager(void);
    static  CSceneManager* m_Instance; //싱글톤
    
    CScene* m_pcScene;
    SCENESTATE m_RsvScene;     // 변경될 씬 예약
    SCENESTATE m_NowScene;     // 현재 씬
    bool m_bSceneChage; // 씬이 변경될것인가 유무
    bool m_bGameEnd;


public:
    ~CSceneManager(void);
    static  CSceneManager* GetInstance(void);


    CTimeController* m_timer;
    float m_dtime;


    void FreeInststance(void);
    
    void Init();
    void SceneChange(SCENESTATE State);
    void Update(void);
    void Render(void);


    inline void ReservationChange(SCENESTATE State) // 씬 변경 예약함수
    {
        m_RsvScene = State;
        m_bSceneChage = true;
    }
    inline SCENESTATE GetRsvScene(void)  // 예약된 씬을 얻어옴
    {
        return m_RsvScene;
    }
    inline bool GetbSceneChange(void)   // 예약유무를 얻어옴
    {
        return m_bSceneChage;
    }
    inline void SetGameEnd(bool bEnd)    // 게임이 종료될 것인가?
    {
        m_bGameEnd = bEnd;
    }
    inline bool GetGameEnd(void)  // 게임이 종료되었는가?
    {
        return m_bGameEnd;
    }
    inline  SCENESTATE GetNowScene(void) // 현재 씬을 반환
    {
        return m_NowScene;
    }


};

