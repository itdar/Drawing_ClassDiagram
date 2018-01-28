//CtrlOpenKey.cpp

#include "CtrlOpenKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "OpenMenuAction.h"

CtrlOpenKey::CtrlOpenKey() {
}

CtrlOpenKey::CtrlOpenKey(const CtrlOpenKey& source) {
}

CtrlOpenKey::~CtrlOpenKey() {
}

void CtrlOpenKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	OpenMenuAction *menu = new OpenMenuAction;
	menu->MenuPress(classDiagramForm->lastClass);
	if (menu != 0) {
		delete menu;
	}
	
}

void CtrlOpenKey::KeyPress(TextEdit *textEdit) {
	OpenMenuAction *menu = new OpenMenuAction;
	menu->MenuPress(textEdit->classDiagramForm->lastClass);
	if (menu != 0) {
		delete menu;
	}
}