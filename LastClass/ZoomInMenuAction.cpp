//ZoomInMenuAction.cpp

#include "ZoomInMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "StatusBar.h"
#include "KnockKnock.h"
#include "ResizeVisitor.h"
#include "Diagram.h"
#include "ScrollMovingObject.h"

ZoomInMenuAction::ZoomInMenuAction() {
}
ZoomInMenuAction::ZoomInMenuAction(const ZoomInMenuAction& source) {
}
ZoomInMenuAction::~ZoomInMenuAction() {
}

void ZoomInMenuAction::MenuPress(LastClass *lastClass) {
	lastClass->classDiagramForm->SetFocus();
	bool ret = false;
	Long zoomRate_ = lastClass->classDiagramForm->zoomRate;
	// nWheelScrollLines 휠 한번에 이동하는 줄 수 (Reg에서 읽어 온다)
	HKEY hKey = 0;
	DWORD dwType = REG_BINARY;
	DWORD dwSize = 10;
	BYTE* pByte = new BYTE[dwSize];

	ZeroMemory(pByte, dwSize);

	RegOpenKey(HKEY_CURRENT_USER, "Control Panel\\Desktop", &hKey);
	RegQueryValueEx(hKey, "WheelScrollLines", NULL, &dwType, pByte, &dwSize);
	RegCloseKey(hKey);

	int nWheelScrollLines = atoi((char*)pByte);
	delete pByte;

	int vertCurPos = lastClass->classDiagramForm->GetScrollPos(SB_VERT);
	if (lastClass->classDiagramForm->selection->GetLength() > 0) {
		lastClass->classDiagramForm->selection->DeleteAllItems();
	}
	Long nextZoomRate;
	lastClass->classDiagramForm->preZoom = lastClass->classDiagramForm->zoomRate;

	
	lastClass->classDiagramForm->zoomRate += 10;
	if (lastClass->classDiagramForm->zoomRate > 130) {
		lastClass->classDiagramForm->zoomRate = 130;
	}
	nextZoomRate = lastClass->classDiagramForm->zoomRate;

	lastClass->classDiagramForm->SetMemoGab(20 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetGabX(8 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetGabY(2 * lastClass->classDiagramForm->zoomRate / 100);
	lastClass->classDiagramForm->SetCaretWidth(2 * lastClass->classDiagramForm->zoomRate / 100);

	lastClass->classDiagramForm->thirty = lastClass->classDiagramForm->thirty*lastClass->classDiagramForm->zoomRate / lastClass->classDiagramForm->preZoom;
	lastClass->classDiagramForm->seventeen = lastClass->classDiagramForm->seventeen*lastClass->classDiagramForm->zoomRate / lastClass->classDiagramForm->preZoom;

	SCROLLINFO vScinfo;
	SCROLLINFO hScinfo;
	ScrollMovingObject moving;
	lastClass->classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
	lastClass->classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
	CRect rect;
	lastClass->classDiagramForm->GetClientRect(&rect);

	moving.MovingObject(lastClass->classDiagramForm->diagram, hScinfo.nPos, vScinfo.nPos);
	vScinfo.nPage = rect.Height();
	hScinfo.nPage = rect.Width();

	vScinfo.nMax = vScinfo.nMax * lastClass->classDiagramForm->zoomRate / lastClass->classDiagramForm->preZoom;
	hScinfo.nMax = hScinfo.nMax * lastClass->classDiagramForm->zoomRate / lastClass->classDiagramForm->preZoom;

	if (vScinfo.nPos > vScinfo.nMax - vScinfo.nPage) {
		vScinfo.nPos = vScinfo.nMax - vScinfo.nPage;
	}
	if (hScinfo.nPos > hScinfo.nMax - hScinfo.nPage) {
		hScinfo.nPos = hScinfo.nMax - hScinfo.nPage;
	}
	lastClass->classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
	lastClass->classDiagramForm->SetScrollInfo(SB_HORZ, &hScinfo);

	CDC memDC;
	ResizeVisitor resizeVisitor(lastClass->classDiagramForm->preZoom, nextZoomRate);
	lastClass->classDiagramForm->diagram->Accept(resizeVisitor, &memDC);

	if (lastClass->classDiagramForm->copyBuffer != NULL) {
		lastClass->classDiagramForm->copyBuffer->Accept(resizeVisitor, &memDC);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	KnockKnock *knocking = new KnockKnock;
	knocking->Knocking(lastClass->classDiagramForm);
	if (knocking != NULL) {
		delete knocking;
	}
	moving.MovingObject(lastClass->classDiagramForm->diagram, -hScinfo.nPos, -vScinfo.nPos);
	if ((zoomRate_ != 60 || lastClass->classDiagramForm->zoomRate != 60) && (zoomRate_ != 130 || lastClass->classDiagramForm->zoomRate != 130)) {
		lastClass->statusBar->DestroyStatus();
		lastClass->statusBar->MakeStatusBar(lastClass, lastClass->GetSafeHwnd(), 0, 0, 5);
	}
	ret = true;

	lastClass->classDiagramForm->SetScrollPos(SB_VERT, vertCurPos);
	lastClass->classDiagramForm->Invalidate(false);

}