#include "GeneralizationMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
GeneralizationMenuAction::GeneralizationMenuAction() {
}
GeneralizationMenuAction::~GeneralizationMenuAction() {
}
void GeneralizationMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingGeneralizationState();
	}
}