//ResizeVisitor.cpp

#include "ResizeVisitor.h"
#include "Diagram.h"

#include "Class.h"
#include "MemoBox.h"
#include "Relation.h"
#include "Line.h"
#include "SelfRelation.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"
#include "Template.h"
#include "Selection.h"
#include "MemoLine.h"
#include "RollNameBox.h"

#include "LastClass.h"
#include "ClassDiagramForm.h"

ResizeVisitor::ResizeVisitor(Long previousZoomRate, Long nextZoomRate) {
	this->previousZoomRate = previousZoomRate;
	this->nextZoomRate = nextZoomRate;
}
ResizeVisitor::~ResizeVisitor() {
}

void ResizeVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
}

void ResizeVisitor::Visit(Class *object, CDC* cPaintDc) {
	Long x1 = object->GetX();
	Long y1 = object->GetY();
	Long x2 = object->GetX() + object->GetWidth();
	Long y2 = object->GetY() + object->GetHeight();
	object->SetX(x1*this->nextZoomRate / this->previousZoomRate);
	object->SetY(y1*this->nextZoomRate / this->previousZoomRate);
	object->SetWidth((x2*this->nextZoomRate / this->previousZoomRate) - object->GetX());
	object->SetHeight((y2*this->nextZoomRate / this->previousZoomRate) - object->GetY());
	object->SetMinimumWidth(object->GetMinimumWidth()*this->nextZoomRate / this->previousZoomRate);
	object->SetMinimumHeight(object->GetMinimumHeight()* this->nextZoomRate/ this->previousZoomRate);
}

void ResizeVisitor::Visit(Text* text, CDC* cPaintDc) {
}

void  ResizeVisitor::Visit(SelfRelation *selfRelation, CDC *cPaintDc) {
	selfRelation->SetX(selfRelation->GetX() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetY(selfRelation->GetY() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetWidth(selfRelation->GetWidth() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetHeight(selfRelation->GetHeight() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetMinimumWidth(selfRelation->GetMinimumWidth() * this->nextZoomRate / this->previousZoomRate);
	selfRelation->SetMinimumHeight(selfRelation->GetMinimumHeight() * this->nextZoomRate / this->previousZoomRate);

	Long x = selfRelation->GetX();
	Long y = selfRelation->GetY();

	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	RollNameBox *rollNameBox = RollNameBox::Instance();
	// 辦難檜賊
	if (selfRelation->leftRightFlag == 0) {
		CPoint startPoint1And4{ x, y };
		CPoint endPoint1And4{ x , y - 40 * this->nextZoomRate / 100 };

		CPoint startPoint2{ x, y - 40 * this->nextZoomRate / 100 };
		CPoint endPoint2{ x + 80 * this->nextZoomRate / 100,  y - 40 * this->nextZoomRate / 100 };

		CPoint startPoint3And5{ x + 80 * this->nextZoomRate / 100, y + 40 * this->nextZoomRate / 100 };
		CPoint endPoint3And5{ x + 30 * this->nextZoomRate / 100,  y + 40 * this->nextZoomRate / 100 };

		selfRelation->rollNamePoints->Modify(0, rollNameBox->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4));
		selfRelation->rollNamePoints->Modify(1, rollNameBox->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2));
		selfRelation->rollNamePoints->Modify(2, rollNameBox->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5));
		selfRelation->rollNamePoints->Modify(3, rollNameBox->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4));
		selfRelation->rollNamePoints->Modify(4, rollNameBox->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5));
	}
	// 謝難檜賊
	else {
		CPoint startPoint1And4{ x, y };
		CPoint endPoint1And4{ x , y - 40 * this->nextZoomRate / 100 };

		CPoint startPoint2{ x - 90 * this->nextZoomRate / 100, y - 40 * this->nextZoomRate / 100 };
		CPoint endPoint2{ x - 80 * this->nextZoomRate / 100,  y - 40 * this->nextZoomRate / 100 };

		CPoint startPoint5{ x - 30 * this->nextZoomRate / 100,  y + 40 * this->nextZoomRate / 100 };
		CPoint endPoint5{ x - 80 * this->nextZoomRate / 100, y + 40 * this->nextZoomRate / 100 };

		CPoint startPoint3{ x - 80 * this->nextZoomRate / 100, y + 40 * this->nextZoomRate / 100 };
		CPoint endPoint3{ x - 120 * this->nextZoomRate / 100, y + 40 * this->nextZoomRate / 100 };

		selfRelation->rollNamePoints->Modify(0, rollNameBox->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4));
		selfRelation->rollNamePoints->Modify(1, rollNameBox->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2));
		selfRelation->rollNamePoints->Modify(2, rollNameBox->GetSelfRelationThirdRollNamePoint(startPoint3, endPoint3));
		selfRelation->rollNamePoints->Modify(3, rollNameBox->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4));
		selfRelation->rollNamePoints->Modify(4, rollNameBox->GetSelfRelationFifthRollNamePoint(startPoint5, endPoint5));
	}
}

void  ResizeVisitor::Visit(Relation *relation, CDC *pDC) {
	Long x1 = relation->GetX();
	Long y1 = relation->GetY();
	Long x2 = relation->GetX() + relation->GetWidth();
	Long y2 = relation->GetY() + relation->GetHeight();
	relation->SetX(x1*this->nextZoomRate / this->previousZoomRate);
	relation->SetY(y1*this->nextZoomRate / this->previousZoomRate);
	relation->SetWidth((x2*this->nextZoomRate / this->previousZoomRate) - relation->GetX());
	relation->SetHeight((y2*this->nextZoomRate / this->previousZoomRate) - relation->GetY());
	relation->SetMinimumWidth(relation->GetMinimumWidth() * this->nextZoomRate / this->previousZoomRate);
	relation->SetMinimumHeight(relation->GetMinimumHeight() * this->nextZoomRate / this->previousZoomRate);

	Long i = 0;
	CPoint tempPoint;
	while (i < relation->GetLength()) {
		tempPoint = relation->GetAt(i);
		tempPoint.x = tempPoint.x * this->nextZoomRate / this->previousZoomRate;
		tempPoint.y = tempPoint.y* this->nextZoomRate / this->previousZoomRate;
		relation->Correct(i, tempPoint);
		i++;
	}

	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();

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

		CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
			relation->GetAt(relation->GetLength() - 1).y };
		CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
		cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
		cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
		relation->rollNamePoints->Modify(2, cPoint3);
		relation->rollNamePoints->Modify(4, cPoint5);

		if (relation->GetLength() % 2 == 0) {//礎熱

			CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
				relation->GetAt((relation->GetLength() - 1) / 2).y };
			CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
				relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
			cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
			relation->rollNamePoints->Modify(1, cPoint2);

		}
		else {//�汝�

			CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
				relation->GetAt((relation->GetLength() - 1) / 2).y };
			cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
			relation->rollNamePoints->Modify(1, cPoint2);

		}
	}
}

void ResizeVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) {
	Long x1 = memoBox->GetX();
	Long y1 = memoBox->GetY();
	Long x2 = memoBox->GetX() + memoBox->GetWidth();
	Long y2 = memoBox->GetY() + memoBox->GetHeight();
	memoBox->SetX(x1*this->nextZoomRate / this->previousZoomRate);
	memoBox->SetY(y1*this->nextZoomRate / this->previousZoomRate);
	memoBox->SetWidth((x2*this->nextZoomRate / this->previousZoomRate) - memoBox->GetX());
	memoBox->SetHeight((y2*this->nextZoomRate / this->previousZoomRate) - memoBox->GetY());
	memoBox->SetMinimumWidth(memoBox->GetMinimumWidth()*this->nextZoomRate / this->previousZoomRate);
	memoBox->SetMinimumHeight(memoBox->GetMinimumHeight() * this->nextZoomRate/ this->previousZoomRate);
}

#include "SmartPointer.h"


void ResizeVisitor::Visit(Selection *selection, CDC *cPaintDc) {
	SmartPointer<Figure*> smartPointer(selection->CreateIterator());
	while (!smartPointer->IsDone()) {
		if (dynamic_cast<Class*>(smartPointer->Current())) {
			static_cast<Class*>(smartPointer->Current())->Accept(*this, cPaintDc);
		}
		else if (dynamic_cast<MemoBox*>(smartPointer->Current())) {
			static_cast<MemoBox*>(smartPointer->Current())->Accept(*this, cPaintDc);
		}
		smartPointer->Next();
	}
}

void ResizeVisitor::Visit(Template *object, CDC *cPaintDc) {
	Long x1 = object->GetX();
	Long y1 = object->GetY();
	Long x2 = object->GetX() + object->GetWidth();
	Long y2 = object->GetY() + object->GetHeight();
	object->SetX(x1*this->nextZoomRate / this->previousZoomRate);
	object->SetY(y1*this->nextZoomRate / this->previousZoomRate);
	object->SetWidth((x2*this->nextZoomRate / this->previousZoomRate) - object->GetX());
	object->SetHeight((y2*this->nextZoomRate / this->previousZoomRate) - object->GetY());
	object->SetMinimumWidth(object->GetMinimumWidth() * this->nextZoomRate / this->previousZoomRate);
	object->SetMinimumHeight(object->GetMinimumHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(ClassName* className, CDC* cPaintDc) {
	Long x1 = className->GetX();
	Long y1 = className->GetY();
	Long x2 = className->GetX() + className->GetWidth();
	Long y2 = className->GetY() + className->GetHeight();
	className->SetX(x1*this->nextZoomRate / this->previousZoomRate);
	className->SetY(y1*this->nextZoomRate / this->previousZoomRate);
	className->SetWidth((x2*this->nextZoomRate / this->previousZoomRate) - className->GetX());
	className->SetHeight((y2*this->nextZoomRate / this->previousZoomRate) - className->GetY());
	className->SetMinimumWidth(className->GetMinimumWidth() * this->nextZoomRate / this->previousZoomRate);
	className->SetMinimumHeight(className->GetMinimumHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(Attribute* attribute, CDC* cPaintDc) {
	Long x1 = attribute->GetX();
	Long y1 = attribute->GetY();
	Long x2 = attribute->GetX() + attribute->GetWidth();
	Long y2 = attribute->GetY() + attribute->GetHeight();
	attribute->SetX(x1*this->nextZoomRate / this->previousZoomRate);
	attribute->SetY(y1*this->nextZoomRate / this->previousZoomRate);
	attribute->SetWidth((x2*this->nextZoomRate / this->previousZoomRate) - attribute->GetX());
	attribute->SetHeight((y2*this->nextZoomRate / this->previousZoomRate) - attribute->GetY());
	attribute->SetMinimumWidth(attribute->GetMinimumWidth() * this->nextZoomRate / this->previousZoomRate);
	attribute->SetMinimumHeight(attribute->GetMinimumHeight() * this->nextZoomRate / this->previousZoomRate);
}
void ResizeVisitor::Visit(Method* method, CDC* cPaintDc) {
	Long x1 = method->GetX();
	Long y1 = method->GetY();
	Long x2 = method->GetX() + method->GetWidth();
	Long y2 = method->GetY() + method->GetHeight();
	method->SetX(x1*this->nextZoomRate / this->previousZoomRate);
	method->SetY(y1*this->nextZoomRate / this->previousZoomRate);
	method->SetWidth((x2*this->nextZoomRate / this->previousZoomRate) - method->GetX());
	method->SetHeight((y2*this->nextZoomRate / this->previousZoomRate) - method->GetY());
	method->SetMinimumWidth(method->GetMinimumWidth() * this->nextZoomRate / this->previousZoomRate);
	method->SetMinimumHeight(method->GetMinimumHeight() * this->nextZoomRate / this->previousZoomRate);
}
void ResizeVisitor::Visit(Reception* reception, CDC* cPaintDc) {
	Long x1 = reception->GetX();
	Long y1 = reception->GetY();
	Long x2 = reception->GetX() + reception->GetWidth();
	Long y2 = reception->GetY() + reception->GetHeight();
	reception->SetX(x1*this->nextZoomRate / this->previousZoomRate);
	reception->SetY(y1*this->nextZoomRate / this->previousZoomRate);
	reception->SetWidth((x2*this->nextZoomRate / this->previousZoomRate) - reception->GetX());
	reception->SetHeight((y2*this->nextZoomRate / this->previousZoomRate) - reception->GetY());
	reception->SetMinimumWidth(reception->GetMinimumWidth() * this->nextZoomRate / this->previousZoomRate);
	reception->SetMinimumHeight(reception->GetMinimumHeight() * this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(Line *line, CDC* cPaintDc) {
	Long x1 = line->GetX();
	Long y1 = line->GetY();
	Long x2 = line->GetX() + line->GetWidth();
	Long y2 = line->GetY() + line->GetHeight();
	line->SetX(x1*this->nextZoomRate / this->previousZoomRate);
	line->SetY(y1*this->nextZoomRate / this->previousZoomRate);
	line->SetWidth((x2*this->nextZoomRate / this->previousZoomRate) - line->GetX());
	line->SetHeight((y2*this->nextZoomRate / this->previousZoomRate) - line->GetY());
	line->SetMinimumWidth(line->GetMinimumWidth()*this->nextZoomRate / this->previousZoomRate);
	line->SetMinimumHeight(line->GetMinimumHeight()* this->nextZoomRate / this->previousZoomRate);
}

void ResizeVisitor::Visit(Generalization *generalization, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Realization *realization, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Dependency *dependency, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Association *association, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Aggregation *aggregation, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Aggregations *aggregations, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Composition *composition, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(Compositions *compositions, CDC* cPaintDc) {
}
void ResizeVisitor::Visit(MemoLine *memoLine, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfGeneralization *selfGeneralization, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfDependency *selfDependency, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfAggregation *selfAggregation, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfAssociation *selfAssociation, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfAggregations *selfAggregations, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfComposition *selfComposition, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(SelfCompositions *selfCompositions, CDC *cPaintDc) {
}
void ResizeVisitor::Visit(Class *object, Long distanceX, Long distanceY) {
}
void ResizeVisitor::Visit(MemoBox *memoBox, Long distanceX, Long distanceY) {
}