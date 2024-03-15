#include "stdafx.h"
#include "CTimeController.h"


 CTimeController::CTimeController()
 {
 
 }
 
 CTimeController::~CTimeController()
 {
 
 }

void CTimeController::Initialize()
{
	/// 1. 해상도 높은 함수
// 	LARGE_INTEGER _time = QueryPerformanceCounter();
// 	_time.u.LowPart;
// 	_time.u.HighPart;

	// 빈도를 얻어온다.
	LARGE_INTEGER _Frequency;
	QueryPerformanceFrequency(&_Frequency);
	m_Frequency = _Frequency.QuadPart;

	/// 2.
	//GetTickCount();
	//GetTickCount64();


	/// 3.
	//timeGetTime();


	/// FPS와 그에 따른 1프레임에 걸리는 시간을 미리 계산(초)
	m_FPS = 60.0f;
	m_TargetElaspedTimeSec = 1.0f / m_FPS;
}

void CTimeController::StartTimeStamp()
{
	QueryPerformanceCounter(&m_StartTimeStamp);
}

void CTimeController::EndTimeStamp()
{
	QueryPerformanceCounter(&m_EndTimeStamp);
}

void CTimeController::CheckTime()
{
	m_ElaspedTime = m_EndTimeStamp.QuadPart - m_StartTimeStamp.QuadPart;
}

float CTimeController::GetElaspedTimeMS() const
{
	return (float)((float)m_ElaspedTime / (float)m_Frequency) * 1000.f;
}

float CTimeController::GetElaspedTimeSec() const
{
	return (float)((float)m_ElaspedTime / (float)m_Frequency);
}

/// <summary>
/// 원하는 FPS에 해당하는 시간이 지났는가?
/// </summary>
bool CTimeController::FPSCheck()
{
	// 지금까지의 걸린 시간을 잰다.
	EndTimeStamp();
	CheckTime();

	if ((m_TargetElaspedTimeSec * 1000.0f) < GetElaspedTimeMS())
	{
		// 다음 프레임으로 갈 수 있다.
		// 시간을 재기 시작한다.
		StartTimeStamp();

		return true;
	}

	return false;
}
