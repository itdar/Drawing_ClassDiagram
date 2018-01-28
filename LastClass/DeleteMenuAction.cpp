#include "DeleteMenuAction.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "DeleteGraphicKey.h"
DeleteMenuAction::DeleteMenuAction() {
}
DeleteMenuAction::~DeleteMenuAction() {
}
void DeleteMenuAction::MenuPress(LastClass* lastClass) {
		CDC cdc;
		DeleteGraphicKey key;
		key.KeyPress(lastClass->classDiagramForm, &cdc);
}