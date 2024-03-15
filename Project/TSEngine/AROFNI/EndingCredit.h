#pragma once
class EndingCredit : public CScene
{

public:
    TSprite* m_BackGround;
    TSprite* m_motion1;
    TSprite* m_motion2;
public:
    EndingCredit();
    ~EndingCredit(void);

    virtual void Init(void);
    virtual void Update(float dtime);
    virtual void Render(void);
    virtual void Release(void);
};

