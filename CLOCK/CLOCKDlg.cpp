
// CLOCKDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CLOCK.h"
#include "CLOCKDlg.h"
#include "afxdialogex.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCLOCKDlg 对话框




CCLOCKDlg::CCLOCKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCLOCKDlg::IDD, pParent)
	, m_h(0)
	, m_m(0)
	, m_s(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCLOCKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_h);
	DDX_Text(pDX, IDC_EDIT2, m_m);
	DDX_Text(pDX, IDC_EDIT3, m_s);
}

BEGIN_MESSAGE_MAP(CCLOCKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_CLOCK, &CCLOCKDlg::OnBnClickedClock)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCLOCKDlg 消息处理程序

BOOL CCLOCKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(1,1000,NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCLOCKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCLOCKDlg::OnPaint()
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
HCURSOR CCLOCKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCLOCKDlg::OnBnClickedClock()
{
	// TODO: 在此添加控件通知处理程序代码
	SetTimer(1,1000,NULL);
}


void CCLOCKDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    TRACE("X=%d ,Y=%d\n",point.x,point.y);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CCLOCKDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int l1=70,l2=50,l3=30;
	CTime t=CTime::GetCurrentTime();//获取系统时间
	m_h=t.GetHour();
	m_m=t.GetMinute();
	m_s=t.GetSecond();
	UpdateData(false);
	CDC *pdc;
	pdc=GetDC();
	pdc->SetWindowOrg(-150,-150);
	CPen *oldpen;
	CPen Pen(PS_SOLID,3,RGB(0,255,255));
	oldpen=pdc->SelectObject(&Pen);
	pdc->Ellipse(-100,100,100,-100);
	pdc->Ellipse(-3,-3,3,3);
	for(int i=0;i<12;i++)
	{
		double l=96,ag=i*3.14159/6;
		double a=l*sin(ag)+1,b=-l*cos(ag)+1,c=l*sin(ag)-1,d=-l*cos(ag)-1;
		pdc->Ellipse(a,b,c,d);
	}
	pdc->TextOutW(-8,-90,L"12");
	pdc->TextOutW(80,-8,L"3");
	pdc->TextOutW(-4,76,L"6");
	pdc->TextOutW(-86,-8,L"9");

	CPen whitepen(PS_SOLID,4,RGB(255,255,255));
	pdc->SelectObject(&whitepen);
	x=l1*sin(m_s*(3.1415926/30)-(3.1415926/30));
	y=l1*-cos(m_s*(3.1415926/30)-(3.1415926/30));
	pdc->MoveTo(0,0);
	pdc->LineTo(x,y);
	CPen pen1(PS_SOLID,2,RGB(255,0,0));
	pdc->SelectObject(&pen1);
	x=l1*sin(m_s*(3.1415926/30));
	y=l1*-cos(m_s*(3.1415926/30));
	pdc->MoveTo(0,0);
	pdc->LineTo(x,y);

	pdc->SelectObject(&whitepen);
	x=l2*sin(m_m*(3.1415926/30)+m_s*(3.1415926/1800));
	y=l2*-cos(m_m*(3.1415926/30)+m_s*(3.1415926/1800));
	pdc->MoveTo(0,0);
	pdc->LineTo(x,y);
	CPen pen2(PS_SOLID,2,RGB(0,0,0));
	pdc->SelectObject(&pen2);
	x=l2*sin(m_m*(3.1415926/30)+m_s*(3.1415926/1800));
	y=l2*-cos(m_m*(3.1415926/30)+m_s*(3.1415926/1800));
	pdc->MoveTo(0,0);
	pdc->LineTo(x,y);

	pdc->SelectObject(&whitepen);
	x=l3*sin(m_h*(3.1415926/30)+m_m*(3.1415926/1800)+m_s*(3.1415926/10800)+3.1415926);
	y=l3*-cos(m_h*(3.1415926/30)+m_m*(3.1415926/1800)+m_s*(3.1415926/10800)+3.1415926);
	pdc->MoveTo(0,0);
	pdc->LineTo(x,y);
	CPen pen3(PS_SOLID,2,RGB(0,0,0));
	pdc->SelectObject(&pen3);
	x=l3*sin(m_h*(3.1415926/30)+m_m*(3.1415926/1800)+m_s*(3.1415926/10800)+3.1415926);
	y=l3*-cos(m_h*(3.1415926/30)+m_m*(3.1415926/1800)+m_s*(3.1415926/10800)+3.1415926);
	pdc->MoveTo(0,0);
	pdc->LineTo(x,y);

	CDialogEx::OnTimer(nIDEvent);
}
