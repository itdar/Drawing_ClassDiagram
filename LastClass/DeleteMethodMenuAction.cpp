#include "DeleteMethodMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "RemoveMethodKey.h"
DeleteMethodMenuAction::DeleteMethodMenuAction() {
}
DeleteMethodMenuAction::~DeleteMethodMenuAction() {
}
void DeleteMethodMenuAction::MenuPress(LastClass* lastClass) {
	Figure *figure = lastClass->classDiagramForm->selection->GetAt(0);
	if (dynamic_cast<Class*>(figure)) {
		CDC cdc;
		RemoveMethodKey key;
		key.KeyPress(lastClass->classDiagramForm, &cdc);
	}
}