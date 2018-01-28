//AddAttributeKey.cpp

#include "AddAttributeKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"

AddAttributeKey::AddAttributeKey() {
}

AddAttributeKey::AddAttributeKey(const AddAttributeKey& source) {
}

AddAttributeKey::~AddAttributeKey() {
}

void AddAttributeKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->selection->GetLength() == 1 && dynamic_cast<Class*>(classDiagramForm->selection->GetAt(0))) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetAttributePosition() == -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram, classDiagramForm->zoomRate);
			classDiagramForm->historyGraphic->redoGraphicArray->Clear();
			classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

			object->AddAttribute(classDiagramForm->diagram);
		}
	}
}

void AddAttributeKey::KeyPress(TextEdit *textEdit) {

}