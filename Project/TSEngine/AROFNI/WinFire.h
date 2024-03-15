#pragma once
class WinFire : public CScene
{

public:

    TSprite* m_BackGround;
    TSprite* m_motion;
public:
    WinFire();
    ~WinFire(void);

    virtual void Init(void);
    virtual void Update(float dtime);
    virtual void Render(void);
    virtual void Release(void);
};

