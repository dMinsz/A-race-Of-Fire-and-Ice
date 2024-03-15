#pragma once

#define SND_SPEED_DEFAULT 1.0f	   //플레이 속도 기본값=1.0 (100%)
#define SND_SPEED_MAX   4.0f       //5배 이상은 거의 들리지 않는다.
#define SND_SPEED_MIN   0.1f	   //너무 느린것도 별로. 적당하게 제한을 건다.

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

	float   m_PlaySpeed = 1.0f;		   //플레이 속도. (배율)★

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
	//ynSndPlay(g_pSE1, PLAY_ONCE_, TRUE);	//1번 연주+되감기 : Play 함수 호출시마다 '처음'부터 플레이.★
	//ynSndPlay(g_pSE2, PLAY_LOOP_, TRUE);	//무한반복+되감기
	//ynSndStop(g_pSE2); //연주 중지
	//ynSndVolumeUp(g_pSE2); //볼륨 업
	//ynSndVolumeDn(g_pSE2); //볼륨 다운
	/*

		ynSndMasterVolumeUp(100);

		ynSndMasterVolumeDn(100);

		ynSndMasterSetVolume(SE_VOL_MAX_);		//100.

		ynSndMasterSetVolume(SE_VOL_MIN_);		//0.*/
	/*
	// 사운드 : MP3 로딩.★
	// MP3 는 한번에 하나의 파일만 로딩, 플레이 가능. 
	// 보틍 BGM 으로 사용을 권장.
	ynMediaLoad( MediaFileName[CurrMedia] );	//★
	//ynMediaLoad("snd/thunder.mp3");			//★
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