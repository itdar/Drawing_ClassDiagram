#include "RealizationMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
RealizationMenuAction::RealizationMenuAction() {
}
RealizationMenuAction::~RealizationMenuAction() {
}
void RealizationMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingRealizationState();
	}
}