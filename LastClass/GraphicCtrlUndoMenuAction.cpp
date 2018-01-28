//GraphicCtrlUndoMenuAction.cpp

#include "GraphicCtrlUndoMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "GraphicCtrlUndoKey.h"
#include "CtrlUndoTextKey.h"
#include "StatusBar.h"

GraphicCtrlUndoMenuAction::GraphicCtrlUndoMenuAction() {
}
GraphicCtrlUndoMenuAction::GraphicCtrlUndoMenuAction(const GraphicCtrlUndoMenuAction& source) {
}
GraphicCtrlUndoMenuAction::~GraphicCtrlUndoMenuAction() {
}

void GraphicCtrlUndoMenuAction::MenuPress(LastClass *lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		GraphicCtrlUndoKey *ctrlUndo = new GraphicCtrlUndoKey;
		CClientDC dc(lastClass->classDiagramForm);
		ctrlUndo->KeyPress(lastClass->classDiagramForm, &dc);
		lastClass->classDiagramForm->Invalidate(false);
		if (ctrlUndo != 0) {
			delete ctrlUndo;
		}
	}
	else {
		CtrlUndoTextKey *ctrlTextUndo = new CtrlUndoTextKey;
		ctrlTextUndo->KeyPress(lastClass->classDiagramForm->textEdit);
		lastClass->classDiagramForm->textEdit->Invalidate(false);
		if (ctrlTextUndo != 0) {
			delete ctrlTextUndo;
		}
	}
	lastClass->statusBar->DestroyStatus();
	lastClass->statusBar->MakeStatusBar(lastClass, lastClass->GetSafeHwnd(), 0, 0, 5);
}