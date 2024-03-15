#pragma once
class AniInfo
{
public:
	// 스프라이트 애니메이션 정보
	int		m_FrmMax; // 스프라이트에서 읽을 컷수

	int m_CutSizeWidth;
	int m_CutSizeHeight;

	float   m_AniTime;// 현재 애니메이션 dtime
	int		m_AniFrm; // 현재컷
	int		m_AniFPS; //현재 애니메이션 프레임

	//예비 character move set 
	int		m_AniMov; //예비용
public:
	AniInfo();

	void init(int frmMax, int CutSizeWidth, int CutSizeHeight, float AniTime = 0.0f, int AniFrm = 0, int AniMov = 0);


};

