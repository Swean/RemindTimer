
// RemindTimer0.1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "RemindTimer0.1.h"
#include "RemindTimer0.1Dlg.h"
#include "afxdialogex.h"
#include <windows.h>
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRemindTimer01Dlg 对话框



CRemindTimer01Dlg::CRemindTimer01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRemindTimer01Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRemindTimer01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRemindTimer01Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_SHOWTASK, &CRemindTimer01Dlg::OnShowTask)
	ON_BN_CLICKED(BTN_Begin, &CRemindTimer01Dlg::OnBnClickedBegin)
	ON_BN_CLICKED(BTN_close, &CRemindTimer01Dlg::OnBnClickedclose)
	ON_BN_CLICKED(BTN_Minimize, &CRemindTimer01Dlg::OnBnClickedMinimize)
	ON_BN_CLICKED(BTN_stop, &CRemindTimer01Dlg::OnBnClickedstop)
END_MESSAGE_MAP()


// CRemindTimer01Dlg 消息处理程序

BOOL CRemindTimer01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	SetWindowText(app_title);
	//初始化托盘
	NotifyIcon.cbSize=sizeof(NOTIFYICONDATA);
    NotifyIcon.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    NotifyIcon.hWnd=m_hWnd;
    lstrcpy(NotifyIcon.szTip,_T("报时系统"));
    NotifyIcon.uCallbackMessage=WM_SHOWTASK;
    NotifyIcon.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP;
    Shell_NotifyIcon(NIM_ADD,&NotifyIcon);

	itvl_sec = 0;
	rpt_cnt = 0;
	if_start = false;
	GetDlgItem(BTN_stop)->EnableWindow(false);
	//[pend]实例化定时器
	SetTimer(ID_TIMER_SEC, 1000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRemindTimer01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRemindTimer01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CRemindTimer01Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CString str_time;
	CString str_rpt;
	CTime init_time;
	CTimeSpan span_cnt;
	switch(nIDEvent)
	{		
		case ID_TIMER_SEC:
			//获取系统时间并显示
			init_time = CTime::GetCurrentTime();
			str_time = init_time.Format("%Y年%m月%d日  %H:%M:%S");
			SetDlgItemText(TEXT_show_sys_time, str_time);	
			
			//显示倒计时
			if(if_start)
			{
				span_cnt = --cnt_sec;
				str_time = span_cnt.Format("剩余时间为  %H时%M分%S秒");
				SetDlgItemText(TEXT_show_count_time, str_time);
				OnFiveCount();				
			}
			break;
			
		case ID_TIMER_CNT://不需要break
			//设置报时定时器,倒计时变为间隔时间
			SetTimer(ID_TIMER_ITVL, itvl_sec * 1000, NULL);
			KillTimer(ID_TIMER_CNT);
		case ID_TIMER_ITVL:
			//定时时间到，重复报时
			TimeUp();//定点报时和更新剩余重复次数
			if(rpt_cnt == 0)//报时结束
			{
				KillTimer(ID_TIMER_ITVL);
				if_start = false;	
				cnt_sec = 0;
				str_time = "注意目前处于停止报时状态";
				SetDlgItemText(TEXT_show_count_time, str_time);
			}
			break;
		default:
			break;
	}
}

void CRemindTimer01Dlg::OnSize(UINT nType, int cx, int cy)
{
	// TODO: 在此处添加消息处理程序代码
	if ( nType == SC_MINIMIZE  || nType == SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE);//隐藏最小化到任务栏的图标
	}
	else
	{
		CDialog::OnSize(nType, cx, cy);
	}
}

void CRemindTimer01Dlg::OnSysCommand(UINT nID, LPARAM lParam )
{
	if(nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);//隐藏最小化到任务栏的图标
	} 
    else  
    {  
        CDialog::OnSysCommand(nID, lParam);  
    }  
}

LRESULT CRemindTimer01Dlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if ((lParam == WM_LBUTTONDOWN) || (lParam == WM_RBUTTONDOWN))
    { 
        ModifyStyleEx(0,WS_EX_TOPMOST);
        ShowWindow(SW_SHOW);
        //Shell_NotifyIcon(NIM_DELETE, &NotifyIcon);//消除托盘图标
    }
	return 0;
}

BOOL CRemindTimer01Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if   (pMsg->message  == WM_KEYDOWN)   
	{   
		int nVirtKey = (int)pMsg->wParam;           
		if(nVirtKey == VK_RETURN || nVirtKey == VK_ESCAPE )   
		{   
			//如果是回车，ESC 
			pMsg->wParam = VK_TAB;
  		}   	
	}   
	return CDialog::PreTranslateMessage(pMsg);
}

void CRemindTimer01Dlg::OnBnClickedclose()
{
	// TODO: 在此添加控件通知处理程序代码
	//[pend]关闭程序
	KillTimer(ID_TIMER_SEC);
	KillTimer(ID_TIMER_CNT);
	KillTimer(ID_TIMER_ITVL);
	CDialogEx::OnCancel();
	Shell_NotifyIcon(NIM_DELETE,&NotifyIcon);    //在托盘区删除图标
	return;
}


void CRemindTimer01Dlg::OnBnClickedMinimize()
{
	// TODO: 在此添加控件通知处理程序代码
	//最小化
    ShowWindow(SW_HIDE);
	return;
}


void CRemindTimer01Dlg::OnBnClickedstop()
{
	// TODO: 在此添加控件通知处理程序代码
	//在开始计时后才能使用，停止计时
	if_start = false;
	KillTimer(ID_TIMER_ITVL);
	GetDlgItem(BTN_stop)->EnableWindow(false);
	CString str_time("注意目前处于停止报时状态");
	SetDlgItemText(TEXT_show_count_time, str_time);
	
	GetDlgItem(BTN_Begin)->EnableWindow(true);
	GetDlgItem(IDC_EDIT_count_min)->EnableWindow(true);
	GetDlgItem(IDC_EDIT_interval_min)->EnableWindow(true);
	GetDlgItem(IDC_COMBO_times)->EnableWindow(true);
	return;
}


void CRemindTimer01Dlg::OnBnClickedBegin()
{
	// TODO: 在此添加控件通知处理程序代码

	//获取输入
	cnt_sec = GetDlgItemInt(IDC_EDIT_count_min) * 60;
	itvl_sec = GetDlgItemInt(IDC_EDIT_interval_min) * 60;
	rpt_cnt = GetDlgItemInt(IDC_COMBO_times);
	CTime bgn_time = CTime::GetCurrentTime();

	//重复时间必须小于开始计时时间,重复次数必须大于0
	if(cnt_sec < itvl_sec)
	{
		//弹出窗口
		this->MessageBox(L"重复间隔大于倒计时时间,请重新输入", L"Warning", MB_OK|MB_ICONEXCLAMATION );
		PlaySound(_T("C:\\WINDOWS\\Media\\Windows 感叹号.wav"), NULL, SND_FILENAME|SND_ASYNC);
		return;
	}
	if(0 >= rpt_cnt)
	{
		//弹出窗口
		this->MessageBox(L"重复次数必须大于0,请重新输入", L"Warning", MB_OK|MB_ICONEXCLAMATION );
		PlaySound(_T("C:\\WINDOWS\\Media\\Windows 感叹号.wav"), NULL, SND_FILENAME|SND_ASYNC);
		return;
	}

	//开始计时，开始计时文本显示此刻的时间，剩余时间显示
	if_start = true;
	SetTimer(ID_TIMER_CNT, cnt_sec * 1000, NULL);
	CTimeSpan span_cnt = cnt_sec;
	CString str_time = span_cnt.Format("剩余时间为  %H时%M分%S秒");
	SetDlgItemText(TEXT_show_count_time, str_time);
	

	//获取系统时间并显示
	str_time = bgn_time.Format("%Y年%m月%d日  %H:%M:%S");
	SetDlgItemText(TEXT_show_begin_time, str_time);
	//设置“停止报时”按钮可用，输入框不可用，最小化
	GetDlgItem(BTN_stop)->EnableWindow(true);	
	GetDlgItem(BTN_Begin)->EnableWindow(false);	
	GetDlgItem(IDC_EDIT_count_min)->EnableWindow(false);
	GetDlgItem(IDC_EDIT_interval_min)->EnableWindow(false);
	GetDlgItem(IDC_COMBO_times)->EnableWindow(false);

    ShowWindow(SW_HIDE);
	return;
}

void CRemindTimer01Dlg::OnFiveCount()
{
	// 倒数5秒的动作
	if(cnt_sec <= 5 && cnt_sec > 0)
	{
		if(cnt_sec == 5)
		{
			//弹出界面
			ShowWindow(SW_SHOW);
		}					
		//5秒倒数放小声音
		PlaySound(_T("C:\\WINDOWS\\Media\\Windows 鸣钟.wav"), NULL, SND_FILENAME|SND_ASYNC);
	}
	return;
}

void CRemindTimer01Dlg::TimeUp()
{
	CString str_rpt;
	cnt_sec = itvl_sec;//重置倒计时
	//播放声音
	PlaySound(_T("C:\\WINDOWS\\Media\\Ring03.wav"), NULL, SND_FILENAME|SND_ASYNC);
	str_rpt.Format(_T("%d"), --rpt_cnt);
	CComboBox *cb_times = (CComboBox*)GetDlgItem(IDC_COMBO_times);//[test]不确定这样写好不好
	cb_times->SelectString(0, str_rpt);
	return;
}