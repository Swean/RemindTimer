
// RemindTimer0.1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRemindTimer01App:
// �йش����ʵ�֣������ RemindTimer0.1.cpp
//

class CRemindTimer01App : public CWinApp
{
public:
	CRemindTimer01App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBegin();
};

extern CRemindTimer01App theApp;