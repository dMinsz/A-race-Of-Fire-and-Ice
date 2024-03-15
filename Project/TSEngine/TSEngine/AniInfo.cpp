#include "AniInfo.h"

AniInfo::AniInfo()
	:m_FrmMax(0), m_CutSizeWidth(0), m_CutSizeHeight(0), m_AniTime(0.0f), m_AniFrm(0), m_AniFPS(0), m_AniMov(0)
{
}

void AniInfo::init(int frmMax, int CutSizeWidth, int CutSizeHeight, float AniTime , int AniFrm , int AniMov )
{
	m_FrmMax = frmMax;
	m_CutSizeWidth = CutSizeWidth;
	m_CutSizeHeight = CutSizeHeight;
	m_AniFPS = frmMax;
	m_AniTime = AniTime;
	m_AniFrm = AniFrm;
	m_AniMov = AniMov;
}