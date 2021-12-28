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
//
// ynWave.h: interface for the ynWave class.
//         
// 웨이브 화일을 로드하고, 읽고, 쓰고, 저장하고, 처리하는 클래스 
// 1999.6.15. 김기홍.
/////////////////////////////////////////////////////////////////////////////
//
// 2004.04.07 : 기홍 :  DX 9.0(2003, Summer) 버전으로 업데이트.
// 2004.04.08 : 주석 및 파일 명 변경
// 2020.07.10 : 신규인터페이스로 YENA 로 개정.
//
#pragma once

#include "Yena_API.h"		//2005.04.07. DLL Export.


namespace YENA {

/////////////////////////////////////////////////////////////////////////////
//
// class ynWave
//
/////////////////////////////////////////////////////////////////////////////
//	
// 웨이브 파일 로드 전용 클래스.
// 지원 포멧은 "Windows PCM" 의 웨이브 파일.
// 스테레오 패닝 (Panning) 또는 3D 포지셔닝 사운드 처리를 위해서는 Mono 채널이어야 한다.
//
class YENA_APIX ynWave  
{
protected:
//  2차 수정으로 멤버 변수 제거. 1999.6.16.
//	HMMIO*			m_pHmmio;			//RIFF 화일 포인터.
//	WAVEFORMATEX*	m_pWaveFormatEx;		//웨이브 화일 데이터.
//	MMCKINFO		m_ParentCkInfo;		//부모 청크 인포.
//	MMCKINFO		m_ChildCkInfo;		//자식 청크 인포.
	
public: 

	//웨이브 화일 열기.	
	BOOL OpenWaveFile(TCHAR* filename, HMMIO* pHmmio, 
						WAVEFORMATEX** ppwfxInfo, MMCKINFO* pParentckinfo);	

	//웨이브 화일을 읽기 위한 준비.
	BOOL StartWaveDataRead(HMMIO* pHmmio, MMCKINFO*  
						pChildCkInfo, MMCKINFO* pParentCkInfo);	  

	//웨이브 화일을 DirectSoundBuffer로 읽어 들인다.
	BOOL ReadWaveFile(HMMIO Hmmio, UINT BufferSize, BYTE* pBuffer, 
						MMCKINFO* pChildCkInfo, UINT* ActualRead); 
	
	//읽기용으로 연 웨이브 화일을 닫는다.
	BOOL CloseReadWaveFile(HMMIO* pHmmio, WAVEFORMATEX** pwfx);	
	//일단 여기까지.... -_-;; 1999.6.15.
	
public:
	ynWave();
	virtual ~ynWave();

};


} //end of namespace YENA;

/************************* end of file "ynWave.h" *****************************/
