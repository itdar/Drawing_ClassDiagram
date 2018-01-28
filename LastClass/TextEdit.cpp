//TextEdit.cpp

#include "LastClass.h"
#include "TextEdit.h"
#include "ClassDiagramForm.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Figure.h"
#include "Caret.h"
#include "KeyBoard.h"
#include "KeyAction.h"
#include "EndKey.h"
#include "TextAreaSelected.h"
#include "HistoryText.h"
#include "DrawingVisitor.h" 
#include "DeleteTextArea.h"
#include "WriteKoreanText.h"
#include "DoubleClickTextArea.h"
#include "FontSet.h"
#include "Selection.h"
#include "EditResizer.h"
#include "Class.h"
#include "Relation.h"
#include "Finder.h"
#include "SelfRelation.h"
#include "StatusBar.h"
#include "Template.h"

//#include <iostream>

BEGIN_MESSAGE_MAP(TextEdit, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_COMPOSITION, OnComposition)
	ON_WM_KILLFOCUS()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()

	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_IME_NOTIFY, OnIMENotify)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

TextEdit::TextEdit(ClassDiagramForm *classDiagramForm, Figure *figure, Long rollNameBoxIndex) {
	this->classDiagramForm = classDiagramForm;
	this->text = NULL;
	this->caret = NULL;
	this->keyBoard = NULL;
	this->historyText = NULL;
	this->textAreaSelected = NULL;
	this->fontSet = NULL;
	this->figure = figure;
	this->rollNameBoxIndex = rollNameBoxIndex;
	this->rowHeight = 14 * this->classDiagramForm->zoomRate / 100;// 폰트 사이즈
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
	this->flagInsert = 0;
	this->flagSelection = 0;
	this->currentX = 0;
	this->copyBuffer = "";
	this->criteriaWidth = figure->GetWidth();
	this->criteriaHeight = figure->GetHeight();
	this->criteriaX = figure->GetX();
	if (dynamic_cast<Template*>(figure)) {
		this->criteriaWidth = classDiagramForm->seventeen + 30 * classDiagramForm->zoomRate / 100;
		this->criteriaX = classDiagramForm->selection->GetAt(0)->GetX() + classDiagramForm->selection->GetAt(0)->GetWidth() - 30 * classDiagramForm->zoomRate / 100;
	}
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct); //override
	CWnd::SetFocus();

	CDC *pDC = this->GetDC();
	this->rowHeight = MulDiv(14 * this->classDiagramForm->zoomRate / 100, GetDeviceCaps(pDC->m_hDC, LOGPIXELSY), 72);// 폰트 사이즈

	this->text = new Text;
	this->caret = new Caret;
	this->keyBoard = new KeyBoard;
	this->historyText = new HistoryText;
	this->textAreaSelected = new TextAreaSelected;
	this->fontSet = new FontSet;

	if (this->rollNameBoxIndex == -1) {
		this->text->SprayString(this->figure->GetContent()); // 넘겨받아온거 자료구조로 뿌려줌 ㅇㅇㅇㅇㅇ
		this->figure->ReplaceString("", this->rowHeight);
	}
	else if (dynamic_cast<Relation*>(this->figure)) {
		this->text->SprayString(static_cast<Relation*>(this->figure)->rollNames->GetAt(this->rollNameBoxIndex));
	}
	else if (dynamic_cast<SelfRelation*>(this->figure)) {
		this->text->SprayString(static_cast<SelfRelation*>(this->figure)->rollNames->GetAt(this->rollNameBoxIndex));
	}

	Invalidate(false);
	return 0;
}

void TextEdit::OnPaint() {
	CWnd::SetFocus();
	CPaintDC dc(this);
	RECT rt;
	this->GetClientRect(&rt);
	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rt.right, rt.bottom);
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, rt.right, rt.bottom), RGB(255, 255, 255));
	DrawingVisitor drawingVisitor(this->classDiagramForm->zoomRate);
	CFont cFont;
	CFont *oldFont = 0;
	CFont *m_oldFont = 0;

	if (this->rollNameBoxIndex == -1) {
		int ih = MulDiv(14 * this->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc, LOGPIXELSY), 72);
		cFont.CreateFont(ih, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, this->fontSet->GetFaceName().c_str());
		SetFont(&cFont, TRUE);
		CFont *oldFont = dc.SelectObject(&cFont);   // 폰트 시작
		CFont *m_oldFont = memDC.SelectObject(&cFont);

		this->text->Accept(drawingVisitor, &memDC);// 받았던거 출력
		if (this->flagSelection == 1) {      // flagSelection이 눌려있으면
			this->textAreaSelected->SelectTextArea(this, &memDC);
		}
	}
	else if (dynamic_cast<Relation*>(this->figure)) {
		cFont.CreateFont(10 * this->classDiagramForm->zoomRate / 100, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
		SetFont(&cFont, TRUE);
		CFont *oldFont = dc.SelectObject(&cFont);   // 폰트 시작
		CFont *m_oldFont = memDC.SelectObject(&cFont);

		this->text->Accept(drawingVisitor, &memDC);// 받았던거 출력
		if (this->flagSelection == 1) {      // flagSelection이 눌려있으면
			this->textAreaSelected->SelectTextArea(this, &memDC);
		}
	}
	else if (dynamic_cast<SelfRelation*>(this->figure)) {
		cFont.CreateFont(10 * this->classDiagramForm->zoomRate / 100, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
		SetFont(&cFont, TRUE);
		CFont *oldFont = dc.SelectObject(&cFont);   // 폰트 시작
		CFont *m_oldFont = memDC.SelectObject(&cFont);

		this->text->Accept(drawingVisitor, &memDC);// 받았던거 출력
		if (this->flagSelection == 1) {      // flagSelection이 눌려있으면
			this->textAreaSelected->SelectTextArea(this, &memDC);
		}
	}

	dc.BitBlt(0, 0, rt.right, rt.bottom, &memDC, 0, 0, SRCCOPY);

	this->caret->MoveToIndex(this, &dc);

	dc.SelectObject(oldFont);
	memDC.SelectObject(m_oldFont);
	cFont.DeleteObject(); // 폰트
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();
	memDC.DeleteDC();
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->koreanEnglish == 0 && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != VK_RETURN &&
		nChar != VK_SPACE && nChar != VK_TAB && nChar != 10 && GetKeyState(VK_CONTROL) >= 0) {

		if (flagSelection == 1) {
			DeleteTextArea *deleteArea = DeleteTextArea::Instance();
			deleteArea->DeleteArea(this);
		}

		this->historyText->PushUndo(this->text, this->caret);
		this->historyText->redoTextArray->Clear();
		this->historyText->redoCaretArray->Clear();

		char nCharacter = nChar;
		SingleByteCharacter singleByteCharacter(nCharacter);
		if (this->caret->GetCharacterIndex() == this->text->GetAt(this->caret->GetRowIndex())->GetLength()) {
			this->text->GetAt(this->caret->GetRowIndex())->Add(singleByteCharacter.Clone());
		}
		else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 0) {
			this->text->GetAt(this->caret->GetRowIndex())->Insert(this->caret->GetCharacterIndex(), singleByteCharacter.Clone());
		}
		else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 1) {
			this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex(), singleByteCharacter.Clone());
		}
		this->caret->MoveForwardCharacterIndex();
	}
	
	CDC *dc = GetDC();
	CFont cFont;
	int ih = MulDiv(14 * this->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc->m_hDC, LOGPIXELSY), 72);
	cFont.CreateFont(ih, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, this->fontSet->GetFaceName().c_str());
	SetFont(&cFont, TRUE);
	dc->SelectObject(cFont);

	EditResizer editResizer;
	editResizer.ResizeEdit(this, dc);
	editResizer.ResizeClass(this, dc);

	cFont.DeleteObject(); // 폰트

	CWnd::HideCaret();

	Invalidate(false);
}

Long TextEdit::OnComposition(WPARAM wParam, LPARAM lParam) {
	HIMC hIMC = ImmGetContext(GetSafeHwnd());

	if (flagSelection == 1) {
		DeleteTextArea *deleteArea = DeleteTextArea::Instance();
		deleteArea->DeleteArea(this);
	}

	WriteKoreanText *writeHanguel = WriteKoreanText::Instance();
	writeHanguel->WriteHanguel(wParam, lParam, hIMC, this);

	ImmReleaseContext(GetSafeHwnd(), hIMC);

	CDC *dc = GetDC();
	CFont cFont;
	int ih = MulDiv(14 * this->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc->m_hDC, LOGPIXELSY), 72);
	cFont.CreateFont(ih, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, this->fontSet->GetFaceName().c_str());
	SetFont(&cFont, TRUE);
	dc->SelectObject(cFont);

	EditResizer editResizer;
	editResizer.ResizeEdit(this, dc);
	editResizer.ResizeClass(this, dc);

	cFont.DeleteObject(); // 폰트

	CWnd::HideCaret();

	Invalidate(false);
	return 0;
}

void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {

	CClientDC dc(this);

	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;

	SetTimer(1, 1, NULL);
	while (elapseTime < dblclkTime) {
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
			KillTimer(1);
		}
		elapseTime++;
	}

	CFont cFont;
	if (this->rollNameBoxIndex == -1) {
		int ih = MulDiv(14 * this->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc, LOGPIXELSY), 72);
		cFont.CreateFont(ih, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, this->fontSet->GetFaceName().c_str());
		SetFont(&cFont, TRUE);
	}
	else {
		cFont.CreateFont(10 * this->classDiagramForm->zoomRate / 100, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
		SetFont(&cFont, TRUE);
	}

	CFont *oldFont = dc.SelectObject(&cFont); // 폰트 시작

	if (GetKeyState(VK_SHIFT) < 0) { // 클릭했는데 쉬프트가 눌려있을 때
		if (this->flagSelection == 0) { // flag 가 안눌려있으면
			this->flagSelection = 1; // flag 를 눌러준다
			this->selectedX = this->caret->GetCharacterIndex(); // selectedX, Y 를 기존 위치 캐럿 상단 좌표로 고정한다
			this->selectedY = this->caret->GetRowIndex();
		}
	}
	else {
		if (this->flagSelection == 1) { // 쉬프트 안눌려있는데 flag 가 눌려있으면 flag 취소해준다
			this->flagSelection = 0;
		}
	}
	this->caret->MoveToPoint(this, &dc, point); // 옮긴 위치로 캐럿을 이동시켜준다

	dc.SelectObject(oldFont);

	cFont.DeleteObject(); // 폰트 끝

	

	SetCapture();
	//CWnd::HideCaret();
	KillTimer(1);
	Invalidate(false);
}

void TextEdit::OnLButtonUp(UINT nFlags, CPoint point) {

	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
		return;
	}

	

	KillTimer(1);

	ReleaseCapture();
	//CWnd::HideCaret();
	Invalidate(false);
}

void TextEdit::OnMouseMove(UINT nFlags, CPoint point) {
	

	
	if (nFlags == MK_LBUTTON) {
		CClientDC dc(this);
		CFont cFont;
		if (this->rollNameBoxIndex == -1) {
			int ih = MulDiv(14 * this->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc, LOGPIXELSY), 72);
			cFont.CreateFont(ih, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, this->fontSet->GetFaceName().c_str());
			SetFont(&cFont, TRUE);
		}
		else {
			cFont.CreateFont(10 * this->classDiagramForm->zoomRate / 100, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
			SetFont(&cFont, TRUE);
		}
		CFont *oldFont = dc.SelectObject(&cFont);// 폰트 시작

		if (this->flagSelection == 0 && this->currentX != 0) {// && this->) { // 왼마우스 눌려있는데 이동시에 flag 진행중인지 확인해서
			this->flagSelection = 1; // flag 진행중 아니면 진행중으로 바꾸고
			this->selectedX = this->caret->GetCharacterIndex(); // 최초 한번 selectedX, Y 를
			this->selectedY = this->caret->GetRowIndex();
		}
		this->caret->MoveToPoint(this, &dc, point); // 새로운 위치로 캐럿 이동한다
		SetCapture();		dc.SelectObject(oldFont);
		cFont.DeleteObject(); // 폰트 끝
		Invalidate(false);
	}
	this->currentX = point.x;
}

void TextEdit::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CClientDC dc(this);

	DoubleClickTextArea *DoubleClick = DoubleClickTextArea::Instance();
	DoubleClick->FindDoubleClickAreaIndex(this);

	Invalidate(false);
}

void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	this->koreanEnglish = 1;
	KeyAction *keyAction = this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);
	if (keyAction != 0) {
		keyAction->KeyPress(this);
	}
	this->koreanEnglish = 0;
	if (nChar == VK_NUMLOCK) {
		if (this->classDiagramForm->numLockFlag == 0) {
			this->classDiagramForm->numLockFlag = 1;
		}
		else if (this->classDiagramForm->numLockFlag == 1) {
			this->classDiagramForm->numLockFlag = 0;
		}
		this->classDiagramForm->lastClass->statusBar->DestroyStatus();
		this->classDiagramForm->lastClass->statusBar->MakeStatusBar(this->classDiagramForm->lastClass, this->classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);
	}
	else if (nChar == VK_CAPITAL) {
		if (this->classDiagramForm->capsLockFlag == 0) {
			this->classDiagramForm->capsLockFlag = 1;
		}
		else if (this->classDiagramForm->capsLockFlag == 1) {
			this->classDiagramForm->capsLockFlag = 0;
		}
		if (nChar == VK_NUMLOCK || nChar == VK_CAPITAL) {
			this->classDiagramForm->lastClass->statusBar->DestroyStatus();
			this->classDiagramForm->lastClass->statusBar->MakeStatusBar(this->classDiagramForm->lastClass, this->classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);
		}
	}

	if (nChar != VK_ESCAPE && nChar != VK_F1 && nChar != 0x46 && nChar != 0x50 && nChar != 0x4F && nChar != 0x4E && nChar != 0x53) {
		CDC *dc = GetDC();
		CFont cFont;
		int ih = MulDiv(14 * this->classDiagramForm->zoomRate / 100, GetDeviceCaps(dc->m_hDC, LOGPIXELSY), 72);
		cFont.CreateFont(ih, 0, 0, 0, this->fontSet->GetFontWeight(), FALSE, FALSE, 0, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, this->fontSet->GetFaceName().c_str());
		SetFont(&cFont, TRUE);
		dc->SelectObject(cFont);

		EditResizer editResizer;
		editResizer.ResizeEdit(this, dc);
		editResizer.ResizeClass(this, dc);

		cFont.DeleteObject(); // 폰트

		CWnd::HideCaret();

		Invalidate(false);
	}
}

LRESULT TextEdit::OnIMENotify(WPARAM wParam, LPARAM lParam) {
	if (wParam == IMN_SETCONVERSIONMODE) {
		if (this->koreanEnglish == 0) {
			this->koreanEnglish = 1;
		}
		else {
			this->koreanEnglish = 0;
		}
	}
	return 0;
}

void TextEdit::OnKillFocus(CWnd *pNewWnd) {
	if (this->rollNameBoxIndex == -1) {
		string content(this->text->MakeText());
		this->figure->ReplaceString(content, this->rowHeight);
	}
	else if (dynamic_cast<Relation*>(this->figure)) {
		string rollNameText(this->text->MakeText());
		static_cast<Relation*>(this->figure)->ReplaceString(rollNameText, this->rollNameBoxIndex);
	}
	else if (dynamic_cast<SelfRelation*>(this->figure)) {
		string rollNameText(this->text->MakeText());
		static_cast<SelfRelation*>(this->figure)->ReplaceString(rollNameText, this->rollNameBoxIndex);
	}

	CWnd::OnKillFocus(pNewWnd);
	CWnd::HideCaret();
	::DestroyCaret();


	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	if (this->historyText != NULL) {
		delete this->historyText;
	}
	if (this->textAreaSelected != NULL) {
		delete this->textAreaSelected;
	}

	if (this->fontSet != NULL) {
		delete this->fontSet;
	}
	if (this != NULL) {
		classDiagramForm->textEdit = NULL;
		delete this;
	}
}

void TextEdit::OnClose() {
	CWnd::HideCaret();
	::DestroyCaret();

	if (this->rollNameBoxIndex == -1) {
		string content(this->text->MakeText());
		this->figure->ReplaceString(content, this->rowHeight);
	}
	else if (dynamic_cast<Relation*>(this->figure)) {
		string rollNameText(this->text->MakeText());
		static_cast<Relation*>(this->figure)->ReplaceString(rollNameText, this->rollNameBoxIndex);
	}
	else if (dynamic_cast<SelfRelation*>(this->figure)) {
		string rollNameText(this->text->MakeText());
		static_cast<SelfRelation*>(this->figure)->ReplaceString(rollNameText, this->rollNameBoxIndex);
	}

	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	if (this->historyText != NULL) {
		delete this->historyText;
	}
	if (this->textAreaSelected != NULL) {
		delete this->textAreaSelected;
	}
	if (this->fontSet != NULL) {
		delete this->fontSet;
	}
	if (this != NULL) {
		this->classDiagramForm->textEdit = NULL;
		delete this;
	}
}
