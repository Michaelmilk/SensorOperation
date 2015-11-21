#pragma once
#include "ChartClass\ChartCtrl.h"
#include "ChartClass\ChartLineSerie.h"
#include "ChartClass\ChartAxis.h"
#include "afxwin.h"

// CPropertyGraphic �Ի���
#define COORDINATELEN 21
class CPropertyGraphic : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyGraphic)

public:
	CPropertyGraphic();
	virtual ~CPropertyGraphic();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_GRAPHIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CChartCtrl m_HSChartCtrl;				//high speed ��ͼ�ؼ�����
	CChartLineSerie* m_pTemperatureLine;	//�����¶�ʵʱ���ߵĶ���
	CChartLineSerie* m_pHumidityLine;		//����ʪ��ʵʱ���ߵĶ���
	double m_curTemperature[COORDINATELEN];			//��������ǰ�¶ȵ�ֵ
	double m_curHumidity[COORDINATELEN];				//��������ǰʪ�ȵ�ֵ
	double m_xCoordinate[COORDINATELEN];				//��������ʮ�����ֵ
	int m_xCoordinateLen;					//������ĳ���
	CStatic m_curvePicCtl;					//ͼƬ�ؼ������ı���

	virtual BOOL OnInitDialog();
	void InitHSChartCtrl();				//��ʼ����ͼ�ؼ�
	void LeftShiftArray(double *arr, int len, int val);					//��������
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
