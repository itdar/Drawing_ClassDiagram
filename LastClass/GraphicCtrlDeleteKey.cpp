//GraphicCtrlDeleteKey.cpp

#include "GraphicCtrlDeleteKey.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "DeleteGraphicKeyMenuAction.h"

GraphicCtrlDeleteKey::GraphicCtrlDeleteKey() {
}

GraphicCtrlDeleteKey::GraphicCtrlDeleteKey(const GraphicCtrlDeleteKey& source) {
}

GraphicCtrlDeleteKey::~GraphicCtrlDeleteKey() {
}

void GraphicCtrlDeleteKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	DeleteGraphicKeyMenuAction *deleteKey = new DeleteGraphicKeyMenuAction;
	deleteKey->MenuPress(classDiagramForm->lastClass);
	if (deleteKey != 0) {
		delete deleteKey;
	}
}

void GraphicCtrlDeleteKey::KeyPress(TextEdit *textEdit) {
	DeleteGraphicKeyMenuAction *deleteKey = new DeleteGraphicKeyMenuAction;
	deleteKey->MenuPress(textEdit->classDiagramForm->lastClass);
	if (deleteKey != 0) {
		delete deleteKey;
	}
}