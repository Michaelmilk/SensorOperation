#pragma once
#include "ChartClass\ChartCtrl.h"
#include "ChartClass\ChartLineSerie.h"
#include "ChartClass\ChartAxis.h"
#include "afxwin.h"

// CPropertyGraphic 对话框
#define COORDINATELEN 21
class CPropertyGraphic : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropertyGraphic)

public:
	CPropertyGraphic();
	virtual ~CPropertyGraphic();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_GRAPHIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CChartCtrl m_HSChartCtrl;				//high speed 绘图控件对象
	CChartLineSerie* m_pTemperatureLine;	//绘制温度实时曲线的对象
	CChartLineSerie* m_pHumidityLine;		//绘制湿度实时曲线的对象
	double m_curTemperature[COORDINATELEN];			//传感器当前温度的值
	double m_curHumidity[COORDINATELEN];				//传感器当前湿度的值
	double m_xCoordinate[COORDINATELEN];				//横坐标有十个点的值
	int m_xCoordinateLen;					//横坐标的长度
	CStatic m_curvePicCtl;					//图片控件关联的变量

	virtual BOOL OnInitDialog();
	void InitHSChartCtrl();				//初始化绘图控件
	void LeftShiftArray(double *arr, int len, int val);					//左移数组
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
