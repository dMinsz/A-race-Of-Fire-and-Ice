#pragma once
class GameIntro : public CScene
{

public:
    TSprite* m_BackGround;
    TSprite* m_PressEnter;
    TSprite* m_motion1;
    TSprite* m_motion2;

public:
    GameIntro();
    ~GameIntro(void);

    virtual void Init(void); 
    virtual void Update(float dtime);
    virtual void Render(void) ;
    virtual void Release(void);




};

