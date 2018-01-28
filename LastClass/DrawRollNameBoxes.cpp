//DrawRollNameBoxes.cpp

#include "DrawRollNameBoxes.h"
#include "RollNameBox.h"
#include "Relation.h"
#include "SelfRelation.h"
#include "LastClass.h"
#include "Class.h"
#include "ClassDiagramForm.h"
#include "Diagram.h"
DrawRollNameBoxes* DrawRollNameBoxes::instance = 0;

DrawRollNameBoxes* DrawRollNameBoxes::Instance() {
	if (instance == 0) {
		instance = new DrawRollNameBoxes;
	}
	return instance;
}

DrawRollNameBoxes::DrawRollNameBoxes() {
}

DrawRollNameBoxes::DrawRollNameBoxes(const DrawRollNameBoxes& source) {
}

DrawRollNameBoxes::~DrawRollNameBoxes() {
}


void DrawRollNameBoxes::DrawFirstRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint{ relationLine->GetX(), relationLine->GetY() };
	CPoint endPoint{ relationLine->GetAt(0).x, relationLine->GetAt(0).y };
	cPoint = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);

	pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}

void DrawRollNameBoxes::DrawSecondRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	if (relationLine->GetLength() % 2 > 0) {
		CPoint startPoint2{ relationLine->GetAt((relationLine->GetLength() - 1) / 2).x,
			relationLine->GetAt((relationLine->GetLength() - 1) / 2).y };
		cPoint = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
		pDC->MoveTo(cPoint.x - 40 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 40 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 40 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 40 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 40 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 40, cPoint.y - 10, cPoint.x + 40, cPoint.y + 10);
	}
	else {
		CPoint startPoint2{ relationLine->GetAt((relationLine->GetLength() - 1) / 2).x,
			relationLine->GetAt((relationLine->GetLength() - 1) / 2).y };
		CPoint endPoint2{ relationLine->GetAt((relationLine->GetLength() - 1) / 2 + 1).x,
			relationLine->GetAt((relationLine->GetLength() - 1) / 2 + 1).y };
		cPoint = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
		pDC->MoveTo(cPoint.x - 40 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 40 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 40 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 40 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 40 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 40, cPoint.y - 10, cPoint.x + 40, cPoint.y + 10);
	}
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}

void DrawRollNameBoxes::DrawThirdRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint3{ relationLine->GetAt(relationLine->GetLength() - 1).x,
		relationLine->GetAt(relationLine->GetLength() - 1).y };
	CPoint endPoint3{ relationLine->GetX() + relationLine->GetWidth() , relationLine->GetY() + relationLine->GetHeight() };
	cPoint = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
	pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}

void DrawRollNameBoxes::DrawFourthRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint{ relationLine->GetX(), relationLine->GetY() };
	CPoint endPoint{ relationLine->GetAt(0).x, relationLine->GetAt(0).y };
	cPoint = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
	pDC->MoveTo(cPoint.x - 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 25 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 25 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}

void DrawRollNameBoxes::DrawFifthRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint3{ relationLine->GetAt(relationLine->GetLength() - 1).x,
		relationLine->GetAt(relationLine->GetLength() - 1).y };
	CPoint endPoint3{ relationLine->GetX() + relationLine->GetWidth() , relationLine->GetY() + relationLine->GetHeight() };

	cPoint = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);

	pDC->MoveTo(cPoint.x - 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 25 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 25 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}

void DrawRollNameBoxes::DrawBoxesWithoutCurvedLine(Relation *relationLine, CDC *pDC, Long zoomRate) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;

	CPoint startPoint{ relationLine->GetX(), relationLine->GetY() };
	CPoint endPoint{ relationLine->GetX() + relationLine->GetWidth(),  relationLine->GetY() + relationLine->GetHeight() };
	cPoint = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
	pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
	cPoint = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
	pDC->MoveTo(cPoint.x - 40 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 40 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 40 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 40 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 40 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	//pDC->Rectangle(cPoint.x - 40, cPoint.y - 10, cPoint.x + 40, cPoint.y + 10);
	cPoint = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
	pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
	cPoint = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
	pDC->MoveTo(cPoint.x - 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 25 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 25 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
	cPoint = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
	pDC->MoveTo(cPoint.x - 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x + 25 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 25 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
	pDC->LineTo(cPoint.x - 25 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
	//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}

void DrawRollNameBoxes::DrawSelfRelationRollNameBox(SelfRelation *SelfRelationLine, CDC *pDC, Long zoomRate) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint;
	LastClass *last = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	Long k = 0;
	Long l = 0;
	Long temp = -1;
	Class *object;
	while (k < last->classDiagramForm->diagram->GetLength() && temp == -1) {
		if (dynamic_cast<Class*>(last->classDiagramForm->diagram->GetAt(k))) {
			object = static_cast<Class*>(last->classDiagramForm->diagram->GetAt(k));
			l = 0;
			while (l < object->GetLength() && temp == -1) {
				if (dynamic_cast<SelfRelation*>(object->GetAt(l)) == SelfRelationLine) {
					temp = k;
				}

				l++;
			}
		}
		k++;
	}
	// ¿À¸¥ÂÊ ¼¿ÇÁ¼±ÀÌ¸é
	if (SelfRelationLine->leftRightFlag == 0) {

		CPoint startPoint1And4{ SelfRelationLine->GetX(), SelfRelationLine->GetY() };
		CPoint endPoint1And4{ SelfRelationLine->GetX() ,  SelfRelationLine->GetY() - 40 * zoomRate / 100 };

		CPoint startPoint2{ SelfRelationLine->GetX(), SelfRelationLine->GetY() - 40 * zoomRate / 100 };
		CPoint endPoint2{ SelfRelationLine->GetX() + 80 * zoomRate / 100,  SelfRelationLine->GetY() - 40 * zoomRate / 100 };

		CPoint startPoint3And5{ SelfRelationLine->GetX() + 80 * zoomRate / 100, SelfRelationLine->GetY() + 40 * zoomRate / 100 };
		CPoint endPoint3And5{ SelfRelationLine->GetX() + 30 * zoomRate / 100,  SelfRelationLine->GetY() + 40 * zoomRate / 100 };

		cPoint = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
		pDC->MoveTo(cPoint.x - 10 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 10 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 10 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 10, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
		cPoint = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
		pDC->MoveTo(cPoint.x - 30 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 30 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 30 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 30 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 30 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 30, cPoint.y - 10, cPoint.x + 30, cPoint.y + 10);
		cPoint = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5);
		pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 50 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 50 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 10, cPoint.y + 10);
		cPoint = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
		pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 50 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 50 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 10, cPoint.y + 10);
		cPoint = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5);
		pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 10 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 10 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 10, cPoint.y + 10);
	}
	// ¿ÞÂÊ ¼¿ÇÁ¼±ÀÌ¸é
	else {
		CPoint startPoint1And4{ SelfRelationLine->GetX(), SelfRelationLine->GetY() };
		CPoint endPoint1And4{ SelfRelationLine->GetX() ,  SelfRelationLine->GetY() - 40 * zoomRate / 100 };

		CPoint startPoint2{ SelfRelationLine->GetX() - 90 * zoomRate / 100, SelfRelationLine->GetY() - 40 * zoomRate / 100 };
		CPoint endPoint2{ SelfRelationLine->GetX() - 80 * zoomRate / 100,  SelfRelationLine->GetY() - 40 * zoomRate / 100 };

		CPoint startPoint5{ SelfRelationLine->GetX() - 30 * zoomRate / 100,  SelfRelationLine->GetY() + 40 * zoomRate / 100 };
		CPoint endPoint5{ SelfRelationLine->GetX() - 80 * zoomRate / 100, SelfRelationLine->GetY() + 40 * zoomRate / 100 };
		CPoint startPoint3{ SelfRelationLine->GetX() - 80 * zoomRate / 100, SelfRelationLine->GetY() + 40 * zoomRate / 100 };
		CPoint endPoint3{ SelfRelationLine->GetX() - 120 * zoomRate / 100, SelfRelationLine->GetY() + 40 * zoomRate / 100 };

		cPoint = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
		pDC->MoveTo(cPoint.x - 10 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 10 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 10 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 10, cPoint.y - 10, cPoint.x + 20, cPoint.y + 10);
		cPoint = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
		pDC->MoveTo(cPoint.x - 30 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 30 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 30 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 30 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 30 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 30, cPoint.y - 10, cPoint.x + 30, cPoint.y + 10);
		cPoint = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3, endPoint3);
		pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 50 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 50 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 10, cPoint.y + 10);
		cPoint = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
		pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 50 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 50 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 10, cPoint.y + 10);
		cPoint = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint5, endPoint5);
		pDC->MoveTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 10 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x + 10 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y + 10 * zoomRate / 100);
		pDC->LineTo(cPoint.x - 20 * zoomRate / 100, cPoint.y - 10 * zoomRate / 100);
		//pDC->Rectangle(cPoint.x - 20, cPoint.y - 10, cPoint.x + 10, cPoint.y + 10);
	}
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}