//AboutMenu.cpp

#include "AboutMenu.h"
#include "LastClass.h"

BEGIN_MESSAGE_MAP(AboutMenu, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
END_MESSAGE_MAP()
AboutMenu::AboutMenu(LastClass *lastClass) {
	this->lastClass = lastClass;
}
int AboutMenu::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	this->lastClass->EnableWindow(FALSE);

	CRect rt;
	this->GetClientRect(&rt);
	this->OnSetFocus(this);

	int sysX = GetSystemMetrics(SM_CXSCREEN);
	int sysY = GetSystemMetrics(SM_CYSCREEN);

	this->SetWindowPos(&wndTop, (sysX - 822) / 2, (sysY - 634) / 2, 818, 624, SWP_NOZORDER);
	return 0;
}
void AboutMenu::OnPaint() {
	CPaintDC dc(this);

	CDC memDC;
	//HBITMAP pOldBitmap;
	HBITMAP bitmap;
	BITMAP bit;
	CRect rt;
	GetClientRect(&rt);
	memDC.CreateCompatibleDC(&dc);
	bitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), "About.bmp", IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (bitmap != NULL) {
		::SelectObject(memDC.m_hDC, bitmap);
		GetObject(bitmap, sizeof(BITMAP), &bit);

		dc.BitBlt(0, 0, bit.bmWidth, bit.bmHeight, &memDC, 0, 0, SRCCOPY);

		DeleteObject(bitmap);
	}
	memDC.DeleteDC();
}

void AboutMenu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_ESCAPE) {
		this->lastClass->EnableWindow(TRUE);

		if (this != 0) {
			delete this;
		}
	}
}

void AboutMenu::OnClose() {
	this->lastClass->EnableWindow(TRUE);

	if (this != 0) {
		delete this;
	}
}