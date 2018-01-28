//GraphicCtrlUndoKey.cpp

#include "GraphicCtrlUndoKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Diagram.h"
#include "Selection.h"
#include "LastClass.h"
#include "StatusBar.h"

GraphicCtrlUndoKey::GraphicCtrlUndoKey() {
}
GraphicCtrlUndoKey::GraphicCtrlUndoKey(const GraphicCtrlUndoKey& source) {
}
GraphicCtrlUndoKey::~GraphicCtrlUndoKey() {
}

void GraphicCtrlUndoKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->historyGraphic->undoGraphicArray->GetLength() > 0) {
		Diagram *diagram_;
		Long zoomRate_;
		classDiagramForm->historyGraphic->PopUndoGraphic(&diagram_, &zoomRate_);


		/*Diagram *tempDiagram = new Diagram(*(classDiagramForm->diagram));

		Long i = 0;
		while (i < classDiagramForm->diagram->GetLength()) {
			FigureComposite *figureComposite = static_cast<FigureComposite*>(classDiagramForm->diagram->GetAt(i));
			Long j = 0;
			while (j < figureComposite->GetLength()) {
				Figure *figure = figureComposite->GetAt(j);
				if (figure->GetEndPointFigure() != 0) {
					Long k = 0;
					while (k < classDiagramForm->diagram->GetLength() && figure->GetEndPointFigure() != classDiagramForm->diagram->GetAt(k)) {
						k++;
					}
					if (k < classDiagramForm->diagram->GetLength()) {
						FigureComposite *tempFigureComposite = static_cast<FigureComposite* >(tempDiagram->GetAt(i));
						Figure *temp = tempFigureComposite->GetAt(j);
						temp->SetEndPointFigure(tempDiagram->GetAt(k));
					}
				}
				j++;
			}
			i++;
		}
		classDiagramForm->historyGraphic->PushRedo(tempDiagram, zoomRate_);*/

		classDiagramForm->historyGraphic->PushRedo(classDiagramForm->diagram, zoomRate_);


		delete classDiagramForm->diagram;
		classDiagramForm->diagram = diagram_;

		classDiagramForm->zoomRate = zoomRate_;
		classDiagramForm->lastClass->statusBar->DestroyStatus();
		classDiagramForm->lastClass->statusBar->MakeStatusBar(classDiagramForm->lastClass, classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);
	}
	classDiagramForm->selection->DeleteAllItems();
}

void GraphicCtrlUndoKey::KeyPress(TextEdit *textEdit) {
}