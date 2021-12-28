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
// ynDShow.h : DirectShow �� �̿��� �̵�� ��� (wav/mp3/asf/avi/mpeg-2)
//
//
// 2010.06.20. Rebuild / Kihong Kim / mad_dog@hanmail.net
// 2020.07.10 : �ű��������̽��� YENA �� ����.
//
//
#pragma once

#include "DShow.h"
#pragma comment(lib, "strmiids.lib")				//DirectShow �ʼ� ���̺귯��.
#pragma comment(lib, "quartz.lib")

//2006.04.01.: B3D �� ����.
//2020.07.10 : YENA �� ����.
namespace YENA
{ 

YENA_API int  B3Show_Init();						//DirectShow �ʱ�ȭ.
YENA_API void B3Show_Release();						//DShow ����.


YENA_API int  B3Show_MediaLoad(TCHAR* filename);	//DShow �̵�� �ε�.
YENA_API void B3Show_MediaRelease();				//DShow �̵�� ����.

YENA_API void B3Show_MediaPlay (BOOL Loop = TRUE);	//�̵�� �÷���(�⺻�� : �ݺ�)
YENA_API void B3Show_MediaStop ();					//�̵�� ����.
YENA_API void B3Show_MediaPause();					//�̵�� �Ͻ�����.

YENA_API void B3Show_MediaUpdate();					//�̵�� ���� ���� : �������� �Ź� ȣ��Ǿ�� �Ѵ�.

 
//YENA_API void B3Show_Help(int x, int y, COLOR col);


YENA_API void B3Show_SetVolume(int val);			//��������. ( 0 ~ 100)
YENA_API int  B3Show_GetVolume();					//�������  ( 0 ~ 100)
YENA_API void B3Show_VolumeUp (int v=100);			//���� �ø��� (�⺻.����1)
YENA_API void B3Show_VolumeDn (int v=100);			//���� ������ (�⺻ ����1)


namespace B3SHOW { 
	extern YENA_APIX BOOL 	  _bPlayLoop;			//BGM Loop Play.
	extern YENA_APIX LONGLONG _TotPlayTime;			//�̵�� ��ü �÷��� �ð�(���뼼����.��)
	extern YENA_APIX LONGLONG _CurrPlayTime;		//�̵�� ���� �÷��� ��ġ(���뼼����.��)	
	extern YENA_APIX int      _CurrVolume;			//���� �÷��� �������.(0~100)
}//end of namespace B3DSHOW


YENA_API int	  B3Show_GetCurrVolume ();			//���� �÷��� �������.(0~100)
YENA_API LONGLONG B3Show_GetTotPlayTime();			//�̵�� ��ü �÷��� �ð�(���뼼����.��)
YENA_API float    B3Show_GetTotPlayTimeSec ();		//�̵�� ��ü �÷��� �ð�(��)
YENA_API LONGLONG B3Show_GetCurrPlayTime   ();		//�̵�� ���� �÷��� ��ġ(���뼼����.��)
YENA_API float    B3Show_GetCurrPlayTimeSec();		//�̵�� ���� �÷��� ��ġ(��)	
YENA_API double   B3Show_SetRate(double rate=1.0);	//�̵�� �÷��� �ӵ� ���� (1.0 = 100%) ���ϰ��� ������ ���� �ӵ�.
YENA_API double   B3Show_GetRate();					//�̵�� ���� �÷��� �ӵ� (1.0 = 100%)
	


}//end of namespace YENA

using namespace YENA;

/************************* end of file "ynDShow.h" ****************************/

