
// RemindTimer0.1Dlg.h : 头文件
//
#pragma once
#define ID_TIMER_SEC  1//用于时钟
#define ID_TIMER_CNT 2//用于倒计时
#define ID_TIMER_ITVL 3//用于重复报时
#define WM_SHOWTASK WM_USER+1


// CRemindTimer01Dlg 对话框
class CRemindTimer01Dlg : public CDialogEx
{
// 构造
public:
	CRemindTimer01Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REMINDTIMER01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	NOTIFYICONDATA NotifyIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBegin();
	afx_msg void OnBnClickedclose();
	afx_msg void OnBnClickedMinimize();
	afx_msg void OnBnClickedstop();

	void OnFiveCount();
	void TimeUp();

//要用到的全局数据
private:
	UINT itvl_sec;//重复报时间隔，单位s
	UINT cnt_sec;//倒计时，单位s
	UINT rpt_cnt;//重复报时次数
	bool  if_start;
	 
};

extern CString app_title;
