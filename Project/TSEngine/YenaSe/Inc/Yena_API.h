/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  B3/YENA : 2D/3D ������ ����.						                       // 
//                                                                         //
//  �� �� : Kihong Kim / mad_dog@hanmail.net                               // 
//          Zero-G Tech,Inc http://www.zero-g.kr						   //	
//  �ʱⰳ�� : 2003.12 - 2004.03.                                          //
//  ����ȯ�� : OS - Windows 2k SP4 / Visual Studio 6.0/2003/2005/2008       //
//                  DirectX 9.0b(2003, summer)                             //
//                  DirectX 9.0c(2007, November)                           //
//                  OpenGL 1.x / 2.x                                       //
//             H/W - AMD Athlon XP(Barton) 2500+@2300                      //    
//                   ATI Radeon 9600 Pro                                   //
//                   ABit NF7-II /w SAMSUNG DDR 512MB                      //
//                   SB Live! DE 5.1                                       //
//  �׽�Ʈ ȯ�� : CPU - AMD Athlon										   //	 
//                      AMD Athlonx64 w/q4                                 // 
//                      Intel Pentium III/IV & Celeron                     //
//                      Core2 w/Quad                                       //
//                VGA - ATI Radeon 9xxx Series                             //
//                          Radeon 1xxx Series                             //
//                          Radeon HD 3/4/5/6 Series                       //
//                      nVidia GeForce 2 MX/Ti Series.                     //  
//                             GeForce 3 Ti Series.                        //
//                             GeForce 4 MX/Ti Series.                     //
//                             GeForce FX Series.                          //
//                             GeForce 5/6/7/8/9xxx Series.                //
//                             GeForce 2/4xx GTS Series.                   //
//                             GeForce 7xx GTX Series.                     //
//                             GeForce 2Way-SLI / 3Way-SLI		   	       //
//                OS - Windows 98 / 2K / XP / VISTA / Win7 x32:x64         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//
// Yena_API.h: ���� �ʼ� ���.
//
// 2003. Kihong Kim / mad_dog@hanmail.net
// 2006.08. Update.
// 2011.04. Update.
// 2017.01. Update. Yena / DX11.1 (Windows SDK 8.1)
//
//////////////////////////////////////////////////////////////////////////////
#pragma once



///////////////////////////////////////////////////////////////////////////////
//
// Yena ���� / ���̺귯�� ���� ó�� 
//
///////////////////////////////////////////////////////////////////////////////

//���̺귯�� �ε� �ɼ�.
#ifndef YENA_EXPORTS 
	#ifdef _DEBUG  
		#ifdef _WIN64
			#pragma comment(lib, "YenaSe64d.lib")	//����� ����.(64��Ʈ)
		#elif _WIN32
			#pragma comment(lib, "YenaSed.lib")		//����� ����
		#endif
	#else
		#ifdef _WIN64
			#pragma comment(lib, "YenaSe64.lib")	//������ ����.(64��Ʈ)
		#elif _WIN32
			#pragma comment(lib, "YenaSe.lib")		//������ ����.
		#endif
	#endif
#endif

//���̺귯�� �ͽ���Ʈ �ɼ�.
#ifdef YENA_EXPORTS
	#define YENA_API  extern "C" __declspec(dllexport)
	//#define YENA_API  __declspec(dllexport)
	#define YENA_APIX __declspec(dllexport)
#else
	#define YENA_API  extern "C" __declspec(dllimport)
	//#define YENA_API  __declspec(dllimport)
	#define YENA_APIX __declspec(dllimport)
#endif



/****************** end of file "Yena_API.h" *******************************/