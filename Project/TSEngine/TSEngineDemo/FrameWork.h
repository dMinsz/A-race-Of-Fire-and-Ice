#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>

//#pragma comment()

// C ��Ÿ�� ��� �����Դϴ�.
#include "stdio.h"			//C���ڿ� ó���� ���� �߰�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

//�̹��� ������ ���� �߰� ���̺귯�� �ε�.
//1. ����ó���� #pragma ���.
//2. ������Ʈ/�Ӽ�/Lib �� ���� �߰�.
#pragma comment(lib, "msimg32")			//MsImg32.lib �ε�. ���� Ȯ���ڴ� ��������.