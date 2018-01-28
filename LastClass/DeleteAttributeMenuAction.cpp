#include "DeleteAttributeMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "RemoveAttributeKey.h"
DeleteAttributeMenuAction::DeleteAttributeMenuAction() {
}
DeleteAttributeMenuAction::~DeleteAttributeMenuAction() {
}
void DeleteAttributeMenuAction::MenuPress(LastClass* lastClass) {
	Figure *figure = lastClass->classDiagramForm->selection->GetAt(0);
	if (dynamic_cast<Class*>(figure)) {
		CDC cdc;
		RemoveAttributeKey key;
		key.KeyPress(lastClass->classDiagramForm, &cdc);
	}
}