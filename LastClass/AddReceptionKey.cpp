//AddReceptionKey.cpp

#include "AddReceptionKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "Diagram.h"
#include "HistoryGraphic.h"

AddReceptionKey::AddReceptionKey() {
}

AddReceptionKey::AddReceptionKey(const AddReceptionKey& source) {
}

AddReceptionKey::~AddReceptionKey() {
}

void AddReceptionKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->selection->GetLength() == 1 && dynamic_cast<Class*>(classDiagramForm->selection->GetAt(0))) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetReceptionPosition() == -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram, classDiagramForm->zoomRate);
			classDiagramForm->historyGraphic->redoGraphicArray->Clear();
			classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

			object->AddReception(classDiagramForm->diagram);
		}
	}

}

void AddReceptionKey::KeyPress(TextEdit *textEdit) {

}