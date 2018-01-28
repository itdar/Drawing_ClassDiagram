//Class.cpp

#include "Class.h"
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
#include "Template.h"
#include "SmartPointer.h"
#include "MemoLine.h"
#include "SelfGeneralization.h"
#include "SelfDependency.h"
#include "SelfAggregation.h"
#include "SelfAssociation.h"
#include "SelfAggregations.h"
#include "SelfDirectedAssociation.h"
#include "SelfComposition.h"
#include "SelfCompositions.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Reception.h"
#include "Iterator.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"
#include "Diagram.h"
#include "Finder.h"
#include "RollNameBox.h"

#include "LastClass.h"
#include "ClassDiagramForm.h"

Class::Class(Long capacity) :FigureComposite(capacity) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->attributePosition = -1;
	this->methodPosition = -1;
	this->receptionPosition = -1;
	this->templetePosition = -1;
}
Class::Class(Long x, Long y, Long width, Long height) : FigureComposite(64) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->attributePosition = -1;
	this->methodPosition = -1;
	this->receptionPosition = -1;
	this->templetePosition = -1;
}
Class::Class(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight) : FigureComposite(64) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->minimumWidth = minimumWidth;
	this->minimumHeight = minimumHeight;
	this->attributePosition = -1;
	this->methodPosition = -1;
	this->receptionPosition = -1;
	this->templetePosition = -1;
}

Class::Class(const Class& source) :FigureComposite(source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->minimumWidth = source.minimumWidth;
	this->minimumHeight = source.minimumHeight;
	this->attributePosition = source.attributePosition;
	this->methodPosition = source.methodPosition;
	this->receptionPosition = source.receptionPosition;
	this->templetePosition = source.templetePosition;
}

Class::~Class() {
	Long i = 0;
	while (i < this->length) {
		delete this->figures[i];
		i++;
	}
}
//void Class::Initialize() {
//	ClassName className(this->x, this->y, this->width, 50, "");
//	this->figures.Store(this->length, className.Clone());
//	this->length++;
//
//	Line line1(this->x, this->y + 50, width, 0);
//	this->figures.Store(this->length, line1.Clone());
//	this->length++;
//
//	Attribute attribute(this->x, this->y + 50, this->width, ((this->y + 50 + this->y + this->height) / 2) - (this->y + 50), "");
//	this->attributePosition = this->figures.Store(this->length, attribute.Clone());
//	this->length++;
//
//	Line line2(this->x, (this->y + 50 + this->y + this->height) / 2, this->width, 0);
//	this->figures.Store(this->length, line2.Clone());
//	this->length++;
//
//	Method method(this->x, (this->y + 50 + this->y + this->height) / 2, this->width, ((this->y + 50 + this->y + this->height) / 2) - (this->y + 50), "");
//	this->methodPosition = this->figures.Store(this->length, method.Clone());
//	this->length++;
//}
void Class::Initialize() {
	LastClass *test = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	Long firstlineHeight = 50 * test->classDiagramForm->zoomRate / 100;
	if (this->height == 90 * test->classDiagramForm->zoomRate / 100) {
		 firstlineHeight = 30 * test->classDiagramForm->zoomRate / 100; //40
	}
	if (this->height == 120 * test->classDiagramForm->zoomRate / 100) {
		firstlineHeight = 40 * test->classDiagramForm->zoomRate / 100;
	}
	if (this->height == 180 * test->classDiagramForm->zoomRate / 100) {
		firstlineHeight = 60 * test->classDiagramForm->zoomRate / 100;
	}
	if (this->height == 210 * test->classDiagramForm->zoomRate / 100) {
		firstlineHeight = 70 * test->classDiagramForm->zoomRate / 100;
	}
	if (this->height == 240 * test->classDiagramForm->zoomRate / 100) {
		firstlineHeight = 80 * test->classDiagramForm->zoomRate / 100;
	}
	if (this->height == 270 * test->classDiagramForm->zoomRate / 100) {
		firstlineHeight = 90 * test->classDiagramForm->zoomRate / 100;
	}
	if (this->height == 300 * test->classDiagramForm->zoomRate / 100) {
		firstlineHeight = 100 * test->classDiagramForm->zoomRate / 100;
	}
	Long lineHeight = (this->height - firstlineHeight) / 2;
	ClassName className(this->x, this->y, this->width, firstlineHeight, "");
	this->figures.Store(this->length, className.Clone());
	this->length++;

	Line line1(this->x, this->y + firstlineHeight, this->width, 0);
	this->figures.Store(this->length, line1.Clone());
	this->length++;

	Attribute attribute(this->x, this->y + firstlineHeight, this->width, lineHeight, "");
	this->attributePosition = this->figures.Store(this->length, attribute.Clone());
	this->length++;

	Line line2(this->x, this->y + firstlineHeight + lineHeight, this->width, 0);
	this->figures.Store(this->length, line2.Clone());
	this->length++;

	Method method(this->x, this->y + firstlineHeight + lineHeight, this->width, lineHeight, "");
	this->methodPosition = this->figures.Store(this->length, method.Clone());
	this->length++;
}
Figure* Class::Move(Long distanceX, Long distanceY) {
	Figure::Move(distanceX, distanceY);
	return this;
}
Class& Class::operator = (const Class& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<Class&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->attributePosition = source.attributePosition;
	this->methodPosition = source.methodPosition;
	this->receptionPosition = source.receptionPosition;
	this->templetePosition = source.templetePosition;

	return *this;
}

Figure* Class::operator [] (Long index) {
	return this->figures[index];
}

Long Class::Add(Figure *figure) {
	Long index;
	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, figure);
	}
	else {
		index = this->figures.AppendFromRear(figure);
		this->capacity++;
	}
	this->length++;

	return index;
}
Long Class::Add(Attribute *attribute) {
	if (this->length < this->capacity) {
		this->attributePosition= this->figures.Store(this->length, attribute);
	}
	else {
		this->attributePosition = this->figures.AppendFromRear(attribute);
		this->capacity++;
	}
	this->length++;
	return this->attributePosition;
}
Long Class::Add(Method *method) {
	if (this->length < this->capacity) {
		this->methodPosition = this->figures.Store(this->length, method);
	}
	else {
		this->methodPosition = this->figures.AppendFromRear(method);
		this->capacity++;
	}
	this->length++;
	return this->methodPosition;
}
Long Class::Add(Reception *reception) {
	if (this->length < this->capacity) {
		this->receptionPosition = this->figures.Store(this->length, reception);
	}
	else {
		this->receptionPosition = this->figures.AppendFromRear(reception);
		this->capacity++;
	}
	this->length++;
	return this->receptionPosition;
}
Long Class::Add(Template *object) {
	if (this->length < this->capacity) {
		this->templetePosition = this->figures.Store(this->length, object);
	}
	else {
		this->templetePosition = this->figures.AppendFromRear(object);
		this->capacity++;
	}
	this->length++;
	return this->templetePosition;
}
Long Class::Add(Long x, Long y, Long width, Long height) {
	Long index;
	Line object(x, y, width, height);

	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, object.Clone());
	}
	else {
		index = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;

	return index;
}



Long Class::AddAttribute(Diagram *diagram) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	Line line(this->x, this->y + this->figures.GetAt(0)->GetHeight(), this->width, 0);
	if (this->length < this->capacity) {
		this->figures.Store(this->length, line.Clone());
	}
	else {
		this->figures.AppendFromRear(line.Clone());
		this->capacity++;
	}
	this->length++;
	Attribute object(this->x, this->y + this->figures.GetAt(0)->GetHeight(), this->width, 50, "");
	if (this->length < this->capacity) {
		this->attributePosition = this->figures.Store(this->length, object.Clone());
	}
	else {
		this->attributePosition = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;

	this->height += 50;
	if (this->methodPosition != -1) {
		this->figures.GetAt(this->methodPosition)->Move(0, 50);
		this->figures.GetAt(this->methodPosition - 1)->Move(0, 50);
	}
	if (this->receptionPosition != -1) {
		this->figures.GetAt(this->receptionPosition)->Move(0, 50);
		this->figures.GetAt(this->receptionPosition - 1)->Move(0, 50);
	}

	Long i = 0;
	Long j = 0;
	Long Quadrant;
	Finder finder;
	while (i < this->GetLength()) {

		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight() - 50);
			if (Quadrant == 3) {
				this->GetAt(i)->Modify(this->GetAt(i)->GetX(), this->GetAt(i)->GetY() + 50, this->GetAt(i)->GetWidth(), this->GetAt(i)->GetHeight() - 50);
			}
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
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
		i++;
	}
	i = 0;
	Long startX = this->GetX();
	Long startY = this->GetY();
	Long endX = this->GetX() + this->GetWidth();
	Long endY = this->GetY() + this->GetHeight();
	while (i<diagram->GetLength()) {
		j = 0;
		FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(diagram->GetAt(i));
		while (j < figureComposite->GetLength()) {
			Figure *figure = figureComposite->GetAt(j);
			if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
				Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
				Long relationEndX = figure->GetX() + figure->GetWidth();
				Long relationEndY = figure->GetY() + figure->GetHeight();
				//if (startX <= relationEndX &&  relationEndX <= endX &&
				//	startY <= relationEndY &&  relationEndY <= endY) {
				if(relation->GetEndPointFigure()==static_cast<Figure*>(this)){
					Quadrant = finder.FindQuadrant(relationEndX, relationEndY,
						startX, startY, endX, endY - 50);
					if (Quadrant == 3) {
						figure->EndPointMove(0, 50);
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
			}
			j++;
		}
		i++;
	}
	return this->attributePosition;
}
Long Class::AddMethod(Diagram *diagram) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	Long y;

	if (this->attributePosition == -1) {
		y = this->y + this->figures.GetAt(0)->GetHeight();
	}
	else {
		y = this->figures.GetAt(this->attributePosition)->GetY() + this->figures.GetAt(this->attributePosition)->GetHeight();

	}
	Line line(this->x, y, this->width, 0);
	if (this->length < this->capacity) {
		this->figures.Store(this->length, line.Clone());
	}
	else {
		this->figures.AppendFromRear(line.Clone());
		this->capacity++;
	}
	this->length++;
	Method object(this->x, y, this->width, 100, "");
	if (this->length < this->capacity) {
		this->methodPosition = this->figures.Store(this->length, object.Clone());
	}
	else {
		this->methodPosition = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;

	this->height += 100;

	if (this->receptionPosition != -1) {
		this->figures.GetAt(this->receptionPosition)->Move(0, 100);
		this->figures.GetAt(this->receptionPosition - 1)->Move(0, 100);
	}

	Long i = 0;
	Long j = 0;
	Long Quadrant;
	Finder finder;
	while (i < this->GetLength()) {

		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight() - 100);
			if (Quadrant == 3) {
				this->GetAt(i)->Modify(this->GetAt(i)->GetX(), this->GetAt(i)->GetY() + 100, this->GetAt(i)->GetWidth(), this->GetAt(i)->GetHeight() - 100);
			}
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
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
		i++;
	}
	i = 0;
	Long startX = this->GetX();
	Long startY = this->GetY();
	Long endX = this->GetX() + this->GetWidth();
	Long endY = this->GetY() + this->GetHeight();
	while (i<diagram->GetLength()) {
		j = 0;
		FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(diagram->GetAt(i));
		while (j < figureComposite->GetLength()) {
			Figure *figure = figureComposite->GetAt(j);
			if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
				Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
				Long relationEndX = figure->GetX() + figure->GetWidth();
				Long relationEndY = figure->GetY() + figure->GetHeight();
				//if (startX <= relationEndX &&  relationEndX <= endX &&
				//	startY <= relationEndY &&  relationEndY <= endY) {
					if (relation->GetEndPointFigure() == static_cast<Figure*>(this)) {
					Quadrant = finder.FindQuadrant(relationEndX, relationEndY,
						startX, startY, endX, endY - 100);
					if (Quadrant == 3) {
						figure->EndPointMove(0, 100);
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
			}
			j++;
		}
		i++;
	}
	return this->methodPosition;
}
Long Class::AddReception(Diagram *diagram) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	Line line(this->x, this->y + this->height, this->width, 0);


	if (this->length < this->capacity) {
		this->figures.Store(this->length, line.Clone());
	}
	else {
		this->figures.AppendFromRear(line.Clone());
		this->capacity++;
	}
	this->length++;

	Reception reception(this->x, this->y + this->height, this->width, 50, "");

	if (this->length < this->capacity) {
		this->receptionPosition = this->figures.Store(this->length, reception.Clone());
	}
	else {
		this->receptionPosition = this->figures.AppendFromRear(reception.Clone());
		this->capacity++;
	}
	this->length++;
	this->height = height + 50;
	Long i = 0;
	Long j = 0;
	Finder finder;
	Long Quadrant;
	while (i < this->GetLength()) {
		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight() - 50);
			if (Quadrant == 3) {
				this->GetAt(i)->Modify(this->GetAt(i)->GetX(), this->GetAt(i)->GetY() + 50, this->GetAt(i)->GetWidth(), this->GetAt(i)->GetHeight() - 50);
			}
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
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
		i++;
	}
	i = 0;
	Long startX = this->GetX();
	Long startY = this->GetY();
	Long endX = this->GetX() + this->GetWidth();
	Long endY = this->GetY() + this->GetHeight();
	while (i<diagram->GetLength()) {
		j = 0;
		FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(diagram->GetAt(i));
		while (j < figureComposite->GetLength()) {
			Figure *figure = figureComposite->GetAt(j);
			if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
				Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
				Long relationEndX = figure->GetX() + figure->GetWidth();
				Long relationEndY = figure->GetY() + figure->GetHeight();
				//if (startX <= relationEndX &&  relationEndX <= endX &&
				//	startY <= relationEndY &&  relationEndY <= endY) {
				if (relation->GetEndPointFigure() == static_cast<Figure*>(this)) {
					Quadrant = finder.FindQuadrant(relationEndX, relationEndY,
						startX, startY, endX, endY - 50);
					if (Quadrant == 3) {
						figure->EndPointMove(0, 50);
					}
					Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
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
			}
			j++;
		}
		i++;
	}

	return this->receptionPosition;
}


Long Class::AddTemplate(Long x, Long y, Long width, Long height) {

	Template object(x, y, width, height);

	if (this->length < this->capacity) {
		this->templetePosition = this->figures.Store(this->length, object.Clone());
	}
	else {
		this->templetePosition = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;

	return this->templetePosition;
}

Long Class::Remove(Long index) {
	Long ret = 0;

	if (this->figures[index] != 0) {
		if (this->attributePosition > index) {
			this->attributePosition--;
		}
		if (this->methodPosition > index) {
			this->methodPosition--;
		}
		if (this->receptionPosition > index) {
			this->receptionPosition--;
		}
		if (this->templetePosition > index) {
			this->templetePosition--;
		}
		delete this->figures[index];
		this->length--;
		this->capacity--;
		ret = this->figures.Delete(index);
	}
	return ret;
}
Long Class::RemoveAttribute() {

	if (this->attributePosition != -1) {
		this->figures.GetAt(0)->Modify(this->x, this->y, this->width, this->figures.GetAt(0)->GetHeight() + this->figures.GetAt(this->attributePosition)->GetHeight());
		if (this->attributePosition < this->methodPosition) {
			this->methodPosition -= 2;
		}
		if (this->attributePosition < this->receptionPosition) {
			this->receptionPosition -= 2;
		}
		if (this->attributePosition < this->templetePosition) {
			this->templetePosition -= 2;
		}

		delete this->figures.GetAt(this->attributePosition);
		this->figures.Delete(this->attributePosition);
		this->length--;
		this->capacity--;

		delete this->figures.GetAt(this->attributePosition - 1);
		this->attributePosition = this->figures.Delete(this->attributePosition - 1);
		this->length--;
		this->capacity--;
	}

	return this->attributePosition;
}
Long Class::RemoveMethod() {
	if (this->methodPosition != -1) {
		if (this->attributePosition == -1) {
			this->figures.GetAt(0)->Modify(this->x, this->y, this->width, this->figures.GetAt(0)->GetHeight() + this->figures.GetAt(this->methodPosition)->GetHeight());
		}
		else {
			this->figures.GetAt(this->attributePosition)->Modify(this->x, this->figures.GetAt(this->attributePosition)->GetY(), this->width, this->figures.GetAt(this->attributePosition)->GetHeight() + this->figures.GetAt(this->methodPosition)->GetHeight());
		}
		if (this->methodPosition < this->attributePosition) {
			this->attributePosition -= 2;
		}
		if (this->methodPosition < this->receptionPosition) {
			this->receptionPosition -= 2;
		}
		if (this->methodPosition < this->templetePosition) {
			this->templetePosition -= 2;
		}
		delete this->figures.GetAt(this->methodPosition);
		this->figures.Delete(this->methodPosition);
		this->length--;
		this->capacity--;

		delete this->figures.GetAt(this->methodPosition - 1);
		this->methodPosition = this->figures.Delete(this->methodPosition - 1);
		this->length--;
		this->capacity--;
	}
	return this->methodPosition;
}
Long Class::RemoveReception() {
	if (this->receptionPosition != -1) {
		if (this->methodPosition != -1) {
			
		this->figures.GetAt(this->methodPosition)->Modify(this->x, this->figures.GetAt(this->methodPosition)->GetY(), this->width, this->figures.GetAt(this->methodPosition)->GetHeight() + this->figures.GetAt(this->receptionPosition)->GetHeight());
		}
		else if (this->attributePosition != -1) {
		
			this->figures.GetAt(this->attributePosition)->Modify(this->x, this->figures.GetAt(this->attributePosition)->GetY(), this->width, this->figures.GetAt(attributePosition)->GetHeight() + this->figures.GetAt(this->receptionPosition)->GetHeight());
		}
		else {
			
			this->figures.GetAt(0)->Modify(this->x, this->y, this->width, this->figures.GetAt(0)->GetHeight() + this->figures.GetAt(this->receptionPosition)->GetHeight());
		}
		if (this->receptionPosition < this->attributePosition) {
			this->attributePosition -= 2;
		}
		if (this->receptionPosition < this->methodPosition) {
			this->methodPosition -= 2;
		}
		if (this->receptionPosition < this->templetePosition) {
			this->templetePosition -= 2;
		}
		delete this->figures.GetAt(this->receptionPosition);
		this->figures.Delete(this->receptionPosition);
		this->length--;
		this->capacity--;

		delete this->figures.GetAt(this->receptionPosition - 1);
		this->receptionPosition = this->figures.Delete(this->receptionPosition - 1);
		this->length--;
		this->capacity--;
	}
	return this->receptionPosition;
}
Long Class::RemoveTemplate() {
	if (this->templetePosition != -1) {

		if (this->templetePosition < this->attributePosition) {
			this->attributePosition--;
		}
		if (this->templetePosition < this->methodPosition) {
			this->methodPosition--;
		}
		if (this->templetePosition < this->receptionPosition) {
			this->receptionPosition--;
		}
		delete this->figures.GetAt(this->templetePosition);
		this->templetePosition = this->figures.Delete(this->templetePosition);
		this->length--;
		this->capacity--;
	}
	return this->templetePosition;
}

Figure* Class::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}

Figure* Class::Clone() const {
	return new Class(*this);
}

void Class::Accept(Visitor& visitor, CDC *pDC) {
	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	CRect rect;
	lastClass->classDiagramForm->GetClientRect(&rect);

	if ((this->GetX() > rect.left
		&& this->GetX() < rect.right
		&& this->GetY() > rect.top
		&& this->GetY() < rect.bottom)
		|| (this->GetX() + this->GetWidth() > rect.left
			&& this->GetX() + this->GetWidth() < rect.right
			&& this->GetY() + this->GetHeight() > rect.top
			&& this->GetY() + this->GetHeight() < rect.bottom)
		|| (this->GetX() > rect.left
			&& this->GetX() < rect.right
			&& this->GetY() + this->GetHeight() > rect.top
			&& this->GetY() + this->GetHeight() < rect.bottom)
		|| (this->GetX() + this->GetWidth() > rect.left
			&& this->GetX() + this->GetWidth() < rect.right
			&& this->GetY() > rect.top
			&& this->GetY() < rect.bottom)) {
		visitor.Visit(this, pDC);
	}

	SmartPointer<Figure*> smartPointer(this->CreateIterator());

	while (!smartPointer->IsDone()) {
		if (dynamic_cast<Relation*>(smartPointer->Current())) {
			if ((static_cast<Relation*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Relation*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Relation*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Relation*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Relation*>(smartPointer->Current())->GetX() + static_cast<Relation*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Relation*>(smartPointer->Current())->GetX() + static_cast<Relation*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Relation*>(smartPointer->Current())->GetY() + static_cast<Relation*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Relation*>(smartPointer->Current())->GetY() + static_cast<Relation*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Relation*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		if (dynamic_cast<SelfRelation*>(smartPointer->Current())) {
			if ((static_cast<SelfRelation*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<SelfRelation*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<SelfRelation*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<SelfRelation*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<SelfRelation*>(smartPointer->Current())->GetX() + static_cast<SelfRelation*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<SelfRelation*>(smartPointer->Current())->GetX() + static_cast<SelfRelation*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<SelfRelation*>(smartPointer->Current())->GetY() + static_cast<SelfRelation*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<SelfRelation*>(smartPointer->Current())->GetY() + static_cast<SelfRelation*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<SelfRelation*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		if (dynamic_cast<Line*>(smartPointer->Current())) {
			if ((static_cast<Line*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Line*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Line*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Line*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Line*>(smartPointer->Current())->GetX() + static_cast<Line*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Line*>(smartPointer->Current())->GetX() + static_cast<Line*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Line*>(smartPointer->Current())->GetY() + static_cast<Line*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Line*>(smartPointer->Current())->GetY() + static_cast<Line*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Line*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Template*>(smartPointer->Current())) {
			if ((static_cast<Template*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Template*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Template*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Template*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Template*>(smartPointer->Current())->GetX() + static_cast<Template*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Template*>(smartPointer->Current())->GetX() + static_cast<Template*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Template*>(smartPointer->Current())->GetY() + static_cast<Template*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Template*>(smartPointer->Current())->GetY() + static_cast<Template*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Template*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<ClassName*>(smartPointer->Current())) {
			if ((static_cast<ClassName*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<ClassName*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<ClassName*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<ClassName*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<ClassName*>(smartPointer->Current())->GetX() + static_cast<ClassName*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<ClassName*>(smartPointer->Current())->GetX() + static_cast<ClassName*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<ClassName*>(smartPointer->Current())->GetY() + static_cast<ClassName*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<ClassName*>(smartPointer->Current())->GetY() + static_cast<ClassName*>(smartPointer->Current())->GetHeight() < rect.bottom)
				|| (static_cast<ClassName*>(smartPointer->Current())->GetX() > rect.left
					&& static_cast<ClassName*>(smartPointer->Current())->GetX() < rect.right
					&& static_cast<ClassName*>(smartPointer->Current())->GetY() + static_cast<ClassName*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<ClassName*>(smartPointer->Current())->GetY() + static_cast<ClassName*>(smartPointer->Current())->GetHeight() < rect.bottom)
				|| (static_cast<ClassName*>(smartPointer->Current())->GetX() + static_cast<ClassName*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<ClassName*>(smartPointer->Current())->GetX() + static_cast<ClassName*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<ClassName*>(smartPointer->Current())->GetY() > rect.top
					&& static_cast<ClassName*>(smartPointer->Current())->GetY() < rect.bottom)) {
				static_cast<ClassName*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Attribute*>(smartPointer->Current())) {
			if ((static_cast<Attribute*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Attribute*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Attribute*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Attribute*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Attribute*>(smartPointer->Current())->GetX() + static_cast<Attribute*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Attribute*>(smartPointer->Current())->GetX() + static_cast<Attribute*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Attribute*>(smartPointer->Current())->GetY() + static_cast<Attribute*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Attribute*>(smartPointer->Current())->GetY() + static_cast<Attribute*>(smartPointer->Current())->GetHeight() < rect.bottom)
				|| (static_cast<Attribute*>(smartPointer->Current())->GetX() > rect.left
					&& static_cast<Attribute*>(smartPointer->Current())->GetX() < rect.right
					&& static_cast<Attribute*>(smartPointer->Current())->GetY() + static_cast<Attribute*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Attribute*>(smartPointer->Current())->GetY() + static_cast<Attribute*>(smartPointer->Current())->GetHeight() < rect.bottom)
				|| (static_cast<Attribute*>(smartPointer->Current())->GetX() + static_cast<Attribute*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Attribute*>(smartPointer->Current())->GetX() + static_cast<Attribute*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Attribute*>(smartPointer->Current())->GetY() > rect.top
					&& static_cast<Attribute*>(smartPointer->Current())->GetY() < rect.bottom)) {
				static_cast<Attribute*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Method*>(smartPointer->Current())) {
			if ((static_cast<Method*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Method*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Method*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Method*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Method*>(smartPointer->Current())->GetX() + static_cast<Method*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Method*>(smartPointer->Current())->GetX() + static_cast<Method*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Method*>(smartPointer->Current())->GetY() + static_cast<Method*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Method*>(smartPointer->Current())->GetY() + static_cast<Method*>(smartPointer->Current())->GetHeight() < rect.bottom)
				|| (static_cast<Method*>(smartPointer->Current())->GetX() > rect.left
					&& static_cast<Method*>(smartPointer->Current())->GetX() < rect.right
					&& static_cast<Method*>(smartPointer->Current())->GetY() + static_cast<Method*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Method*>(smartPointer->Current())->GetY() + static_cast<Method*>(smartPointer->Current())->GetHeight() < rect.bottom)
				|| (static_cast<Method*>(smartPointer->Current())->GetX() + static_cast<Method*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Method*>(smartPointer->Current())->GetX() + static_cast<Method*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Method*>(smartPointer->Current())->GetY() > rect.top
					&& static_cast<Method*>(smartPointer->Current())->GetY() < rect.bottom)) {
				static_cast<Method*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Reception*>(smartPointer->Current())) {
			if ((static_cast<Reception*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Reception*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Reception*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Reception*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Reception*>(smartPointer->Current())->GetX() + static_cast<Reception*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Reception*>(smartPointer->Current())->GetX() + static_cast<Reception*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Reception*>(smartPointer->Current())->GetY() + static_cast<Reception*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Reception*>(smartPointer->Current())->GetY() + static_cast<Reception*>(smartPointer->Current())->GetHeight() < rect.bottom)
				|| (static_cast<Reception*>(smartPointer->Current())->GetX() > rect.left
					&& static_cast<Reception*>(smartPointer->Current())->GetX() < rect.right
					&& static_cast<Reception*>(smartPointer->Current())->GetY() + static_cast<Reception*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Reception*>(smartPointer->Current())->GetY() + static_cast<Reception*>(smartPointer->Current())->GetHeight() < rect.bottom)
				|| (static_cast<Reception*>(smartPointer->Current())->GetX() + static_cast<Reception*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Reception*>(smartPointer->Current())->GetX() + static_cast<Reception*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Reception*>(smartPointer->Current())->GetY() > rect.top
					&& static_cast<Reception*>(smartPointer->Current())->GetY() < rect.bottom)) {
				static_cast<Reception*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Generalization*>(smartPointer->Current())) {
			if ((static_cast<Generalization*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Generalization*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Generalization*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Generalization*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Generalization*>(smartPointer->Current())->GetX() + static_cast<Generalization*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Generalization*>(smartPointer->Current())->GetX() + static_cast<Generalization*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Generalization*>(smartPointer->Current())->GetY() + static_cast<Generalization*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Generalization*>(smartPointer->Current())->GetY() + static_cast<Generalization*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Generalization*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Realization*>(smartPointer->Current())) {
			if ((static_cast<Realization*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Realization*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Realization*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Realization*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Realization*>(smartPointer->Current())->GetX() + static_cast<Realization*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Realization*>(smartPointer->Current())->GetX() + static_cast<Realization*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Realization*>(smartPointer->Current())->GetY() + static_cast<Realization*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Realization*>(smartPointer->Current())->GetY() + static_cast<Realization*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Realization*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Dependency*>(smartPointer->Current())) {
			if ((static_cast<Dependency*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Dependency*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Dependency*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Dependency*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Dependency*>(smartPointer->Current())->GetX() + static_cast<Dependency*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Dependency*>(smartPointer->Current())->GetX() + static_cast<Dependency*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Dependency*>(smartPointer->Current())->GetY() + static_cast<Dependency*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Dependency*>(smartPointer->Current())->GetY() + static_cast<Dependency*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Dependency*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Association*>(smartPointer->Current())) {
			if ((static_cast<Association*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Association*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Association*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Association*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Association*>(smartPointer->Current())->GetX() + static_cast<Association*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Association*>(smartPointer->Current())->GetX() + static_cast<Association*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Association*>(smartPointer->Current())->GetY() + static_cast<Association*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Association*>(smartPointer->Current())->GetY() + static_cast<Association*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Association*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<DirectedAssociation*>(smartPointer->Current())) {
			if ((static_cast<DirectedAssociation*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<DirectedAssociation*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<DirectedAssociation*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<DirectedAssociation*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<DirectedAssociation*>(smartPointer->Current())->GetX() + static_cast<DirectedAssociation*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<DirectedAssociation*>(smartPointer->Current())->GetX() + static_cast<DirectedAssociation*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<DirectedAssociation*>(smartPointer->Current())->GetY() + static_cast<DirectedAssociation*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<DirectedAssociation*>(smartPointer->Current())->GetY() + static_cast<DirectedAssociation*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<DirectedAssociation*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Aggregation*>(smartPointer->Current())) {
			if ((static_cast<Aggregation*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Aggregation*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Aggregation*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Aggregation*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Aggregation*>(smartPointer->Current())->GetX() + static_cast<Aggregation*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Aggregation*>(smartPointer->Current())->GetX() + static_cast<Aggregation*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Aggregation*>(smartPointer->Current())->GetY() + static_cast<Aggregation*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Aggregation*>(smartPointer->Current())->GetY() + static_cast<Aggregation*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Aggregation*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Aggregations*>(smartPointer->Current())) {
			if ((static_cast<Aggregations*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Aggregations*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Aggregations*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Aggregations*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Aggregations*>(smartPointer->Current())->GetX() + static_cast<Aggregations*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Aggregations*>(smartPointer->Current())->GetX() + static_cast<Aggregations*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Aggregations*>(smartPointer->Current())->GetY() + static_cast<Aggregations*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Aggregations*>(smartPointer->Current())->GetY() + static_cast<Aggregations*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Aggregations*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Composition*>(smartPointer->Current())) {
			if ((static_cast<Composition*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Composition*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Composition*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Composition*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Composition*>(smartPointer->Current())->GetX() + static_cast<Composition*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Composition*>(smartPointer->Current())->GetX() + static_cast<Composition*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Composition*>(smartPointer->Current())->GetY() + static_cast<Composition*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Composition*>(smartPointer->Current())->GetY() + static_cast<Composition*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Composition*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<Compositions*>(smartPointer->Current())) {
			if ((static_cast<Compositions*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<Compositions*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<Compositions*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<Compositions*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<Compositions*>(smartPointer->Current())->GetX() + static_cast<Compositions*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<Compositions*>(smartPointer->Current())->GetX() + static_cast<Compositions*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<Compositions*>(smartPointer->Current())->GetY() + static_cast<Compositions*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<Compositions*>(smartPointer->Current())->GetY() + static_cast<Compositions*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<Compositions*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<MemoLine*>(smartPointer->Current())) {
			if ((static_cast<MemoLine*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<MemoLine*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<MemoLine*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<MemoLine*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<MemoLine*>(smartPointer->Current())->GetX() + static_cast<MemoLine*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<MemoLine*>(smartPointer->Current())->GetX() + static_cast<MemoLine*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<MemoLine*>(smartPointer->Current())->GetY() + static_cast<MemoLine*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<MemoLine*>(smartPointer->Current())->GetY() + static_cast<MemoLine*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<MemoLine*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<SelfGeneralization*>(smartPointer->Current())) {
			if ((static_cast<SelfGeneralization*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<SelfGeneralization*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<SelfGeneralization*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<SelfGeneralization*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<SelfGeneralization*>(smartPointer->Current())->GetX() + static_cast<SelfGeneralization*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<SelfGeneralization*>(smartPointer->Current())->GetX() + static_cast<SelfGeneralization*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<SelfGeneralization*>(smartPointer->Current())->GetY() + static_cast<SelfGeneralization*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<SelfGeneralization*>(smartPointer->Current())->GetY() + static_cast<SelfGeneralization*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<SelfGeneralization*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<SelfDependency*>(smartPointer->Current())) {
			if ((static_cast<SelfDependency*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<SelfDependency*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<SelfDependency*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<SelfDependency*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<SelfDependency*>(smartPointer->Current())->GetX() + static_cast<SelfDependency*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<SelfDependency*>(smartPointer->Current())->GetX() + static_cast<SelfDependency*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<SelfDependency*>(smartPointer->Current())->GetY() + static_cast<SelfDependency*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<SelfDependency*>(smartPointer->Current())->GetY() + static_cast<SelfDependency*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<SelfDependency*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<SelfAggregation*>(smartPointer->Current())) {
			if ((static_cast<SelfAggregation*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<SelfAggregation*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<SelfAggregation*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<SelfAggregation*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<SelfAggregation*>(smartPointer->Current())->GetX() + static_cast<SelfAggregation*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<SelfAggregation*>(smartPointer->Current())->GetX() + static_cast<SelfAggregation*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<SelfAggregation*>(smartPointer->Current())->GetY() + static_cast<SelfAggregation*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<SelfAggregation*>(smartPointer->Current())->GetY() + static_cast<SelfAggregation*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<SelfAggregation*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<SelfAssociation*>(smartPointer->Current())) {
			if ((static_cast<SelfAssociation*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<SelfAssociation*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<SelfAssociation*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<SelfAssociation*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<SelfAssociation*>(smartPointer->Current())->GetX() + static_cast<SelfAssociation*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<SelfAssociation*>(smartPointer->Current())->GetX() + static_cast<SelfAssociation*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<SelfAssociation*>(smartPointer->Current())->GetY() + static_cast<SelfAssociation*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<SelfAssociation*>(smartPointer->Current())->GetY() + static_cast<SelfAssociation*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<SelfAssociation*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<SelfAggregations*>(smartPointer->Current())) {
			if ((static_cast<SelfAggregations*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<SelfAggregations*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<SelfAggregations*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<SelfAggregations*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<SelfAggregations*>(smartPointer->Current())->GetX() + static_cast<SelfAggregations*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<SelfAggregations*>(smartPointer->Current())->GetX() + static_cast<SelfAggregations*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<SelfAggregations*>(smartPointer->Current())->GetY() + static_cast<SelfAggregations*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<SelfAggregations*>(smartPointer->Current())->GetY() + static_cast<SelfAggregations*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<SelfAggregations*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<SelfDirectedAssociation*>(smartPointer->Current())) {
			if ((static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetX() + static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetX() + static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetY() + static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetY() + static_cast<SelfDirectedAssociation*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<SelfDirectedAssociation*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<SelfComposition*>(smartPointer->Current())) {
			if ((static_cast<SelfComposition*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<SelfComposition*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<SelfComposition*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<SelfComposition*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<SelfComposition*>(smartPointer->Current())->GetX() + static_cast<SelfComposition*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<SelfComposition*>(smartPointer->Current())->GetX() + static_cast<SelfComposition*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<SelfComposition*>(smartPointer->Current())->GetY() + static_cast<SelfComposition*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<SelfComposition*>(smartPointer->Current())->GetY() + static_cast<SelfComposition*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<SelfComposition*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		else if (dynamic_cast<SelfCompositions*>(smartPointer->Current())) {
			if ((static_cast<SelfCompositions*>(smartPointer->Current())->GetX() > rect.left
				&& static_cast<SelfCompositions*>(smartPointer->Current())->GetX() < rect.right
				&& static_cast<SelfCompositions*>(smartPointer->Current())->GetY() > rect.top
				&& static_cast<SelfCompositions*>(smartPointer->Current())->GetY() < rect.bottom)
				|| (static_cast<SelfCompositions*>(smartPointer->Current())->GetX() + static_cast<SelfCompositions*>(smartPointer->Current())->GetWidth() > rect.left
					&& static_cast<SelfCompositions*>(smartPointer->Current())->GetX() + static_cast<SelfCompositions*>(smartPointer->Current())->GetWidth() < rect.right
					&& static_cast<SelfCompositions*>(smartPointer->Current())->GetY() + static_cast<SelfCompositions*>(smartPointer->Current())->GetHeight() > rect.top
					&& static_cast<SelfCompositions*>(smartPointer->Current())->GetY() + static_cast<SelfCompositions*>(smartPointer->Current())->GetHeight() < rect.bottom)) {
				static_cast<SelfCompositions*>(smartPointer->Current())->Accept(visitor, pDC);
			}
		}
		smartPointer->Next();
	}
}

void Class::Accept(Visitor& visitor, Long distanceX, Long distanceY) {
	visitor.Visit(this, distanceX, distanceY);
}

Long Class::SetMinimumWidthR(Long zoomRate) {
	this->minimumWidth = 120 * zoomRate / 100;
	SmartPointer<Figure*> iterator(this->CreateIterator());
	for (iterator->First();!iterator->IsDone();iterator->Next()) {
		if (!dynamic_cast<Line*>(iterator->Current()) && !dynamic_cast<Relation*>(iterator->Current()) && !dynamic_cast<SelfRelation*>(iterator->Current()) && iterator->Current()->GetMinimumWidth() > this->minimumWidth) {
			this->minimumWidth = iterator->Current()->GetMinimumWidth();
		}
	}
	return this->minimumWidth;
}



Long Class::Correct(Figure *figure, Long index) {
	return index = this->figures.Modify(index, figure);
}