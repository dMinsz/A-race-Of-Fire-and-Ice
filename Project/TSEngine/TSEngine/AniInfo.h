#pragma once
class AniInfo
{
public:
	// ��������Ʈ �ִϸ��̼� ����
	int		m_FrmMax; // ��������Ʈ���� ���� �Ƽ�

	int m_CutSizeWidth;
	int m_CutSizeHeight;

	float   m_AniTime;// ���� �ִϸ��̼� dtime
	int		m_AniFrm; // ������
	int		m_AniFPS; //���� �ִϸ��̼� ������

	//���� character move set 
	int		m_AniMov; //�����
public:
	AniInfo();

	void init(int frmMax, int CutSizeWidth, int CutSizeHeight, float AniTime = 0.0f, int AniFrm = 0, int AniMov = 0);


};

