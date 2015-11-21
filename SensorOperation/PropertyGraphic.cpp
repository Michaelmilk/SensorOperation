// PropertyGraphic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SensorOperation.h"
#include "PropertyGraphic.h"
#include "afxdialogex.h"


// CPropertyGraphic �Ի���

IMPLEMENT_DYNAMIC(CPropertyGraphic, CPropertyPage)

CPropertyGraphic::CPropertyGraphic()
	: CPropertyPage(CPropertyGraphic::IDD)
{
	m_xCoordinateLen = COORDINATELEN;
	//����ʼֵ����Ϊ0
	ZeroMemory(&m_curTemperature, sizeof(double)*m_xCoordinateLen);
	ZeroMemory(&m_curHumidity, sizeof(double)*m_xCoordinateLen);

	//��ʼ���ײ��������ֵ
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


// CPropertyGraphic ��Ϣ�������

void CPropertyGraphic::InitHSChartCtrl()
{
	//����ؼ��б�ǩ��ʾ
	m_HSChartCtrl.GetLegend()->SetVisible(true);
	m_HSChartCtrl.GetLegend()->SetHorizontalMode(true);
	m_HSChartCtrl.GetLegend()->UndockLegend(30, 20);
	m_HSChartCtrl.GetLegend()->SetFont(80, _T("Microsoft Sans Serif"));

	//��ȡͼƬ�ؼ���rect����
	CRect picCtlRect;
	m_curvePicCtl.GetWindowRect(picCtlRect);
	ScreenToClient(picCtlRect);


	//��ͼƬ�ؼ������򴴽���ͼ�ؼ�
	m_HSChartCtrl.Create(this, picCtlRect, 1);
	//�����ײ�����
	CChartStandardAxis* pBottomAxis =
		m_HSChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	pBottomAxis->SetMinMax(-20, 0);//���귶ΧΪ1-10
	pBottomAxis->SetTickIncrement(false, 1.0);//������Ϊ1

	//������ߵ�����
	CChartStandardAxis* pLeftAxis =
		m_HSChartCtrl.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetMinMax(0, 90);//���귶ΧΪ0-90
	pLeftAxis->SetTickIncrement(false, 5.0);//������Ϊ5

	//�����ұߵ�����
	CChartStandardAxis* pRightAxis =
		m_HSChartCtrl.CreateStandardAxis(CChartCtrl::RightAxis);
	pRightAxis->SetMinMax(0, 90);//���귶ΧΪ0-90
	pRightAxis->SetTickIncrement(false, 5.0);//������Ϊ5

	m_pTemperatureLine = m_HSChartCtrl.CreateLineSerie();//���������¶�ʵʱ���ߵĶ���
	m_pHumidityLine = m_HSChartCtrl.CreateLineSerie();//��������ʪ��ʵʱ���ߵĶ���
	COLORREF SerieColorGreen = RGB(0, 255, 0);//����ʵʱ���ߵ���ɫ��ɫ��Ĭ����ɫΪ��ɫ
	COLORREF SerieColorBlue = RGB(0, 0, 255);//����ʵʱ���ߵ���ɫ��ɫ��Ĭ����ɫΪ��ɫ
	m_pTemperatureLine->SetColor(SerieColorGreen);//�����¶�ʵʱ����Ϊ��ɫ
	m_pHumidityLine->SetColor(SerieColorBlue);//����ʪ��ʵʱ���ߵ���ɫΪ��ɫ
	m_pTemperatureLine->SetName(_T("Temperature"));//��ʾ�¶ȱ�ǩ
	m_pHumidityLine->SetName(_T("Humidity"));//��ʾʪ�ȱ�ǩ
	
	UpdateData(FALSE);
}

BOOL CPropertyGraphic::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ʼ����ͼ�ؼ�
	InitHSChartCtrl();
	
	SetTimer(2, 1000, NULL);
	SetTimer(3, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


HBRUSH CPropertyGraphic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_DLG)
	{
		hbr = CreateSolidBrush(RGB(240, 240, 240));
		return hbr;
	}

	switch (pWnd->GetDlgCtrlID())
	{
		//���IDΪIDC_CTL1��IDC_CTL2��IDC_CTL3�Ŀؼ�����ͬ��������  
		case IDC_STATIC_HUMIDITY:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(255, 0, 0));   //����ɫ����Ϊ��ɫ  
			return (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);
		}
		case IDC_STATIC_TRMPERATURE:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(0, 255, 0));   //����ɫ����Ϊ��ɫ  
			return (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);
		}
		default:
			return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CPropertyGraphic::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//��ʱ�����¶�ʵʱ����
	if (2 == nIDEvent)
	{
		m_pTemperatureLine->ClearSerie();
		LeftShiftArray(m_curTemperature, m_xCoordinateLen, 20 + rand() % 2);
		m_pTemperatureLine->AddPoints(m_xCoordinate, m_curTemperature, m_xCoordinateLen);

	}

	//��ʱ����ʪ��ʵʱ����
	if (3 == nIDEvent)
	{
		m_pHumidityLine->ClearSerie();
		LeftShiftArray(m_curHumidity, m_xCoordinateLen, 75 + rand() % 4);
		m_pHumidityLine->AddPoints(m_xCoordinate, m_curHumidity, m_xCoordinateLen);

	}
	CPropertyPage::OnTimer(nIDEvent);
}

//��������
void CPropertyGraphic::LeftShiftArray(double *arr, int len, int val)
{
	for (int i = 1; i < len; i++)
		arr[i - 1] = arr[i];
	arr[len - 1] = val;
}