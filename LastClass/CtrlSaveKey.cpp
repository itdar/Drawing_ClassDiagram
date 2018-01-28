//CtrlSaveKey.cpp

#include "CtrlSaveKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "SaveMenuAction.h"

CtrlSaveKey::CtrlSaveKey() {
}

CtrlSaveKey::CtrlSaveKey(const CtrlSaveKey& source) {
}

CtrlSaveKey::~CtrlSaveKey() {
}

void CtrlSaveKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	SaveMenuAction *save = new SaveMenuAction;
	save->MenuPress(classDiagramForm->lastClass);
	if (save != 0) {
		delete save;
	}
}

void CtrlSaveKey::KeyPress(TextEdit *textEdit) {
	SaveMenuAction *save = new SaveMenuAction;
	
	save->MenuPress(textEdit->classDiagramForm->lastClass);
	if (save != 0) {
		delete save;
	}
}