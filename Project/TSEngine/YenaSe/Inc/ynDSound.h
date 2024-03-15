/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  B3D/YENA : DX/GL ��� �ϵ���� ���� 2D/3D ����.                         // 
//                                                                         //
//  �� �� : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Interactive. http://www.zero-g.kr		   		       //	
//  �ʱ����� : 2003.12 - 2004.03.                                          //
//  ����ȯ�� : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008/2010 //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 10.1(2010, Jun)                                //
//             H/W - AMD Athlon XP(Barton) 2500+@2300                      //    
//                   ATI Radeon 9600 Pro                                   //
//                   ABit NF7-II /w SAMSUNG DDR 512MB                      //
//                   SB Live! DE 5.1                                       //
//  �׽�Ʈ ȯ�� : CPU - AMD Athlon										   //	 
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
// ynDSound.h : ���̷�Ʈ ����  ���� ��� ȭ��.
//				 1999.6.2. Kihong Kim / mad_dog@hanmail.net 
//
// 1999.6.16. : ����.
// 2004.04.07 : ��ȫ - DX 9.0(2003, Summer) �������� ������Ʈ.
// 2004.04.08 : �ּ� �� ���� �� ����
// 2020.07.10 : �ű��������̽��� YENA �� ����.
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
#pragma comment(lib, "dsound")		//2004.04.07. ��ȫ
//#pragma comment(lib, "DSound3D")	//2004.04.07. ��ȫ
#pragma comment(lib, "dxguid")		//��ũ����. IID_DirectSound8
//#include <xaudio2.h>
//#pragma comment(lib,"xaudio2.lib")
//#include "dxguid.h"

 
//#include "define.h"		//WAVE ��¿� ���� ����...

//#include "cdplay.h"  //cd audio track ó�� ���� ����.
//#include "wave.h"    //���̺� ȭ�� ó�� ���� ����. 1999.6.16.

#include "ynWave.h"


//2006.04.01.: B3D �� ����.
//2020.07.10 : YENA �� ����.
namespace YENA {



////////////////////////////////////////////////////////////////////////////
//
// DIRECT SOUND  ����
//
typedef LPDIRECTSOUND8				LPDSOUND;
typedef LPDIRECTSOUNDBUFFER			LPDSBUFFERMIX;
typedef LPDIRECTSOUNDBUFFER8		LPDSBUFFER2ND;

/*
#ifndef __DSOBJ
#define __DSOBJ
typedef struct __DSOBJ
{
	LPDIRECTSOUND8			pDSound;		//���̷�Ʈ ���� ��ü.	: ver.8 ���.
	LPDIRECTSOUNDBUFFER		pDSoundBuffer;	//���̷�Ʈ ���� 1�� ���� ������.. : ver.8 ������.
	LPDIRECTSOUNDBUFFER8	pDSBuffer2nd[MAX_WAVE_]; //���̷�Ʈ ���� 2�� ����. : ver.8 ���.
	//DSBUFFERDESC			dsbdesc;		//���� ��ũ���� ����ü..
	//WAVEFORMATEX			wfx;            //���̺� ȭ������ ����ü.
}DSOBJ, *LPDSOBJ;

#endif // #define __DSOBJ;
*/

//////////////////////////////////////////////////////////////////////////////
//
#ifndef YES_
#define YES_ TRUE
#define NO_  FALSE
#endif

#define PLAY_ONCE_	FALSE			//�÷��� 1���� ���.
#define PLAY_LOOP_  TRUE 			//�÷��� �ݺ� ���.

extern YENA_APIX LPDSOUND		g_B3pDS;			//���� ���̷�Ʈ ���� �������̽� ������.
extern YENA_APIX LPDSBUFFERMIX	g_B3pMixBuffer;		//���� ���̷�Ʈ ���� 1�� ����.
extern YENA_APIX LONG			g_B3lMasterVolume;	//������ ����. 

#define SE_VOL_MAX_  100			//�ִ� ���� (DSound ������ 0db) 
#define SE_VOL_MIN_  0				//�ּ� ���� (DSound ������ -10,000db)

#define SE_PEN_MAX_	 100				//���⺰ �ִ� �д� ��. 
#define SE_PEN_CENTER_ 0				//���⺰ �ּ� �д� ��. 
#define SE_PEN_MIN_ -100				//���⺰ �ּ� �д� ��. 



//////////////////////////////////////////////////////////////////////////////
// ���� �Լ�.
//////////////////////////////////////////////////////////////////////////////


//extern LPDIRECTSOUNDBUFFER g_B3lpDSBuffer[MAX_WAVE];  //���̷�Ʈ ���� ����.

// DSound �ʱ�ȭ.
// ���̷��� ���尴ü�� Ŭ������ ������Ű�� �ʱ�ȭ ��Ų��. ����� FALSE ����.
// ���ó: WinMain()�� ���̷�Ʈ �ʱ�ȭ �κ�.
//
YENA_API BOOL	B3Sound_Init(HWND hwnd);   

// DSound ����.
// ���̷�Ʈ ���� ��ü�� Ŭ������ ���� �Ѵ�. 
// ���ó : ���α׷� ����� 
YENA_API void	B3Sound_Release();  

/*
void B3Sound_PlayMaster();
void B3Sound_StopMaster();*/

//������ ����  ���� �Լ�.
YENA_API LONG B3Sound_MasterGetVolume ();					//������ ���� ȹ��.	
YENA_API BOOL B3Sound_MasterSetVolume (LONG v = 100);		//������ ���� ����. v = ����, ������ 0 ~ 100.(max)
YENA_API LONG B3Sound_MasterVolumeUp  (LONG dv = 100);		//������ ���� �ø�. dv = �ʴ� ������
YENA_API LONG B3Sound_MasterVolumeDn  (LONG dv = 100);		//������ ���� ����. dv = �ʴ� ���ҷ�
 
YENA_API int   B3Sound_MasterSetFreq   (DWORD frq);			//������ �÷��� ���ļ� ����.  �⺻ = 0, �ּ� 100 ~ 20,000 
YENA_API DWORD B3Sound_MasterGetFreq   ();					//������ �÷��� ���� ���ļ� ȹ��.



//extern DSOBJ*	g_B3pDSObj;
//extern ynSoundEffect*	g_B3pSE;








////////////////////////////////////////////////////////////////////////////// 
//
// class ynSoundEffect
//
////////////////////////////////////////////////////////////////////////////// 
//
// ���̺� ȭ�� ��� Ŭ����
// ynWave Ŭ������ ���, DSound ���.
//
class YENA_APIX ynSoundEffect : public ynWave
{
protected:
	LPDSOUND		m_pDS;					//���̷�Ʈ ���� ��ü ������.(�ܺ�����)
	LPDSBUFFERMIX	m_pMixBuffer;			//1�� ���� ������ (�ܺ�����)

	LPDSBUFFER2ND	m_p2ndBuffer;			//2�� ���� ������ (���λ���)
	DWORD			m_Position;				//���� �������� ���� ��ġ : Pause ���� ���.

	TCHAR*			m_pWaveFileName;		//�ε�� ���̺� ���ϸ� (������ ���)

	HRESULT			m_Volume;				//���� ����.

	LONG			m_lPanPosition;			//'Panning Position' ��.
											//-100(����) ~ +100(������), �߾��� 0.

	DWORD  m_Freq = 0;		//���� ���ļ�.

public:

	//���� & �Ҹ���
	//������ : ��� �ʱ�ȭ, ���̺� ���� �ε� �� 2�� ���� ������ ���.
	ynSoundEffect(LPDSOUND pDS = g_B3pDS,					 
				 LPDSBUFFERMIX pMixBuffer=g_B3pMixBuffer	 
				);

 	ynSoundEffect(TCHAR* wavefilename,					 
				 LPDSOUND pDS = g_B3pDS,					 
				 LPDSBUFFERMIX pMixBuffer=g_B3pMixBuffer	 
				);

	//�Ҹ��� : 2�� ���� ����.
	virtual ~ynSoundEffect();							

 		 
	// ���̺� ȭ�� �ε�.
	// wavename : ���̺����� (*.wav) ��.
	// ������ true, ���н� false ����.
	//
	BOOL  Load (TCHAR* wavename);			

	//���� ������ �����Ѵ�.
	// bLoop = �ݺ�����, 
	// bRewind =�ǰ��⿩��. TRUE(YES_) �̸�, �Լ� ȣ��� ������ ó������ �÷���.  
	// ���ϰ� : ���� �÷��� (����) ����. �ҽ� �ϴ��� [�ּ�1] �� �����Ұ�.
	//
 	DWORD Play (BOOL bLoop=PLAY_ONCE_, BOOL bRewind=NO_);	

	//���� ����.
	void  Stop ();							
	//void Pause();

	BOOL SetVolume(LONG dwVol);				//���� ����
	LONG GetVolume();						//���� ���� ���.

	LONG VolumeUp(LONG lVol);				//lVol ��ŭ ������ �ø���.
	LONG VolumeDn(LONG lVol);				//lVol ��ŭ ������ ������.

	BOOL SetPan(LONG lVal);					//val ��ŭ �д��Ѵ�. lVol �� ��������� -100 ~ +100. 
	LONG GetPan();							//val ��ŭ �д��Ѵ�. lVol �� ��������� -100 ~ +100. 
	LONG SetPan2Left(LONG val);				//val ��ŭ �������� �д��Ѵ�.  val�� ��ȿ������ 0~100. 
	LONG SetPan2Right(LONG val);			//val ��ŭ ���������� �д��Ѵ�.val�� ��ȿ������ 0~100.
	
	DWORD SetFreq (DWORD frq);
	DWORD GetFreq ();


	void Release();							// 2�� ���� ����.

protected:

	// 2�� ���� ����. ���׷��̵� �ʿ���.
	BOOL Create2ndBuffer(WAVEFORMATEX* pWfx, DWORD dwBuffSize);		
	 
 
}; //end of class ynSoundEffect

typedef ynSoundEffect* LPSOUNDEFFECT;
typedef ynSoundEffect* LPYNSNDFX;
typedef ynSoundEffect* LPSNDFX;




} //end of namespace YENA;


//#endif //#define _SE_H__

/*
//[�ּ�1] ynSoundEffect::Play �Լ� ȣ��� ���ϰ���. ������ ���°� ���ϵ�. : dsound.h 
#define DSBSTATUS_PLAYING           0x00000001
#define DSBSTATUS_BUFFERLOST        0x00000002
#define DSBSTATUS_LOOPING           0x00000004
#define DSBSTATUS_LOCHARDWARE       0x00000008
#define DSBSTATUS_LOCSOFTWARE       0x00000010
#define DSBSTATUS_TERMINATED        0x00000020
*/


//#endif //#ifdef BSOUND_


/*********************** end of file "ynDSound.h" ****************************/