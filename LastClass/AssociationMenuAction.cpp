#include "AssociationMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
AssociationMenuAction::AssociationMenuAction() {
}
AssociationMenuAction::~AssociationMenuAction() {
}
void AssociationMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingAssociationState();
	}
}