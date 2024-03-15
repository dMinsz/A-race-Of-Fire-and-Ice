#pragma once

#define SND_SPEED_DEFAULT 1.0f	   //�÷��� �ӵ� �⺻��=1.0 (100%)
#define SND_SPEED_MAX   4.0f       //5�� �̻��� ���� �鸮�� �ʴ´�.
#define SND_SPEED_MIN   0.1f	   //�ʹ� �����͵� ����. �����ϰ� ������ �Ǵ�.

#define MEDIA_MAX 8

#define SOUND_PATH "../Resource/Sounds/"

enum class BGMList
{
	TITLE, INGAME,WINFIRE, BGM_END
};

enum class SoundList
{
	FIREEAT,FIREMISS,ICEEAT,ICEMISS, SOUND_END
};

class SoundManager
{
	static SoundManager* m_Instance;

	LPSOUNDEFFECT m_BGM[(int)BGMList::BGM_END];
	LPSOUNDEFFECT m_Sounds[(int)SoundList::SOUND_END];

	float   m_PlaySpeed = 1.0f;		   //�÷��� �ӵ�. (����)��

	TCHAR* BGMFileName[(int)BGMList::BGM_END] =
	{
		"ROFI_main.wav",
		"ROFI_ingame.wav",
		"ROFI_ingame.wav"
		
	};

	TCHAR* MediaFileName[(int)SoundList::SOUND_END] =
	{	
		"fire_eat.wav",
		"fire_miss.wav",
		"ice_eat.wav",
		"ice_miss.wav"
	};
	int    m_CurrMedia = 0;
	double m_CurrMediaPlayRate = 1.0f;
	//ynSndPlay(g_pSE1, PLAY_ONCE_, TRUE);	//1�� ����+�ǰ��� : Play �Լ� ȣ��ø��� 'ó��'���� �÷���.��
	//ynSndPlay(g_pSE2, PLAY_LOOP_, TRUE);	//���ѹݺ�+�ǰ���
	//ynSndStop(g_pSE2); //���� ����
	//ynSndVolumeUp(g_pSE2); //���� ��
	//ynSndVolumeDn(g_pSE2); //���� �ٿ�
	/*

		ynSndMasterVolumeUp(100);

		ynSndMasterVolumeDn(100);

		ynSndMasterSetVolume(SE_VOL_MAX_);		//100.

		ynSndMasterSetVolume(SE_VOL_MIN_);		//0.*/
	/*
	// ���� : MP3 �ε�.��
	// MP3 �� �ѹ��� �ϳ��� ���ϸ� �ε�, �÷��� ����. 
	// ���v BGM ���� ����� ����.
	ynMediaLoad( MediaFileName[CurrMedia] );	//��
	//ynMediaLoad("snd/thunder.mp3");			//��
	//ynMediaLoad("snd/GT2s.mp3");
	ynMediaPlay();*/

public:
	static SoundManager* GetInstance();

	void LoadData();
	void ReleaseData();

	void PlayBackGround();
	void PlayOnce(SoundList list);



	LPSOUNDEFFECT GetBGMList(int BGMList) { 
		return m_BGM[BGMList];
	};
};