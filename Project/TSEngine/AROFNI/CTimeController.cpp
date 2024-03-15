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
	/// 1. �ػ� ���� �Լ�
// 	LARGE_INTEGER _time = QueryPerformanceCounter();
// 	_time.u.LowPart;
// 	_time.u.HighPart;

	// �󵵸� ���´�.
	LARGE_INTEGER _Frequency;
	QueryPerformanceFrequency(&_Frequency);
	m_Frequency = _Frequency.QuadPart;

	/// 2.
	//GetTickCount();
	//GetTickCount64();


	/// 3.
	//timeGetTime();


	/// FPS�� �׿� ���� 1�����ӿ� �ɸ��� �ð��� �̸� ���(��)
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
/// ���ϴ� FPS�� �ش��ϴ� �ð��� �����°�?
/// </summary>
bool CTimeController::FPSCheck()
{
	// ���ݱ����� �ɸ� �ð��� ���.
	EndTimeStamp();
	CheckTime();

	if ((m_TargetElaspedTimeSec * 1000.0f) < GetElaspedTimeMS())
	{
		// ���� ���������� �� �� �ִ�.
		// �ð��� ��� �����Ѵ�.
		StartTimeStamp();

		return true;
	}

	return false;
}
