/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  YENA/YENA : DX/GL ��� �ϵ���� ���� 2D/3D ����.                         // 
//                                                                         //
//  �� �� : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Interactive. http://www.zero-g.kr		   		       //	
//  �ʱ����� : 2003.12 - 2004.03.                                          //
//  ����ȯ�� : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008/2010 //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 10.1(2010, Jun)                                //
//                  OpenGL 1.x / 2.x / 3.x                                 //
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
// Yena ���� / ���̺귯�� ���� ���  
//
// 20.1113 Yena.h ���� ���� ���̺귯�� �и�
//
///////////////////////////////////////////////////////////////////////////////
//#include "Yena.h"
#include "Yena_API.h"

//#define YENA_SOUND_EXPORTS	//���� ���̺귯�� �ͽ���Ʈ ���� 	
#ifdef YENA_SOUND_EXPORTS
#include "DXErr.h"
//#include "ynDefine.h"			//���� �ڷ�/Ŭ����/���� ������.
//#include "YnError.h"			//���� �޼��� ����.
//#include "ynLog.h"			//�α�����
#endif


///////////////////////////////////////////////////////////////////////////////
//
// Yena ���� / ���� ���̺귯�� ���  
//
///////////////////////////////////////////////////////////////////////////////
#include "ynWave.h"
#include "ynDSound.h"
#include "ynDShow.h"
 
#ifndef _in_
#define _in_		//[in] �Է�
#define _out_		//[out] ���
#define _inout_		//[inout] �Է� �� ���
#endif


//////////////////////////////////////////////////////////////////////////////
//
// ��Ƽ��̾� �������̽�. (����)(v.2.29)
//
//////////////////////////////////////////////////////////////////////////////

namespace YENA
{

//-----------------------------------------------
// �������̽� ������.(����) v.2.29 (20.1028)
//-----------------------------------------------
//
// ��Ƽ�̵�� �ý��� �ʱ�ȭ : ���� �ʱ⿡ �ѹ� ȣ��.
// hWnd : ������ �ڵ�.
// ���� : �����ϸ� YN_OK, ���и� YN_FAIL
//
YENA_APIX int ynMMedia_Initial(HWND hwnd);

// ��Ƽ�̵�� �ý��� �ʱ�ȭ : ���� ����� �ѹ� ȣ��.
//
YENA_APIX void ynMMedia_Release();

// ��Ƽ�̵�� �ý��� ���� : �� �����Ӹ��� �����ؾ� ��.
// dTime : ���� Ÿ�̸�, �����ӽð�.
YENA_APIX int ynMMedia_Update(float dTime);






//-----------------------------------------------
// Wave ���� ó�� API
//-----------------------------------------------

//���� Ŭ���� ������.
//#define LPSOUNDEFFECT  ynSoundEffect*


// ���� ���� �ε� 
// filename : [in] ���ϸ�, Wave ���� ����.  ���׷��� �д� (Panning) �Ǵ� 
//                 3D �����Ŵ� ���� ó���� ���ؼ��� Mono ä���̾�� �Ѵ�.
// ppSnd : [out] ���� ��ü ������.
//
// ������ TRUE ����, ���н� FALSE ����.
//
YENA_APIX int ynSndLoad(_in_ TCHAR* filename, _inout_ LPSOUNDEFFECT* ppSnd);		


// ���� ���� �ε� 
// filename : [in] ���ϸ�, Wave ���� ����.  ���׷��� �д� (Panning) �Ǵ� 
//                 3D �����Ŵ� ���� ó���� ���ؼ��� Mono ä���̾�� �Ѵ�.
// rSnd : [out] ���� ��ü ������ ���۷���
//
// ������ TRUE ����, ���н� FALSE ����.
//
YENA_APIX int ynSndLoad( _in_ TCHAR* filename, _inout_ LPSOUNDEFFECT& snd);


// ���� ���� ���� 
// snd :  ���� ��ü ������.
YENA_APIX void ynSndRelease(_inout_ LPSOUNDEFFECT& snd);					



// ���� ���� �÷���
// pSnd  : �÷����� ���� ��ü ������.
// bLoop : '�ݺ�' �÷��� ����. 
// bRewind : �ǰ��⿩��. TRUE(YES_) ������, �Լ� ȣ��� ������ ó������ �÷���.
// ���ϰ� : �÷��� ����. ���н� YN_FAIL ����.
//
YENA_APIX int ynSndPlay(_in_ LPSOUNDEFFECT pSnd, _in_ BOOL bLoop = PLAY_ONCE_, _in_ BOOL bRewind = NO_ );

// ���� �÷��� ����.
// pSnd  : �÷����� ���� ��ü ������.
// ���ϰ� : ������ YN_OK, ���н� YN_FAIL ����.
//
YENA_APIX int ynSndStop(LPSOUNDEFFECT pSnd);


// ���� �÷��� ���� ����.
// pSnd : �÷����� ���� ��ü ������.
// vol  : ������ ������. ������ 0~100 . �� ���� 100 ������ ���ú�(db) ������ �����Ǿ� ���ȴ�. 
// ������ TRUE, ���н� FALSE  �� ����.
//
YENA_APIX int ynSndSetVolume(LPSOUNDEFFECT snd, LONG vol);

// ���� �÷��� ���� ���.
// pSnd : �÷����� ���� ��ü ������.
// ���ϰ� : ���� ������. ������ 0~100.  ���н� YN_FAIL  �� ����.
//
YENA_APIX LONG ynSndGetVolume(LPSOUNDEFFECT snd);

// ���� �÷��� ���� �ø���
// pSnd : �÷����� ���� ��ü ������.
// v  :  ���� ������. �ʴ� ��ȭ��, �⺻�� 100.
// ���ϰ� : ���� ������. ������ 0~100.  ���н� YN_FAIL  �� ����.
//
YENA_APIX LONG ynSndVolumeUp(LPSOUNDEFFECT snd, LONG v = 100);

// ���� �÷��� ���� ����
// pSnd : �÷����� ���� ��ü ������.
// v  :  ���� ������. �ʴ� ��ȭ��, �⺻�� 100.
// ���ϰ� : ���� ������. ������ 0~100.  ���н� YN_FAIL  �� ����.
//
YENA_APIX LONG ynSndVolumeDn(LPSOUNDEFFECT snd, LONG v = 100);



// ���� �д� Panning ����
// pSnd : �÷����� ���� ��ü ������.
// v  :  �д� ��ġ. ������ -100 ~ 100. ���ο��� db(���ú�)��  �����Ǿ� ���ȴ�. <����> Ȯ��
// ���ϰ� : ���� �д� ��ġ. ���н� YN_FAIL ����.
//  <����>
//  �߾� (���� �ִ�) : 0  (0db)
//  ���� �ִ�      : -100 (-10,000db) 
//  ������ �ִ�    : +100 (+10,000db) 
//
YENA_APIX int ynSndSetPan(LPSOUNDEFFECT snd, LONG v = 0);


// ���� �д� Panning ����
// pSnd : �÷����� ���� ��ü ������.
// ���ϰ� : ���� �д� ��ġ. ���н� YN_FAIL ����. <����> Ȯ��.
//  <����>
//  �߾� (���� �ִ�) : 0  (0db)
//  ���� �ִ�      : -100 (-10,000db) 
//  ������ �ִ�    : +100 (+10,000db) 
//
YENA_APIX int ynSndGetPan(LPSOUNDEFFECT snd);


// ���� ���� �д� Panning ����
// pSnd : �÷����� ���� ��ü ������.
// v  :  �д׷�, �ʴ� ��ȭ��, ���ο��� db(���ú�)�� �����Ǿ� ���ȴ�. 
//       ���� �д� �ִ밪�� -100 
// ���ϰ� : ���� �д� ��ġ  ���н� YN_FAIL ����.
//
YENA_APIX int ynSndPanLeft(LPSOUNDEFFECT snd, LONG v = 100);

// ���� ������ �д� Panning ����
// pSnd : �÷����� ���� ��ü ������.
// v  :  �д׷�, �ʴ� ��ȭ��, ���ο��� db(���ú�)�� �����Ǿ� ���ȴ�. 
//       ������ �д� �ִ밪�� 100 
// ���ϰ� : ���� �д� ��ġ ���н� YN_FAIL ����.
//
YENA_APIX int ynSndPanRight(LPSOUNDEFFECT snd, LONG v = 100);


// ���� ���� �ӵ� ����
// pSnd : �÷����� ���� ��ü ������.
// v    : �÷��� �ӵ� ����.
// ���ϰ� : ���� �ӵ� ��. ���н� YN_FAIL ����. <����> Ȯ��.
//  <����>
// �⺻ : 1 ���   (100%)
// �ִ� : 4 ���   (400%) : �� �̻��� '�鸮��' �ʴ´�..
// ���� : 0.1 ��� (10%)  : �ʹ� �����͵� ����.. �����ϰ� ������ �Ǵ�.
//
//
YENA_APIX float ynSndSetSpeed(LPSOUNDEFFECT snd, float v = 1.0f);

// ���� ���� �ӵ� ���� (Hz)
// pSnd : �÷����� ���� ��ü ������.
// f    : �÷��� �ӵ� 
// ���ϰ� : ���� �ӵ� ��. ���н� YN_FAIL ����. <ynSndSetSpeed> Ȯ��.
//
YENA_APIX DWORD ynSndSetFreq(LPSOUNDEFFECT snd, DWORD f = 0);


// ���� ���� �ӵ� ȹ��
// ���ϰ� : ���� �ӵ� (����) ���н� YN_FAIL ����. <����> Ȯ��.
//
YENA_APIX float ynSndGetSpeed(LPSOUNDEFFECT snd);


// ���� ���� �ӵ� ȹ��
// ���ϰ� : ���� �ӵ� ��. ���н� YN_FAIL ����. <����> Ȯ��.
//
YENA_APIX DWORD ynSndGetFreq( LPSOUNDEFFECT snd);

// ���� ���ּӵ� ����.
// ynSndSetSpeed �� ����.
#define ynSndSpeedReset(s)   ynSndSetSpeed((s), 1);


//���� ȣȯ ��ũ��
//#define  ynSndPlay(se)			se->Play()						
//#define  ynSndPlayLoop(se)		se->Play(PLAY_LOOP_, NO_)
//#define  ynSndStop(se)			se->Stop();

// ���� ���� ����. 
//#define  ynSndSetVolume(se, v)  se->SetVolume(v)
//#define  ynSndGetVolume(se)     se->GetVolume()
//#define  ynSndVolumeUp(se, v)   se->VolumeUp(v)
//#define  ynSndVolumeDn(se, v)   se->VolumeDn(v)

// ���� �д�
//#define  ynSndSetPan(se, v)     se->SetPan(v)
//#define  ynSndGetPan(se, v)     se->GetPan(v)
//#define  ynSndPanLeft(se, v)    se->SetPan2Left(v)
//#define  ynSndPanRight(se, v)   se->SetPan2Right(v)




//-----------------------------------------------
// ���� ȣȯ�� ������. (v.1.5.7) ����.
//-----------------------------------------------
// (v.2.30) ����. ���忣�� �ʱ�ȭ/�����  Yena ���� �ڵ�ó����. 
//                ����ڰ� ���� ����� �ʿ�� ����.
#define ynSound_Initial		ynMMedia_Initial		// ��Ƽ�̵�� �ý��� �ʱ�ȭ : ���� �ʱ⿡ �ѹ� ȣ��. ynMMedia_Initial ������.
#define ynSound_Release		ynMMedia_Release		// ��Ƽ�̵�� �ý��� �ʱ�ȭ : ���� ����� �ѹ� ȣ��. ynMMedia_Release ������.
#define ynSound_Update		ynMMedia_Update			// ��Ƽ�̵�� �ý��� ���� : �� �����Ӹ��� �����ؾ� ��. ynMMedia_Update ������.

//�������̽� ������.(����)
//#define ynSound_Initial   B3Sound_Init
//#define ynSound_Release   B3Sound_Release
//#define ynSound_Update	B3Sound_Update



// Wave ������ ���� ����
#define ynSndMasterVolumeUp		B3Sound_MasterVolumeUp	//������ ���� �ø�. dv = �ʴ� ������
#define ynSndMasterVolumeDn		B3Sound_MasterVolumeDn	//������ ���� ����. dv = �ʴ� ���ҷ�
#define ynSndMasterSetVolume	B3Sound_MasterSetVolume	//������ ���� ����. v = ����, ������ 0 ~ 100.(max)
#define ynSndMasterGetVolume	B3Sound_MasterGetVolume	//������ ���� ȹ��.
#define ynSndMasterSetFreq      B3Sound_MasterSetFreq	//������ �÷��� ���ļ� ����.  �⺻ = 0, �ּ� 100 ~ 20,000 
#define ynSndMasterGetFreq      B3Sound_MasterGetFreq	//������ �÷��� ���� ���ļ� ȹ��.


// Mp3 ó�� API
#define ynMediaLoad				B3Show_MediaLoad		//�̵�� ���� �ε�..
#define ynMediaRelease			B3Show_MediaRelease		//�̵�� ���� ����.
#define ynMediaPlay				B3Show_MediaPlay		//�̵�� �÷���..
#define ynMediaPause			B3Show_MediaPause		//�̵�� �÷��� �Ͻ�����.
#define ynMediaStop				B3Show_MediaStop		//�̵�� �÷��� ����.
#define ynMediaVolumeUp			B3Show_VolumeUp			//���� �ø�.
#define ynMediaVolumeDn			B3Show_VolumeDn			//���� ����.
#define ynMediaSetVolume		B3Show_SetVolume		//���� ����.
#define ynGetCurrVolume			B3Show_GetCurrVolume	//���� ���� ���.

// �̵�� ����(mp3) �÷��� ���� ȹ��.
#define ynMediaGetTotPlayTime			B3Show_GetTotPlayTime			//��ü �÷��� �ð� (����) ���.
#define ynMediaGetTotPlayTimeSec		B3Show_GetTotPlayTimeSec
#define ynMediaGetCurrPlayTime			B3Show_GetCurrPlayTime			//���� �÷��� �ð� (����) ���.
#define ynMediaGetCurrPlayTimeSec		B3Show_GetCurrPlayTimeSec
#define ynMediaSetRate                  B3Show_SetRate					//�̵�� �÷��� �ӵ� ���� (1.0 = 100%) ���ϰ��� ������ ���� �ӵ�. 
#define ynMediaGetRate                  B3Show_GetRate					//�̵�� ���� �÷��� �ӵ� (1.0 = 100%)


//�̵�� �ð����� ����ü.
struct MMEDIAINFO
{
	LONGLONG totTime;		//��ü ���ֽð�.
	LONGLONG curTime;		//���� ���ֽð�

	DWORD  totMin, totSec, totCSec;		//��ü ���ֽð� (��:��:��:�����)
	DWORD  curMin, curSec, curCSec;		//���� ���ֽð� (��:��:��:�����)

	float   prog;		//�÷��� ����.(%)

	double  rate;		//���� ���ļ�.

	LONG event;
	LONG_PTR eventParam1, eventParam2;
	long timeOut;
};
typedef MMEDIAINFO* LPMMEDIAINFO;
typedef MMEDIAINFO  ynMMediaInfo;


// ���� �÷��� ���� �̵�� ���� ȹ��.
// pSnd : [in] ������ ȹ���� ���� ��ü ������.
// pInfo  : [out] ������ ������ ����ü ������.
//
YENA_APIX int ynMediaInfo( _out_ LPMMEDIAINFO pInfo);
//YENA_APIX DWORD ynMediaGetInfo( _in_ LPSOUNDEFFECT snd, _out_ LPMMEDIAINFO pInfo);






}//end of YENA.

using namespace YENA;






////////////////////////////////////////////////////////////////////////////// 
//
// ���� ���̺귯�� ���� ���ǿ� ����  : 20.1112
//
////////////////////////////////////////////////////////////////////////////// 
#define YENA_SE 1
#ifndef YENA_EXPORTS			
#define YENA_SOUND_EXPORTS		//Yens SE & �Ϲ� App Ÿ�� ������
#endif
#ifdef YENA_SOUND_EXPORTS 
namespace YENA {


//
// ����� ���� ������.
//
//YENA_APIX void ynLogMsg(BOOL bMBox, TCHAR* msg, ...);
YENA_APIX int ynErrorW(BOOL bMBox, TCHAR* msg, ...);

//�̸� ȣȯ�� ����.
#define ynLogMsg  ynErrorW
#define B3D_Error ynErrorW			//�Ϲ�+�α�+�ܼ� ��¹���.
//#define B3D_Error(bMBox, msg, ...)  ynErrorW( bMBox, msg, __VA_ARGS__ )		//�Ϲ�+�α�+�ܼ� ��¹���.

//#ifndef YN_OK
//#define YN_OK		0x00000000					//Ư���� '����' ����. 1 �̻��� �����ڵ�� ����.
//#define YN_OK		0x00000001					//Ư���� '����' ����. 1 �̻��� �����ڵ�� ����.
//#define YN_ERROR	-1
#define YN_ERROR	YN_FAIL
//#define YN_FAIL		YN_ERROR
#define YNFAILED(a)  ( (a) != YN_OK )		//����, ����..
#define YNOK(a)      ( (a) == YN_OK )		//���� ����.����!
//#endif

#include "assert.h"
#define ASSERT assert
 


//
// ��Ÿ �ý��� ���� �Լ� �� ������ : ynDefine.h ������.
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
#define YN_OK	   0					//���� ����. Ư���� ���� ����.
#define YN_FAIL   -1					//���� �߻�.
#define YN_FAILED(v)   ((v) != YN_OK)	//���� üũ ��ũ��.
#endif
 

// ���� * ��Į�� ��  (ex)  col = col * 0.5f
//COLOR  operator * (COLOR  & lhs, float s);
//COLORA operator * (COLORA & lhs, float s);



/*//���콺 �Է� ����. --> DInput ���.
#define MS_STANDBY   0x0000		//�����.
#define MS_LBTNDOWN  0x0100		//��ư ����.
#define MS_LBTNUP	 0x8100		//��ư ������ ������.
#define MS_RBTNDOWN  0x0001		//��ư ����.
#define MS_RBTNUP	 0x0081		//��ư ������ ������.
*/

//����� ���� ������.
#define _DEBUG_LV1_  
//#define _DEBUG_LV2_  
//#define _DEBUG_LV3_  






//  ynTextDrawSV   : ������ ȭ����ǥ�� ���������� ���ڿ��� ����մϴ�. (����� ��Ʈ)
//                   
// �Ķ���� :  pFont = ����� ��Ʈ ��ü ������.
//            x,y = ȭ����ǥ.   
//            col = ��»���  
//            msg = ����� ���ڿ� 
//            dTime = ��� �ӵ� ó���� �����ӽð� . �и������� ���� �Ǽ�ȯ��. 1.0 = 1000 ms = 1 sec  
//					
// ���ڸ� �����ӵ��� ���������� ����մϴ�.  
// ���� 80���� �̻�, �Ǵ� ���๮��(CR_LF) �� ������ ��� ���� �ٷ� �ڵ����� �������ϴ�.   
// ���� 80 ���� ���� 40�� ���� ǥ���� �� �ֽ��ϴ�.
// ��� �ִ� ���ڼ��� 4096. ���ڼ��� �ѱ�� overflow ���� �߻�. 
// ����� ��Ʈ��  ����ũ�⿡ �°� �ٰ��� LineSpace �� �����ؾ� �մϴ�.
// LineSpace �� ��Ʈ������ ������ �� �ֽ��ϴ�. ynFontCreate ����
//
YENA_APIX void ynTextDrawSV(HDC hdc, int x, int y, COLORREF col, TCHAR* msg, float dTime);







}//end of YENA.

#endif //end of YENA_SOUND_EXPORTS





/********************* end of file "ynSound.h" **************************/