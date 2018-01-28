//GraphicCtrlRedoKey.cpp

#include "GraphicCtrlRedoKey.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Diagram.h"
#include "Selection.h"
#include "LastClass.h"
#include "StatusBar.h"
#include "ClassDiagramForm.h"

GraphicCtrlRedoKey::GraphicCtrlRedoKey() {
}
GraphicCtrlRedoKey::GraphicCtrlRedoKey(const GraphicCtrlRedoKey& source) {
}
GraphicCtrlRedoKey::~GraphicCtrlRedoKey() {
}

void GraphicCtrlRedoKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->historyGraphic->redoGraphicArray->GetLength() > 0) {
		Diagram *diagram_;
		Long zoomRate_;
		classDiagramForm->historyGraphic->PopRedoGraphic(&diagram_, &zoomRate_);

		//Diagram *tempDiagram = new Diagram(*(classDiagramForm->diagram));
		//classDiagramForm->historyGraphic->PushUndo(tempDiagram, zoomRate_);//이부분이 문제 새로 할당해서 관계선이 끊어진상태인데 넘겨줌
		classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram, zoomRate_);

		delete classDiagramForm->diagram;
		classDiagramForm->diagram = diagram_;
		/*Long i = 0;
		while (i < diagram_->GetLength()) {
			FigureComposite *figureComposite = static_cast<FigureComposite*>(diagram_->GetAt(i));
			Long j = 0;
			while (j < figureComposite->GetLength()) {
				Figure *figure = figureComposite->GetAt(j);
				if (figure->GetEndPointFigure() != 0) {
					Long k = 0;
					while (k < diagram_->GetLength() && figure->GetEndPointFigure() != diagram_->GetAt(k)) {
						k++;
					}
					if (k < diagram_->GetLength()) {
						FigureComposite *tempFigureComposite = static_cast<FigureComposite* >(classDiagramForm->diagram->GetAt(i));
						Figure *temp = tempFigureComposite->GetAt(j);
						temp->SetEndPointFigure(classDiagramForm->diagram->GetAt(k));
					}
				}
				j++;
			}
			i++;
		}*/
		classDiagramForm->zoomRate = zoomRate_;
		classDiagramForm->lastClass->statusBar->DestroyStatus();
		classDiagramForm->lastClass->statusBar->MakeStatusBar(classDiagramForm->lastClass, classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);
	}
	classDiagramForm->selection->DeleteAllItems();
}

void GraphicCtrlRedoKey::KeyPress(TextEdit *textEdit) {
}