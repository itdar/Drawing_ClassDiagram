//FigureComposite.cpp
#include "Relation.h"
#include "Class.h"
#include "SelfRelation.h"
#include "Finder.h"
#include "FigureComposite.h"
#include "Template.h"
#include "Line.h"
#include "SmartPointer.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "Reception.h"
#include "SelfRelation.h"
#include "RollNameBox.h"

#include "LastClass.h"
#include "ClassDiagramForm.h"

FigureComposite::FigureComposite(Long capacity) : figures(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

FigureComposite::FigureComposite(const FigureComposite& source) : figures(source.figures) {
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<FigureComposite&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

FigureComposite::~FigureComposite() {
}

FigureComposite& FigureComposite::operator = (const FigureComposite& source) {
	this->figures = source.figures;
	this->capacity = source.capacity;
	this->length = source.length;

	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<FigureComposite&>(source)).figures[i]->Clone());
		i++;
	}
	return *this;
}

ArrayIterator<Figure*>* FigureComposite::CreateIterator() const {
	return new ArrayIterator<Figure*>(&this->figures);
}
Figure* FigureComposite::ModifyComponetsToRightDirection(Diagram *diagram, Long distanceX) {
	LastClass *last = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	Long i = 0;
	Long length = 0;
	Long Quadrant;
	Figure *(*figures) = new Figure*[32]; // 32개 넘어가면..?
	Finder finder;
	Long distanceX_;
	double classWidth;
	double distanceToRelationX;
	double modifiedWidth;
	double modifiedDistance;
	Long modifiedRelationX;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;


	//LastClass *test = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	if (this->GetWidth() + distanceX <= this->minimumWidth) { // * test->classDiagramForm->zoomRate / 100) {
		distanceX = this->minimumWidth - this->GetWidth();
	}

	finder.FindRelationEndPoints(diagram, this, figures, &length);
	while (i < length) {
		Quadrant = finder.FindQuadrant(figures[i]->GetX() + figures[i]->GetWidth(), figures[i]->GetY() + figures[i]->GetHeight(),
			this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
		Relation *relation = static_cast<Relation*>(figures[i]);
		if (Quadrant == 1 || Quadrant == 3) {
			classWidth = static_cast<double>(this->width);
			distanceToRelationX = static_cast<double>(figures[i]->GetX() + figures[i]->GetWidth()) - static_cast<double>(this->x);
			modifiedWidth = static_cast<double>(this->width + distanceX);
			modifiedDistance = (modifiedWidth*distanceToRelationX) / classWidth;
			modifiedRelationX = this->x + static_cast<Long>(modifiedDistance);
			distanceX_ = modifiedRelationX - (figures[i]->GetX() + figures[i]->GetWidth());
			figures[i]->EndPointMove(distanceX_, 0);
		}
		else if (Quadrant == 2) {
			figures[i]->EndPointMove(distanceX, 0);

		}
		//관계선 에디트 이동
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

		i++;
	}

	delete[] figures;
	i = 0;

	while (i < this->GetLength()) {
		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
			if (Quadrant == 1 || Quadrant == 3) {
				classWidth = static_cast<double>(this->width);
				distanceToRelationX = static_cast<double>(this->GetAt(i)->GetX()) - static_cast<double>(this->x);
				modifiedWidth = static_cast<double>(this->width + distanceX);
				modifiedDistance = (modifiedWidth*distanceToRelationX) / classWidth;
				modifiedRelationX = this->x + static_cast<Long>(modifiedDistance);
				distanceX_ = modifiedRelationX - this->GetAt(i)->GetX();
				this->GetAt(i)->Move(distanceX_, 0);
			}
			else if (Quadrant == 2) {
				this->GetAt(i)->Move(distanceX, 0);
			}
			//관계선 에디트 이동
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
		else if (dynamic_cast<Template*>(this->GetAt(i))) {
			this->GetAt(i)->Move(distanceX, 0);
		}
		else if (dynamic_cast<SelfRelation*>(this->GetAt(i)) && static_cast<SelfRelation*>(this->GetAt(i))->leftRightFlag == 0) {
			this->GetAt(i)->Move(distanceX, 0);
			SelfRelation *selfRelation = static_cast<SelfRelation*>(this->GetAt(i));
			//자기자신 에디트 이동
			CPoint startPoint1And4{ selfRelation->GetX(), selfRelation->GetY() };
			CPoint endPoint1And4{ selfRelation->GetX() ,  selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };

			CPoint startPoint2{ selfRelation->GetX(), selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint2{ selfRelation->GetX() + 80 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };

			CPoint startPoint3And5{ selfRelation->GetX() + 80 * last->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint3And5{ selfRelation->GetX() + 30 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			cPoint1 = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
			cPoint2 = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
			cPoint3 = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5);
			cPoint4 = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
			cPoint5 = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5);
			selfRelation->rollNamePoints->Modify(0, cPoint1);
			selfRelation->rollNamePoints->Modify(1, cPoint2);
			selfRelation->rollNamePoints->Modify(2, cPoint3);
			selfRelation->rollNamePoints->Modify(3, cPoint4);
			selfRelation->rollNamePoints->Modify(4, cPoint5);

		}
		else { // Line 이랑 에딧영역
			this->GetAt(i)->Modify(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(), this->GetAt(i)->GetWidth() + distanceX, this->GetAt(i)->GetHeight());

		}
		i++;
	}

	this->width = this->width + distanceX;
	return this;
}

Long FigureComposite::Correct(Long index, Figure *figure) {
	return index = this->figures.Modify(index, figure);
}

Figure* FigureComposite::ModifyComponetsToDownDirection(Diagram *diagram, Long distanceY) {
	LastClass *test = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	Long i = 0;
	Long length = 0;
	Long Quadrant;
	Figure *(*figures) = new Figure*[32]; // 32개 넘어가면..?
	Finder finder;
	Long distanceY_;
	double classHeight;
	double distanceToRelationY;
	double modifiedHeight;
	double modifiedDistance;
	Long modifiedRelationY;
	Long editPosition;
	Long minimumHeight;
	Long limitY;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	if (dynamic_cast<Class*>(this)) {
		Class *object = static_cast<Class*>(this);
		if (object->GetReceptionPosition() != -1) {
			editPosition = object->GetReceptionPosition();
		}
		else if (object->GetMethodPosition() != -1) {
			editPosition = object->GetMethodPosition();
		}
		else if (object->GetAttributePosition() != -1) {
			editPosition = object->GetAttributePosition();
		}
		else {
			editPosition = 0;
		}

		minimumHeight = this->GetAt(editPosition)->GetMinimumHeight();
		limitY = this->GetAt(editPosition)->GetY() + minimumHeight;
		if (editPosition == 0) {
			if (this->y + this->height + distanceY < limitY+25 * test->classDiagramForm->zoomRate / 100) {
				distanceY = limitY - this->y - this->height+25 * test->classDiagramForm->zoomRate / 100;
			}
		}
		else {
			if (this->y + this->height + distanceY < limitY) {
				distanceY = limitY - this->y - this->height;
			}
		}
		this->GetAt(editPosition)->Modify(this->GetAt(editPosition)->GetX(), this->GetAt(editPosition)->GetY(), this->GetAt(editPosition)->GetWidth(),
			this->GetAt(editPosition)->GetHeight() + distanceY);
	}

	else if (this->height + distanceY <= this->minimumHeight) {
		distanceY = this->minimumHeight - this->height;
	}

	finder.FindRelationEndPoints(diagram, this, figures, &length);

	while (i < length) {
		Quadrant = finder.FindQuadrant(figures[i]->GetX() + figures[i]->GetWidth(), figures[i]->GetY() + figures[i]->GetHeight(),
			this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
		Relation *relation = static_cast<Relation*>(figures[i]);
		if (Quadrant == 2 || Quadrant == 4) {
			classHeight = static_cast<double>(this->height);
			distanceToRelationY = static_cast<double>(figures[i]->GetY() + figures[i]->GetHeight()) - static_cast<double>(this->y);
			modifiedHeight = static_cast<double>(this->height + distanceY);
			modifiedDistance = (modifiedHeight*distanceToRelationY) / classHeight;
			modifiedRelationY = this->y + static_cast<Long>(modifiedDistance);
			distanceY_ = modifiedRelationY - (figures[i]->GetY() + figures[i]->GetHeight());
			figures[i]->EndPointMove(0, distanceY_);
		}
		else if (Quadrant == 3) {
			figures[i]->EndPointMove(0, distanceY);
		}
		//관계선 에디트 이동
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
		i++;
	}

	delete[] figures;
	i = 0;

	while (i < this->GetLength()) {
		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
			if (Quadrant == 2 || Quadrant == 4) {
				classHeight = static_cast<double>(this->height);
				distanceToRelationY = static_cast<double>(this->GetAt(i)->GetY()) - static_cast<double>(this->y);
				modifiedHeight = static_cast<double>(this->height + distanceY);
				modifiedDistance = (modifiedHeight*distanceToRelationY) / classHeight;
				modifiedRelationY = this->y + static_cast<Long>(modifiedDistance);
				distanceY_ = modifiedRelationY - this->GetAt(i)->GetY();
				this->GetAt(i)->Move(0, distanceY_);
			}
			else if (Quadrant == 3) {
				this->GetAt(i)->Move(0, distanceY);
			}
			//관계선 에디트 이동
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
		i++;
	}

	this->height = this->height + distanceY;

	return this;
}
Figure* FigureComposite::ModifyComponetsToUpDirection(Diagram *diagram, Long distanceY) {
	LastClass *last = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	Long i = 0;
	Long length = 0;
	Long Quadrant;
	Figure *(*figures) = new Figure*[32]; // 32개 넘어가면..?
	Finder finder;
	Long distanceY_;
	double classHeight;
	double distanceToRelationY;
	double modifiedHeight;
	double modifiedDistance;
	Long modifiedRelationY;
	Long editPosition;
	Long minimumHeight;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;

	if (dynamic_cast<Class*>(this)) {
		Class *object = static_cast<Class*>(this);
		if (object->GetReceptionPosition() != -1) {
			editPosition = object->GetReceptionPosition();
		}
		else if (object->GetMethodPosition() != -1) {
			editPosition = object->GetMethodPosition();
		}
		else if (object->GetAttributePosition() != -1) {
			editPosition = object->GetAttributePosition();
		}
		else {
			editPosition = 0;
		}
		minimumHeight = this->GetAt(editPosition)->GetMinimumHeight();
		if (editPosition == 0) {
			minimumHeight += 20;
		}

		if (this->GetAt(editPosition)->GetHeight() - minimumHeight < distanceY) {
			distanceY = this->GetAt(editPosition)->GetHeight() - minimumHeight;
		}

		this->GetAt(editPosition)->Modify(this->GetAt(editPosition)->GetX(), this->GetAt(editPosition)->GetY() + distanceY, this->GetAt(editPosition)->GetWidth(),
			this->GetAt(editPosition)->GetHeight() - distanceY);
	}

	else if (distanceY > 0 && this->height - distanceY < this->minimumHeight) {
		distanceY = this->height - this->minimumHeight;
	}

	finder.FindRelationEndPoints(diagram, this, figures, &length);

	while (i < length) {
		Quadrant = finder.FindQuadrant(figures[i]->GetX() + figures[i]->GetWidth(), figures[i]->GetY() + figures[i]->GetHeight(),
			this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
		Relation *relation = static_cast<Relation*>(figures[i]);
		if (Quadrant == 2 || Quadrant == 4) {
			classHeight = static_cast<double>(this->height);
			distanceToRelationY = static_cast<double>(this->y) + static_cast<double>(this->GetHeight()) - static_cast<double>(figures[i]->GetY() + figures[i]->GetHeight());
			modifiedHeight = static_cast<double>(this->height + distanceY);
			modifiedDistance = (modifiedHeight*distanceToRelationY) / classHeight;
			modifiedRelationY = this->y + this->GetHeight() - static_cast<Long>(modifiedDistance);
			distanceY_ = (figures[i]->GetY() + figures[i]->GetHeight()) - modifiedRelationY;
			figures[i]->EndPointMove(0, distanceY_);
		}
		else if (Quadrant == 1) {
			figures[i]->EndPointMove(0, distanceY);
		}
		//관계선 에디트 이동
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
		i++;
	}

	delete[] figures;
	i = 0;

	while (i < this->GetLength()) {
		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
			if (Quadrant == 2 || Quadrant == 4) {
				classHeight = static_cast<double>(this->height);
				distanceToRelationY = static_cast<double>(this->y) + static_cast<double>(this->GetHeight()) - static_cast<double>(this->GetAt(i)->GetY());
				modifiedHeight = static_cast<double>(this->height + distanceY);
				modifiedDistance = (modifiedHeight*distanceToRelationY) / classHeight;
				modifiedRelationY = this->y + this->GetHeight() - static_cast<Long>(modifiedDistance);
				distanceY_ = this->GetAt(i)->GetY() - modifiedRelationY;
				this->GetAt(i)->Move(0, distanceY_);
			}
			else if (Quadrant == 1) {
				this->GetAt(i)->Move(0, distanceY);
			}
			//관계선 에디트 이동
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
		else if (dynamic_cast<SelfRelation*>(this->GetAt(i)) && static_cast<SelfRelation*>(this->GetAt(i))->leftRightFlag == 0) {
			this->GetAt(i)->Move(0, distanceY);
			SelfRelation *selfRelation = static_cast<SelfRelation*>(this->GetAt(i));
			//자기자신 에디트 이동
			CPoint startPoint1And4{ selfRelation->GetX(), selfRelation->GetY() };
			CPoint endPoint1And4{ selfRelation->GetX() ,  selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };

			CPoint startPoint2{ selfRelation->GetX(), selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint2{ selfRelation->GetX() + 80 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };

			CPoint startPoint3And5{ selfRelation->GetX() + 80 * last->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint3And5{ selfRelation->GetX() + 30 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			cPoint1 = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
			cPoint2 = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
			cPoint3 = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5);
			cPoint4 = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
			cPoint5 = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5);
			selfRelation->rollNamePoints->Modify(0, cPoint1);
			selfRelation->rollNamePoints->Modify(1, cPoint2);
			selfRelation->rollNamePoints->Modify(2, cPoint3);
			selfRelation->rollNamePoints->Modify(3, cPoint4);
			selfRelation->rollNamePoints->Modify(4, cPoint5);

		}
		else if (dynamic_cast<SelfRelation*>(this->GetAt(i)) && static_cast<SelfRelation*>(this->GetAt(i))->leftRightFlag == 1) {
			this->GetAt(i)->Move(0, distanceY);
			SelfRelation *selfRelation = static_cast<SelfRelation*>(this->GetAt(i));
			//자기자신 에디트 이동
			CPoint startPoint1And4{ selfRelation->GetX(), selfRelation->GetY() };
			CPoint endPoint1And4{ selfRelation->GetX() ,  selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };

			CPoint startPoint2{ selfRelation->GetX() - 90 * last->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint2{ selfRelation->GetX() - 80 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint startPoint3{ selfRelation->GetX() - 80 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint3{ selfRelation->GetX() - 120 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint startPoint5{ selfRelation->GetX() - 30 * last->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint5{ selfRelation->GetX() - 80 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			cPoint1 = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
			cPoint2 = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
			cPoint3 = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3, endPoint3);
			cPoint4 = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
			cPoint5 = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint5, endPoint5);
			selfRelation->rollNamePoints->Modify(0, cPoint1);
			selfRelation->rollNamePoints->Modify(1, cPoint2);
			selfRelation->rollNamePoints->Modify(2, cPoint3);
			selfRelation->rollNamePoints->Modify(3, cPoint4);
			selfRelation->rollNamePoints->Modify(4, cPoint5);
		}
		if (dynamic_cast<Class*>(this)) {
			Class *object = static_cast<Class*>(this);
			if (dynamic_cast<Line*>(this->GetAt(i)) || dynamic_cast<ClassName*>(this->GetAt(i)) && editPosition != 0 || dynamic_cast<Template*>(this->GetAt(i))) {
				this->GetAt(i)->Move(0, distanceY);
			}

			if (object->GetReceptionPosition() != -1 || object->GetMethodPosition() != -1) {
				if (dynamic_cast<Attribute*>(this->GetAt(i))) {
					this->GetAt(i)->Move(0, distanceY);
				}
			}
			if (object->GetReceptionPosition() != -1) {
				if (dynamic_cast<Method*>(this->GetAt(i))) {
					this->GetAt(i)->Move(0, distanceY);
				}
			}
		}

		i++;
	}

	this->y = y + distanceY;
	this->height = this->height - distanceY;


	return this;
}

Figure* FigureComposite::ModifyComponetsToLeftDirection(Diagram *diagram, Long distanceX) {
	LastClass *last = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	Long i = 0;
	Long length = 0;
	Long Quadrant;
	Figure *(*figures) = new Figure*[32]; // 32개 넘어가면..?
	Finder finder;
	Long distanceX_;
	double classWidth;
	double distanceToRelationX;
	double modifiedWidth;
	double modifiedDistance;
	Long modifiedRelationX;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	if (distanceX > 0 && this->GetWidth() - distanceX < this->minimumWidth) {
		distanceX = this->GetWidth() - this->minimumWidth;
	}

	finder.FindRelationEndPoints(diagram, this, figures, &length);
	while (i < length) {
		Quadrant = finder.FindQuadrant(figures[i]->GetX() + figures[i]->GetWidth(), figures[i]->GetY() + figures[i]->GetHeight(),
			this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
		Relation *relation = static_cast<Relation*>(figures[i]);
		if (Quadrant == 1 || Quadrant == 3) {
			classWidth = static_cast<double>(this->width);
			distanceToRelationX = static_cast<double>(this->x + this->width) - static_cast<double>(figures[i]->GetX() + figures[i]->GetWidth());
			modifiedWidth = static_cast<double>(this->width - distanceX);
			modifiedDistance = (modifiedWidth*distanceToRelationX) / classWidth;
			modifiedRelationX = this->x + this->width - static_cast<Long>(modifiedDistance);
			distanceX_ = modifiedRelationX - (figures[i]->GetX() + figures[i]->GetWidth());
			figures[i]->EndPointMove(distanceX_, 0);
		}
		else if (Quadrant == 4) {
			figures[i]->EndPointMove(distanceX, 0);
		}
		//관계선 에디트 이동
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
		i++;
	}

	delete[] figures;
	i = 0;

	while (i < this->GetLength()) {
		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			Quadrant = finder.FindQuadrant(this->GetAt(i)->GetX(), this->GetAt(i)->GetY(),
				this->GetX(), this->GetY(), this->GetX() + this->GetWidth(), this->GetY() + this->GetHeight());
			Relation *relation = static_cast<Relation*>(this->GetAt(i));
			if (Quadrant == 1 || Quadrant == 3) {
				classWidth = static_cast<double>(this->width);
				distanceToRelationX = static_cast<double>(this->x + this->width) - static_cast<double>(this->GetAt(i)->GetX());
				modifiedWidth = static_cast<double>(this->width - distanceX);
				modifiedDistance = (modifiedWidth*distanceToRelationX) / classWidth;
				modifiedRelationX = this->x + this->width - static_cast<Long>(modifiedDistance);
				distanceX_ = modifiedRelationX - this->GetAt(i)->GetX();
				this->GetAt(i)->Move(distanceX_, 0);
			}
			else if (Quadrant == 4) {
				this->GetAt(i)->Move(distanceX, 0);
			}
			//관계선 에디트 이동
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
		else if (dynamic_cast<SelfRelation*>(this->GetAt(i)) && static_cast<SelfRelation*>(this->GetAt(i))->leftRightFlag == 1) {
			this->GetAt(i)->Move(distanceX, 0);
			SelfRelation *selfRelation = static_cast<SelfRelation*>(this->GetAt(i));
			//자기자신 에디트 이동
			CPoint startPoint1And4{ selfRelation->GetX(), selfRelation->GetY() };
			CPoint endPoint1And4{ selfRelation->GetX() ,  selfRelation->GetY() - 40 };

			CPoint startPoint2{ selfRelation->GetX()-90 * last->classDiagramForm->zoomRate / 100, selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint2{ selfRelation->GetX() - 80 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() - 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint startPoint3{ selfRelation->GetX() - 80 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint3{ selfRelation->GetX() - 120 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint startPoint5{ selfRelation->GetX() - 30 * last->classDiagramForm->zoomRate / 100, selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			CPoint endPoint5{ selfRelation->GetX() - 80 * last->classDiagramForm->zoomRate / 100,  selfRelation->GetY() + 40 * last->classDiagramForm->zoomRate / 100 };
			cPoint1 = rollNameBoxesPoint->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4);
			cPoint2 = rollNameBoxesPoint->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2);
			cPoint3 = rollNameBoxesPoint->GetSelfRelationThirdRollNamePoint(startPoint3, endPoint3);
			cPoint4 = rollNameBoxesPoint->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4);
			cPoint5 = rollNameBoxesPoint->GetSelfRelationFifthRollNamePoint(startPoint5, endPoint5);
			selfRelation->rollNamePoints->Modify(0, cPoint1);
			selfRelation->rollNamePoints->Modify(1, cPoint2);
			selfRelation->rollNamePoints->Modify(2, cPoint3);
			selfRelation->rollNamePoints->Modify(3, cPoint4);
			selfRelation->rollNamePoints->Modify(4, cPoint5);
		}
		else if (dynamic_cast<Line*>(this->GetAt(i)) || dynamic_cast<ClassName*>(this->GetAt(i)) || dynamic_cast<Attribute*>(this->GetAt(i))
			|| dynamic_cast<Method*>(this->GetAt(i)) || dynamic_cast<Reception*>(this->GetAt(i))) { // Line 이랑 에딧영역
			this->GetAt(i)->Modify(this->GetAt(i)->GetX() + distanceX, this->GetAt(i)->GetY(), this->GetAt(i)->GetWidth() - distanceX, this->GetAt(i)->GetHeight());
		}
		i++;
	}

	this->x = this->x + distanceX;
	this->width = this->width - distanceX;

	return this;
}