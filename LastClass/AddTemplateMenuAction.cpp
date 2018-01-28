#include "AddTemplateMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "AddTemplateKey.h"
AddTemplateMenuAction::AddTemplateMenuAction() {
}
AddTemplateMenuAction::~AddTemplateMenuAction() {
}
void AddTemplateMenuAction::MenuPress(LastClass* lastClass) {

	Figure *figure = lastClass->classDiagramForm->selection->GetAt(0);
	if (dynamic_cast<Class*>(figure)) {
		CDC cdc;
		AddTemplateKey key;
		 key.KeyPress(lastClass->classDiagramForm, &cdc);
	}
	
}