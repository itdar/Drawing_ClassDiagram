//MovingSelfRelation.cpp
#include "MovingSelfRelation.h"
#include "SelfRelation.h"
#include "Figure.h"
#include "Diagram.h"
#include "Class.h"
#include "ClassDiagramForm.h"
#include "SelectionState.h"
#include "Selection.h"
#include "LastClass.h"
#include "RollNameBox.h"
#include "HistoryGraphic.h"

MovingSelfRelation* MovingSelfRelation::instance = 0;

MouseLButtonAction* MovingSelfRelation::Instance() {
	if (instance == 0) {
		instance = new MovingSelfRelation;
	}
	return instance;
}
void MovingSelfRelation::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	CPoint cPoint;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	SelfRelation *selfRelation = static_cast<SelfRelation*>(selection->GetAt(0));
	Long k = 0;
	Long l = 0;
	Long temp = -1;
	Class *object;
	Long i = 0;
	while (k < diagram->GetLength() && temp == -1) {
		if (dynamic_cast<Class*>(diagram->GetAt(k))) { // 클래스에서 셀프선 찾는다
			object = static_cast<Class*>(diagram->GetAt(k));
			l = 0;
			while (l < object->GetLength() && temp == -1) {
				if (static_cast<SelfRelation*>(object->GetAt(l)) == selfRelation) {
					temp = k;
				}

				l++;
			}
		}
		k++;
	}
	classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram, classDiagramForm->zoomRate);
	classDiagramForm->historyGraphic->redoGraphicArray->Clear();
	classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

	if (currentX < diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() / 2) { // 왼쪽으로 끌어다가 놓으면
		selfRelation->Modify(diagram->GetAt(temp)->GetX() + 30 * classDiagramForm->zoomRate / 100, diagram->GetAt(temp)->GetY(),
			-selfRelation->GetWidth(), -selfRelation->GetHeight());
		CPoint startPoint1And4{ selfRelation->GetX(), selfRelation->GetY() };
		CPoint endPoint1And4{ selfRelation->GetX() ,  selfRelation->GetY() - 40 * classDiagramForm->zoomRate / 100 };
		CPoint startPoint2{ selfRelation->GetX() - 90 * classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * classDiagramForm->zoomRate / 100 };
		CPoint endPoint2{ selfRelation->GetX() - 80 * classDiagramForm->zoomRate / 100,  selfRelation->GetY() - 40 * classDiagramForm->zoomRate / 100 };
		CPoint startPoint5{ selfRelation->GetX() - 30 * classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };
		CPoint endPoint5{ selfRelation->GetX() - 80 * classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };
		CPoint startPoint3{ selfRelation->GetX() - 80 * classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };
		CPoint endPoint3{ selfRelation->GetX() - 120 * classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };

		cPoint = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
		selfRelation->rollNamePoints->Modify(0, cPoint);
		cPoint = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
		selfRelation->rollNamePoints->Modify(1, cPoint);
		cPoint = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3, endPoint3);
		selfRelation->rollNamePoints->Modify(2, cPoint);
		cPoint = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
		selfRelation->rollNamePoints->Modify(3, cPoint);
		cPoint = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint5, endPoint5);
		selfRelation->rollNamePoints->Modify(4, cPoint);

		selfRelation->leftRightFlag = 1;
	}
	else { // 오른쪽으로 끌어다놓으면서
		if (static_cast<Class*>(diagram->GetAt(temp))->GetTempletePosition() == -1) { // 템플릿기호가 없으면
			selfRelation->Modify(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * classDiagramForm->zoomRate / 100, diagram->GetAt(temp)->GetY(),
				selfRelation->GetWidth(), selfRelation->GetHeight());
			CPoint startPoint1And4{ selfRelation->GetX(), selfRelation->GetY() };
			CPoint endPoint1And4{ selfRelation->GetX() ,  selfRelation->GetY() - 40 * classDiagramForm->zoomRate / 100 };
			CPoint startPoint2{ selfRelation->GetX(), selfRelation->GetY() - 40 * classDiagramForm->zoomRate / 100 };
			CPoint endPoint2{ selfRelation->GetX() + 80 * classDiagramForm->zoomRate / 100,  selfRelation->GetY() - 40 * classDiagramForm->zoomRate / 100 };
			CPoint startPoint3And5{ selfRelation->GetX() + 80 * classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };
			CPoint endPoint3And5{ selfRelation->GetX() + 30 * classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };

			cPoint = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
			selfRelation->rollNamePoints->Modify(0, cPoint);
			cPoint = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
			selfRelation->rollNamePoints->Modify(1, cPoint);
			cPoint = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5);
			selfRelation->rollNamePoints->Modify(2, cPoint);
			cPoint = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
			selfRelation->rollNamePoints->Modify(3, cPoint);
			cPoint = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5);
			selfRelation->rollNamePoints->Modify(4, cPoint);

			selfRelation->leftRightFlag = 0;
		}
		else {
			selfRelation->Modify(diagram->GetAt(temp)->GetX() + 30 * classDiagramForm->zoomRate / 100, diagram->GetAt(temp)->GetY(),
				-selfRelation->GetWidth(), -selfRelation->GetHeight());
			CPoint startPoint1And4{ selfRelation->GetX(), selfRelation->GetY() };
			CPoint endPoint1And4{ selfRelation->GetX() ,  selfRelation->GetY() - 40 * classDiagramForm->zoomRate / 100 };
			CPoint startPoint2{ selfRelation->GetX() - 90 * classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * classDiagramForm->zoomRate / 100 };
			CPoint endPoint2{ selfRelation->GetX() - 80 * classDiagramForm->zoomRate / 100,  selfRelation->GetY() - 40 * classDiagramForm->zoomRate / 100 };
			CPoint startPoint5{ selfRelation->GetX() - 30 * classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };
			CPoint endPoint5{ selfRelation->GetX() - 80 * classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };
			CPoint startPoint3{ selfRelation->GetX() - 80 * classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };
			CPoint endPoint3{ selfRelation->GetX() - 120 * classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * classDiagramForm->zoomRate / 100 };

			cPoint = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
			selfRelation->rollNamePoints->Modify(0, cPoint);
			cPoint = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
			selfRelation->rollNamePoints->Modify(1, cPoint);
			cPoint = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3, endPoint3);
			selfRelation->rollNamePoints->Modify(2, cPoint);
			cPoint = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
			selfRelation->rollNamePoints->Modify(3, cPoint);
			cPoint = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint5, endPoint5);
			selfRelation->rollNamePoints->Modify(4, cPoint);

			selfRelation->leftRightFlag = 1;
		}
	}
	this->ChangeState(mouseLButton, SelectionState::Instance());
}


void MovingSelfRelation::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}
void MovingSelfRelation::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	LastClass *test = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);

	SelfRelation *selfRelation = static_cast<SelfRelation*>(selection->GetAt(0));
	Long k = 0;
	Long l = 0;
	Long temp = -1;
	Class *object;

	while (k < diagram->GetLength() && temp == -1) {
		if (dynamic_cast<Class*>(diagram->GetAt(k))) {
			object = static_cast<Class*>(diagram->GetAt(k));
			l = 0;
			while (l < object->GetLength() && temp == -1) {
				if (dynamic_cast<SelfRelation*>(object->GetAt(l)) == selfRelation) {
					temp = k;
				}

				l++;
			}
		}
		k++;
	}
	if (currentX < diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() / 2) {
		pDC->MoveTo(diagram->GetAt(temp)->GetX() + 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY());
		pDC->LineTo(diagram->GetAt(temp)->GetX() + 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
		pDC->MoveTo(diagram->GetAt(temp)->GetX() + 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
		pDC->LineTo(diagram->GetAt(temp)->GetX() - 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
		pDC->MoveTo(diagram->GetAt(temp)->GetX() - 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
		pDC->LineTo(diagram->GetAt(temp)->GetX() - 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
		pDC->MoveTo(diagram->GetAt(temp)->GetX() - 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
		pDC->LineTo(diagram->GetAt(temp)->GetX(), selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
	}
	else {
		if (dynamic_cast<Class*>(diagram->GetAt(temp))->GetTempletePosition() == -1) {
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY());
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth(), selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
		}
		else {
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 17 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() - 30 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
			pDC->MoveTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth() + 50 * test->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
			pDC->LineTo(diagram->GetAt(temp)->GetX() + diagram->GetAt(temp)->GetWidth(), selfRelation->GetY() + 40 * test->classDiagramForm->zoomRate / 100);
		}

	}


	pDC->SelectObject(oldPen);
	pen.DeleteObject();

}