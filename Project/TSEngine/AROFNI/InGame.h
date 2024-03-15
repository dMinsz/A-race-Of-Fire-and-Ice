#pragma once
class InGame : public CScene
{
protected:
    TSprite* m_BackGround;

    //플레이어 1,2
    std::vector<TSprite*> m_Lodead_Player1_Sprites;
    std::vector<TSprite*> m_Lodead_Player2_Sprites;

    TSprite* m_Player1Arr[6];
    TSprite* m_Player2Arr[6];
    Player* m_Player1;
    Player2* m_Player2;
    TSprite* m_SprPlayer1Gage;
    TSprite* m_SprPlayer2Gage;

    //맵
    //맵 패턴
    ItemPatern* EASYPattern;
    ItemPatern* NORMALPattern;
    ItemPatern* HARD00Pattern;
    ItemPatern* HARD01Pattern;
    ItemPatern* HARD02Pattern;
    ItemPatern* HARD03Pattern;
    ItemPatern* HARD04Pattern;
    ItemPatern* HELLPattern;

    GameManager* m_MapManager;

    //vs ui
    //TSprite* m_UIvs;
    
    
    
    TSprite* m_UIBackVs; //맨뒤
    TSprite* m_UIFireBar;
   // TSprite* m_UIFireHP;
    TSprite* m_UIIceBar;
    //TSprite* m_UIIceHP;


    //scroll 속도 업 타이밍용
    float m_timeing;

public:
    InGame();
    ~InGame(void);

    virtual void Init(void);
    virtual void Update(float dtime);
    virtual void Render(void);
    virtual void Release(void);


protected:
    void LoadSpritesPlayer1();
    void MakePlayer1();

    void LoadSpritesPlayer2();
    void MakePlayer2();

    void GeneratePattern();
    void MakeMap();

    void LoadSpritesVSUi();


};


