#include "CompositionsMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
CompositionsMenuAction::CompositionsMenuAction() {
}
CompositionsMenuAction::~CompositionsMenuAction() {
}
void CompositionsMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingCompositionsState();
	}
}