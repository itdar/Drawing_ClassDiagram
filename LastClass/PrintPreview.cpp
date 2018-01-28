//PrintPreview.cpp

#include "PrintPreview.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Relation.h"
#include "DrawingVisitor.h"
#include "Diagram.h"
#include "Finder.h"
#include "PrintPreviewButton.h"
#include "PrintPreviewButtonAction.h"
#include "KnockKnock.h"
#include "ResizeVisitor.h"
#include "ScrollMovingObject.h"
//#include <afxwin.h>
//#include <afxdlgs.h>

BEGIN_MESSAGE_MAP(PrintPreview, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_COMMAND_RANGE(1, 5, OnCommandButton)
END_MESSAGE_MAP()

PrintPreview::PrintPreview(LastClass *lastClass) {
	this->lastClass = lastClass;
	this->printPreviewButton = NULL;

	this->nextButton = NULL;
	this->previousButton = NULL;
	this->printButton = NULL;
	this->printZoomIn = NULL;
	this->printZoomOut = NULL;

	this->horizontalPage = 0;
	this->verticalPage = 0;
	this->horizontalPageSize = 2000;
	this->verticalPageSize = 2000;
	this->horizontalPaperSize = 0;
	this->verticalPaperSize = 0;
	this->zoomRate = 100;
	this->totalPage=0;
	this->classDaigramFormZoomRate = 100;
}

int PrintPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	this->printPreviewButton = new PrintPreviewButton;

	this->ModifyStyle(0, WS_OVERLAPPEDWINDOW);
	this->nextButton = new CButton;
	this->nextButton->Create("다음 페이지", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(775, 10, 925, 50), this, 1);
	this->previousButton = new CButton;
	this->previousButton->Create("이전 페이지", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(420, 10, 570, 50), this, 2);
	this->printButton = new CButton;
	this->printButton->Create("인쇄하기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER, CRect(600, 10, 745, 50), this, 3);

	ScrollMovingObject scrollMovingObject;
	Long hPos = this->lastClass->classDiagramForm->GetScrollPos(SB_HORZ);
	Long vPos = this->lastClass->classDiagramForm->GetScrollPos(SB_VERT);
	int min;
	this->lastClass->classDiagramForm->GetScrollRange(SB_HORZ, &min, &this->hScrollMax);
	this->lastClass->classDiagramForm->GetScrollRange(SB_VERT, &min, &this->vScrollMax);
	scrollMovingObject.MovingObject(this->lastClass->classDiagramForm->diagram, hPos, vPos);

	this->classDaigramFormZoomRate = lastClass->classDiagramForm->zoomRate;
	ResizeVisitor visitor1(lastClass->classDiagramForm->zoomRate, 100);
	lastClass->classDiagramForm->zoomRate = 100;
	lastClass->classDiagramForm->SetMemoGab(20 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetGabX(8 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetGabY(2 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetCaretWidth(2 * lastClass->classDiagramForm->zoomRate / 100);
	CDC memDC;
	lastClass->classDiagramForm->diagram->Accept(visitor1, &memDC);

	KnockKnock *knocking = new KnockKnock;
	knocking->Knocking(lastClass->classDiagramForm);
	if (knocking != NULL) {
		delete knocking;
	}

	this->lastClass->EnableWindow(false);
	Long horizontalPageLimit = (scrollMovingObject.GetHorizontalMax(this->lastClass->classDiagramForm->diagram) / this->horizontalPageSize);
	this->horizontalPaperSize = horizontalPageLimit*this->horizontalPageSize;
	if (scrollMovingObject.GetHorizontalMax(this->lastClass->classDiagramForm->diagram) % this->horizontalPageSize != 0) {
		this->horizontalPaperSize += this->horizontalPageSize;
	}
	Long verticalPageLimit = (scrollMovingObject.GetVerticalMax(this->lastClass->classDiagramForm->diagram) / this->verticalPageSize);
	this->verticalPaperSize = verticalPageLimit*this->verticalPageSize;
	if (scrollMovingObject.GetVerticalMax(this->lastClass->classDiagramForm->diagram) % this->verticalPageSize != 0) {
		this->verticalPaperSize += this->verticalPageSize;
	}

	Invalidate(false);

	return 0;
}
void PrintPreview::OnPaint() {
	CPaintDC dc(this);
	CRect rec;
	this->GetClientRect(&rec);
	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	ScrollMovingObject scrollMovingObject;
	scrollMovingObject.MovingObject(lastClass->classDiagramForm->diagram, -(this->horizontalPage), -(this->verticalPage));

	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, this->horizontalPageSize, this->verticalPageSize);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, this->horizontalPageSize, this->verticalPageSize), RGB(255, 255, 255));
	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	int ih = MulDiv(14 * lastClass->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc, LOGPIXELSY), 72);
	cFont.CreateFont(ih, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);
	DrawingVisitor drawingVisitor(100);
	this->lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);

	Long a = (rec.CenterPoint().x) * 5 / 8;
	Long b = (rec.CenterPoint().y) * 1 / 6;
	Long c = (rec.CenterPoint().x) * 11 / 8 - (rec.CenterPoint().x) * 5 / 8;
	Long d = (rec.CenterPoint().y) * 11 / 6 - (rec.CenterPoint().y) * 1 / 6;

	CBitmap *pOldBitmapOne;
	CBitmap bitmapOne;
	CDC memDCOne;
	memDCOne.CreateCompatibleDC(&dc);
	bitmapOne.CreateCompatibleBitmap(&dc, rec.Width(), rec.Height());
	pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
	//회색바탕 준비
	memDCOne.FillSolidRect(rec, RGB(153, 153, 153));
	//회색바탕 전체화면으로 출력
	dc.BitBlt(0, 0, rec.Width(), rec.Height(), &memDCOne, 0, 0, SRCCOPY);


	//흰종이 출력
	memDCOne.StretchBlt(a, b, c, d, &memDC, 0, 0, this->horizontalPageSize, this->verticalPageSize, SRCCOPY);

	//회색바탕에 흰종이 같이 출력
	dc.BitBlt(0, 0, rec.Width(), rec.Height(), &memDCOne, 0, 0, SRCCOPY);

	memDC.SelectObject(oldFont);
	cFont.DeleteObject();
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
	memDCOne.SelectObject(pOldBitmap);
	bitmapOne.DeleteObject();
	memDCOne.DeleteDC();
	scrollMovingObject.MovingObject(lastClass->classDiagramForm->diagram, (this->horizontalPage), (this->verticalPage));
}
void PrintPreview::OnDraw(CDC *cdc) {

}
void PrintPreview::OnPrint(CDC *cdc, CPrintInfo *pInfo, UINT page) {
	ScrollMovingObject scrollMovingObject;
	Long verticalPageCount = scrollMovingObject.GetVerticalMax(this->lastClass->classDiagramForm->diagram) / this->verticalPageSize;
	if (scrollMovingObject.GetVerticalMax(this->lastClass->classDiagramForm->diagram) % this->verticalPageSize != 0) {
		verticalPageCount++;
	}

	Long currentPrintHorizontalPage = ((page - 1) / verticalPageCount)*this->horizontalPageSize;
	Long currentPrintVerticalPage = ((page - 1) % verticalPageCount)*this->verticalPageSize;
	scrollMovingObject.MovingObject(this->lastClass->classDiagramForm->diagram, -currentPrintHorizontalPage, -currentPrintVerticalPage);

	Long width = pInfo->m_rectDraw.Width();
	Long hegiht = pInfo->m_rectDraw.Height();
	CDC memDC;
	CRect rect;
	this->lastClass->classDiagramForm->GetClientRect(&rect);
	CBitmap *pOldBitmap;
	CBitmap bitmap;

	CPaintDC dc(this);

	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, this->horizontalPageSize, this->verticalPageSize);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, this->horizontalPageSize, this->verticalPageSize), RGB(255, 255, 255));
	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	int ih = MulDiv(14 * lastClass->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc, LOGPIXELSY), 72);
	cFont.CreateFont(ih, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);

	DrawingVisitor drawingVisitor(100);
	this->lastClass->classDiagramForm->diagram->Accept(drawingVisitor, &memDC);
	//WritingVisitor writingVisitor(100);
	//this->lastClass->classDiagramForm->diagram->Accept(writingVisitor, &memDC);


	CBitmap *pOldBitmapOne;
	CBitmap bitmapOne;
	CDC memDCOne;
	memDCOne.CreateCompatibleDC(&dc);
	bitmapOne.CreateCompatibleBitmap(&dc, this->horizontalPageSize, this->verticalPageSize);
	pOldBitmapOne = memDCOne.SelectObject(&bitmapOne);
	memDCOne.FillSolidRect(CRect(0, 0, this->horizontalPageSize, this->verticalPageSize), RGB(255, 255, 255));
	memDCOne.BitBlt(0, 0, this->horizontalPageSize, this->verticalPageSize, &memDC, 0, 0, SRCCOPY);

	int mapMode = cdc->GetMapMode();
	memDCOne.SetMapMode(mapMode);
	cdc->SetStretchBltMode(COLORONCOLOR);

	//cdc->SetMapMode(MM_ISOTROPIC);
	//cdc->SetWindowExt(100, 100);
	//cdc->SetViewportExt(this->zoomRate, this->zoomRate);

	cdc->StretchBlt(100, 100, width - 200, hegiht - 200, &memDCOne, 0, 0, this->horizontalPageSize, this->verticalPageSize, SRCCOPY);

	memDC.SelectObject(oldFont);
	cFont.DeleteObject();
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
	memDCOne.SelectObject(pOldBitmap);
	bitmapOne.DeleteObject();
	memDCOne.DeleteDC();
	scrollMovingObject.MovingObject(this->lastClass->classDiagramForm->diagram, currentPrintHorizontalPage, currentPrintVerticalPage);
}

BOOL PrintPreview::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	CFrameWnd::SetFocus();

	SetFocus();
	bool ret = false;

	// nWheelScrollLines 휠 한번에 이동하는 줄 수 (Reg에서 읽어 온다)
	HKEY hKey = 0;
	DWORD dwType = REG_BINARY;
	DWORD dwSize = 10;
	BYTE* pByte = new BYTE[dwSize];

	//ZeroMemory(pByte, dwSize);
	
	//RegOpenKey(HKEY_CURRENT_USER, "Control Panel\\Desktop", &hKey);
	//RegQueryValueEx(hKey, "WheelScrollLines", NULL, &dwType, pByte, &dwSize);
//	RegCloseKey(hKey);

	int nWheelScrollLines = atoi((char*)pByte);
	//delete pByte;

	//int vertCurPos = GetScrollPos(SB_VERT);

	if (GetKeyState(VK_CONTROL) >= 0) {
		if (zDelta <= 0) { //마우스 휠 다운
	//		vertCurPos += nWheelScrollLines * 20;
		}
		else {  //마우스 휠 업
	//		vertCurPos -= nWheelScrollLines * 20;
		}
		ret = true;
	}
	else {
		if (zDelta <= 0) { //마우스 휠 다운
			this->zoomRate += 10;
			this->verticalPageSize += 100;
			if (this->verticalPageSize > 3000) {
				this->verticalPageSize = 3000;
			}
			this->horizontalPageSize += 100;
			if (this->horizontalPageSize > 3000) {
				this->horizontalPageSize = 3000;
			}
			if (this->zoomRate < 50) {
				this->zoomRate = 50;
			}
		}
		else {  //마우스 휠 업
			this->zoomRate -= 10;
			this->verticalPageSize -= 100;
			if (this->verticalPageSize < 1000) {
				this->verticalPageSize = 1000;
			}
			this->horizontalPageSize -= 100;
			if (this->horizontalPageSize < 1000) {
				this->horizontalPageSize = 1000;
			}
			if (this->zoomRate > 190) {
				this->zoomRate = 190;
			}
		}
		ret = true;
	}
	//SetScrollPos(SB_VERT, vertCurPos);
	CRect rect(0, 0, this->horizontalPageSize, this->verticalPageSize);
	Long l = 0;
	Long m;
	Long n;
	Long k=1;
	Finder finder;
	Long length = lastClass->classDiagramForm->diagram->GetLength();
	this->totalPage = 0;
	while (this->horizontalPaperSize > rect.left ){
		rect.MoveToY(0);
		while (this->verticalPaperSize > rect.top) {
			ret = false;
			l = 0;
			while (l < length && ret != true) { // 2페이지에 클래스나 메모박스가 있는지 확인.
				FigureComposite *figureComposite = (FigureComposite*)lastClass->classDiagramForm->diagram->GetAt(l);
				CRect comperRect(figureComposite->GetX(), figureComposite->GetY(), figureComposite->GetX() + figureComposite->GetWidth(), figureComposite->GetY() + figureComposite->GetHeight());
				ret = finder.FindRectangleByArea(comperRect, rect);
				m = 0;
				while (m < figureComposite->GetLength() && ret != true) {
					Figure *figure = figureComposite->GetAt(m);
					ret = finder.FindRectangleByPoint(rect, figure->GetX(), figure->GetY());
					if (dynamic_cast<Relation*>(figure)) {
						Relation *relation = static_cast<Relation*>(figure);
						n = 0;
						while (n < relation->GetLength() && ret != true) {
							CPoint point1 = relation->GetAt(n);
							ret = finder.FindRectangleByPoint(rect, point1.x, point1.y);
							n++;
						}
					}
					m++;
				}
				l++;

			}
			if (ret == true) {
				this->totalPage = k;
			}
			k++;
			rect.MoveToY(rect.top + this->verticalPageSize);
		}
		rect.MoveToX(rect.left+this->horizontalPageSize);
	}
	if (GetKeyState(VK_CONTROL) < 0) {
		Invalidate(false);
	}

	return ret;
}
void PrintPreview::OnClose() {
	this->lastClass->EnableWindow(true);

	lastClass->classDiagramForm->zoomRate = this->classDaigramFormZoomRate;
	ResizeVisitor visitor2(100, lastClass->classDiagramForm->zoomRate);
	lastClass->classDiagramForm->SetMemoGab(20 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetGabX(8 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetGabY(2 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetCaretWidth(2 * lastClass->classDiagramForm->zoomRate / 100);
	CDC memDC;
	lastClass->classDiagramForm->diagram->Accept(visitor2, &memDC);
	KnockKnock *knocking = new KnockKnock;
	knocking->Knocking(lastClass->classDiagramForm);
	ScrollMovingObject scrollMovingObject;
	Long hPos = this->lastClass->classDiagramForm->GetScrollPos(SB_HORZ);
	Long vPos = this->lastClass->classDiagramForm->GetScrollPos(SB_VERT);

	scrollMovingObject.MovingObject(this->lastClass->classDiagramForm->diagram, -hPos, -vPos);

	this->lastClass->classDiagramForm->SetScrollRange(SB_HORZ, 0, this->hScrollMax);
	this->lastClass->classDiagramForm->SetScrollRange(SB_VERT, 0, this->vScrollMax);

	if (knocking != NULL) {
		delete knocking;
	}

	if (this->nextButton != 0) {
		delete this->nextButton;
		this->nextButton = NULL;
	}
	if (this->printButton != 0) {
		delete this->printButton;
		this->printButton = NULL;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
		this->previousButton = NULL;
	}
	if (this->printZoomIn != 0) {
		delete this->printZoomIn;
		this->printZoomIn = NULL;
	}
	if (this->printZoomOut != 0) {
		delete this->printZoomOut;
		this->printZoomOut = NULL;
	}
	if (this->lastClass->printPreview != NULL) {
		this->lastClass->printPreview = NULL;
	}
	if (this != NULL) {
		delete this;
	}
}

void PrintPreview::OnBeginPrinting(CDC *pDc, CPrintInfo *pInfo) {
	
}

void PrintPreview::OnEndPrinting(CDC *pDc, CPrintInfo *pInfo) {
	this->lastClass->EnableWindow(true);

	lastClass->classDiagramForm->zoomRate = this->classDaigramFormZoomRate;
	ResizeVisitor visitor2(100, lastClass->classDiagramForm->zoomRate);
	lastClass->classDiagramForm->SetMemoGab(20 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetGabX(8 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetGabY(2 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetCaretWidth(2 * lastClass->classDiagramForm->zoomRate / 100);
	CDC memDC;
	lastClass->classDiagramForm->diagram->Accept(visitor2, &memDC);
	KnockKnock *knocking = new KnockKnock;
	knocking->Knocking(lastClass->classDiagramForm);
	ScrollMovingObject scrollMovingObject;
	Long hPos = this->lastClass->classDiagramForm->GetScrollPos(SB_HORZ);
	Long vPos = this->lastClass->classDiagramForm->GetScrollPos(SB_VERT);
	scrollMovingObject.MovingObject(this->lastClass->classDiagramForm->diagram, -hPos, -vPos);

	this->lastClass->classDiagramForm->SetScrollRange(SB_HORZ, 0, this->hScrollMax);
	this->lastClass->classDiagramForm->SetScrollRange(SB_VERT, 0, this->vScrollMax);

	if (knocking != NULL) {
		delete knocking;
	}

	if (this->nextButton != 0) {
		delete this->nextButton;
		this->nextButton = NULL;
	}
	if (this->printButton != 0) {
		delete this->printButton;
		this->printButton = NULL;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
		this->previousButton = NULL;
	}
	if (this->printZoomIn != 0) {
		delete this->printZoomIn;
		this->printZoomIn = NULL;
	}
	if (this->printZoomOut != 0) {
		delete this->printZoomOut;
		this->printZoomOut = NULL;
	}
	if (this->lastClass->printPreview != NULL) {
		this->lastClass->printPreview = NULL;
	}
	if (this != NULL) {
		delete this;
	}
}

void PrintPreview::OnSize(UINT nType, int cx, int cy) {
	CRect rect;
	this->GetClientRect(&rect);
	this->printButton->MoveWindow(rect.CenterPoint().x*11/12, 10, rect.CenterPoint().x*2/12, 50);
	this->nextButton->MoveWindow(rect.CenterPoint().x*11/8- rect.CenterPoint().x * 2 / 12, 10, rect.CenterPoint().x * 2 / 12, 50);
	this->previousButton->MoveWindow(rect.CenterPoint().x *5/8, 10, rect.CenterPoint().x * 2 / 12, 50);
	Invalidate(false);
}
BOOL PrintPreview::DoModal() {
	if (this->GetParent()) {
		this->GetParent()->EnableWindow(FALSE);
		RunModalLoop(MLF_SHOWONIDLE);
		DestroyWindow();
	}
	return TRUE;
}

void PrintPreview::OnCommandButton(UINT idNumber) {
	PrintPreviewButtonAction *buttonPressed = this->printPreviewButton->ButtonPressed(idNumber);
	if (buttonPressed != 0) {
		buttonPressed->ButtonPress(this);
	}
}