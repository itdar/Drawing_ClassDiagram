#include "CompositionMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
CompositionMenuAction::CompositionMenuAction() {
}
CompositionMenuAction::~CompositionMenuAction() {
}
void CompositionMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingCompositionState();
	}
}