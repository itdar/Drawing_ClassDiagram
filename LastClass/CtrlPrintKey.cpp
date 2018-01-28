//CtrlPrintKey.cpp

#include "CtrlPrintKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "FilePrintMenuAction.h"

CtrlPrintKey::CtrlPrintKey() {
}

CtrlPrintKey::CtrlPrintKey(const CtrlPrintKey& source) {
}

CtrlPrintKey::~CtrlPrintKey() {
}

void CtrlPrintKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	FilePrintMenuAction *print = new FilePrintMenuAction;
	print->MenuPress(classDiagramForm->lastClass);
	if (print != 0) {
		delete print;
	}
}

void CtrlPrintKey::KeyPress(TextEdit *textEdit) {
	FilePrintMenuAction *print = new FilePrintMenuAction;
	print->MenuPress(textEdit->classDiagramForm->lastClass);
	if (print != 0) {
		delete print;
	}
}