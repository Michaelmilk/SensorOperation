
// SensorOperation.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSensorOperationApp: 
// �йش����ʵ�֣������ SensorOperation.cpp
//

class CSensorOperationApp : public CWinApp
{
public:
	CSensorOperationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSensorOperationApp theApp;