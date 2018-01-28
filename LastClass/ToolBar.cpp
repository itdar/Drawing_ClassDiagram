//ToolBar.cpp

#include "ToolBar.h"
#include "resource.h"
#include "ToolBarProcess.h"

ToolBar::ToolBar() {
	this->hTool1 = 0;
	this->hTool2 = 0;
}
ToolBar::ToolBar(const ToolBar& source) {
}
ToolBar::~ToolBar() {
}
void ToolBar::MakeToolBar(HWND hWndParent) {
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | TBSTYLE_FLAT | WS_VISIBLE | CCS_NORESIZE | WS_BORDER | TBSTYLE_TRANSPARENT, 0, 0, 1361, 55,
		hWndParent, NULL, GetModuleHandle(NULL), NULL);
	this->hTool1 = hTool;
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	TBBUTTON tbb[28];
	//TBADDBITMAP tbab;
	Long iNew, iopen, iSave, iredo, iundo, idelete_, icut, icopy, ipaste, iprint, iprintpre, ihelp,izoomIn,izoomout;
	TCHAR newfile[10] = "새파일";
	TCHAR open[10] = "열기";
	TCHAR save[10] = "저장하기";
	TCHAR redo[10] = "재실행";
	TCHAR undo[10] = "되돌리기";
	TCHAR delete_[10] = "지우기";
	TCHAR cut[10] = "자르기";
	TCHAR copy[10] = "복사하기";
	TCHAR paste[10] = "붙여넣기";
	TCHAR print[10] = "인쇄하기";
	TCHAR printpre[10] = "미리보기";
	TCHAR help[10] = "도움말";
	TCHAR zoomIn[10] = "확대하기";
	TCHAR zoomout[10] = "축소하기";

	//tbab.hInst = HINST_COMMCTRL;
	//tbab.nID = IDB_STD_SMALL_COLOR;
	//SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);
	iNew = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)newfile);
	iopen = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)open);
	iSave = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)save);
	iredo = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)redo);
	iundo = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)undo);
	idelete_ = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)delete_);
	icut = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)cut);
	icopy = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)copy);
	ipaste = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)paste);
	iprint = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)print);
	iprintpre = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)printpre);
	ihelp = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)help);
	izoomIn = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)zoomIn);
	izoomout = SendMessage(hTool, TB_ADDSTRING,
		(WPARAM)NULL, (LPARAM)zoomout);
	SendMessage(hTool, TB_SETBUTTONSIZE, 0, MAKELPARAM(32, 28));
	SendMessage(hTool, TB_SETBITMAPSIZE, 0, (LPARAM)MAKELPARAM(32, 28));
	DWORD backgroundColor = GetSysColor(COLOR_BTNFACE);///여기부터
	COLORMAP colorMap;
	colorMap.from = RGB(255, 255, 255);
	colorMap.to = backgroundColor;
	HBITMAP hbm = CreateMappedBitmap(NULL, IDB_FILE, 0, &colorMap, 1);
	TBADDBITMAP tb;
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	int index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = index;
	tbb[0].fsState = TBSTATE_ENABLED;
	tbb[0].fsStyle = TBSTYLE_BUTTON ;
	tbb[0].idCommand = ID_BUTTON40001;
	tbb[0].iString = iNew;
	tbb[1].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_OPEN_, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[2].iBitmap = index;
	tbb[2].fsState = TBSTATE_ENABLED;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_BUTTON40002;
	tbb[2].iString = iopen;
	tbb[3].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_SAVE, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[4].iBitmap = index;
	tbb[4].fsState = TBSTATE_ENABLED;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	tbb[4].idCommand = ID_BUTTON40003;
	tbb[4].iString = iSave;
	tbb[5].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_UNDO, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[6].iBitmap = index;
	tbb[6].fsState = TBSTATE_ENABLED;
	tbb[6].fsStyle = TBSTYLE_BUTTON;
	tbb[6].idCommand = ID_BUTTON40005;
	tbb[6].iString = iundo;
	tbb[7].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_REDO, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[8].iBitmap = index;
	tbb[8].fsState = TBSTATE_ENABLED;
	tbb[8].fsStyle = TBSTYLE_BUTTON;
	tbb[8].idCommand = ID_BUTTON40006;
	tbb[8].iString = iredo;
	tbb[9].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_DELETE, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[10].iBitmap = index;
	tbb[10].fsState = TBSTATE_ENABLED;
	tbb[10].fsStyle = TBSTYLE_BUTTON;
	tbb[10].idCommand = ID_BUTTON40007;
	tbb[10].iString = idelete_;
	tbb[11].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_CUT, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[12].iBitmap = index;
	tbb[12].fsState = TBSTATE_ENABLED;
	tbb[12].fsStyle = TBSTYLE_BUTTON;
	tbb[12].idCommand = ID_BUTTON40008;
	tbb[12].iString = icut;
	tbb[13].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_COPY, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[14].iBitmap = index;
	tbb[14].fsState = TBSTATE_ENABLED;
	tbb[14].fsStyle = TBSTYLE_BUTTON;
	tbb[14].idCommand = ID_BUTTON40009;
	tbb[14].iString = icopy;
	tbb[15].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_PASTE, 0, &colorMap, 1);//붙여넣기
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[16].iBitmap = index;
	tbb[16].fsState = TBSTATE_ENABLED;
	tbb[16].fsStyle = TBSTYLE_BUTTON;
	tbb[16].idCommand = ID_BUTTON40010;
	tbb[16].iString = ipaste;
	tbb[17].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_PRINT, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[22].iBitmap = index;
	tbb[22].fsState = TBSTATE_ENABLED;
	tbb[22].fsStyle = TBSTYLE_BUTTON;
	tbb[22].idCommand = ID_BUTTON40011;
	tbb[22].iString = iprint;
	tbb[23].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_PRINTPRE, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[24].iBitmap = index;
	tbb[24].fsState = TBSTATE_ENABLED;
	tbb[24].fsStyle = TBSTYLE_BUTTON;
	tbb[24].idCommand = ID_BUTTON40012;
	tbb[24].iString = iprintpre;
	tbb[25].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_SUPPORT, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[26].iBitmap = index;
	tbb[26].fsState = TBSTATE_ENABLED;
	tbb[26].fsStyle = TBSTYLE_BUTTON;
	tbb[26].idCommand = ID_BUTTON40013;
	tbb[26].iString = ihelp;
	tbb[27].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_ZOOMIN, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[18].iBitmap = index;
	tbb[18].fsState = TBSTATE_ENABLED;
	tbb[18].fsStyle = TBSTYLE_BUTTON;
	tbb[18].idCommand = ID_BUTTON40029;
	tbb[18].iString = izoomIn;
	tbb[19].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	hbm = CreateMappedBitmap(NULL, IDB_ZOOMOUT, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[20].iBitmap = index;
	tbb[20].fsState = TBSTATE_ENABLED;
	tbb[20].fsStyle = TBSTYLE_BUTTON;
	tbb[20].idCommand = ID_BUTTON40030;
	tbb[20].iString = izoomout;
	tbb[21].fsStyle = TBSTYLE_BUTTON | BTNS_SEP;

	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)tbb);
}
void ToolBar::MakeAnotherToolBar(HWND hWndParent) {
	InitCommonControls();
	HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | TBSTYLE_FLAT| TBSTYLE_TRANSPARENT | WS_VISIBLE | CCS_VERT  |CCS_NORESIZE | WS_BORDER, 0, 56, 60, 591,
		hWndParent, NULL, GetModuleHandle(NULL), NULL);
	
	this->hTool2 = hTool;
	SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	//DWORD dwExStyle = TBSTYLE_EX_DRAWDDARROWS;
	//SendMessage(hTool, TB_SETEXTENDEDSTYLE, 0, (LPARAM)dwExStyle);
	TBBUTTON tbb[12];
	SendMessage(hTool, TB_SETBUTTONSIZE, 0, MAKELPARAM(48, 43));
	SendMessage(hTool, TB_SETBITMAPSIZE, 0, (LPARAM)MAKELPARAM(48, 43));
	DWORD backgroundColor = GetSysColor(COLOR_BTNFACE);///여기부터
	COLORMAP colorMap;
	colorMap.from = RGB(255, 255, 255);
	colorMap.to = backgroundColor;
	HBITMAP hbm = CreateMappedBitmap(NULL, IDB_CLASS, 0, &colorMap, 1);
	TBADDBITMAP tb;
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	int index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	ZeroMemory(tbb, sizeof(tbb));
	tbb[0].iBitmap = index;
	tbb[0].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[0].fsStyle = TBSTYLE_BUTTON;
	tbb[0].idCommand = ID_BUTTON40017;
	hbm = CreateMappedBitmap(NULL, IDB_MEMOBOX, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[1].iBitmap = index;
	tbb[1].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[1].fsStyle = TBSTYLE_BUTTON;
	tbb[1].idCommand = ID_BUTTON40018;
	hbm = CreateMappedBitmap(NULL, IDB_GENERALIZATION, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[2].iBitmap = index;
	tbb[2].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[2].fsStyle = TBSTYLE_BUTTON;
	tbb[2].idCommand = ID_BUTTON40019;
	hbm = CreateMappedBitmap(NULL, IDB_REALIZATION, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[3].iBitmap = index;
	tbb[3].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[3].fsStyle = TBSTYLE_BUTTON;
	tbb[3].idCommand = ID_BUTTON40020;
	hbm = CreateMappedBitmap(NULL, IDB_DEPENDENCY, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[4].iBitmap = index;
	tbb[4].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[4].fsStyle = TBSTYLE_BUTTON;
	tbb[4].idCommand = ID_BUTTON40021;
	hbm = CreateMappedBitmap(NULL, IDB_ASSOCIATION, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[5].iBitmap = index;
	tbb[5].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[5].fsStyle = TBSTYLE_BUTTON;
	tbb[5].idCommand = ID_BUTTON40022;
	hbm = CreateMappedBitmap(NULL, IDB_DIRECTEDASSOCIATION, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[6].iBitmap = index;
	tbb[6].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[6].fsStyle = TBSTYLE_BUTTON;
	tbb[6].idCommand = ID_BUTTON40023;
	hbm = CreateMappedBitmap(NULL, IDB_AGGREGATION, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[7].iBitmap = index;
	tbb[7].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[7].fsStyle = TBSTYLE_BUTTON;
	tbb[7].idCommand = ID_BUTTON40024;
	hbm = CreateMappedBitmap(NULL, IDB_AGGREGATIONS, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[8].iBitmap = index;
	tbb[8].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[8].fsStyle = TBSTYLE_BUTTON;
	tbb[8].idCommand = ID_BUTTON40025;
	hbm = CreateMappedBitmap(NULL, IDB_COMPOSITION, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[9].iBitmap = index;
	tbb[9].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[9].fsStyle = TBSTYLE_BUTTON;
	tbb[9].idCommand = ID_BUTTON40026;
	hbm = CreateMappedBitmap(NULL, IDB_COMPOSITIONS, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[10].iBitmap = index;
	tbb[10].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[10].fsStyle = TBSTYLE_BUTTON;
	tbb[10].idCommand = ID_BUTTON40027;
	hbm = CreateMappedBitmap(NULL, IDB_MEMOLINE, 0, &colorMap, 1);
	tb.hInst = NULL;
	tb.nID = (UINT_PTR)hbm;
	index = SendMessage(hTool, TB_ADDBITMAP, 1, (LPARAM)&tb);
	tbb[11].iBitmap = index;
	tbb[11].fsState = TBSTATE_ENABLED | TBSTATE_WRAP;
	tbb[11].fsStyle = TBSTYLE_BUTTON;
	tbb[11].idCommand = ID_BUTTON40028;
	SendMessage(hTool, TB_ADDBUTTONS, sizeof(tbb) / sizeof(TBBUTTON), (LPARAM)tbb);
	
}

void ToolBar::ButtonSelected(UINT parm_control_id, LastClass *lastClass, ClassDiagramForm *classDiagramForm, CDC *cdc) {
	ToolBarProcess toolBarProcess;
	switch (parm_control_id) {
	case  40002:toolBarProcess.OnOpenClicked(lastClass);
		break;
	case 40003:toolBarProcess.OnSaveFileClicked(lastClass);
		break;
	case 40004:toolBarProcess.OnNewFileClicked(lastClass);
		break;
	case 40005:toolBarProcess.OnUndoFileClicked(lastClass);
		break;
	case 40006:toolBarProcess.OnRedoFileClicked(lastClass);
		break;
	case 40007:toolBarProcess.OnFinishFileClicked(lastClass);
		break;
	case 40008:toolBarProcess.OnCutFileClicked(lastClass);
		break;
	case 40009:toolBarProcess.OnCopyFileClicked(lastClass);
		break;
	case 40010:toolBarProcess.OnPasteFileClicked(lastClass);
		break;
	case 40011:toolBarProcess.OnPrintFileClicked(lastClass);
		break;
	case 40012:toolBarProcess.OnPrintPreFileClicked(lastClass);
		break;
	case 40013:toolBarProcess.OnSupportFileClicked(lastClass);
		break;
	case  40017:toolBarProcess.OnClassClicked(lastClass);
		break;
	case 40018:toolBarProcess.OnMemoBoxClicked(lastClass);
		break;
	case 40019:toolBarProcess.OnGeneralizationClicked(lastClass);
		break;
	case 40020:toolBarProcess.OnRelizationClicked(lastClass);
		break;
	case 40021:toolBarProcess.OnDependencyClicked(lastClass);
		break;
	case 40022:toolBarProcess.OnAssociationClicked(lastClass);
		break;
	case 40023:toolBarProcess.OnDirectedAssociationClicked(lastClass);
		break;
	case 40024:toolBarProcess.OnAggregationClicked(lastClass);
		break;
	case 40025:toolBarProcess.OnAggregationsClicked(lastClass);
		break;
	case 40026:toolBarProcess.OnCompositionClicked(lastClass);
		break;
	case 40027:toolBarProcess.OnCompositionsClicked(lastClass);
		break;
	case 40028:toolBarProcess.OnMemoLineClicked(lastClass);
		break;
	case 40029:toolBarProcess.OnZoomInClicked(lastClass);
		break;
	case 40030:toolBarProcess.OnZoomOutClicked(lastClass);
		break;
	default:
		break;
	}
}

void ToolBar::ChangeToolBarSize(RECT *rect) {
	CWnd *cwnd = CWnd::FromHandle(this->hTool1);
	if (cwnd != NULL) {
		cwnd->SetWindowPos(cwnd, 0, 0, rect->right - 1, 55, SWP_NOMOVE | SWP_NOZORDER);
	}
}
void ToolBar::ChangeAnotherToolBarSize(RECT *rect) {
	CWnd *cwnd = CWnd::FromHandle(this->hTool2);
	if (cwnd != NULL) {
		cwnd->SetWindowPos(cwnd, 0, 56, 60, rect->bottom - 85, SWP_NOMOVE | SWP_NOZORDER);
	}
}

void ToolBar::DestroyToolBar() {
	if (this != NULL) {
		DestroyWindow(this->hTool1);
		DestroyWindow(this->hTool2);
		this->hTool1 = 0;
		this->hTool2 = 0;
	}
}