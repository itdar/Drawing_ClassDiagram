#include "NewMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
#include "Diagram.h"
#include "Selection.h"
#include "HistoryGraphic.h"
#include "KeyBoard.h"
#include "ResizeVisitor.h"
#include "StatusBar.h"
#include "TextEdit.h"

#include <afxdlgs.h>

using namespace std;

NewMenuAction::NewMenuAction() {
}
NewMenuAction::~NewMenuAction() {
}
void NewMenuAction::MenuPress(LastClass* lastClass) {
	int messageBox = IDNO;
	INT_PTR int_ptr = IDOK;
	if (lastClass->classDiagramForm->textEdit != NULL) {
		lastClass->classDiagramForm->textEdit->OnClose();
		lastClass->classDiagramForm->textEdit = NULL;
	}
	if (lastClass->classDiagramForm->historyGraphic->undoGraphicArray->GetLength() != 0
		|| lastClass->classDiagramForm->historyGraphic->redoGraphicArray->GetLength() != 0) {
		if (lastClass->classDiagramForm->fileName != "") { //저장된 이름이 있으면
			CString object;
			object = "변경내용을 ";
			object.Append(lastClass->classDiagramForm->fileName);
			object.Append("에 저장하시겠습니까?");
			messageBox = lastClass->classDiagramForm->MessageBox(object, "ClassDiagram", MB_YESNOCANCEL);
		}
		else { // 이름 없는 파일이면
			messageBox = lastClass->classDiagramForm->MessageBox(_T("변경 내용을 제목 없음에 저장하시겠습니까?"), "ClassDiagram", MB_YESNOCANCEL);
			if (messageBox == IDYES) {
				CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "텍스트 문서(*.txt)");
				int_ptr = dlgFile.DoModal();
				if (int_ptr == IDOK)
				{
					lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
				}
			}
		}
		if (messageBox == IDYES && int_ptr == IDOK) {
			lastClass->classDiagramForm->Save();
		}
	}
	if (messageBox != IDCANCEL && int_ptr == IDOK ) {
			if (lastClass->classDiagramForm->diagram != NULL) {
			delete lastClass->classDiagramForm->diagram;
		}
		if (lastClass->classDiagramForm->selection != NULL) {
			delete lastClass->classDiagramForm->selection;
		}
		if (lastClass->classDiagramForm->mouseLButton != NULL) {
			delete lastClass->classDiagramForm->mouseLButton;
		}
		if (lastClass->classDiagramForm->keyBoard != NULL) {
			delete lastClass->classDiagramForm->keyBoard;
		}
		if (lastClass->classDiagramForm->historyGraphic != NULL) {
			delete lastClass->classDiagramForm->historyGraphic;
		}
		lastClass->classDiagramForm->diagram = new Diagram();
		lastClass->classDiagramForm->selection = new Selection;
		lastClass->classDiagramForm->mouseLButton = new MouseLButton;
		lastClass->classDiagramForm->historyGraphic = new HistoryGraphic;
		lastClass->classDiagramForm->keyBoard = new KeyBoard;
		lastClass->classDiagramForm->fileName = "";


		lastClass->classDiagramForm->zoomRate = 100;
		lastClass->classDiagramForm->SetMemoGab(20 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->SetGabX(8 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->SetGabY(2 * lastClass->classDiagramForm->zoomRate / 100);
		lastClass->classDiagramForm->SetCaretWidth(2 * lastClass->classDiagramForm->zoomRate / 100);
		SCROLLINFO vScinfo;
		SCROLLINFO hScinfo;

		lastClass->classDiagramForm->GetScrollInfo(SB_VERT, &vScinfo);
		lastClass->classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
		CRect rect;
		lastClass->classDiagramForm->GetClientRect(&rect);

		vScinfo.nPage = rect.Height();
		hScinfo.nPage = rect.Width();

		vScinfo.nMax = 2000;
		hScinfo.nMax = 4000;


		vScinfo.nPos = 0;
		hScinfo.nPos = 0;

		lastClass->classDiagramForm->SetScrollInfo(SB_VERT, &vScinfo);
		lastClass->classDiagramForm->SetScrollInfo(SB_HORZ, &hScinfo);
	}
	lastClass->statusBar->DestroyStatus();
	lastClass->statusBar->MakeStatusBar(lastClass, lastClass->GetSafeHwnd(), 0, 0, 5);

	lastClass->classDiagramForm->Invalidate(false);
}