// PropertyGraphic.cpp : 实现文件
//

#include "stdafx.h"
#include "SensorOperation.h"
#include "PropertyGraphic.h"
#include "afxdialogex.h"


// CPropertyGraphic 对话框

IMPLEMENT_DYNAMIC(CPropertyGraphic, CPropertyPage)

CPropertyGraphic::CPropertyGraphic()
	: CPropertyPage(CPropertyGraphic::IDD)
{
	m_xCoordinateLen = COORDINATELEN;
	//将初始值设置为0
	ZeroMemory(&m_curTemperature, sizeof(double)*m_xCoordinateLen);
	ZeroMemory(&m_curHumidity, sizeof(double)*m_xCoordinateLen);

	//初始化底部横坐标的值
	for (int i = 0; i < COORDINATELEN; i++)
		m_xCoordinate[i] = i - 20;
}

CPropertyGraphic::~CPropertyGraphic()
{
}

void CPropertyGraphic::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_CURVE, m_curvePicCtl);
}


BEGIN_MESSAGE_MAP(CPropertyGraphic, CPropertyPage)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPropertyGraphic 消息处理程序

void CPropertyGraphic::InitHSChartCtrl()
{
	//允许控件中标签显示
	m_HSChartCtrl.GetLegend()->SetVisible(true);
	m_HSChartCtrl.GetLegend()->SetHorizontalMode(true);
	m_HSChartCtrl.GetLegend()->UndockLegend(30, 20);
	m_HSChartCtrl.GetLegend()->SetFont(80, _T("Microsoft Sans Serif"));

	//获取图片控件的rect区域
	CRect picCtlRect;
	m_curvePicCtl.GetWindowRect(picCtlRect);
	ScreenToClient(picCtlRect);


	//在图片控件的区域创建绘图控件
	m_HSChartCtrl.Create(this, picCtlRect, 1);
	//创建底部坐标
	CChartStandardAxis* pBottomAxis =
		m_HSChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetMinMax(-20, 0);//坐标范围为1-10
	pBottomAxis->SetTickIncrement(false, 1.0);//坐标间隔为1

	//创建左边的坐标
	CChartStandardAxis* pLeftAxis =
		m_HSChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetMinMax(0, 90);//坐标范围为0-90
	pLeftAxis->SetTickIncrement(false, 5.0);//坐标间隔为5

	//创建右边的坐标
	CChartStandardAxis* pRightAxis =
		m_HSChartCtrl.CreateStandardAxis(CChartCtrl::RightAxis);
	pRightAxis->SetMinMax(0, 90);//坐标范围为0-90
	pRightAxis->SetTickIncrement(false, 5.0);//坐标间隔为5

	m_pTemperatureLine = m_HSChartCtrl.CreateLineSerie();//创建绘制温度实时曲线的对象
	m_pHumidityLine = m_HSChartCtrl.CreateLineSerie();//创建绘制湿度实时曲线的对象
	COLORREF SerieColorGreen = RGB(0, 255, 0);//创建实时曲线的颜色蓝色，默认颜色为红色
	COLORREF SerieColorBlue = RGB(0, 0, 255);//创建实时曲线的颜色蓝色，默认颜色为红色
	m_pTemperatureLine->SetColor(SerieColorGreen);//绘制温度实时曲线为绿色
	m_pHumidityLine->SetColor(SerieColorBlue);//绘制湿度实时曲线的颜色为蓝色
	m_pTemperatureLine->SetName(_T("Temperature"));//显示温度标签
	m_pHumidityLine->SetName(_T("Humidity"));//显示湿度标签
	
	UpdateData(FALSE);
}

BOOL CPropertyGraphic::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//初始化绘图控件
	InitHSChartCtrl();
	
	SetTimer(2, 1000, NULL);
	SetTimer(3, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


HBRUSH CPropertyGraphic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG)
	{
		hbr = CreateSolidBrush(RGB(240, 240, 240));
		return hbr;
	}

	switch (pWnd->GetDlgCtrlID())
	{
		//针对ID为IDC_CTL1、IDC_CTL2和IDC_CTL3的控件进行同样的设置  
		case IDC_STATIC_HUMIDITY:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(255, 0, 0));   //将颜色设置为蓝色  
			return (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);
		}
		case IDC_STATIC_TRMPERATURE:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(0, 255, 0));   //将颜色设置为绿色  
			return (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);
		}
		default:
			return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CPropertyGraphic::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//定时绘制温度实时曲线
	if (2 == nIDEvent)
	{
		m_pTemperatureLine->ClearSerie();
		LeftShiftArray(m_curTemperature, m_xCoordinateLen, 20 + rand() % 2);
		m_pTemperatureLine->AddPoints(m_xCoordinate, m_curTemperature, m_xCoordinateLen);

	}

	//定时绘制湿度实时曲线
	if (3 == nIDEvent)
	{
		m_pHumidityLine->ClearSerie();
		LeftShiftArray(m_curHumidity, m_xCoordinateLen, 75 + rand() % 4);
		m_pHumidityLine->AddPoints(m_xCoordinate, m_curHumidity, m_xCoordinateLen);

	}
	CPropertyPage::OnTimer(nIDEvent);
}

//左移数组
void CPropertyGraphic::LeftShiftArray(double *arr, int len, int val)
{
	for (int i = 1; i < len; i++)
		arr[i - 1] = arr[i];
	arr[len - 1] = val;
}