//PrintPreview.h
#ifndef _PRINTPREVIEW_H
#define _PRINTPREVIEW_H

#include <afxwin.h>
#include <afxpriv.h>
typedef signed long int Long;

class LastClass;
class PrintPreviewButton;
class PrintPreview : public CFrameWnd {
public:
	PrintPreview(LastClass *lastClass);
	void OnPrint(CDC *cdc , CPrintInfo *pInfo, UINT page);
	void OnEndPrinting(CDC *pDc, CPrintInfo *pInfo);
	void OnBeginPrinting(CDC *pDc, CPrintInfo *pInfo);	
	BOOL DoModal();
	LastClass *lastClass;
	//void OnInitialUpdate();
	afx_msg void OnClose();

private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDraw(CDC *cdc ) ;
	//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnCommandButton(UINT parm_control_id);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

private:
	PrintPreviewButton *printPreviewButton;
	CButton *nextButton;
	CButton *previousButton;
	CButton *printButton;
	CButton *printZoomIn;
	CButton *printZoomOut;
public:
	Long horizontalPage;
	Long verticalPage;
	Long horizontalPageSize;
	Long verticalPageSize;
	Long zoomRate;
	Long horizontalPaperSize;
	Long verticalPaperSize;
	Long totalPage;
	Long classDaigramFormZoomRate;
	int hScrollMax;
	int vScrollMax;
};
#endif // !_PRINTPREVIEW_H
