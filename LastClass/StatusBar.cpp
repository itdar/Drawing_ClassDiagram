
#include "StatusBar.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Diagram.h"

StatusBar::StatusBar() {
	this->hStatus = 0;
}

StatusBar::StatusBar(const StatusBar& source) {
}

StatusBar::~StatusBar() {
}

HWND StatusBar::MakeStatusBar(LastClass *lastClass, HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts) {
	HWND hwndStatus;
	RECT rcClient;
	HLOCAL hloc;
	PINT paParts;
	int i, nWidth;

	// Ensure that the common control DLL is loaded.
	InitCommonControls();

	// Create the status bar.
	Long tempZoomRate1 = lastClass->classDiagramForm->zoomRate;
	CString mainString;
	if (tempZoomRate1 == 100) {
		mainString = " Draw ClassDiagram!!!  Version 2.27     Learn more about Software in ParkCom 02)587-9424";
	}
	else {
		mainString = " Draw ClassDiagram!!!  Version 2.27     Learn more about Software in ParkCom 02)587-9424";
	}
	hwndStatus = CreateWindowEx(
		WS_EX_APPWINDOW  | WS_EX_WINDOWEDGE | CCS_NORESIZE,   // no extended styles
		STATUSCLASSNAME,         // name of status bar class
		(LPCTSTR)mainString,           // no text when first created
		//SBARS_SIZEGRIP |         // includes a sizing grip
		WS_CHILD | WS_VISIBLE,   // creates a visible child window
		0, 614, 1361, 635,              // ignores size and position
		hwndParent,              // handle to parent window
		(HMENU)idStatus,		 // child window identifier
		hinst,                   // handle to application instance
		NULL);                   // no window creation data

								 // Get the coordinates of the parent window's client area.
	lastClass->GetClientRect(&rcClient);

	// Allocate an array for holding the right edge coordinates.
	hloc = LocalAlloc(LHND, sizeof(int) * cParts - 10);
	paParts = (PINT)LocalLock(hloc);

	// Calculate the right edge coordinate for each part, and
	// copy the coordinates to the array.
	nWidth = rcClient.right / cParts;
	paParts[0] = nWidth * 3;
	int rightEdge = nWidth * 3 + nWidth/2;
	for (i = 1; i < cParts; i++) {
		paParts[i] = rightEdge;
		rightEdge += nWidth/2;
	}

	// Tell the status bar to create the window parts.
	//언제 lastClass , 다시 그리거나 각각 따로 다시 호출해주거나 할지 정해야함
	SendMessage(hwndStatus, SB_SETPARTS, (WPARAM)cParts, (LPARAM)paParts);
	if (lastClass->classDiagramForm->capsLockFlag == 0) {
		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)1, (LPARAM)" CapsLock Off ");
	}
	else {
		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)1, (LPARAM)" CapsLock On ");
	}
	if (lastClass->classDiagramForm->numLockFlag == 0) {
		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)2, (LPARAM)" NumLock On ");
	}
	else {
		SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)2, (LPARAM)" NumLock Off ");
	}
	int a;
	//확대 축소 기능 form 에 넣을거면 주석 풀면됨
	Long tempZoomRate2 = lastClass->classDiagramForm->zoomRate;
	a = tempZoomRate2;
	CString tempString;
	tempString.Format(" ZoomRate : %d ", tempZoomRate2);
	SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)3, (LPARAM)(LPCTSTR)tempString);

	Long tempLength = lastClass->classDiagramForm->diagram->GetLength();
	a = tempLength;
	CString tempString2;
	tempString2.Format(" Obj : %d", tempLength);
	SendMessage(hwndStatus, SB_SETTEXT, (WPARAM)4, (LPARAM)(LPCTSTR)tempString2);

	// Free the array, and return.
	LocalUnlock(hloc);
	LocalFree(hloc);

	CRect rect1;
	lastClass->GetClientRect(&rect1);
	rect1.top = rect1.bottom - 20;
	rect1.left += 250;
	lastClass->InvalidateRect(rect1);

	this->hStatus = hwndStatus;

	return hwndStatus;
}

void StatusBar::ChangeStatusBarSize(RECT *rect) {
	CWnd *cwnd = CWnd::FromHandle(this->hStatus);
	cwnd->SetWindowPos(cwnd, 0, rect->bottom-21, rect->right, rect->bottom, SWP_NOMOVE | SWP_NOZORDER);
}

void StatusBar::DestroyStatus() {
	DestroyWindow(this->hStatus);
	this->hStatus = 0;
}