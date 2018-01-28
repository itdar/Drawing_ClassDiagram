//GraphicCtrlCopyMenuAction.cpp

#include "GraphicCtrlCopyMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "GraphicCtrlCopyKey.h"

GraphicCtrlCopyMenuAction::GraphicCtrlCopyMenuAction() {
}
GraphicCtrlCopyMenuAction::GraphicCtrlCopyMenuAction(const GraphicCtrlCopyMenuAction& source) {
}
GraphicCtrlCopyMenuAction::~GraphicCtrlCopyMenuAction() {
}

void GraphicCtrlCopyMenuAction::MenuPress(LastClass *lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		GraphicCtrlCopyKey *ctrlUndo = new GraphicCtrlCopyKey;
		CClientDC dc(lastClass->classDiagramForm);
		ctrlUndo->KeyPress(lastClass->classDiagramForm, &dc);
		lastClass->classDiagramForm->Invalidate(false);
		if (ctrlUndo != 0) {
			delete ctrlUndo;
		}
	}
}