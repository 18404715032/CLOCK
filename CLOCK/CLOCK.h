
// CLOCK.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCLOCKApp:
// �йش����ʵ�֣������ CLOCK.cpp
//

class CCLOCKApp : public CWinApp
{
public:
	CCLOCKApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCLOCKApp theApp;