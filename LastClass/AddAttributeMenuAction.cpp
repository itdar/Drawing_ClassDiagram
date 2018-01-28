#include "AddAttributeMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "AddAttributeKey.h"
AddAttributeMenuAction::AddAttributeMenuAction() {
}
AddAttributeMenuAction::~AddAttributeMenuAction() {
}
void AddAttributeMenuAction::MenuPress(LastClass* lastClass) {
	Figure *figure = lastClass->classDiagramForm->selection->GetAt(0);
	if (dynamic_cast<Class*>(figure)) {
		CDC cdc;
		AddAttributeKey key;
		key.KeyPress(lastClass->classDiagramForm, &cdc);
	}
}