//MovingVisitor.cpp
#include "SelfRelation.h"
#include"MovingVisitor.h"
#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "Selection.h"
#include "Template.h"
#include "Line.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "MemoLine.h"
#include "RollNameBox.h"
#include "SmartPointer.h"
#include <iostream>
using namespace std;

MovingVisitor::MovingVisitor() {
}
MovingVisitor::~MovingVisitor() {
}
void MovingVisitor::Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) {
	Long length = selection->GetLength();
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	Long i = 0;
	Long j;
	Long k = 0;
	Long l = 0;
	Long m;
	Figure *figure;
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	while (i < length) {
		figure = selection->GetAt(i);

		if (dynamic_cast<FigureComposite*>(figure)) { //클래스나 메모면
			Long startX = figure->GetX();
			Long startY = figure->GetY();
			Long endX = figure->GetX() + figure->GetWidth();
			Long endY = figure->GetY() + figure->GetHeight();
			figure->Move(distanceX, distanceY); // 해당 클래스나 메모 이동
			FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환
			j = 0;
			while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
				figure = figureComposite->GetAt(j);
				figure->Move(distanceX, distanceY);
				if (dynamic_cast<Relation*>(figure)) {
					Relation *relation = static_cast<Relation*>(figure);
					m = 0;
					if (selection->GetLength() != 1) {
						while (m < relation->GetLength()) {
							CPoint point(relation->GetAt(m).x + distanceX, relation->GetAt(m).y + distanceY);
							relation->Move(m, point);
							m++;
						}
					}
					if (relation->GetLength() == 0) {
						CPoint startPoint(figure->GetX(), figure->GetY());
						CPoint endPoint(figure->GetX() + figure->GetWidth(), figure->GetY() + figure->GetHeight());
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(3, cPoint4);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(4, cPoint5);
						cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(1, cPoint2);
					}
					else if (relation->GetLength() > 0) {
						CPoint startPoint(figure->GetX(), figure->GetY());
						CPoint endPoint(relation->GetAt(0).x, relation->GetAt(0).y);
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(3, cPoint4);

					}

				}
				else if (dynamic_cast<SelfRelation*>(figure)) {
					SelfRelation *selfRelation = static_cast<SelfRelation*>(figure);
					cPoint1 = selfRelation->rollNamePoints->GetAt(0);
					cPoint1.x += distanceX;
					cPoint1.y += distanceY;
					cPoint2 = selfRelation->rollNamePoints->GetAt(1);
					cPoint2.x += distanceX;
					cPoint2.y += distanceY;
					cPoint3 = selfRelation->rollNamePoints->GetAt(2);
					cPoint3.x += distanceX;
					cPoint3.y += distanceY;
					cPoint4 = selfRelation->rollNamePoints->GetAt(3);
					cPoint4.x += distanceX;
					cPoint4.y += distanceY;
					cPoint5 = selfRelation->rollNamePoints->GetAt(4);
					cPoint5.x += distanceX;
					cPoint5.y += distanceY;
					selfRelation->rollNamePoints->Modify(0, cPoint1);
					selfRelation->rollNamePoints->Modify(1, cPoint2);
					selfRelation->rollNamePoints->Modify(2, cPoint3);
					selfRelation->rollNamePoints->Modify(3, cPoint4);
					selfRelation->rollNamePoints->Modify(4, cPoint5);
				}
				j++;
			}

			k = 0;
			while (k < diagram->GetLength()) {
				figureComposite = static_cast<FigureComposite*>(diagram->GetAt(k));
				l = 0;
				while (l < figureComposite->GetLength()) {
					if (dynamic_cast<Relation*>(figureComposite->GetAt(l))) {
						figure = figureComposite->GetAt(l);
						if (figure->GetEndPointFigure() == selection->GetAt(i)) {
							figure->EndPointMove(distanceX, distanceY);

							RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
							Relation *relation = static_cast<Relation*>(figure);
							if (relation->GetLength() == 0) {
								CPoint startPoint(figure->GetX(), figure->GetY());
								CPoint endPoint(figure->GetX() + figure->GetWidth(), figure->GetY() + figure->GetHeight());
								cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
								cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
								cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
								cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
								relation->rollNamePoints->Modify(0, cPoint1);
								relation->rollNamePoints->Modify(3, cPoint4);
								relation->rollNamePoints->Modify(2, cPoint3);
								relation->rollNamePoints->Modify(4, cPoint5);
								cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
								relation->rollNamePoints->Modify(1, cPoint2);
							}
							else {
								CPoint startPoint(relation->GetAt(relation->GetLength() - 1).x, relation->GetAt(relation->GetLength() - 1).y);
								CPoint  endPoint(figure->GetX() + figure->GetWidth(), figure->GetY() + figure->GetHeight());
								cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
								cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
								relation->rollNamePoints->Modify(2, cPoint3);
								relation->rollNamePoints->Modify(4, cPoint5);

							}
						}
					}
					l++;
				}
				k++;
			}


		}
		i++;
	}
}

void MovingVisitor::Visit(Class *object, Long distanceX, Long distanceY) {
	Figure *figure;
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();

	object->Move(distanceX, distanceY);

	SmartPointer<Figure*>classIterator(object->CreateIterator());
	for (classIterator->First();!classIterator->IsDone();classIterator->Next()) {
		figure = classIterator->Current();
		figure->Move(distanceX, distanceY);
		if (dynamic_cast<Relation*>(figure)) {
			figure->EndPointMove(distanceX, distanceY);
			Relation *relation = static_cast<Relation*>(figure);
			Long m = 0;
			while (m < relation->GetLength()) {
				CPoint point(relation->GetAt(m).x + distanceX, relation->GetAt(m).y + distanceY);
				relation->Move(m, point);
				m++;
			}
			if (relation->GetLength() == 0) {
				CPoint startPoint(figure->GetX(), figure->GetY());
				CPoint endPoint(figure->GetX() + figure->GetWidth(), figure->GetY() + figure->GetHeight());
				cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
				cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
				cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
				cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
				relation->rollNamePoints->Modify(0, cPoint1);
				relation->rollNamePoints->Modify(3, cPoint4);
				relation->rollNamePoints->Modify(2, cPoint3);
				relation->rollNamePoints->Modify(4, cPoint5);
				cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
				relation->rollNamePoints->Modify(1, cPoint2);
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

				if (relation->GetLength() % 2 == 0) {//짝수

					CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
						relation->GetAt((relation->GetLength() - 1) / 2).y };
					CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
						relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
					relation->rollNamePoints->Modify(1, cPoint2);

				}
				else {//홀수

					CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
						relation->GetAt((relation->GetLength() - 1) / 2).y };
					cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
					relation->rollNamePoints->Modify(1, cPoint2);
				}
			}
		}
		else if (dynamic_cast<SelfRelation*>(figure)) {
			SelfRelation *selfRelation = static_cast<SelfRelation*>(figure);

			cPoint1 = selfRelation->rollNamePoints->GetAt(0);
			cPoint1.x += distanceX;
			cPoint1.y += distanceY;
			cPoint2 = selfRelation->rollNamePoints->GetAt(1);
			cPoint2.x += distanceX;
			cPoint2.y += distanceY;
			cPoint3 = selfRelation->rollNamePoints->GetAt(2);
			cPoint3.x += distanceX;
			cPoint3.y += distanceY;
			cPoint4 = selfRelation->rollNamePoints->GetAt(3);
			cPoint4.x += distanceX;
			cPoint4.y += distanceY;
			cPoint5 = selfRelation->rollNamePoints->GetAt(4);
			cPoint5.x += distanceX;
			cPoint5.y += distanceY;
			selfRelation->rollNamePoints->Modify(0, cPoint1);
			selfRelation->rollNamePoints->Modify(1, cPoint2);
			selfRelation->rollNamePoints->Modify(2, cPoint3);
			selfRelation->rollNamePoints->Modify(3, cPoint4);
			selfRelation->rollNamePoints->Modify(4, cPoint5);
		}
	}
}

void MovingVisitor::Visit(Class *object, CDC* pDC) {

}
void MovingVisitor::Visit(MemoBox *memoBox, Long distanceX, Long distanceY) {
	Relation *relation;
	SmartPointer<Figure*>memoBoxIterator(memoBox->CreateIterator());
	memoBox->Move(distanceX, distanceY);
	for (memoBoxIterator->First();!memoBoxIterator->IsDone();memoBoxIterator->Next()) {
		memoBoxIterator->Current()->Move(distanceX, distanceY);
		memoBoxIterator->Current()->EndPointMove(distanceX, distanceY);
		relation = static_cast<Relation*>(memoBoxIterator->Current());
		Long i = 0;
		while (i < memoBox->GetLength()) {
			CPoint point(relation->GetAt(i).x + distanceX, relation->GetAt(i).y + distanceY);
			relation->Move(i, point);
			i++;
		}
	}
}
void MovingVisitor::Visit(MemoBox *memoBox, CDC *pDC) {

}
void MovingVisitor::Visit(Selection *selection, CDC *pDC) {
}
void MovingVisitor::Visit(Template *object, CDC *pDC) {
}
void MovingVisitor::Visit(ClassName* className, CDC* pDC) {
}
void MovingVisitor::Visit(Attribute* attribute, CDC* pDC) {;
}
void MovingVisitor::Visit(Method* method, CDC* pDC) {
}
void MovingVisitor::Visit(Reception* reception, CDC* pDC) {
}
void MovingVisitor::Visit(Line *line, CDC* pDC) {
}
void MovingVisitor::Visit(Generalization *generalization, CDC* pDC) {
}
void MovingVisitor::Visit(Realization *realization, CDC* pDC) {
}
void MovingVisitor::Visit(Dependency *dependency, CDC* pDC) {
}
void MovingVisitor::Visit(Association *association, CDC* pDC) {
}
void MovingVisitor::Visit(DirectedAssociation *directedAssociation, CDC* pDC) {
}
void MovingVisitor::Visit(Aggregation *aggregation, CDC* pDC) {
}
void MovingVisitor::Visit(Aggregations *aggregations, CDC* pDC) {
}
void MovingVisitor::Visit(Composition *composition, CDC* pDC) {
}
void MovingVisitor::Visit(Compositions *compositions, CDC* pDC) {
}
void MovingVisitor::Visit(MemoLine *memoLine, CDC *pDC) {
}
void MovingVisitor::Visit(SelfGeneralization *selfGeneralization, CDC *pDC) {
}
void MovingVisitor::Visit(SelfDependency *selfDependency, CDC *pDC) {
}
void MovingVisitor::Visit(SelfAggregation *selfAggregation, CDC *pDC) {
}
void MovingVisitor::Visit(SelfAssociation *selfAssociation, CDC *pDC) {
}
void MovingVisitor::Visit(SelfAggregations *selfAggregations, CDC *pDC) {
}
void MovingVisitor::Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *pDC) {
}
void MovingVisitor::Visit(SelfComposition *selfComposition, CDC *pDC) {
}
void MovingVisitor::Visit(SelfCompositions *selfCompositions, CDC *pDC) {
}
void MovingVisitor::Visit(SelfRelation *selfRelation, CDC *cPaintDc) {
}
void MovingVisitor::Visit(Relation *relation, CDC *cPaintDc) {
}
void MovingVisitor::Visit(Text* text, CDC* pDC) {
}
