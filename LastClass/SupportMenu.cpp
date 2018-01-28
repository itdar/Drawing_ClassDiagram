//SupportMenu.cpp

#include "SupportMenu.h"
#include "LastClass.h"

BEGIN_MESSAGE_MAP(SupportMenu, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(1, OnpreviousButton)
	ON_BN_CLICKED(2, OnNextButton)
	ON_BN_CLICKED(3, OnOkButton)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
SupportMenu::SupportMenu(LastClass *lastClass) {
	this->lastClass = lastClass;
	this->page = 1;
	this->menualCount = 5;
}
int SupportMenu::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	this->lastClass->EnableWindow(FALSE);

	CRect rt;
	this->GetClientRect(&rt);
	this->OnSetFocus(this);

	int sysX = GetSystemMetrics(SM_CXSCREEN);
	int sysY = GetSystemMetrics(SM_CYSCREEN);

	this->SetWindowPos(&wndTop, (sysX - 1046) / 2, (sysY - 648) / 2, 1046, 648, SWP_NOZORDER);

	this->GetClientRect(&rt);
	CPoint point = rt.CenterPoint();
	
	this->nextButton = new CButton;
	this->nextButton->Create("¡ç", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER,
		CRect(point.x - 100, rt.bottom - 45, point.x - 40, rt.bottom - 5), this, 1);
	this->previousButton = new CButton;
	this->previousButton->Create("¡æ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER,
		CRect(point.x + 40, rt.bottom - 45, point.x + 100, rt.bottom - 5), this, 2);
	this->okButton = new CButton;
	this->okButton->Create("È®ÀÎ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER | BS_VCENTER,
		CRect(rt.right - 100, rt.bottom - 45, rt.right - 5, rt.bottom - 5), this, 3);
	return 0;
}
void SupportMenu::OnPaint() {
	CPaintDC dc(this);

	CDC memDC;
	//HBITMAP pOldBitmap;
	HBITMAP bitmap;
	BITMAP bit;
	CRect rt;
	GetClientRect(&rt);
	memDC.CreateCompatibleDC(&dc);
	CString menualPage;
	menualPage.Format("Menual_%d.bmp", this->page);
	bitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), menualPage, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (bitmap != NULL) {
		::SelectObject(memDC.m_hDC, bitmap);
		GetObject(bitmap, sizeof(BITMAP), &bit);

		dc.BitBlt(0, 0, bit.bmWidth, bit.bmHeight, &memDC, 0, 0, SRCCOPY);

		DeleteObject(bitmap);
	}
	memDC.DeleteDC();

	CPoint point = rt.CenterPoint();

	dc.SetTextAlign(TA_CENTER);
	dc.SetBkColor(RGB(255, 255, 255));
	dc.SetBkMode(OPAQUE);
	CString pagePage;
	pagePage.Format("%d  /  %d", this->page, this->menualCount);
	dc.TextOut(point.x, rt.bottom - 35, pagePage);
}

void SupportMenu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_ESCAPE) {
		this->lastClass->EnableWindow(TRUE);

		if (this->nextButton != 0) {
			delete this->nextButton;
		}
		if (this->previousButton != 0) {
			delete this->previousButton;
		}
		if (this->okButton != 0) {
			delete this->okButton;
		}
		if (this != 0) {
			delete this;
		}
	}
}

void SupportMenu::OnNextButton() {
	if (this->page < this->menualCount) {
		this->page += 1;
		Invalidate(false);
	}
}
void SupportMenu::OnpreviousButton() {
	if (this->page > 1) {
		this->page -= 1;
		Invalidate(false);
	}
}

void SupportMenu::OnOkButton() {
	this->lastClass->EnableWindow(TRUE);

	Invalidate(false);
	if (this->nextButton != 0) {
		delete this->nextButton;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
	}
	if (this->okButton != 0) {
		delete this->okButton;
	}
	if (this != 0) {
		delete this;
	}
}

void SupportMenu::OnClose() {
	this->lastClass->EnableWindow(TRUE);

	if (this->nextButton != 0) {
		delete this->nextButton;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
	}
	if (this->okButton != 0) {
		delete this->okButton;
	}
	if (this != 0) {
		delete this;
	}
}