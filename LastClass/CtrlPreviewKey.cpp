//CtrlPreviewKey.cpp

#include "CtrlPreviewKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "FilePrintPreviewMenuAction.h"

CtrlPreviewKey::CtrlPreviewKey() {
}

CtrlPreviewKey::CtrlPreviewKey(const CtrlPreviewKey& source) {
}

CtrlPreviewKey::~CtrlPreviewKey() {
}

void CtrlPreviewKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	FilePrintPreviewMenuAction *preview = new FilePrintPreviewMenuAction;
	preview->MenuPress(classDiagramForm->lastClass);
	if (preview != 0) {
		delete preview;
	}
}

void CtrlPreviewKey::KeyPress(TextEdit *textEdit) {
	FilePrintPreviewMenuAction *preview = new FilePrintPreviewMenuAction;
	preview->MenuPress(textEdit->classDiagramForm->lastClass);
	if (preview != 0) {
		delete preview;
	}
}