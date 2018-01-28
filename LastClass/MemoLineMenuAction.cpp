#include "MemoLineMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
MemoLineMenuAction::MemoLineMenuAction() {
}
MemoLineMenuAction::~MemoLineMenuAction() {
}
void MemoLineMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingMemoLineState();
	}
}