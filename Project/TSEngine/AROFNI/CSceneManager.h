#pragma once


enum SCENESTATE // �����¸� ǥ���� enum
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
    static  CSceneManager* m_Instance; //�̱���
    
    CScene* m_pcScene;
    SCENESTATE m_RsvScene;     // ����� �� ����
    SCENESTATE m_NowScene;     // ���� ��
    bool m_bSceneChage; // ���� ����ɰ��ΰ� ����
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


    inline void ReservationChange(SCENESTATE State) // �� ���� �����Լ�
    {
        m_RsvScene = State;
        m_bSceneChage = true;
    }
    inline SCENESTATE GetRsvScene(void)  // ����� ���� ����
    {
        return m_RsvScene;
    }
    inline bool GetbSceneChange(void)   // ���������� ����
    {
        return m_bSceneChage;
    }
    inline void SetGameEnd(bool bEnd)    // ������ ����� ���ΰ�?
    {
        m_bGameEnd = bEnd;
    }
    inline bool GetGameEnd(void)  // ������ ����Ǿ��°�?
    {
        return m_bGameEnd;
    }
    inline  SCENESTATE GetNowScene(void) // ���� ���� ��ȯ
    {
        return m_NowScene;
    }


};

