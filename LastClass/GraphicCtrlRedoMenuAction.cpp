//GraphicCtrlRedoMenuAction.cpp

#include "GraphicCtrlRedoMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "GraphicCtrlRedoKey.h"
#include "CtrlRedoTextKey.h"
#include "StatusBar.h"

GraphicCtrlRedoMenuAction::GraphicCtrlRedoMenuAction() {
}
GraphicCtrlRedoMenuAction::GraphicCtrlRedoMenuAction(const GraphicCtrlRedoMenuAction& source) {
}
GraphicCtrlRedoMenuAction::~GraphicCtrlRedoMenuAction() {
}

void GraphicCtrlRedoMenuAction::MenuPress(LastClass *lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		GraphicCtrlRedoKey *ctrlRedo = new GraphicCtrlRedoKey;
		CClientDC dc(lastClass->classDiagramForm);
		ctrlRedo->KeyPress(lastClass->classDiagramForm, &dc);
		lastClass->classDiagramForm->Invalidate(false);
		if (ctrlRedo != 0) {
			delete ctrlRedo;
		}
	}
	else {
		CtrlRedoTextKey *ctrlTextRedo = new CtrlRedoTextKey;
		ctrlTextRedo->KeyPress(lastClass->classDiagramForm->textEdit);
		lastClass->classDiagramForm->textEdit->Invalidate(false);
		if (ctrlTextRedo != 0) {
			delete ctrlTextRedo;
		}
	}
	lastClass->statusBar->DestroyStatus();
	lastClass->statusBar->MakeStatusBar(lastClass, lastClass->GetSafeHwnd(), 0, 0, 5);
}