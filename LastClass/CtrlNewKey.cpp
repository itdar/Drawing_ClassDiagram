//CtrlNewKey.cpp

#include "CtrlNewKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "NewMenuAction.h"

CtrlNewKey::CtrlNewKey() {
}

CtrlNewKey::CtrlNewKey(const CtrlNewKey& source) {
}

CtrlNewKey::~CtrlNewKey() {
}

void CtrlNewKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	NewMenuAction *menu = new NewMenuAction;
	menu->MenuPress(classDiagramForm->lastClass);
	if (menu != 0) {
		delete menu;
	}
}

void CtrlNewKey::KeyPress(TextEdit *textEdit) {
	NewMenuAction *menu = new NewMenuAction;
	menu->MenuPress(textEdit->classDiagramForm->lastClass);
	if (menu != 0) {
		delete menu;
	}
}