#include "MemoBoxMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
MemoBoxMenuAction::MemoBoxMenuAction() {
}
MemoBoxMenuAction::~MemoBoxMenuAction() {
}
void MemoBoxMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingMemoBoxState();
	}
}