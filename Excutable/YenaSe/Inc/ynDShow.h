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
// ynDShow.h : DirectShow 를 이용한 미디어 출력 (wav/mp3/asf/avi/mpeg-2)
//
//
// 2010.06.20. Rebuild / Kihong Kim / mad_dog@hanmail.net
// 2020.07.10 : 신규인터페이스로 YENA 로 개정.
//
//
#pragma once

#include "DShow.h"
#pragma comment(lib, "strmiids.lib")				//DirectShow 필수 라이브러리.
#pragma comment(lib, "quartz.lib")

//2006.04.01.: B3D 로 개정.
//2020.07.10 : YENA 로 개정.
namespace YENA
{ 

YENA_API int  B3Show_Init();						//DirectShow 초기화.
YENA_API void B3Show_Release();						//DShow 제거.


YENA_API int  B3Show_MediaLoad(TCHAR* filename);	//DShow 미디어 로딩.
YENA_API void B3Show_MediaRelease();				//DShow 미디어 제거.

YENA_API void B3Show_MediaPlay (BOOL Loop = TRUE);	//미디어 플레이(기본값 : 반복)
YENA_API void B3Show_MediaStop ();					//미디어 정지.
YENA_API void B3Show_MediaPause();					//미디어 일시정지.

YENA_API void B3Show_MediaUpdate();					//미디어 상태 갱신 : 엔진에서 매번 호출되어야 한다.

 
//YENA_API void B3Show_Help(int x, int y, COLOR col);


YENA_API void B3Show_SetVolume(int val);			//볼륨설정. ( 0 ~ 100)
YENA_API int  B3Show_GetVolume();					//볼륨얻기  ( 0 ~ 100)
YENA_API void B3Show_VolumeUp (int v=100);			//볼륨 올리기 (기본.증가1)
YENA_API void B3Show_VolumeDn (int v=100);			//볼륨 내리기 (기본 감소1)


namespace B3SHOW { 
	extern YENA_APIX BOOL 	  _bPlayLoop;			//BGM Loop Play.
	extern YENA_APIX LONGLONG _TotPlayTime;			//미디어 전체 플레이 시간(나노세컨드.초)
	extern YENA_APIX LONGLONG _CurrPlayTime;		//미디어 현제 플레이 위치(나노세컨드.초)	
	extern YENA_APIX int      _CurrVolume;			//현재 플레이 볼륨얻기.(0~100)
}//end of namespace B3DSHOW


YENA_API int	  B3Show_GetCurrVolume ();			//현재 플레이 볼륨얻기.(0~100)
YENA_API LONGLONG B3Show_GetTotPlayTime();			//미디어 전체 플레이 시간(나노세컨드.초)
YENA_API float    B3Show_GetTotPlayTimeSec ();		//미디어 전체 플레이 시간(초)
YENA_API LONGLONG B3Show_GetCurrPlayTime   ();		//미디어 현제 플레이 위치(나노세컨드.초)
YENA_API float    B3Show_GetCurrPlayTimeSec();		//미디어 현재 플레이 위치(초)	
YENA_API double   B3Show_SetRate(double rate=1.0);	//미디어 플레이 속도 설정 (1.0 = 100%) 리턴값은 설정후 현재 속도.
YENA_API double   B3Show_GetRate();					//미디어 현재 플레이 속도 (1.0 = 100%)
	


}//end of namespace YENA

using namespace YENA;

/************************* end of file "ynDShow.h" ****************************/

