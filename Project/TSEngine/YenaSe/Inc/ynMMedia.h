/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  YENA/YENA : DX/GL 기반 하드웨어 가속 2D/3D 엔진.                         // 
//                                                                         //
//  제 작 : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Interactive. http://www.zero-g.kr		   		       //	
//  초기제작 : 2003.12 - 2004.03.                                          //
//  개발환경 : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008/2010 //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 10.1(2010, Jun)                                //
//                  OpenGL 1.x / 2.x / 3.x                                 //
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
//
// ynSound.h 
//
// 2005.02.02. Update.Kihong Kim / mad_dog@hanmail.net
// 2011.02.10. Update
// 2016.12.11. Update
// 2018.03.20. Update
// 2020.08.22. Update
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#pragma warning(disable:4996)
#include "windows.h"
#include "tchar.h"
typedef TCHAR* LPTCHAR;


///////////////////////////////////////////////////////////////////////////////
//
// Yena 엔진 / 라이브러리 공통 헤더  
//
// 20.1113 Yena.h 에서 사운드 라이브러리 분리
//
///////////////////////////////////////////////////////////////////////////////
//#include "Yena.h"
#include "Yena_API.h"

//#define YENA_SOUND_EXPORTS	//사운드 라이브러리 익스포트 정의 	
#ifdef YENA_SOUND_EXPORTS
#include "DXErr.h"
//#include "ynDefine.h"			//각종 자료/클래스/구문 재정의.
//#include "YnError.h"			//에러 메세지 관리.
//#include "ynLog.h"			//로그파일
#endif


///////////////////////////////////////////////////////////////////////////////
//
// Yena 엔진 / 사운드 라이브러리 헤더  
//
///////////////////////////////////////////////////////////////////////////////
#include "ynWave.h"
#include "ynDSound.h"
#include "ynDShow.h"
 
#ifndef _in_
#define _in_		//[in] 입력
#define _out_		//[out] 출력
#define _inout_		//[inout] 입력 및 출력
#endif


//////////////////////////////////////////////////////////////////////////////
//
// 멀티디미어 인터페이스. (신형)(v.2.29)
//
//////////////////////////////////////////////////////////////////////////////

namespace YENA
{

//-----------------------------------------------
// 인터페이스 재정의.(신형) v.2.29 (20.1028)
//-----------------------------------------------
//
// 멀티미디어 시스템 초기화 : 엔진 초기에 한번 호출.
// hWnd : 윈도우 핸들.
// 리턴 : 성공하면 YN_OK, 실패면 YN_FAIL
//
YENA_APIX int ynMMedia_Initial(HWND hwnd);

// 멀티미디어 시스템 초기화 : 엔진 종료시 한번 호출.
//
YENA_APIX void ynMMedia_Release();

// 멀티미디어 시스템 갱신 : 매 프레임마다 갱신해야 함.
// dTime : 엔진 타이머, 프레임시간.
YENA_APIX int ynMMedia_Update(float dTime);






//-----------------------------------------------
// Wave 파일 처리 API
//-----------------------------------------------

//사운드 클래스 재정의.
//#define LPSOUNDEFFECT  ynSoundEffect*


// 사운드 파일 로드 
// filename : [in] 파일명, Wave 파일 지원.  스테레오 패닝 (Panning) 또는 
//                 3D 포지셔닝 사운드 처리를 위해서는 Mono 채널이어야 한다.
// ppSnd : [out] 사운드 객체 포인터.
//
// 성공시 TRUE 리턴, 실패시 FALSE 리턴.
//
YENA_APIX int ynSndLoad(_in_ TCHAR* filename, _inout_ LPSOUNDEFFECT* ppSnd);		


// 사운드 파일 로드 
// filename : [in] 파일명, Wave 파일 지원.  스테레오 패닝 (Panning) 또는 
//                 3D 포지셔닝 사운드 처리를 위해서는 Mono 채널이어야 한다.
// rSnd : [out] 사운드 객체 포인터 레퍼런스
//
// 성공시 TRUE 리턴, 실패시 FALSE 리턴.
//
YENA_APIX int ynSndLoad( _in_ TCHAR* filename, _inout_ LPSOUNDEFFECT& snd);


// 사운드 파일 제거 
// snd :  사운드 객체 포인터.
YENA_APIX void ynSndRelease(_inout_ LPSOUNDEFFECT& snd);					



// 사운드 파일 플레이
// pSnd  : 플레이할 사운드 객체 포인터.
// bLoop : '반복' 플레이 여부. 
// bRewind : 되감기여부. TRUE(YES_) 설정시, 함수 호출시 무조건 처음부터 플레이.
// 리턴값 : 플레이 상태. 실패시 YN_FAIL 리턴.
//
YENA_APIX int ynSndPlay(_in_ LPSOUNDEFFECT pSnd, _in_ BOOL bLoop = PLAY_ONCE_, _in_ BOOL bRewind = NO_ );

// 사운드 플레이 중지.
// pSnd  : 플레이할 사운드 객체 포인터.
// 리턴값 : 성공시 YN_OK, 실패시 YN_FAIL 리턴.
//
YENA_APIX int ynSndStop(LPSOUNDEFFECT pSnd);


// 사운드 플레이 볼륨 조절.
// pSnd : 플레이할 사운드 객체 포인터.
// vol  : 지정할 볼륨값. 범위는 0~100 . 이 갑은 100 단위의 데시빌(db) 값으로 보정되어 사용된다. 
// 성공시 TRUE, 실패시 FALSE  를 리턴.
//
YENA_APIX int ynSndSetVolume(LPSOUNDEFFECT snd, LONG vol);

// 사운드 플레이 볼륨 얻기.
// pSnd : 플레이할 사운드 객체 포인터.
// 리턴값 : 현재 볼륨값. 범위는 0~100.  실패시 YN_FAIL  를 리턴.
//
YENA_APIX LONG ynSndGetVolume(LPSOUNDEFFECT snd);

// 사운드 플레이 볼륨 올리기
// pSnd : 플레이할 사운드 객체 포인터.
// v  :  증가 볼륨량. 초당 변화량, 기본값 100.
// 리턴값 : 현재 볼륨값. 범위는 0~100.  실패시 YN_FAIL  를 리턴.
//
YENA_APIX LONG ynSndVolumeUp(LPSOUNDEFFECT snd, LONG v = 100);

// 사운드 플레이 볼륨 감소
// pSnd : 플레이할 사운드 객체 포인터.
// v  :  감소 볼륨량. 초당 변화량, 기본값 100.
// 리턴값 : 현재 볼륨값. 범위는 0~100.  실패시 YN_FAIL  를 리턴.
//
YENA_APIX LONG ynSndVolumeDn(LPSOUNDEFFECT snd, LONG v = 100);



// 사운드 패닝 Panning 조절
// pSnd : 플레이할 사운드 객체 포인터.
// v  :  패닝 위치. 범위는 -100 ~ 100. 내부에서 db(데시빌)로  보정되어 사용된다. <참조> 확인
// 리턴값 : 현재 패닝 위치. 실패시 YN_FAIL 리턴.
//  <참조>
//  중앙 (양쪽 최대) : 0  (0db)
//  왼쪽 최대      : -100 (-10,000db) 
//  오른쪽 최대    : +100 (+10,000db) 
//
YENA_APIX int ynSndSetPan(LPSOUNDEFFECT snd, LONG v = 0);


// 사운드 패닝 Panning 조절
// pSnd : 플레이할 사운드 객체 포인터.
// 리턴값 : 현재 패닝 위치. 실패시 YN_FAIL 리턴. <참조> 확인.
//  <참조>
//  중앙 (양쪽 최대) : 0  (0db)
//  왼쪽 최대      : -100 (-10,000db) 
//  오른쪽 최대    : +100 (+10,000db) 
//
YENA_APIX int ynSndGetPan(LPSOUNDEFFECT snd);


// 사운드 왼쪽 패닝 Panning 조절
// pSnd : 플레이할 사운드 객체 포인터.
// v  :  패닝량, 초당 변화량, 내부에서 db(데시빌)로 보정되어 사용된다. 
//       왼쪽 패닝 최대값은 -100 
// 리턴값 : 현재 패닝 위치  실패시 YN_FAIL 리턴.
//
YENA_APIX int ynSndPanLeft(LPSOUNDEFFECT snd, LONG v = 100);

// 사운드 오른쪽 패닝 Panning 조절
// pSnd : 플레이할 사운드 객체 포인터.
// v  :  패닝량, 초당 변화량, 내부에서 db(데시빌)로 보정되어 사용된다. 
//       오른쪽 패닝 최대값은 100 
// 리턴값 : 현재 패닝 위치 실패시 YN_FAIL 리턴.
//
YENA_APIX int ynSndPanRight(LPSOUNDEFFECT snd, LONG v = 100);


// 사운드 연주 속도 설정
// pSnd : 플레이할 사운드 객체 포인터.
// v    : 플레이 속도 배율.
// 리턴값 : 현재 속도 값. 실패시 YN_FAIL 리턴. <참조> 확인.
//  <참조>
// 기본 : 1 배속   (100%)
// 최대 : 4 배속   (400%) : 이 이상은 '들리지' 않는다..
// 최저 : 0.1 배속 (10%)  : 너무 느린것도 별로.. 적당하게 제한을 건다.
//
//
YENA_APIX float ynSndSetSpeed(LPSOUNDEFFECT snd, float v = 1.0f);

// 사운드 연주 속도 설정 (Hz)
// pSnd : 플레이할 사운드 객체 포인터.
// f    : 플레이 속도 
// 리턴값 : 현재 속도 값. 실패시 YN_FAIL 리턴. <ynSndSetSpeed> 확인.
//
YENA_APIX DWORD ynSndSetFreq(LPSOUNDEFFECT snd, DWORD f = 0);


// 사운드 연주 속도 획득
// 리턴값 : 현재 속도 (배율) 실패시 YN_FAIL 리턴. <참조> 확인.
//
YENA_APIX float ynSndGetSpeed(LPSOUNDEFFECT snd);


// 사운드 연주 속도 획득
// 리턴값 : 현재 속도 값. 실패시 YN_FAIL 리턴. <참조> 확인.
//
YENA_APIX DWORD ynSndGetFreq( LPSOUNDEFFECT snd);

// 사운드 연주속도 리셋.
// ynSndSetSpeed 와 동일.
#define ynSndSpeedReset(s)   ynSndSetSpeed((s), 1);


//구형 호환 매크로
//#define  ynSndPlay(se)			se->Play()						
//#define  ynSndPlayLoop(se)		se->Play(PLAY_LOOP_, NO_)
//#define  ynSndStop(se)			se->Stop();

// 사운드 볼륨 조절. 
//#define  ynSndSetVolume(se, v)  se->SetVolume(v)
//#define  ynSndGetVolume(se)     se->GetVolume()
//#define  ynSndVolumeUp(se, v)   se->VolumeUp(v)
//#define  ynSndVolumeDn(se, v)   se->VolumeDn(v)

// 사운드 패닝
//#define  ynSndSetPan(se, v)     se->SetPan(v)
//#define  ynSndGetPan(se, v)     se->GetPan(v)
//#define  ynSndPanLeft(se, v)    se->SetPan2Left(v)
//#define  ynSndPanRight(se, v)   se->SetPan2Right(v)




//-----------------------------------------------
// 구형 호환성 재정의. (v.1.5.7) 이전.
//-----------------------------------------------
// (v.2.30) 개정. 사운드엔진 초기화/운용은  Yena 에서 자동처리중. 
//                사용자가 직접 사용할 필요는 없음.
#define ynSound_Initial		ynMMedia_Initial		// 멀티미디어 시스템 초기화 : 엔진 초기에 한번 호출. ynMMedia_Initial 사용권장.
#define ynSound_Release		ynMMedia_Release		// 멀티미디어 시스템 초기화 : 엔진 종료시 한번 호출. ynMMedia_Release 사용권장.
#define ynSound_Update		ynMMedia_Update			// 멀티미디어 시스템 갱신 : 매 프레임마다 갱신해야 함. ynMMedia_Update 사용권장.

//인터페이스 재정의.(신형)
//#define ynSound_Initial   B3Sound_Init
//#define ynSound_Release   B3Sound_Release
//#define ynSound_Update	B3Sound_Update



// Wave 마스터 볼륨 조절
#define ynSndMasterVolumeUp		B3Sound_MasterVolumeUp	//마스터 볼륨 올림. dv = 초당 증가량
#define ynSndMasterVolumeDn		B3Sound_MasterVolumeDn	//마스터 볼륨 내림. dv = 초당 감소량
#define ynSndMasterSetVolume	B3Sound_MasterSetVolume	//마스터 볼룸 설정. v = 볼륨, 범위는 0 ~ 100.(max)
#define ynSndMasterGetVolume	B3Sound_MasterGetVolume	//마스터 볼룸 획득.
#define ynSndMasterSetFreq      B3Sound_MasterSetFreq	//마스터 플레이 주파수 설정.  기본 = 0, 최소 100 ~ 20,000 
#define ynSndMasterGetFreq      B3Sound_MasterGetFreq	//마스터 플레이 현재 주파수 획득.


// Mp3 처리 API
#define ynMediaLoad				B3Show_MediaLoad		//미디어 파일 로드..
#define ynMediaRelease			B3Show_MediaRelease		//미디어 파일 제거.
#define ynMediaPlay				B3Show_MediaPlay		//미디어 플레이..
#define ynMediaPause			B3Show_MediaPause		//미디어 플레이 일시정지.
#define ynMediaStop				B3Show_MediaStop		//미디어 플레이 정지.
#define ynMediaVolumeUp			B3Show_VolumeUp			//볼륨 올림.
#define ynMediaVolumeDn			B3Show_VolumeDn			//볼륨 내림.
#define ynMediaSetVolume		B3Show_SetVolume		//볼륨 설정.
#define ynGetCurrVolume			B3Show_GetCurrVolume	//현재 볼륨 얻기.

// 미디어 파일(mp3) 플레이 정보 획득.
#define ynMediaGetTotPlayTime			B3Show_GetTotPlayTime			//전체 플레이 시간 (길이) 얻기.
#define ynMediaGetTotPlayTimeSec		B3Show_GetTotPlayTimeSec
#define ynMediaGetCurrPlayTime			B3Show_GetCurrPlayTime			//현재 플레이 시간 (길이) 얻기.
#define ynMediaGetCurrPlayTimeSec		B3Show_GetCurrPlayTimeSec
#define ynMediaSetRate                  B3Show_SetRate					//미디어 플레이 속도 설정 (1.0 = 100%) 리턴값은 설정후 현재 속도. 
#define ynMediaGetRate                  B3Show_GetRate					//미디어 현재 플레이 속도 (1.0 = 100%)


//미디어 시간정보 구조체.
struct MMEDIAINFO
{
	LONGLONG totTime;		//전체 연주시간.
	LONGLONG curTime;		//현재 연주시간

	DWORD  totMin, totSec, totCSec;		//전체 연주시간 (시:분:초:백분초)
	DWORD  curMin, curSec, curCSec;		//현재 연주시간 (시:분:초:백분초)

	float   prog;		//플레이 비율.(%)

	double  rate;		//현재 주파수.

	LONG event;
	LONG_PTR eventParam1, eventParam2;
	long timeOut;
};
typedef MMEDIAINFO* LPMMEDIAINFO;
typedef MMEDIAINFO  ynMMediaInfo;


// 현재 플레이 중인 미디어 정보 획득.
// pSnd : [in] 정보를 획득할 사운드 객체 포인터.
// pInfo  : [out] 정보를 저장할 구조체 포인터.
//
YENA_APIX int ynMediaInfo( _out_ LPMMEDIAINFO pInfo);
//YENA_APIX DWORD ynMediaGetInfo( _in_ LPSOUNDEFFECT snd, _out_ LPMMEDIAINFO pInfo);






}//end of YENA.

using namespace YENA;






////////////////////////////////////////////////////////////////////////////// 
//
// 사운드 라이브러리 전용 정의와 선언  : 20.1112
//
////////////////////////////////////////////////////////////////////////////// 
#define YENA_SE 1
#ifndef YENA_EXPORTS			
#define YENA_SOUND_EXPORTS		//Yens SE & 일반 App 타겟 재정의
#endif
#ifdef YENA_SOUND_EXPORTS 
namespace YENA {


//
// 디버깅 관련 재정의.
//
//YENA_APIX void ynLogMsg(BOOL bMBox, TCHAR* msg, ...);
YENA_APIX int ynErrorW(BOOL bMBox, TCHAR* msg, ...);

//이름 호환성 유지.
#define ynLogMsg  ynErrorW
#define B3D_Error ynErrorW			//일반+로그+콘솔 출력버전.
//#define B3D_Error(bMBox, msg, ...)  ynErrorW( bMBox, msg, __VA_ARGS__ )		//일반+로그+콘솔 출력버전.

//#ifndef YN_OK
//#define YN_OK		0x00000000					//특별한 '문제' 없음. 1 이상은 에러코드로 판정.
//#define YN_OK		0x00000001					//특별한 '문제' 없음. 1 이상은 에러코드로 판정.
//#define YN_ERROR	-1
#define YN_ERROR	YN_FAIL
//#define YN_FAIL		YN_ERROR
#define YNFAILED(a)  ( (a) != YN_OK )		//에러, 실패..
#define YNOK(a)      ( (a) == YN_OK )		//에럴 없음.성공!
//#endif

#include "assert.h"
#define ASSERT assert
 


//
// 기타 시스템 관련 함수 및 재정의 : ynDefine.h 재정의.
//
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(pBuff) if((pBuff)){ (pBuff)->Release(); (pBuff) = NULL; }
#define SAFE_DELETE(pBuff)	if((pBuff)){ delete (pBuff);     (pBuff) = NULL; }
#define SAFE_DELARRY(pBuff) if((pBuff)){ delete [] (pBuff);  (pBuff) = NULL; }
#define SAFE_FREE(pBuff)    if((pBuff)){ free(pBuff);        (pBuff) = NULL; }
#endif

#ifndef IsKeyDn
#define IsKeyDn(key)	((GetAsyncKeyState(key)&0x8000) == 0x8000)
#define IsKeyUp(key)	((GetAsyncKeyState(key)&0x8001) == 0x8001)
#endif 

#ifndef YES_
#define YES_ TRUE
#define NO_  FALSE
#endif

#ifndef YN_OK
#define YN_OK	   0					//에러 없음. 특별한 문제 없음.
#define YN_FAIL   -1					//에러 발생.
#define YN_FAILED(v)   ((v) != YN_OK)	//에러 체크 매크로.
#endif
 

// 색상 * 스칼라 곱  (ex)  col = col * 0.5f
//COLOR  operator * (COLOR  & lhs, float s);
//COLORA operator * (COLORA & lhs, float s);



/*//마우스 입력 상태. --> DInput 사용.
#define MS_STANDBY   0x0000		//대기중.
#define MS_LBTNDOWN  0x0100		//버튼 눌림.
#define MS_LBTNUP	 0x8100		//버튼 눌린후 떨어짐.
#define MS_RBTNDOWN  0x0001		//버튼 눌림.
#define MS_RBTNUP	 0x0081		//버튼 눌린후 떨어짐.
*/

//디버깅 정보 재정의.
#define _DEBUG_LV1_  
//#define _DEBUG_LV2_  
//#define _DEBUG_LV3_  






//  ynTextDrawSV   : 지정된 화면좌표에 연속적으로 문자열을 출력합니다. (사용자 폰트)
//                   
// 파라미터 :  pFont = 사용자 폰트 객체 포인터.
//            x,y = 화면좌표.   
//            col = 출력색상  
//            msg = 출력할 문자열 
//            dTime = 출력 속도 처리용 프레임시간 . 밀리세컨드 단위 실수환산. 1.0 = 1000 ms = 1 sec  
//					
// 글자를 일정속도로 연속적으로 출력합니다.  
// 가로 80글자 이상, 또는 개행문자(CR_LF) 를 만나는 경우 다음 줄로 자동으로 내려갑니다.   
// 가로 80 글자 세로 40줄 까지 표현할 수 있습니다.
// 출력 최대 문자수는 4096. 문자수를 넘기면 overflow 에러 발생. 
// 사용자 폰트의  문자크기에 맞게 줄간격 LineSpace 를 설정해야 합니다.
// LineSpace 는 폰트생성시 조절할 수 있습니다. ynFontCreate 참조
//
YENA_APIX void ynTextDrawSV(HDC hdc, int x, int y, COLORREF col, TCHAR* msg, float dTime);







}//end of YENA.

#endif //end of YENA_SOUND_EXPORTS





/********************* end of file "ynSound.h" **************************/