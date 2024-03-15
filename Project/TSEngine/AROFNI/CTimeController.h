#pragma once
/// <summary>
/// 시간 관련 클래스
///
/// 2020.11.13
/// </summary>
class CTimeController
{
public:
	CTimeController();
	~CTimeController();



public:
	void Initialize();

	void StartTimeStamp();
	void EndTimeStamp();

	void CheckTime();
	float GetElaspedTimeMS() const;
	float GetElaspedTimeSec() const;


	bool FPSCheck();

private:
	__int64 m_Frequency;

	LARGE_INTEGER m_StartTimeStamp;
	LARGE_INTEGER m_EndTimeStamp;


	__int64 m_ElaspedTime;


	float m_FPS;					// 원하는 FPS (예: 60)
	float m_TargetElaspedTimeSec;	// 그래서 도달해야 하는 시간 (예: 16.7ms)





	/// 1. FPS제어?

	/// 2. 특정 구간의 걸린 시간을 재 보고 싶다.

};

