#include "SaveAsMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"

#include "ResizeVisitor.h"
#include "Diagram.h"

#include <afxdlgs.h>
using namespace std;

SaveAsMenuAction::SaveAsMenuAction() {
}
SaveAsMenuAction::~SaveAsMenuAction() {
}
void SaveAsMenuAction::MenuPress(LastClass* lastClass) {

	CFileDialog  dlgFile(false,"txt","*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT,"텍스트 문서(*.txt)");
	if (dlgFile.DoModal() == IDOK)
	{
		CString fileName = lastClass->classDiagramForm->GetFileName();
		lastClass->classDiagramForm->fileName = dlgFile.GetPathName();
		lastClass->classDiagramForm->Save();
		CString temp = lastClass->classDiagramForm->SetFileName(fileName);
	}

}