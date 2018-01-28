#include "DirectedAssociationMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
DirectedAssociationMenuAction::DirectedAssociationMenuAction() {
}
DirectedAssociationMenuAction::~DirectedAssociationMenuAction() {
}
void DirectedAssociationMenuAction::MenuPress(LastClass* lastClass) {
	if (lastClass->classDiagramForm->textEdit == 0) {
		lastClass->classDiagramForm->mouseLButton->ChangeDrawingDirectedAssociationState();
	}
}