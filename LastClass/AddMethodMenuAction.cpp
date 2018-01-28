#include "AddMethodMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "AddMethodKey.h"
AddMethodMenuAction::AddMethodMenuAction() {
}
AddMethodMenuAction::~AddMethodMenuAction() {
}
void AddMethodMenuAction::MenuPress(LastClass* lastClass) {
	Figure *figure = lastClass->classDiagramForm->selection->GetAt(0);
	if (dynamic_cast<Class*>(figure)) {
		CDC cdc;
		AddMethodKey key;
		key.KeyPress(lastClass->classDiagramForm, &cdc);
	}
}