//SelfRelation.cpp

#include "RollNameBox.h"
#include "Visitor.h"
#include "SelfRelation.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"

SelfRelation::SelfRelation() :Figure() {
	this->leftRightFlag = 0;
}

SelfRelation::SelfRelation(Long x, Long y, Long width, Long height) : Figure(x, y, width, height) {
	LastClass *lastClass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));

	this->leftRightFlag = 0;
	this->rollNamePoints = new Array<CPoint>(5);
	this->rollNames = new Array<string>(5);

	CPoint startPoint1And4{ x, y };
	CPoint endPoint1And4{ x , y - 40 * lastClass->classDiagramForm->zoomRate / 100 };

	CPoint startPoint2{ x, y - 40 * lastClass->classDiagramForm->zoomRate / 100 };
	CPoint endPoint2{ x + 80 * lastClass->classDiagramForm->zoomRate / 100,  y - 40 * lastClass->classDiagramForm->zoomRate / 100 };

	CPoint startPoint3And5{ x + 80 * lastClass->classDiagramForm->zoomRate / 100, y + 40 * lastClass->classDiagramForm->zoomRate / 100 };
	CPoint endPoint3And5{ x + 30 * lastClass->classDiagramForm->zoomRate / 100,  y + 40 * lastClass->classDiagramForm->zoomRate / 100 };

	RollNameBox *rollNameBox = RollNameBox::Instance();
	this->rollNamePoints->Store(0, rollNameBox->GetSelfRelationFirstRollNamePoint(startPoint1And4, endPoint1And4));
	this->rollNamePoints->Store(1, rollNameBox->GetSelfRelationSecondRollNamePoint(startPoint2, endPoint2));
	this->rollNamePoints->Store(2, rollNameBox->GetSelfRelationThirdRollNamePoint(startPoint3And5, endPoint3And5));
	this->rollNamePoints->Store(3, rollNameBox->GetSelfRelationFourthRollNamePoint(startPoint1And4, endPoint1And4));
	this->rollNamePoints->Store(4, rollNameBox->GetSelfRelationFifthRollNamePoint(startPoint3And5, endPoint3And5));
}

SelfRelation::SelfRelation(const SelfRelation& source) : Figure(source) {
	this->leftRightFlag = source.leftRightFlag;
	Long i = 0;

	if (this->rollNamePoints != 0) {
		rollNamePoints->Clear();
	}
	this->rollNamePoints = new Array<CPoint>(5);
	i = 0;
	while (i < source.rollNamePoints->GetLength()) {
		this->rollNamePoints->Store(i, const_cast<SelfRelation&>(source).rollNamePoints->GetAt(i));
		i++;
	}

	if (this->rollNames != 0) {
		rollNames->Clear();
	}
	this->rollNames = new Array<string>(5);
	i = 0;
	while (i < 5) {
		this->rollNames->Store(i, const_cast<SelfRelation&>(source).rollNames->GetAt(i));
		i++;
	}
}

SelfRelation::~SelfRelation() {
}

SelfRelation& SelfRelation::operator=(const SelfRelation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->leftRightFlag = source.leftRightFlag;
	return *this;
}

void SelfRelation::ReplaceString(string rollNameText, Long rollNameBoxIndex) {
	this->rollNames->Modify(rollNameBoxIndex, rollNameText);
}

void SelfRelation::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this, cPaintDc);
}
