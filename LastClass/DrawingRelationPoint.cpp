//DrawingRelationPoint.cpp

#include "DrawingRelationPoint.h"
#include "Relation.h"
#include "Finder.h"
#include "Selection.h"
#include "Diagram.h"
#include "SelectionState.h"
#include "RollNameBox.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "PreciseMoving.h"

DrawingRelationPoint* DrawingRelationPoint::instance = 0;

MouseLButtonAction* DrawingRelationPoint::Instance() {
	if (instance == 0) {
		instance = new DrawingRelationPoint;
	}
	return instance;
}
void DrawingRelationPoint::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Relation *relation = static_cast<Relation*>(selection->GetAt(0));
	bool point = false;
	bool startLine = false;
	bool squareFace = false;
	bool endLine = false;
	CPoint lineStart(relation->GetX(), relation->GetY());
	CPoint lineEnd;
	Long index = 0;
	Finder finder;
	CPoint startCPoint;
	CPoint currentCPoint;
	PreciseMoving temp;
	temp.ConvertPoint(&currentX, &currentY);
	startCPoint.x = startX;
	startCPoint.y = startY;
	currentCPoint.x = currentX;
	currentCPoint.y = currentY;

	classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
	classDiagramForm->historyGraphic->redoGraphicArray->Clear();
	classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;


	while (index < relation->GetLength() && point == false) {
		CRect rect(relation->GetAt(index).x - 10, relation->GetAt(index).y - 10, relation->GetAt(index).x + 10, relation->GetAt(index).y + 10);
		point = finder.FindRectangleByPoint(rect, startX, startY);
		index++;
	}
	if (point == true) {
		CPoint point(currentX, currentY);
		relation->MergePoints(index, point);
		//병합에  맞게 텍스트 위치 이동

		CPoint startPoint{ relation->GetX(), relation->GetY() };
		CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
		cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
		cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
		relation->rollNamePoints->Modify(0, cPoint1);
		relation->rollNamePoints->Modify(3, cPoint4);
		CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
			relation->GetAt(relation->GetLength() - 1).y };
		CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
		cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
		cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
		relation->rollNamePoints->Modify(2, cPoint3);
		relation->rollNamePoints->Modify(4, cPoint5);

		if (relation->GetLength() % 2 > 0) {
			CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
				relation->GetAt((relation->GetLength() - 1) / 2).y };
			cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
			relation->rollNamePoints->Modify(1, cPoint2);

		}
		else {
			CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
				relation->GetAt((relation->GetLength() - 1) / 2).y };
			CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
				relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
			cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
			relation->rollNamePoints->Modify(1, cPoint2);
		}


		relation->Move(index - 1, point);
		//이동에 맞게 텍스트 위치 이동
		if (index == 1) {//처음 포인트이동
			CPoint startPoint{ relation->GetX(), relation->GetY() };
			CPoint endPoint{ currentX, currentY };
			cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
			cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
			relation->rollNamePoints->Modify(0, cPoint1);
			relation->rollNamePoints->Modify(3, cPoint4);
		}
		if (index == relation->GetLength()) {//마지막 포인트 이동
			CPoint startPoint3{ currentX, currentY };
			CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
			cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
			cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
			relation->rollNamePoints->Modify(2, cPoint3);
			relation->rollNamePoints->Modify(4, cPoint5);
		}
		if (relation->GetLength() % 2 == 0) {//짝수
			if (index == relation->GetLength() / 2 || index == relation->GetLength() / 2 + 1) {//중간거 영향 주는거
				CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
					relation->GetAt((relation->GetLength() - 1) / 2).y };
				CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
					relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
				cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
				relation->rollNamePoints->Modify(1, cPoint2);
			}
		}
		else {//홀수
			if (index == relation->GetLength() / 2 + 1) {//중간거 영향 주는거
				CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
					relation->GetAt((relation->GetLength() - 1) / 2).y };
				cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
				relation->rollNamePoints->Modify(1, cPoint2);
			}
		}

	}
	if (point == false && startLine == false) {
		Long j = 0;
		while (j < relation->GetLength() && squareFace == false) {
			lineEnd.x = relation->GetAt(j).x;
			lineEnd.y = relation->GetAt(j).y;
			squareFace = finder.FindLineByPoint(lineStart, lineEnd, startX, startY);
			lineStart.x = lineEnd.x;
			lineStart.y = lineEnd.y;
			j++;
		}
		if (squareFace == false) {
			lineEnd.x = relation->GetWidth() + relation->GetX();
			lineEnd.y = relation->GetHeight() + relation->GetY();
			squareFace = finder.FindLineByPoint(lineStart, lineEnd, startX, startY);
		}
		if (squareFace == true) {
			relation->Add(startCPoint, currentCPoint);

			CPoint startPoint{ relation->GetX(), relation->GetY() };
			CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
			cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
			cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
			relation->rollNamePoints->Modify(0, cPoint1);
			relation->rollNamePoints->Modify(3, cPoint4);
			CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
				relation->GetAt(relation->GetLength() - 1).y };
			CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
			cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
			cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
			relation->rollNamePoints->Modify(2, cPoint3);
			relation->rollNamePoints->Modify(4, cPoint5);

			if (relation->GetLength() % 2 > 0) {
				CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
					relation->GetAt((relation->GetLength() - 1) / 2).y };
				cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
				relation->rollNamePoints->Modify(1, cPoint2);

			}
			else {
				CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
					relation->GetAt((relation->GetLength() - 1) / 2).y };
				CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
					relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
				cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
				relation->rollNamePoints->Modify(1, cPoint2);
			}

		}
	}
	this->ChangeState(mouseLButton, SelectionState::Instance());
}
void DrawingRelationPoint::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
	if (selection->GetLength() > 0) {
		this->ChangeState(mouseLButton, SelectionState::Instance());
	}
	else {
		this->ChangeDefault(mouseLButton);
	}
}
void DrawingRelationPoint::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	bool ret = false;
	bool vertex = false;
	Relation *relation = static_cast<Relation*>(selection->GetAt(0));
	Finder finder;

	CPoint lineStart(relation->GetX(), relation->GetY());
	Long index = 0;
	CPoint lineEnd;

	while (index < relation->GetLength() && ret == false) {
		CRect rect(relation->GetAt(index).x - 10, relation->GetAt(index).y - 10, relation->GetAt(index).x + 10, relation->GetAt(index).y + 10);
		ret = finder.FindRectangleByPoint(rect, startX, startY);
		index++;
	}

	if (ret == true && relation->GetLength() == 1) {
		lineEnd.x = relation->GetX() + relation->GetWidth();
		lineEnd.y = relation->GetY() + relation->GetHeight();
	}

	else if (ret == true && index == 1 && index < relation->GetLength()) {
		lineEnd.x = relation->GetAt(index).x;
		lineEnd.y = relation->GetAt(index).y;
	}
	else if (ret == true && index == relation->GetLength()) {
		lineStart.x = relation->GetAt(index - 2).x;
		lineStart.y = relation->GetAt(index - 2).y;
		lineEnd.x = relation->GetX() + relation->GetWidth();
		lineEnd.y = relation->GetY() + relation->GetHeight();
	}

	else if (ret == true) {
		lineStart.x = relation->GetAt(index - 2).x;
		lineStart.y = relation->GetAt(index - 2).y;
		lineEnd.x = relation->GetAt(index).x;
		lineEnd.y = relation->GetAt(index).y;
	}

	Long j = 0;
	while (j < relation->GetLength() && ret == false) {
		lineEnd.x = relation->GetAt(j).x;
		lineEnd.y = relation->GetAt(j).y;
		ret = finder.FindLineByPoint(lineStart, lineEnd, startX, startY);
		if (ret == false) {
			lineStart.x = lineEnd.x;
			lineStart.y = lineEnd.y;
		}
		j++;
	}
	if (ret == false) {
		lineEnd.x = relation->GetWidth() + relation->GetX();
		lineEnd.y = relation->GetHeight() + relation->GetY();
		ret = finder.FindLineByPoint(lineStart, lineEnd, startX, startY);
	}

	CRect rect(relation->GetX() - 10, relation->GetY() - 10, relation->GetX() + 10, relation->GetY() + 10);
	vertex = finder.FindRectangleByPoint(rect, currentX, currentY);
	Long i = 0;
	while (i < relation->GetLength() && vertex == false) {
		CRect rect(relation->GetAt(i).x - 10, relation->GetAt(i).y - 10, relation->GetAt(i).x + 10, relation->GetAt(i).y + 10);
		vertex = finder.FindRectangleByPoint(rect, currentX, currentY);
		i++;
	}
	if (vertex == false) {
		CRect rect(relation->GetX() + relation->GetWidth() - 10, relation->GetY() + relation->GetHeight() - 10, relation->GetX() + relation->GetWidth() + 10, relation->GetY() + relation->GetHeight() + 10);
		vertex = finder.FindRectangleByPoint(rect, currentX, currentY);
	}
	if (vertex == true) {
		if (i == 0) {
			lineStart.x = relation->GetX();
			lineStart.y = relation->GetY();
		}
		else if (i < index) {
			lineStart.x = relation->GetAt(i - 1).x;
			lineStart.y = relation->GetAt(i - 1).y;
		}
		else if (i > relation->GetLength()) {
			lineEnd.x = relation->GetX() + relation->GetWidth();
			lineEnd.y = relation->GetY() + relation->GetHeight();
		}
		else if (i > index) {
			lineEnd.x = relation->GetAt(i - 1).x;
			lineEnd.y = relation->GetAt(i - 1).y;
		}

	}
	PreciseMoving temp;
	temp.ConvertPoint(&currentX, &currentY);

	if (ret == true) {
		pDC->MoveTo(lineStart.x, lineStart.y);
		pDC->LineTo(currentX, currentY);
		pDC->MoveTo(lineEnd.x, lineEnd.y);
		pDC->LineTo(currentX, currentY);
	}
}