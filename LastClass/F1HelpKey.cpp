//F1HelpKey.cpp

#include "F1HelpKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "SupportMenuAction.h"

F1HelpKey::F1HelpKey() {
}

F1HelpKey::F1HelpKey(const F1HelpKey& source) {
}

F1HelpKey::~F1HelpKey() {
}

void F1HelpKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	SupportMenuAction *support = new SupportMenuAction;
	support->MenuPress(classDiagramForm->lastClass);
	if (support != 0) {
		delete support;
	}
}

void F1HelpKey::KeyPress(TextEdit *textEdit) {
	SupportMenuAction *support = new SupportMenuAction;
	support->MenuPress(textEdit->classDiagramForm->lastClass);
	if (support != 0) {
		delete support;
	}
}