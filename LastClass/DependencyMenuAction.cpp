#include "DependencyMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
DependencyMenuAction::DependencyMenuAction() {
}
DependencyMenuAction::~DependencyMenuAction() {
}
void DependencyMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingDependencyState();
	}
}