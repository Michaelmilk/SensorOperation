
// SensorOperationDlg.h : ͷ�ļ�
//

#pragma once
#include "PropertyGraphic.h"

// CSensorOperationDlg �Ի���
class CSensorOperationDlg : public CDialogEx
{
// ����
public:
	CSensorOperationDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SENSOROPERATION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CPropertySheet m_propertySheet;//����ҳ��sheet
	CPropertyGraphic m_graphicPage;//ʵʱ��������ҳ
};
