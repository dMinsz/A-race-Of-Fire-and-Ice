/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  B3D/YENA : DX/GL 기반 하드웨어 가속 2D/3D 엔진.                         // 
//                                                                         //
//  제 작 : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Interactive. http://www.zero-g.kr		   		       //	
//  초기제작 : 2003.12 - 2004.03.                                          //
//  개발환경 : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008/2010 //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 10.1(2010, Jun)                                //
//             H/W - AMD Athlon XP(Barton) 2500+@2300                      //    
//                   ATI Radeon 9600 Pro                                   //
//                   ABit NF7-II /w SAMSUNG DDR 512MB                      //
//                   SB Live! DE 5.1                                       //
//  테스트 환경 : CPU - AMD Athlon										   //	 
//                      AMD Athlonx64 w/q4                                 // 
//                      Intel Pentium III/IV & Celeron                     //
//                            Core2 w/Quad                                 //
//                VGA - ATI Radeon 9xxx Series                             //
//                          Radeon 1xxx Series                             //
//                          Radeon HD 3/4/5/6/7/8xxx Series                //
//                      nVidia GeForce 2 MX/Ti Series.                     //  
//                             GeForce 3 Ti Series.                        //
//                             GeForce 4 MX/Ti Series.                     //
//                             GeForce FX Series.                          //
//                             GeForce 5/6/7/8/9 Series.                   //
//                             GeForce 200/300/400/500 Series.             // 
//                             GeForce SLI / 3Way-SLI					   //
//                OS - Windows 98 / 2K / XP / VISTA / win7 x32:x64         //
//                     Mac OS X, iOS 5.x (B3Yena-Beta)                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////// 
//
// ynDSound.h : 다이렉트 사운드  관련 헤더 화일.
//				 1999.6.2. Kihong Kim / mad_dog@hanmail.net 
//
// 1999.6.16. : 수정.
// 2004.04.07 : 기홍 - DX 9.0(2003, Summer) 버전으로 업데이트.
// 2004.04.08 : 주석 및 파일 명 변경
// 2020.07.10 : 신규인터페이스로 YENA 로 개정.
//
//#ifdef BSOUND_

//#ifndef _B3SOUND_H__
//#define _B3SOUND_H__
#pragma once

/*
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 */
#include "YENA_API.h"		//2005.04.07. DLL Export.

#include "dsound.h"
#pragma comment(lib, "dsound")		//2004.04.07. 기홍
//#pragma comment(lib, "DSound3D")	//2004.04.07. 기홍
#pragma comment(lib, "dxguid")		//링크에러. IID_DirectSound8
//#include <xaudio2.h>
//#pragma comment(lib,"xaudio2.lib")
//#include "dxguid.h"

 
//#include "define.h"		//WAVE 출력에 관한 정보...

//#include "cdplay.h"  //cd audio track 처리 관련 모줄.
//#include "wave.h"    //웨이브 화일 처리 관련 모줄. 1999.6.16.

#include "ynWave.h"


//2006.04.01.: B3D 로 개정.
//2020.07.10 : YENA 로 개정.
namespace YENA {



////////////////////////////////////////////////////////////////////////////
//
// DIRECT SOUND  설정
//
typedef LPDIRECTSOUND8				LPDSOUND;
typedef LPDIRECTSOUNDBUFFER			LPDSBUFFERMIX;
typedef LPDIRECTSOUNDBUFFER8		LPDSBUFFER2ND;

/*
#ifndef __DSOBJ
#define __DSOBJ
typedef struct __DSOBJ
{
	LPDIRECTSOUND8			pDSound;		//다이렉트 사운드 객체.	: ver.8 사용.
	LPDIRECTSOUNDBUFFER		pDSoundBuffer;	//다이렉트 사운드 1차 버퍼 포인터.. : ver.8 사용금지.
	LPDIRECTSOUNDBUFFER8	pDSBuffer2nd[MAX_WAVE_]; //다이렉트 사운드 2차 버퍼. : ver.8 사용.
	//DSBUFFERDESC			dsbdesc;		//버퍼 디스크립션 구조체..
	//WAVEFORMATEX			wfx;            //웨이브 화일포멧 구조체.
}DSOBJ, *LPDSOBJ;

#endif // #define __DSOBJ;
*/

//////////////////////////////////////////////////////////////////////////////
//
#ifndef YES_
#define YES_ TRUE
#define NO_  FALSE
#endif

#define PLAY_ONCE_	FALSE			//플레이 1번만 출력.
#define PLAY_LOOP_  TRUE 			//플레이 반복 출력.

extern YENA_APIX LPDSOUND		g_B3pDS;			//전역 다이렉트 사운드 인터페이스 포인터.
extern YENA_APIX LPDSBUFFERMIX	g_B3pMixBuffer;		//전역 다이렉트 사운드 1차 버퍼.
extern YENA_APIX LONG			g_B3lMasterVolume;	//마스터 볼륨. 

#define SE_VOL_MAX_  100			//최대 볼륨 (DSound 에서는 0db) 
#define SE_VOL_MIN_  0				//최소 볼륨 (DSound 에서는 -10,000db)

#define SE_PEN_MAX_	 100				//방향별 최대 패닝 값. 
#define SE_PEN_CENTER_ 0				//방향별 최소 패닝 값. 
#define SE_PEN_MIN_ -100				//방향별 최소 패닝 값. 



//////////////////////////////////////////////////////////////////////////////
// 전역 함수.
//////////////////////////////////////////////////////////////////////////////


//extern LPDIRECTSOUNDBUFFER g_B3lpDSBuffer[MAX_WAVE];  //다이렉트 사운드 버퍼.

// DSound 초기화.
// 다이렉드 사운드객체와 클래스를 생성시키고 초기화 시킨다. 실폐시 FALSE 리턴.
// 사용처: WinMain()의 다이렉트 초기화 부분.
//
YENA_API BOOL	B3Sound_Init(HWND hwnd);   

// DSound 해제.
// 다이렉트 사운드 객체와 클래스를 삭제 한다. 
// 사용처 : 프로그램 종료시 
YENA_API void	B3Sound_Release();  

/*
void B3Sound_PlayMaster();
void B3Sound_StopMaster();*/

//마스터 볼륨  관련 함수.
YENA_API LONG B3Sound_MasterGetVolume ();					//마스터 볼룸 획득.	
YENA_API BOOL B3Sound_MasterSetVolume (LONG v = 100);		//마스터 볼륨 설정. v = 볼륨, 범위는 0 ~ 100.(max)
YENA_API LONG B3Sound_MasterVolumeUp  (LONG dv = 100);		//마스터 볼륨 올림. dv = 초당 증가량
YENA_API LONG B3Sound_MasterVolumeDn  (LONG dv = 100);		//마스터 볼룸 내림. dv = 초당 감소량
 
YENA_API int   B3Sound_MasterSetFreq   (DWORD frq);			//마스터 플레이 주파수 설정.  기본 = 0, 최소 100 ~ 20,000 
YENA_API DWORD B3Sound_MasterGetFreq   ();					//마스터 플레이 현재 주파수 획득.



//extern DSOBJ*	g_B3pDSObj;
//extern ynSoundEffect*	g_B3pSE;








////////////////////////////////////////////////////////////////////////////// 
//
// class ynSoundEffect
//
////////////////////////////////////////////////////////////////////////////// 
//
// 웨이브 화일 운용 클래스
// ynWave 클래스를 상속, DSound 사용.
//
class YENA_APIX ynSoundEffect : public ynWave
{
protected:
	LPDSOUND		m_pDS;					//다이렉트 사운드 객체 포인터.(외부지정)
	LPDSBUFFERMIX	m_pMixBuffer;			//1차 버퍼 포인터 (외부지정)

	LPDSBUFFER2ND	m_p2ndBuffer;			//2차 버퍼 포인터 (내부생성)
	DWORD			m_Position;				//연재 연주중인 곳의 위치 : Pause 에서 사용.

	TCHAR*			m_pWaveFileName;		//로드된 웨이브 파일명 (복구시 사용)

	HRESULT			m_Volume;				//연주 볼륨.

	LONG			m_lPanPosition;			//'Panning Position' 값.
											//-100(왼쪽) ~ +100(오른쪽), 중앙은 0.

	DWORD  m_Freq = 0;		//현재 주파수.

public:

	//생성 & 소멸자
	//생성자 : 멤버 초기화, 웨이브 파일 로드 및 2차 버퍼 생성을 담당.
	ynSoundEffect(LPDSOUND pDS = g_B3pDS,					 
				 LPDSBUFFERMIX pMixBuffer=g_B3pMixBuffer	 
				);

 	ynSoundEffect(TCHAR* wavefilename,					 
				 LPDSOUND pDS = g_B3pDS,					 
				 LPDSBUFFERMIX pMixBuffer=g_B3pMixBuffer	 
				);

	//소멸자 : 2차 버퍼 제거.
	virtual ~ynSoundEffect();							

 		 
	// 웨이브 화일 로드.
	// wavename : 웨이브파일 (*.wav) 명.
	// 성공시 true, 실패시 false 리턴.
	//
	BOOL  Load (TCHAR* wavename);			

	//사운드 파일을 연주한다.
	// bLoop = 반복여부, 
	// bRewind =되감기여부. TRUE(YES_) 이면, 함수 호출시 무조건 처음부터 플레이.  
	// 리턴값 : 사운드 플레이 (버퍼) 상태. 소스 하단의 [주석1] 를 참조할것.
	//
 	DWORD Play (BOOL bLoop=PLAY_ONCE_, BOOL bRewind=NO_);	

	//연주 중지.
	void  Stop ();							
	//void Pause();

	BOOL SetVolume(LONG dwVol);				//볼륨 조절
	LONG GetVolume();						//현재 볼륨 얻기.

	LONG VolumeUp(LONG lVol);				//lVol 만큼 볼륨을 올린다.
	LONG VolumeDn(LONG lVol);				//lVol 만큼 볼륨을 내린다.

	BOOL SetPan(LONG lVal);					//val 만큼 패닝한다. lVol 의 유요범위는 -100 ~ +100. 
	LONG GetPan();							//val 만큼 패닝한다. lVol 의 유요범위는 -100 ~ +100. 
	LONG SetPan2Left(LONG val);				//val 만큼 왼쪽으로 패닝한다.  val의 유효범위는 0~100. 
	LONG SetPan2Right(LONG val);			//val 만큼 오른쪽으로 패닝한다.val의 유효범위는 0~100.
	
	DWORD SetFreq (DWORD frq);
	DWORD GetFreq ();


	void Release();							// 2차 버퍼 해제.

protected:

	// 2차 버퍼 생성. 업그레이드 필요함.
	BOOL Create2ndBuffer(WAVEFORMATEX* pWfx, DWORD dwBuffSize);		
	 
 
}; //end of class ynSoundEffect

typedef ynSoundEffect* LPSOUNDEFFECT;
typedef ynSoundEffect* LPYNSNDFX;
typedef ynSoundEffect* LPSNDFX;




} //end of namespace YENA;


//#endif //#define _SE_H__

/*
//[주석1] ynSoundEffect::Play 함수 호출시 리턴값들. 다음의 상태가 리턴됨. : dsound.h 
#define DSBSTATUS_PLAYING           0x00000001
#define DSBSTATUS_BUFFERLOST        0x00000002
#define DSBSTATUS_LOOPING           0x00000004
#define DSBSTATUS_LOCHARDWARE       0x00000008
#define DSBSTATUS_LOCSOFTWARE       0x00000010
#define DSBSTATUS_TERMINATED        0x00000020
*/


//#endif //#ifdef BSOUND_


/*********************** end of file "ynDSound.h" ****************************/