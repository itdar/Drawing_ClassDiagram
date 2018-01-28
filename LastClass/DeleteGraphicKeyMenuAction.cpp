//DeleteGraphicKeyMenuAction.cpp

#include "DeleteGraphicKeyMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "DeleteGraphicKey.h"
#include "StatusBar.h"
#include "LastClass.h"

DeleteGraphicKeyMenuAction::DeleteGraphicKeyMenuAction() {
}
DeleteGraphicKeyMenuAction::DeleteGraphicKeyMenuAction(const DeleteGraphicKeyMenuAction& source) {
}
DeleteGraphicKeyMenuAction::~DeleteGraphicKeyMenuAction() {
}

void DeleteGraphicKeyMenuAction::MenuPress(LastClass *lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		DeleteGraphicKey *ctrlUndo = new DeleteGraphicKey;
		CClientDC dc(lastClass->classDiagramForm);
		ctrlUndo->KeyPress(lastClass->classDiagramForm, &dc);
		
		lastClass->classDiagramForm->Invalidate(false);
		if (ctrlUndo != 0) {
			delete ctrlUndo;
		}
		lastClass->statusBar->DestroyStatus();
		lastClass->statusBar->MakeStatusBar(lastClass, lastClass->GetSafeHwnd(), 0, 0, 5);
	}
}