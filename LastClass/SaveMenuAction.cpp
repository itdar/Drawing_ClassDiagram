#include "SaveMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "ResizeVisitor.h"
#include "Diagram.h"
#include "Figure.h"
#include <afxdlgs.h>

using namespace std;

SaveMenuAction::SaveMenuAction() {
}
SaveMenuAction::~SaveMenuAction() {
}
void SaveMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit != NULL) {
		lastClass->classDiagramForm->textEdit->OnClose();
		lastClass->classDiagramForm->textEdit = NULL;
	}
	if (lastClass->classDiagramForm->fileName == "") {
		int messageBox = lastClass->MessageBox(_T("변경 내용을 제목 없음에 저장하시겠습니까?"), "ClassDiagram", MB_YESNOCANCEL);
		if (messageBox == IDYES) {
			CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "텍스트 문서(*.txt)");
			if (dlgFile.DoModal() == IDOK){
				ResizeVisitor resizeVisitor1(lastClass->classDiagramForm->zoomRate, 100); // previous / next
				CDC dc;
				//lastClass->classDiagramForm->diagram->Accept(resizeVisitor1, &dc);

				lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
				lastClass->classDiagramForm->Save();

				ResizeVisitor resizeVisitor2(100, lastClass->classDiagramForm->zoomRate);
				//lastClass->classDiagramForm->diagram->Accept(resizeVisitor2, &dc);
			}
		}
	}
	else {
		ResizeVisitor resizeVisitor1(lastClass->classDiagramForm->zoomRate, 100);
		CDC dc;
		//lastClass->classDiagramForm->diagram->Accept(resizeVisitor1, &dc);

		lastClass->classDiagramForm->Save();

		ResizeVisitor resizeVisitor2(100, lastClass->classDiagramForm->zoomRate);
		//lastClass->classDiagramForm->diagram->Accept(resizeVisitor2, &dc);
	}

}