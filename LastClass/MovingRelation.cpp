#include "MovingRelation.h"
#include "Relation.h"
#include "Finder.h"
#include "Selection.h"
#include "SelectionState.h"
#include "Diagram.h"
#include "RollNameBox.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "PreciseMoving.h"

MovingRelation* MovingRelation::instance = 0;

MouseLButtonAction* MovingRelation::Instance() {
	if (instance == 0) {
		instance = new MovingRelation;
	}
	return instance;
}

void MovingRelation::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
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
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	CPoint startLinePoint;
	CPoint endLinePoint;
	startCPoint.x = startX;
	startCPoint.y = startY;
	PreciseMoving temp;
	temp.ConvertPoint(&currentX, &currentY);
	currentCPoint.x = currentX;
	currentCPoint.y = currentY;

	classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
	classDiagramForm->historyGraphic->redoGraphicArray->Clear();
	classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

	CRect object(relation->GetX() - 10, relation->GetY() - 10, relation->GetX() + 10, relation->GetY() + 10);
	startLine = finder.FindRectangleByPoint(object, startX, startY);
	if (startLine == true) {

		Figure *figure = finder.GetParents(diagram, relation);
		Long x = figure->GetX();
		Long y = figure->GetY();
		Long width = figure->GetWidth();
		Long height = figure->GetHeight();
		Long relationX = currentX;
		Long relationY = currentY;
		if (x + width <= currentX) {
			relationX = x + width - 1;
		}
		else if (x >= currentX) {
			relationX = x + 1;
		}
		if (y + height <= currentY) {
			relationY = y + height - 1;
		}
		else if (figure->GetY() >= currentY) {
			relationY = figure->GetY() + 1;
		}

		CRect rect(x, y, x + width, y + height);
		Finder finder;
		startLinePoint.x = relationX;
		startLinePoint.y = relationY;

		if (relation->GetLength() == 0) {
			endLinePoint.x = relation->GetX() + relation->GetWidth();
			endLinePoint.y = relation->GetY() + relation->GetHeight();
		}
		else {
			endLinePoint.x = relation->GetAt(0).x;
			endLinePoint.y = relation->GetAt(0).y;
		}
		CPoint cross = finder.GetCrossPoint(startLinePoint, endLinePoint, rect);
		relation->Modify(cross.x, cross.y, relation->GetWidth() + relation->GetX() - cross.x, relation->GetHeight() + relation->GetY() - cross.y);

		if (relation->GetLength() == 0) {
			CPoint startPoint{ relation->GetX(), relation->GetY() };
			CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
			cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
			cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
			cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
			cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
			cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
			relation->rollNamePoints->Modify(0, cPoint1);
			relation->rollNamePoints->Modify(1, cPoint2);
			relation->rollNamePoints->Modify(2, cPoint3);
			relation->rollNamePoints->Modify(3, cPoint4);
			relation->rollNamePoints->Modify(4, cPoint5);
		}
		else {
			CPoint startPoint{ relation->GetX(), relation->GetY() };
			CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
			cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
			cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
			relation->rollNamePoints->Modify(0, cPoint1);
			relation->rollNamePoints->Modify(3, cPoint4);
		}

	}
	else { // 끝점찾기
		Long i = 0;
		FigureComposite *figures = 0;

		while (i < diagram->GetLength() && endLine != true) {
			figures = static_cast<FigureComposite*>(diagram->GetAt(i));
			if (relation->GetEndPointFigure() == figures) {
				endLine = true;
			}
			//CRect object(figures->GetX(), figures->GetY(), figures->GetX() + figures->GetWidth(), figures->GetY() + figures->GetHeight());
			//endLine = finder.FindRectangleByPoint(object, relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight());
			i++;
		}

		if (endLine == true) {
			//끝점 변경하는 로직.
			Long x = figures->GetX();
			Long y = figures->GetY();
			Long width = figures->GetWidth();
			Long height = figures->GetHeight();
			Long relationX = currentX;
			Long relationY = currentY;
			if (x + width < currentX) {
				relationX = x + width - 1;
			}
			else if (x > currentX) {
				relationX = x + 1;
			}
			if (y + height < currentY) {
				relationY = y + height - 1;
			}
			else if (y > currentY) {
				relationY = y + 1;
			}

			CRect rect(x, y, x + width, y + height);
			Finder finder;

			endLinePoint.x = relationX;
			endLinePoint.y = relationY;
			if (relation->GetLength() == 0) {
				startLinePoint.x = relation->GetX();
				startLinePoint.y = relation->GetY();
			}
			else {
				startLinePoint.x = relation->GetAt(relation->GetLength() - 1).x;
				startLinePoint.y = relation->GetAt(relation->GetLength() - 1).y;
			}
			CPoint cross = finder.GetCrossPoint(startLinePoint, endLinePoint, rect);
			relation->Modify(relation->GetX(), relation->GetY(), cross.x - relation->GetX(), cross.y - relation->GetY());

			if (relation->GetLength() == 0) {
				CPoint startPoint{ relation->GetX(), relation->GetY() };
				CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
				cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
				cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
				cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
				cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
				cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
				relation->rollNamePoints->Modify(0, cPoint1);
				relation->rollNamePoints->Modify(1, cPoint2);
				relation->rollNamePoints->Modify(2, cPoint3);
				relation->rollNamePoints->Modify(3, cPoint4);
				relation->rollNamePoints->Modify(4, cPoint5);
			}
			else {
				CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
					relation->GetAt(relation->GetLength() - 1).y };
				CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
				cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
				cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
				relation->rollNamePoints->Modify(2, cPoint3);
				relation->rollNamePoints->Modify(4, cPoint5);
			}
		}
	}
	this->ChangeState(mouseLButton, SelectionState::Instance());
}
void MovingRelation::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}
void MovingRelation::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);

	Relation *relation = static_cast<Relation*>(selection->GetAt(0));
	bool startLine = false;
	bool endLine = false;
	CPoint lineStart;
	CPoint lineEnd;
	Finder finder;

	//시작점 찾기
	CRect object(relation->GetX() - 10, relation->GetY() - 10, relation->GetX() + 10, relation->GetY() + 10);
	startLine = finder.FindRectangleByPoint(object, startX, startY);
	if (startLine == true) {
		Figure *figure = finder.GetParents(diagram, relation);
		Long x = figure->GetX();
		Long y = figure->GetY();
		Long width = figure->GetWidth();
		Long height = figure->GetHeight();
		Long relationX = currentX;
		Long relationY = currentY;

		if (x + width <= currentX) {
			relationX = x + width - 1;
		}
		else if (x >= currentX) {
			relationX = x + 1;
		}
		if (y + height <= currentY) {
			relationY = y + height - 1;
		}
		else if (figure->GetY() >= currentY) {
			relationY = figure->GetY() + 1;
		}
		lineStart.x = relationX;
		lineStart.y = relationY;

		if (relation->GetLength() > 0) {
			lineEnd.x = relation->GetAt(0).x;
			lineEnd.y = relation->GetAt(0).y;
		}
		else {
			lineEnd.x = relation->GetX() + relation->GetWidth();
			lineEnd.y = relation->GetY() + relation->GetHeight();
		}
		CRect rect(x, y, x + width, y + height);
		lineStart = finder.GetCrossPoint(lineStart, lineEnd, rect);

		PreciseMoving temp;
		temp.ConvertPoint(&lineStart.x, &lineStart.y);
	}
	else { // 끝점찾기
		Long i = 0;
		FigureComposite *figures = 0;
		while (i < diagram->GetLength() && endLine != true) {
			figures = static_cast<FigureComposite*>(diagram->GetAt(i));
			CRect object(figures->GetX(), figures->GetY(), figures->GetX() + figures->GetWidth(), figures->GetY() + figures->GetHeight());
			endLine = finder.FindRectangleByPoint(object, relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight());
			i++;
		}
		if (endLine == true) {
			Long x = figures->GetX();
			Long y = figures->GetY();
			Long width = figures->GetWidth();
			Long height = figures->GetHeight();
			Long relationX = currentX;
			Long relationY = currentY;

			if (x + width < currentX) {
				relationX = x + width - 1;
			}
			else if (x > currentX) {
				relationX = x + 1;
			}
			if (y + height < currentY) {
				relationY = y + height - 1;
			}
			else if (y > currentY) {
				relationY = y + 1;
			}

			CRect rect(x, y, x + width, y + height);
			Finder finder;


			if (relation->GetLength() > 0) {
				lineStart.x = relation->GetAt(relation->GetLength() - 1).x;
				lineStart.y = relation->GetAt(relation->GetLength() - 1).y;
			}
			else {

				lineStart.x = relation->GetX();
				lineStart.y = relation->GetY();
			}
			lineEnd.x = relationX;
			lineEnd.y = relationY;


			lineEnd = finder.GetCrossPoint(lineStart, lineEnd, rect);

			PreciseMoving temp;
			temp.ConvertPoint(&lineEnd.x, &lineEnd.y);
		}
	}
	pDC->MoveTo(lineStart.x, lineStart.y);
	pDC->LineTo(lineEnd.x, lineEnd.y);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();

}