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
//
// ynWave.h: interface for the ynWave class.
//         
// ���̺� ȭ���� �ε��ϰ�, �а�, ����, �����ϰ�, ó���ϴ� Ŭ���� 
// 1999.6.15. ���ȫ.
/////////////////////////////////////////////////////////////////////////////
//
// 2004.04.07 : ��ȫ :  DX 9.0(2003, Summer) �������� ������Ʈ.
// 2004.04.08 : �ּ� �� ���� �� ����
// 2020.07.10 : �ű��������̽��� YENA �� ����.
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
// ���̺� ���� �ε� ���� Ŭ����.
// ���� ������ "Windows PCM" �� ���̺� ����.
// ���׷��� �д� (Panning) �Ǵ� 3D �����Ŵ� ���� ó���� ���ؼ��� Mono ä���̾�� �Ѵ�.
//
class YENA_APIX ynWave  
{
protected:
//  2�� �������� ��� ���� ����. 1999.6.16.
//	HMMIO*			m_pHmmio;			//RIFF ȭ�� ������.
//	WAVEFORMATEX*	m_pWaveFormatEx;		//���̺� ȭ�� ������.
//	MMCKINFO		m_ParentCkInfo;		//�θ� ûũ ����.
//	MMCKINFO		m_ChildCkInfo;		//�ڽ� ûũ ����.
	
public: 

	//���̺� ȭ�� ����.	
	BOOL OpenWaveFile(TCHAR* filename, HMMIO* pHmmio, 
						WAVEFORMATEX** ppwfxInfo, MMCKINFO* pParentckinfo);	

	//���̺� ȭ���� �б� ���� �غ�.
	BOOL StartWaveDataRead(HMMIO* pHmmio, MMCKINFO*  
						pChildCkInfo, MMCKINFO* pParentCkInfo);	  

	//���̺� ȭ���� DirectSoundBuffer�� �о� ���δ�.
	BOOL ReadWaveFile(HMMIO Hmmio, UINT BufferSize, BYTE* pBuffer, 
						MMCKINFO* pChildCkInfo, UINT* ActualRead); 
	
	//�б������ �� ���̺� ȭ���� �ݴ´�.
	BOOL CloseReadWaveFile(HMMIO* pHmmio, WAVEFORMATEX** pwfx);	
	//�ϴ� �������.... -_-;; 1999.6.15.
	
public:
	ynWave();
	virtual ~ynWave();

};


} //end of namespace YENA;

/************************* end of file "ynWave.h" *****************************/
