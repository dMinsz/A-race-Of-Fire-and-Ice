#pragma once
/// <summary>
/// �ð� ���� Ŭ����
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


	float m_FPS;					// ���ϴ� FPS (��: 60)
	float m_TargetElaspedTimeSec;	// �׷��� �����ؾ� �ϴ� �ð� (��: 16.7ms)





	/// 1. FPS����?

	/// 2. Ư�� ������ �ɸ� �ð��� �� ���� �ʹ�.

};

