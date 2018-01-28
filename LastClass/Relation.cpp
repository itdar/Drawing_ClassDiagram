//Relation.cpp

#include "Relation.h"
#include "Finder.h"
#include "RollNameBox.h"
#include "DrawingVisitor.h"
#include "Figure.h"

Relation::Relation(Long capacity) :Figure(), points(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

Relation::Relation(const Relation& source) : Figure(source), points(source.points) {
	Long i = 0;

	if (this->rollNamePoints != 0) {
		rollNamePoints->Clear();
	}
	this->rollNamePoints = new Array<CPoint>(5);
	i = 0;
	while (i < source.rollNamePoints->GetLength()) {
		this->rollNamePoints->Store(i, const_cast<Relation&>(source).rollNamePoints->GetAt(i));
		i++;
	}

	if (this->rollNames != 0) {
		rollNames->Clear();
	}
	this->rollNames = new Array<string>(5);
	i = 0;
	while (i < 5) {
		this->rollNames->Store(i, const_cast<Relation&>(source).rollNames->GetAt(i));
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
}

Relation::Relation(Long x, Long y, Long width, Long height) :Figure(x, y, width, height), points(10) {
	this->capacity = 10;
	this->length = 0;
	this->rollNamePoints = new Array<CPoint>(5);
	this->rollNames = new Array<string>(5);
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Store(0, rollNameBox->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Store(1, rollNameBox->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Store(2, rollNameBox->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Store(3, rollNameBox->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Store(4, rollNameBox->GetFifthRollNamePoint(startPoint, endPoint));
}

Relation& Relation::operator=(const Relation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	Long i = 0;
	while (i < source.length) {
		this->points.Modify(i, const_cast<Relation&>(source).points[i]);
		i++;
	}
	return *this;
}

Relation::~Relation() {
}

Figure* Relation::Clone() const {
	return new Relation(*this);
}

Long Relation::Move(Long index, CPoint cPoint) {
	return this->points.Modify(index, cPoint);
}

CPoint Relation::GetAt(Long index) {
	return this->points.GetAt(index);
}

Long Relation::Add(const CPoint& startCPoint, const CPoint& currentCPoint) {
	Long index;
	Finder finder;
	if (this->length == 0) { // 관계선이 없으면
		index = this->points.Store(this->length, currentCPoint); //store 로 저장한다
	}
	else { // 선이 있으면
		bool ret = false;
		CPoint lineStart(this->x, this->y);
		CPoint lineEnd;

		index = 0;
		while (index < this->length && ret == false) { // 선을 찾을 때까지 전체 반복한다
			lineEnd.x = this->GetAt(index).x;
			lineEnd.y = this->GetAt(index).y;
			ret = finder.FindLineByPoint(lineStart, lineEnd, startCPoint.x, startCPoint.y);
			lineStart.x = lineEnd.x;
			lineStart.y = lineEnd.y;
			index++;
		}
		if (ret == true) { // 찾았으면
			index--;
		}
		lineEnd.x = this->width + this->x;
		lineEnd.y = this->height + this->y;
		if (ret == false) { // 못찾았으면
			ret = finder.FindLineByPoint(lineStart, lineEnd, startCPoint.x, startCPoint.y);
		}

		this->points.Insert(index, currentCPoint); // 이동된 currentCPoint 를 insert 한다
		this->capacity++;
	}
	this->length++;
	return index;
}
Long Relation::Add(const CPoint& cPoint) {
	if (this->length < this->capacity) {
		this->points.Store(this->length, cPoint);
	}
	else {
		this->points.AppendFromRear(cPoint);
		this->capacity++;
	}
	this->length++;
	return this->length;
}
Long Relation::Remove(Long index) {
	this->length--;
	this->capacity--;
	return this->points.Delete(index);
}
void Relation::MergePoints(Long selectIndex, CPoint cPoint) {
	Long index = -1;
	bool ret;
	Finder finder;
	CRect cRect1(cPoint.x - 5, cPoint.y - 5, cPoint.x + 5, cPoint.y + 5);
	CPoint compare;
	compare.x = this->x;
	compare.y = this->y;

	CRect cRect(compare.x - 5, compare.y - 5, compare.x + 5, compare.y + 5);
	ret = finder.FindRectangleByArea(cRect1, cRect);
	if (ret == true) {
		index = 0;
	}
	Long i = 0;
	while (i < this->length && index == -1) {
		compare.x = this->GetAt(i).x;
		compare.y = this->GetAt(i).y;
		CRect cRect2(compare.x - 5, compare.y - 5, compare.x + 5, compare.y + 5);
		ret = finder.FindRectangleByArea(cRect1, cRect2);
		if (ret == true) {
			index = i + 1;
		}
		i++;
	}
	if (index == -1) {
		compare.x = this->x + this->width;
		compare.y = this->y + this->height;
		CRect cRect3(compare.x - 5, compare.y - 5, compare.x + 5, compare.y + 5);
		ret = finder.FindRectangleByArea(cRect1, cRect3);
		if (ret == true)
		{
			index = this->length + 1;

		}
	}

	Long startIndex = selectIndex;
	Long currentIndex = index;
	if (currentIndex != -1) {
		if (startIndex > currentIndex) {
			Long i = 0;
			Long count = startIndex - currentIndex;
			while (i < count) {
				this->Remove(currentIndex + 1);
				i++;
			}
		}
		if (startIndex < currentIndex) {
			Long i = 0;
			Long count = currentIndex - startIndex;
			while (i < count) {
				this->Remove(startIndex);
				i++;
			}
		}
	}
}

void Relation::ReplaceString(string rollNameText, Long rollNameBoxIndex) {
	this->rollNames->Modify(rollNameBoxIndex, rollNameText);
}

void Relation::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);//, cPaintDc);
}

void Relation::MovePaste(Long distanceX, Long distanceY) {
	this->x = this->x + distanceX;
	this->y = this->y + distanceY;
}

Long Relation::Correct(Long index, CPoint point) {
	return this->points.Modify(index, point);
}


