#include "ScrollMovingObject.h"
#include "Figure.h"
#include "FigureComposite.h"
#include "Diagram.h"
#include "Relation.h"
#include "SelfRelation.h"
#include "RollNameBox.h"

ScrollMovingObject::ScrollMovingObject() {

}
ScrollMovingObject::ScrollMovingObject(const ScrollMovingObject& source) {

}
ScrollMovingObject& ScrollMovingObject::operator = (const ScrollMovingObject& source) {
	return *this;
}
ScrollMovingObject::~ScrollMovingObject() {

}
void ScrollMovingObject::MovingObject(Diagram* diagram, Long distanceX, Long distanceY) {

	Long i = 0;
	Long j;
	Long k;

	FigureComposite* figureComposite;
	Relation* relation;
	SelfRelation *selfRelation;
	Figure* figure;

	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;

	while (i < diagram->GetLength()) { // 선택된 개수만큼 반복
		figureComposite = static_cast<FigureComposite*>(diagram->GetAt(i));

		figureComposite->Move(distanceX, distanceY); // 해당 클래스나 메모 이동
		//FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환
		j = 0;
		while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
			figure = figureComposite->GetAt(j);
			figure->Move(distanceX, distanceY);
			if (dynamic_cast<Relation*>(figure)) {
				relation = static_cast<Relation*>(figure);
				relation->EndPointMove(distanceX, distanceY);
				k = 0;
				while (k < relation->GetLength()) {
					CPoint point(relation->GetAt(k).x + distanceX, relation->GetAt(k).y + distanceY);
					relation->Move(k, point);
					k++;
				}
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
			if (dynamic_cast<SelfRelation*>(figure)) {
				selfRelation = static_cast<SelfRelation*>(figure);
				selfRelation->EndPointMove(distanceX, distanceY);
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
		i++;
	}
}
bool ScrollMovingObject::FindHorizontal(Diagram* diagram, Long x) {
	bool ret=false;

	Long i = 0;
	Long j;
	Long k;
	CPoint point;
	FigureComposite* composite;
	Relation* relation;
	SelfRelation* selfRelation;

	while (i < diagram->GetLength() && ret == false) {
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		if (composite->GetRight() >= x) {
			ret = true;
		}

		j = 0;
		while (j < composite->GetLength() && ret == false) {
			k = 0;
			if (dynamic_cast<Relation*>(composite->GetAt(j))) {
				relation = static_cast<Relation*>(composite->GetAt(j));
				if (relation->GetRight() >= x || relation->GetLeft() >= x) {
					ret = true;
				}
				while (k < relation->GetLength() && ret == false) {
					point = relation->GetAt(k);
					if (point.x >= x) {
						ret = true;
					}
					k++;
				}
			}
			if (dynamic_cast<SelfRelation*>(composite->GetAt(j))) {
				selfRelation = static_cast<SelfRelation*>(composite->GetAt(j));
				if (selfRelation->leftRightFlag == 0 && selfRelation->rollNamePoints->GetAt(1).x >= x) {
					ret = true;
				}
			}

			j++;
		}
		i++;
	}
	return ret;
}
Long ScrollMovingObject::GetHorizontalMax(Diagram* diagram) {
	Long ret = 0;
	Long i = 0;
	Long j;
	Long k;
	CPoint point;
	FigureComposite* composite;
	Relation* relation;
	SelfRelation* selfRelation;

	while (i < diagram->GetLength()) {
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		ret = max(composite->GetRight(), ret);
		j = 0;
		while (j < composite->GetLength()) {
			if (dynamic_cast<Relation*>(composite->GetAt(j))) {
				relation = static_cast<Relation*>(composite->GetAt(j));
				ret = max(relation->GetRight(), ret);
				ret = max(relation->GetLeft(), ret);
				k = 0;
				while (k < relation->GetLength()) {
					point = relation->GetAt(k);
					ret = max(point.x, ret);
					k++;
				}
			}
			if (dynamic_cast<SelfRelation*>(composite->GetAt(j))) {
				selfRelation = static_cast<SelfRelation*>(composite->GetAt(j));
				if (selfRelation->leftRightFlag == 0) {
					point = selfRelation->rollNamePoints->GetAt(1);
					ret = max(point.x, ret);
				}
			}
			j++;
		}
		i++;
	}
	return ret;
}

bool ScrollMovingObject::FindVertical(Diagram* diagram, Long y) {
	bool ret=false;

	Long i = 0;
	Long j;
	Long k;
	CPoint point;
	FigureComposite* composite;
	Relation* relation;

	while (i < diagram->GetLength() && ret == false) {
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		if (composite->GetBottom() >= y) {
			ret = true;
		}

		j = 0;
		while (j < composite->GetLength() && ret == false) {
			k = 0;
			if (dynamic_cast<Relation*>(composite->GetAt(j))) {
				relation = static_cast<Relation*>(composite->GetAt(j));
				if (relation->GetBottom() >= y || relation->GetTop() >= y) {
					ret = true;
				}
				while (k < relation->GetLength() && ret == false) {
					point = relation->GetAt(k);
					if (point.y >= y) {
						ret = true;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}

	return ret;
}

Long ScrollMovingObject::GetVerticalMax(Diagram* diagram) {
	Long ret = 0;
	Long i = 0;
	Long j;
	Long k;
	CPoint point;
	FigureComposite* composite;
	Relation* relation;
	SelfRelation* selfRelation;

	while (i < diagram->GetLength()) {
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		ret = max(composite->GetBottom(), ret);
		j = 0;
		while (j < composite->GetLength()) {
			if (dynamic_cast<Relation*>(composite->GetAt(j))) {
				relation = static_cast<Relation*>(composite->GetAt(j));
				ret = max(relation->GetTop(), ret);
				ret = max(relation->GetBottom(), ret);
				k = 0;
				while (k < relation->GetLength()) {
					point = relation->GetAt(k);
					ret = max(point.y, ret);
					k++;
				}
			}
			j++;
		}
		i++;
	}
	return ret;
}