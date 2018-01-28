//RemoveAttributeKey.cpp

#include "RemoveAttributeKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

RemoveAttributeKey::RemoveAttributeKey() {
}

RemoveAttributeKey::RemoveAttributeKey(const RemoveAttributeKey& source) {
}

RemoveAttributeKey::~RemoveAttributeKey() {
}

void RemoveAttributeKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->selection->GetLength() == 1 && dynamic_cast<Class*>(classDiagramForm->selection->GetAt(0))) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetAttributePosition() != 1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram, classDiagramForm->zoomRate);
			classDiagramForm->historyGraphic->redoGraphicArray->Clear();
			classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

			object->RemoveAttribute();
		}
	}
}

void RemoveAttributeKey::KeyPress(TextEdit *textEdit) {
}