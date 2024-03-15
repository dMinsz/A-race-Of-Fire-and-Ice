#pragma once
class CScene
{

public:
    CScene(void);
    virtual ~CScene(void); 

    virtual void Init(void) = 0;
    virtual void Update(float dtime) = 0;
    virtual void Render(void) = 0;
    virtual void Release(void) = 0;
};

