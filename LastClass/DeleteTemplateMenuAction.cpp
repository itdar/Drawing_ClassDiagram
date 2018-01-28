#include "DeleteTemplateMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "RemoveTemplateKey.h"
DeleteTemplateMenuAction::DeleteTemplateMenuAction() {
}
DeleteTemplateMenuAction::~DeleteTemplateMenuAction() {
}
void DeleteTemplateMenuAction::MenuPress(LastClass* lastClass) {

	Figure *figure = lastClass->classDiagramForm->selection->GetAt(0);
	if (dynamic_cast<Class*>(figure)) {
		CDC cdc;
		RemoveTemplateKey key;
		key.KeyPress(lastClass->classDiagramForm, &cdc);
	}

}