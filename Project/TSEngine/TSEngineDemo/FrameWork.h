#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

//#pragma comment()

// C 런타임 헤더 파일입니다.
#include "stdio.h"			//C문자열 처리를 위해 추가.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//이미지 블렌딩을 위한 추가 라이브러리 로드.
//1. 선행처리기 #pragma 사용.
//2. 프로젝트/속성/Lib 에 직접 추가.
#pragma comment(lib, "msimg32")			//MsImg32.lib 로드. 뒤의 확장자는 생략가능.