#include "MovingObject.h"
#include "Figure.h"
#include "Selection.h"
#include "Finder.h"
#include "Line.h"
#include "SelectionState.h"
#include "Relation.h"
#include "Diagram.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "RollNameBox.h"
#include "PreciseMoving.h"

MovingObject* MovingObject::instance = 0;

MouseLButtonAction* MovingObject::Instance() {
	if (instance == 0) {
		instance = new MovingObject;
	}
	return instance;
}

void MovingObject::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;

	//if (dynamic_cast<FigureComposite*>(selection->GetAt(0))) {
	if(selection->GetLength() > 0){
		MovingVisitor movingVisitor;
		FigureComposite *figures = static_cast<FigureComposite*>(selection->GetAt(0));
		Finder finder;
		Long i = 0;
		Long j = 0;
		bool ret = false;

		CRect cRect1(figures->GetX() + (currentX - startX), figures->GetY() + (currentY - startY), figures->GetX() + (currentX - startX) + figures->GetWidth(), figures->GetY() + (currentY - startY) + figures->GetHeight());
		//ret = diagram->CheckOverlapSelection(cRect1, selection);

		// FigureComposite에 관계선 점 겹치면 점 Remove
		i = 0;
		while (i < figures->GetLength()) {
			if (dynamic_cast<Relation*>(figures->GetAt(i))) {
				Relation *object = static_cast<Relation*>(figures->GetAt(i));
				j = 0;
				while (j < object->GetLength()) {
					CPoint cPoint = object->GetAt(j);
					bool ret1 = finder.FindRectangleByPoint(cRect1, cPoint.x, cPoint.y);
					if (ret1 == true) {
						object->Remove(j);
						CPoint startPoint{ object->GetX(), object->GetY() };
						CPoint endPoint{ object->GetAt(0).x, object->GetAt(0).y };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						object->rollNamePoints->Modify(0, cPoint1);
						object->rollNamePoints->Modify(3, cPoint4);
						CPoint startPoint3{ object->GetAt(object->GetLength() - 1).x,
							object->GetAt(object->GetLength() - 1).y };
						CPoint endPoint3{ object->GetX() + object->GetWidth() , object->GetY() + object->GetHeight() };
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
						object->rollNamePoints->Modify(2, cPoint3);
						object->rollNamePoints->Modify(4, cPoint5);

						if (object->GetLength() % 2 > 0) {
							CPoint startPoint2{ object->GetAt((object->GetLength() - 1) / 2).x,
								object->GetAt((object->GetLength() - 1) / 2).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
							object->rollNamePoints->Modify(1, cPoint2);

						}
						else {
							CPoint startPoint2{ object->GetAt((object->GetLength() - 1) / 2).x,
								object->GetAt((object->GetLength() - 1) / 2).y };
							CPoint endPoint2{ object->GetAt((object->GetLength() - 1) / 2 + 1).x,
								object->GetAt((object->GetLength() - 1) / 2 + 1).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
							object->rollNamePoints->Modify(1, cPoint2);
						}

						j--;
					}
					j++;
				}
			}
			i++;
		}
	}
	this->ChangeState(mouseLButton, SelectionState::Instance());
}

void MovingObject::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
	if (selection->GetLength() == 0) {
		this->ChangeDefault(mouseLButton);
	}
}

void MovingObject::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;

	//if (dynamic_cast<FigureComposite*>(selection->GetAt(0))) {
	if (selection->GetLength() > 0) {
		MovingVisitor movingVisitor;
		FigureComposite *figures = static_cast<FigureComposite*>(selection->GetAt(0));
		Finder finder;
		Long i = 0;
		Long j = 0;
		bool ret = false;

		CRect cRect1(figures->GetX() + (currentX - classDiagramForm->currentX_2), figures->GetY() + (currentY - classDiagramForm->currentY_2), figures->GetX() + (currentX - classDiagramForm->currentX_2) + figures->GetWidth(), figures->GetY() + (currentY - classDiagramForm->currentY_2) + figures->GetHeight());

		i = 0;
		while (i < figures->GetLength()) {
			if (dynamic_cast<Relation*>(figures->GetAt(i))) {
				Relation *object = static_cast<Relation*>(figures->GetAt(i));
				j = 0;
				while (j < object->GetLength()) {
					CPoint cPoint = object->GetAt(j);
					//bool ret2 = true;
					bool ret1 = finder.FindRectangleByPoint(cRect1, cPoint.x, cPoint.y);
					if (ret1 == true) {
						object->Remove(j);
						CPoint startPoint{ object->GetX(), object->GetY() };
						CPoint endPoint{ object->GetAt(0).x, object->GetAt(0).y };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						object->rollNamePoints->Modify(0, cPoint1);
						object->rollNamePoints->Modify(3, cPoint4);
						CPoint startPoint3{ object->GetAt(object->GetLength() - 1).x,
							object->GetAt(object->GetLength() - 1).y };
						CPoint endPoint3{ object->GetX() + object->GetWidth() , object->GetY() + object->GetHeight() };
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
						object->rollNamePoints->Modify(2, cPoint3);
						object->rollNamePoints->Modify(4, cPoint5);

						if (object->GetLength() % 2 > 0) {
							CPoint startPoint2{ object->GetAt((object->GetLength() - 1) / 2).x,
								object->GetAt((object->GetLength() - 1) / 2).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
							object->rollNamePoints->Modify(1, cPoint2);

						}
						else {
							CPoint startPoint2{ object->GetAt((object->GetLength() - 1) / 2).x,
								object->GetAt((object->GetLength() - 1) / 2).y };
							CPoint endPoint2{ object->GetAt((object->GetLength() - 1) / 2 + 1).x,
								object->GetAt((object->GetLength() - 1) / 2 + 1).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
							object->rollNamePoints->Modify(1, cPoint2);
						}

						j--;
					}
					j++;
				}
			}
			i++;
		}
		if (classDiagramForm->firstDrag == 0) {
			classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
			classDiagramForm->historyGraphic->redoGraphicArray->Clear();
			classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

			classDiagramForm->widthGab = startX - selection->GetAt(0)->GetX();
			classDiagramForm->heightGab = startY - selection->GetAt(0)->GetY();
			classDiagramForm->firstDrag = 1;
		}

		Long nextX = currentX - classDiagramForm->widthGab;
		Long nextY = currentY - classDiagramForm->heightGab;

		PreciseMoving temp;
		temp.ConvertPoint(&nextX, &nextY);

		Long distanceX = (nextX - selection->GetAt(0)->GetX());
		Long distanceY = (nextY - selection->GetAt(0)->GetY());

		selection->Accept(diagram, movingVisitor, distanceX, distanceY);

		int vertCurPos = classDiagramForm->GetScrollPos(SB_VERT);
		int horzCurPos = classDiagramForm->GetScrollPos(SB_HORZ);
		if (selection->GetAt(0)->GetX() < -horzCurPos || selection->GetAt(0)->GetY() < -vertCurPos) {
			selection->Accept(diagram, movingVisitor, -distanceX, -distanceY);
		}
	}
	//this->ChangeState(mouseLButton, SelectionState::Instance());
}