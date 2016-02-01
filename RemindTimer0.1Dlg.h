
// RemindTimer0.1Dlg.h : ͷ�ļ�
//
#pragma once
#define ID_TIMER_SEC  1//����ʱ��
#define ID_TIMER_CNT 2//���ڵ���ʱ
#define ID_TIMER_ITVL 3//�����ظ���ʱ
#define WM_SHOWTASK WM_USER+1


// CRemindTimer01Dlg �Ի���
class CRemindTimer01Dlg : public CDialogEx
{
// ����
public:
	CRemindTimer01Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_REMINDTIMER01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	NOTIFYICONDATA NotifyIcon;

	// ���ɵ���Ϣӳ�亯��
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

//Ҫ�õ���ȫ������
private:
	UINT itvl_sec;//�ظ���ʱ�������λs
	UINT cnt_sec;//����ʱ����λs
	UINT rpt_cnt;//�ظ���ʱ����
	bool  if_start;
	 
};

extern CString app_title;
