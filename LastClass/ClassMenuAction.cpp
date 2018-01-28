#include "ClassMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
#include "DrawingClass.h"
ClassMenuAction::ClassMenuAction() {
}
ClassMenuAction::~ClassMenuAction() {
}
void ClassMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingClassState();
	}
}