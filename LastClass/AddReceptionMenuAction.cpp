#include "AddReceptionMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "AddReceptionKey.h"
AddReceptionMenuAction::AddReceptionMenuAction() {
}
AddReceptionMenuAction::~AddReceptionMenuAction() {
}
void AddReceptionMenuAction::MenuPress(LastClass* lastClass) {
	Figure *figure = lastClass->classDiagramForm->selection->GetAt(0);
	if (dynamic_cast<Class*>(figure)) {
		CDC cdc;
		AddReceptionKey key;
		key.KeyPress(lastClass->classDiagramForm, &cdc);
	}
}