//HistoryGraphic.cpp

#include "HistoryGraphic.h"
#include "Diagram.h"
#include "FigureComposite.h"
#include "Figure.h"
#include "Text.h"

HistoryGraphic* HistoryGraphic::instance = 0;

HistoryGraphic* HistoryGraphic::Instance() {
	if (instance == 0) {
		instance = new HistoryGraphic;
	}
	return instance;
}

HistoryGraphic::HistoryGraphic() {
	this->undoGraphicArray = new Array<Diagram*>(0);
	this->redoGraphicArray = new Array<Diagram*>(0);
	this->undoGraphicZoomRateArray = new Array<Long>(0);
	this->redoGraphicZoomRateArray = new Array<Long>(0);
}

HistoryGraphic::HistoryGraphic(const HistoryGraphic& source) {
	this->undoGraphicArray = source.undoGraphicArray;
	this->redoGraphicArray = source.redoGraphicArray;
	this->undoGraphicZoomRateArray = source.undoGraphicZoomRateArray;
	this->redoGraphicZoomRateArray = source.redoGraphicZoomRateArray;
}

HistoryGraphic::~HistoryGraphic() {
	delete this->undoGraphicArray;
	delete this->redoGraphicArray;
	delete this->undoGraphicZoomRateArray;
	delete this->redoGraphicZoomRateArray;
}

void HistoryGraphic::PushUndo(Diagram *diagram, Long zoomRate) {
	
	if (this->undoGraphicArray->GetCapacity() < 50) {
		this->undoGraphicArray->AppendFromFront(static_cast<Diagram*>(diagram->Clone()));
		this->undoGraphicZoomRateArray->AppendFromFront(zoomRate);
	}
	else {
		this->undoGraphicArray->Insert(0, static_cast<Diagram*>(diagram->Clone()));
		this->undoGraphicArray->DeleteFromRear();
		this->undoGraphicZoomRateArray->Insert(0, zoomRate);
		this->undoGraphicZoomRateArray->DeleteFromRear();
	}
	Long i = 0;
	while ( i <diagram->GetLength()) {
		FigureComposite *figureComposite = static_cast<FigureComposite*>(diagram->GetAt(i));
		Long j = 0;
		while (j < figureComposite->GetLength()) {
			Figure *figure = figureComposite->GetAt(j);
			if (figure->GetEndPointFigure() != 0) {
				Long k = 0;
				while (k < diagram->GetLength() && figure->GetEndPointFigure() != diagram->GetAt(k)) {
					k++;
				}
				if (k < diagram->GetLength()) {
					Diagram *diarams = this->undoGraphicArray->GetAt(0);
					FigureComposite *tempFigureComposite = static_cast<FigureComposite*>(diarams->GetAt(i));//->GetAt(j);
					Figure *temp = tempFigureComposite->GetAt(j);
					temp->SetEndPointFigure(this->undoGraphicArray->GetAt(0)->GetAt(k));
				}
			}
			j++;
		}
		i++;
	}
}

void HistoryGraphic::PopUndoGraphic(Diagram*(*diagram), Long *zoomRate){
	// *diagram = 0;
	if (this->undoGraphicArray->GetLength() > 0) {
		(*diagram) = this->undoGraphicArray->GetAt(0);
		this->undoGraphicArray->Delete(0);
		(*zoomRate) = this->undoGraphicZoomRateArray->GetAt(0);
		this->undoGraphicZoomRateArray->Delete(0);
	}
}

void HistoryGraphic::PushRedo(Diagram *diagram, Long zoomRate){
	
	if (this->redoGraphicArray->GetCapacity() < 50) {
		this->redoGraphicArray->AppendFromFront(static_cast<Diagram*>(diagram->Clone()));
		this->redoGraphicZoomRateArray->AppendFromFront(zoomRate);
	}
	else {
		this->redoGraphicArray->Insert(0, static_cast<Diagram*>(diagram->Clone()));
		this->redoGraphicArray->DeleteFromRear();
		this->redoGraphicZoomRateArray->Insert(0, zoomRate);
		this->redoGraphicZoomRateArray->DeleteFromRear();
	}
	Long i = 0;
	while (i <diagram->GetLength()) {
		FigureComposite *figureComposite = static_cast<FigureComposite*>(diagram->GetAt(i));
		Long j = 0;
		while (j < figureComposite->GetLength()) {
			Figure *figure = figureComposite->GetAt(j);
			if (figure->GetEndPointFigure() != 0) {
				Long k = 0;
				while (k < diagram->GetLength() && figure->GetEndPointFigure() != diagram->GetAt(k)) {
					k++;
				}
				if (k < diagram->GetLength()) {
					Diagram *diagrams = this->redoGraphicArray->GetAt(0);
					FigureComposite *tempFigureComposite = static_cast<FigureComposite*>(diagrams->GetAt(i));
					Figure *temp = tempFigureComposite->GetAt(j);
					temp->SetEndPointFigure(diagrams->GetAt(k));
				}
			}
			j++;
		}
		i++;
	}
}

void HistoryGraphic::PopRedoGraphic(Diagram*(*diagram), Long *zoomRate){
	//Diagram *diagram = 0;
	if (this->redoGraphicArray->GetLength() > 0) {
		(*diagram) = this->redoGraphicArray->GetAt(0);
		this->redoGraphicArray->Delete(0);
		(*zoomRate) = this->redoGraphicZoomRateArray->GetAt(0);
		this->redoGraphicZoomRateArray->Delete(0);
	}
}
