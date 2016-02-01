
// RemindTimer0.1.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "RemindTimer0.1.h"
#include "RemindTimer0.1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRemindTimer01App

BEGIN_MESSAGE_MAP(CRemindTimer01App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRemindTimer01App ����

CRemindTimer01App::CRemindTimer01App()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CRemindTimer01App ����

CRemindTimer01App theApp;
CString app_title;//ȫ�ֱ���


// CRemindTimer01App ��ʼ��

BOOL CRemindTimer01App::InitInstance()
{
	CWinApp::InitInstance();

	//����ֻ��1��ʵ��
	CWnd *hPreWnd, *hChiWnd;
	app_title = "RemindTimer";

    if ( hPreWnd = CWnd::FindWindow(NULL, app_title ))
    {		
		hChiWnd = hPreWnd->GetLastActivePopup();
		hChiWnd->SetForegroundWindow(); //�ҵ������ǰ��
		hChiWnd->ShowWindow(SW_RESTORE);
		return FALSE;
	}


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CRemindTimer01Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�


	return TRUE; // ��һ��ʵ��
}


//	return FALSE;
//}



