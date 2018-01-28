#include "DeleteReceptionMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "RemoveReceptionKey.h"
DeleteReceptionMenuAction::DeleteReceptionMenuAction() {
}
DeleteReceptionMenuAction::~DeleteReceptionMenuAction() {
}
void DeleteReceptionMenuAction::MenuPress(LastClass* lastClass) {
	Figure *figure = lastClass->classDiagramForm->selection->GetAt(0);
	if (dynamic_cast<Class*>(figure)) {
		CDC cdc;
		RemoveReceptionKey key;
		key.KeyPress(lastClass->classDiagramForm, &cdc);
	}
}