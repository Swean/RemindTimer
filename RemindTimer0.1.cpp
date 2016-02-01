
// RemindTimer0.1.cpp : 定义应用程序的类行为。
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


// CRemindTimer01App 构造

CRemindTimer01App::CRemindTimer01App()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CRemindTimer01App 对象

CRemindTimer01App theApp;
CString app_title;//全局变量


// CRemindTimer01App 初始化

BOOL CRemindTimer01App::InitInstance()
{
	CWinApp::InitInstance();

	//控制只能1个实例
	CWnd *hPreWnd, *hChiWnd;
	app_title = "RemindTimer";

    if ( hPreWnd = CWnd::FindWindow(NULL, app_title ))
    {		
		hChiWnd = hPreWnd->GetLastActivePopup();
		hChiWnd->SetForegroundWindow(); //找到并激活到前端
		hChiWnd->ShowWindow(SW_RESTORE);
		return FALSE;
	}


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CRemindTimer01Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。


	return TRUE; // 第一个实例
}


//	return FALSE;
//}



