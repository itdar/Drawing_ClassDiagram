//DeleteGraphicKey.cpp

#include "DeleteGraphicKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "Relation.h"
#include "Diagram.h"
#include "MouseLButton.h"
#include "LastClass.h"
#include "StatusBar.h"

DeleteGraphicKey::DeleteGraphicKey() {
}

DeleteGraphicKey::DeleteGraphicKey(const DeleteGraphicKey& source) {
}

DeleteGraphicKey::~DeleteGraphicKey() {
}

void DeleteGraphicKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	Long i = 0;
	Long j;
	Long k;
	FigureComposite *selectedComposite;
	FigureComposite *composite;
	Figure *relation;
	while (i < classDiagramForm->selection->GetLength()) {
		if (dynamic_cast<FigureComposite*>(classDiagramForm->selection->GetAt(i))) {
			selectedComposite = static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(i));
			j = 0;
			while (j < classDiagramForm->diagram->GetLength()) {
				composite = static_cast<FigureComposite*>(classDiagramForm->diagram->GetAt(j));
				k = 0;
				while (k < composite->GetLength()) {
					if (dynamic_cast<Relation*>(composite->GetAt(k))) {
						relation = composite->GetAt(k);
						if (relation->GetEndPointFigure() == static_cast<Figure*>(selectedComposite)){
							classDiagramForm->selection->Add(relation);
						}
					}
					k++;
				}
				j++;
			}
		}
		i++;
	}

	if (classDiagramForm->selection->GetLength() > 0) {
		classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram, classDiagramForm->zoomRate);
		classDiagramForm->historyGraphic->redoGraphicArray->Clear();
		classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();
		while (classDiagramForm->selection->GetLength() != 0) {
			classDiagramForm->selection->Remove(classDiagramForm->diagram, classDiagramForm->selection->GetAt(classDiagramForm->selection->GetLength() - 1));
		}
	}
	classDiagramForm->lastClass->statusBar->DestroyStatus();
	classDiagramForm->lastClass->statusBar->MakeStatusBar(classDiagramForm->lastClass, classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);

	classDiagramForm->mouseLButton->ChangeDefault();
}

void DeleteGraphicKey::KeyPress(TextEdit *textEdit) {

}