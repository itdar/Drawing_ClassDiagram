#include "Selection.h"
#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "Diagram.h"
#include "Relation.h"
#include "Finder.h"
#include "SelfRelation.h"
#include "Class.h"
#include "Template.h"
#include "HistoryGraphic.h"
#include "Association.h"
#include  "Aggregation.h"
#include "Aggregations.h"
#include "DirectedAssociation.h"
#include "SelfAggregation.h"
#include "SelfAggregations.h"
#include "SelfAssociation.h"
#include "SelfDirectedAssociation.h"

Selection::Selection(Long capacity) :FigureComposite(capacity) {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}
Selection::Selection(const Selection& source) : FigureComposite(source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;
}
Selection::~Selection() {
}
Selection& Selection::operator=(const Selection& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < source.length) {
		this->figures.Modify(i, (const_cast<Selection&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;

	return *this;
}

Long Selection::Add(Figure *figure) {
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

Long Selection::Remove(Diagram *diagram, Figure *figure) {
	Long i = 0;
	Long index = -1;
	FigureComposite *figures = 0;
	while (i < diagram->GetLength() && figure != diagram->GetAt(i)) {
		i++;
	}
	if (i < diagram->GetLength()) {
		index = i;
		diagram->Remove(index);
	}

	i = 0;
	Long j;
	while (i < diagram->GetLength() && index == -1) {
		j = 0;
		figures = static_cast<FigureComposite*>(diagram->GetAt(i));
		while (j < figures->GetLength() && figure != figures->GetAt(j)) {
			j++;
		}
		if (j < figures->GetLength()) {
			index = j;
			figures->Remove(index);
		}
		i++;
	}

	this->figures.Delete(this->length - 1);
	this->length--;
	this->capacity--;
	return index;
}

Long Selection::Remove(Long index) {
	this->capacity--;
	this->length--;
	return this->figures.Delete(index);
}

Figure* Selection::Clone() const {
	return new Selection(*this);
}

Figure* Selection::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}
void Selection::DeleteAllItems() {
	while (this->length != 0) {
		this->figures.Delete(this->length - 1);
		this->length--;
		this->capacity--;
	}
}

void Selection::SelectByArea(Diagram *diagram, CRect area) {

	Finder finder;
	Long i = 0;
	Long j;
	Long k;

	FigureComposite *composite;
	CRect rect;
	bool ret = false;
	Relation *relation;

	while (i < diagram->GetLength()) {
		//수정
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		rect.left = composite->GetX();
		rect.top = composite->GetY();
		rect.right = composite->GetX() + composite->GetWidth();
		rect.bottom = composite->GetY() + composite->GetHeight();

		ret = finder.FindRectangleByArea(rect, area);

		if (ret == true) {
			if (this->length < this->capacity) {
				this->figures.Store(this->length, composite);
			}
			else {
				this->figures.AppendFromRear(composite);
				this->capacity++;
			}
			this->length++;
		}

		j = 0;
		while (j < composite->GetLength()) {
			if (dynamic_cast<Relation*>(composite->GetAt(j))) {

				relation = static_cast<Relation*>(composite->GetAt(j));

				CPoint lineStart(relation->GetX(), relation->GetY());
				CPoint lineEnd;

				ret = false;
				k = 0;

				while (k < relation->GetLength() && ret == false) {
					lineEnd.x = relation->GetAt(k).x;
					lineEnd.y = relation->GetAt(k).y;
					ret = finder.FindLineByArea(lineStart, lineEnd, area);
					lineStart.x = lineEnd.x;
					lineStart.y = lineEnd.y;
					k++;
				}

				lineEnd.x = relation->GetWidth() + relation->GetX();
				lineEnd.y = relation->GetHeight() + relation->GetY();

				if (ret == false) {
					ret = finder.FindLineByArea(lineStart, lineEnd, area);
				}

				if (ret == true) {
					if (this->length < this->capacity) {
						this->figures.Store(this->length, relation);
					}
					else {
						this->figures.AppendFromRear(relation);
						this->capacity++;
					}
					this->length++;
				}
			}
			j++;
		}
		i++;
	}
}
Long Selection::SelectByPoint(Long x, Long y) {
	Finder finder;
	CRect rect;
	FigureComposite *composite;
	Relation *relation = 0;
	SelfRelation *selfRelation = 0;
	bool ret = false;
	Long i = 0;
	Long j = 0;
	Long index = -1;
	CPoint lineStart;
	CPoint lineEnd;
	bool squareFace = false;

	while (i < this->GetLength() && index == -1) {
		if (dynamic_cast<Relation*>(this->GetAt(i))) {
			relation = static_cast<Relation*>(this->GetAt(i));


			CRect rect(relation->GetX() - 10, relation->GetY() - 10, relation->GetX() + 10, relation->GetY() + 10);
			if (finder.FindRectangleByPoint(rect, x, y)) {
				index = 1;
			}
			CRect rect1(relation->GetX() + relation->GetWidth() - 10, relation->GetY() + relation->GetHeight() - 10, relation->GetX() + relation->GetWidth() + 10, relation->GetY() + relation->GetHeight() + 10);
			if (finder.FindRectangleByPoint(rect1, x, y)) {
				index = 1;
			}
			if (index == -1) {
				CPoint lineStart(relation->GetX(), relation->GetY());
				while (j < relation->GetLength() && squareFace == false) {
					lineEnd.x = relation->GetAt(j).x;
					lineEnd.y = relation->GetAt(j).y;
					squareFace = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					lineStart.x = lineEnd.x;
					lineStart.y = lineEnd.y;
					j++;
				}
				if (squareFace == false) {
					lineEnd.x = relation->GetWidth() + relation->GetX();
					lineEnd.y = relation->GetHeight() + relation->GetY();
					squareFace = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}
				if (squareFace == true) {
					index = 2;
				}
			}
		}

		if (dynamic_cast<FigureComposite*>(this->GetAt(i))) {
			composite = static_cast<FigureComposite*>(this->GetAt(i));
			if (dynamic_cast<Class*>(composite)) {
				if (static_cast<Class*>(composite)->GetTempletePosition() != -1) {
					Template *object2 = dynamic_cast<Template*>(composite->GetAt(static_cast<Class*>(composite)->GetTempletePosition()));
					//좌상
					rect.left = composite->GetX() - 3;
					rect.top = object2->GetY() - 3;
					rect.right = composite->GetX() + 6;
					rect.bottom = object2->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 3;
					}
					if (ret != true) {//중 상단
						rect.left = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 - 4;
						rect.top = object2->GetY() - 3;
						rect.right = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 + 5;
						rect.bottom = object2->GetY() + 6;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 4;
						}
					}
					if (ret != true) {//우상
						rect.left = object2->GetX() + object2->GetWidth() - 6;
						rect.top = object2->GetY() - 3;
						rect.right = object2->GetX() + object2->GetWidth() + 3;
						rect.bottom = object2->GetY() + 6;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 5;
						}
					}
					if (ret != true) {//좌중
						rect.left = composite->GetX() - 3;
						rect.top = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 - 4;;
						rect.right = composite->GetX() + 6;
						rect.bottom = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 + 5;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 6;
						}
					}
					if (ret != true) {//우중
						rect.left = object2->GetX() + object2->GetWidth() - 6;
						rect.top = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 - 4;
						rect.right = object2->GetX() + object2->GetWidth() + 3;
						rect.bottom = object2->GetY() + (composite->GetY() + composite->GetHeight() - object2->GetY()) / 2 + 5;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 7;
						}
					}
					if (ret != true) {//좌하
						rect.left = composite->GetX() - 3;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + 6;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 8;
						}
					}
					if (ret != true) {//중하
						rect.left = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 - 4;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + (object2->GetX() + object2->GetWidth() - composite->GetX()) / 2 + 5;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 9;
						}
					}
					if (ret != true) {	//우하
						rect.left = object2->GetX() + object2->GetWidth() - 6;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = object2->GetX() + object2->GetWidth() + 3;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 10;
						}
					}
				}
				else {
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() - 3;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 3;
					}
					if (ret != true) {//중상
						rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
						rect.top = composite->GetY() - 3;
						rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
						rect.bottom = composite->GetY() + 6;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 4;
						}
					}
					if (ret != true) {//
						rect.left = composite->GetX() + composite->GetWidth() - 6;
						rect.top = composite->GetY() - 3;
						rect.right = composite->GetX() + composite->GetWidth() + 3;
						rect.bottom = composite->GetY() + 6;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 5;
						}
					}
					if (ret != true) {
						rect.left = composite->GetX() - 3;
						rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
						rect.right = composite->GetX() + 6;
						rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 6;
						}
					}
					if (ret != true) {
						rect.left = composite->GetX() + composite->GetWidth() - 6;
						rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
						rect.right = composite->GetX() + composite->GetWidth() + 3;
						rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 7;
						}
					}
					if (ret != true) {
						rect.left = composite->GetX() - 3;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + 6;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 8;
						}
					}
					if (ret != true) {
						rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 9;
						}
					}
					if (ret != true) {
						rect.left = composite->GetX() + composite->GetWidth() - 6;
						rect.top = composite->GetY() + composite->GetHeight() - 6;
						rect.right = composite->GetX() + composite->GetWidth() + 3;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						ret = finder.FindRectangleByPoint(rect, x, y);
						if (ret == true) {
							index = 10;
						}
					}
				}
			}
			else {
				rect.left = composite->GetX() - 3;
				rect.top = composite->GetY() - 3;
				rect.right = composite->GetX() + 6;
				rect.bottom = composite->GetY() + 6;
				ret = finder.FindRectangleByPoint(rect, x, y);
				if (ret == true) {
					index = 3;
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
					rect.top = composite->GetY() - 3;
					rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
					rect.bottom = composite->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 4;
					}
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() - 6;
					rect.top = composite->GetY() - 3;
					rect.right = composite->GetX() + composite->GetWidth() + 3;
					rect.bottom = composite->GetY() + 6;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 5;
					}
				}
				if (ret != true) {
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 6;
					}
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() - 6;
					rect.top = composite->GetY() + composite->GetHeight() / 2 - 4;
					rect.right = composite->GetX() + composite->GetWidth() + 3;
					rect.bottom = composite->GetY() + composite->GetHeight() / 2 + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 7;
					}
				}
				if (ret != true) {
					rect.left = composite->GetX() - 3;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + 6;
					rect.bottom = composite->GetY() + composite->GetHeight() + 5;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 8;
					}
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() / 2 - 4;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + composite->GetWidth() / 2 + 5;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 9;
					}
				}
				if (ret != true) {
					rect.left = composite->GetX() + composite->GetWidth() - 6;
					rect.top = composite->GetY() + composite->GetHeight() - 6;
					rect.right = composite->GetX() + composite->GetWidth() + 3;
					rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 10;
					}
				}
			}//1여기에 템플릿일때 if() 이거하고/2 템플릿일때 작은 사각형 누르기 하고/3 확대하기 
			CPoint attributeStartPoint(0, 0);
			CPoint attributeEndPoint(0, 0);
			CPoint methodStartPoint(0, 0);
			CPoint methodEndPoint(0, 0);
			CPoint receptionStartPoint(0, 0);
			CPoint receptionEndPoint(0, 0);
			if (dynamic_cast<Class*>(composite)) {
				Class *object = static_cast<Class*>(composite);
				if (object->GetAttributePosition() != -1) {
					attributeStartPoint.x = object->GetAt(object->GetAttributePosition() - 1)->GetX();
					attributeStartPoint.y = object->GetAt(object->GetAttributePosition() - 1)->GetY();
					attributeEndPoint.x = object->GetAt(object->GetAttributePosition() - 1)->GetX() + object->GetAt(object->GetAttributePosition() - 1)->GetWidth();
					attributeEndPoint.y = object->GetAt(object->GetAttributePosition() - 1)->GetY();
				}
				if (object->GetMethodPosition() != -1) {
					methodStartPoint.x = object->GetAt(object->GetMethodPosition() - 1)->GetX();
					methodStartPoint.y = object->GetAt(object->GetMethodPosition() - 1)->GetY();
					methodEndPoint.x = object->GetAt(object->GetMethodPosition() - 1)->GetX() + object->GetAt(object->GetMethodPosition() - 1)->GetWidth();
					methodEndPoint.y = object->GetAt(object->GetMethodPosition() - 1)->GetY();
				}
				if (object->GetReceptionPosition() != -1) {
					receptionStartPoint.x = object->GetAt(object->GetReceptionPosition() - 1)->GetX();
					receptionStartPoint.y = object->GetAt(object->GetReceptionPosition() - 1)->GetY();
					receptionEndPoint.x = object->GetAt(object->GetReceptionPosition() - 1)->GetX() + object->GetAt(object->GetReceptionPosition() - 1)->GetWidth();
					receptionEndPoint.y = object->GetAt(object->GetReceptionPosition() - 1)->GetY();
				}
			}
			if (ret == true) {
				//index = 3;
			}
			else {
				rect.left = x - 8;
				rect.top = y - 8;
				rect.right = x + 8;
				rect.bottom = y + 8;
					if (ret != true) {
						ret = finder.FindLineByArea(attributeStartPoint, attributeEndPoint, rect);
					}
				
					if (ret != true) {
						ret = finder.FindLineByArea(methodStartPoint, methodEndPoint, rect);
					}
				
					if (ret != true) {
						ret = finder.FindLineByArea(receptionStartPoint, receptionEndPoint, rect);
					}
				
				if (ret == true) {
					index = 12;
				}
				else {
					if (dynamic_cast<Class*>(composite)) {
						if (static_cast<Class*>(composite)->GetTempletePosition() != -1) {
							Template *object2 = dynamic_cast<Template*>(composite->GetAt(static_cast<Class*>(composite)->GetTempletePosition()));
							rect.left = composite->GetX() - 3;
							rect.top = object2->GetY() - 3;
							rect.right = object2->GetX() + object2->GetWidth() + 3;
							rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						}
						else {
							rect.left = composite->GetX() - 3;
							rect.top = composite->GetY() - 3;
							rect.right = composite->GetX() + composite->GetWidth() + 3;
							rect.bottom = composite->GetY() + composite->GetHeight() + 3;
						}
					}
					else {
						rect.left = composite->GetX() - 3;
						rect.top = composite->GetY() - 3;
						rect.right = composite->GetX() + composite->GetWidth() + 3;
						rect.bottom = composite->GetY() + composite->GetHeight() + 3;
					}

					ret = finder.FindRectangleByPoint(rect, x, y);
					if (ret == true) {
						index = 11;
					}
				}
			}
		}
		i++;
	}
	return index;

}


Long Selection::SelectByPoint(Diagram *diagram, Long x, Long y) {
	LastClass *lastClass = (LastClass*)CFrameWnd::FindWindow(NULL, "LastClass");
	Long zoomRate = lastClass->classDiagramForm->zoomRate;
	Finder finder;
	CRect rect;
	FigureComposite *composite;
	Relation *relation = 0;
	SelfRelation *selfRelation = 0;
	bool ret = false;
	Long i = 0;
	Long j;
	Long k;
	Long index = -1;
	CPoint lineStart;
	CPoint lineEnd;
	Long isOne = 0;
	while (i < diagram->GetLength()/*&& ret == false*/) {//
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		if (dynamic_cast<Class*>(composite)) {
			if (static_cast<Class*>(composite)->GetTempletePosition() == -1) {
				Class *object = static_cast<Class*>(composite);
				rect.left = object->GetLeft();
				rect.top = object->GetTop();
				rect.right = object->GetRight();
				rect.bottom = object->GetBottom();
				ret = finder.FindRectangleByPoint(rect, x, y);
			}
			else {
				Class *object = static_cast<Class*>(composite);
				Figure *figure = object->GetAt(object->GetTempletePosition());
				rect.left = composite->GetLeft();
				rect.top = figure->GetTop();
				rect.right = figure->GetRight();
				rect.bottom = composite->GetBottom();
				ret = finder.FindRectangleByPoint(rect, x, y);
			}

		}
		else {
			rect.left = composite->GetLeft();
			rect.top = composite->GetTop();
			rect.right = composite->GetRight();
			rect.bottom = composite->GetBottom();
			ret = finder.FindRectangleByPoint(rect, x, y);
		}
		//1여기에 템플릿일때 if() 이거하고/2 템플릿일때 작은 사각형 누르기 하고/3 확대하기 

		if (ret == true && isOne == 0) {
			if (this->length < this->capacity) {
				this->figures.Store(this->length, composite);
			}
			else {
				this->figures.AppendFromRear(composite);
				this->capacity++;
			}
			isOne = 1;
			this->length++;
			index = this->length;
		}
		else if (ret == true && isOne == 1) {
			this->figures.Modify(0, composite);
			index = this->length;
		}

		j = 0;
		while (j < composite->GetLength() && ret == false) {
			if (dynamic_cast<Relation*>(composite->GetAt(j))) {
				relation = static_cast<Relation*>(composite->GetAt(j));


				lineStart.x = relation->GetX();
				lineStart.y = relation->GetY();

				k = 0;
				while (k < relation->GetLength() && ret == false) {

					lineEnd.x = relation->GetAt(k).x;
					lineEnd.y = relation->GetAt(k).y;
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					lineStart.x = lineEnd.x;
					lineStart.y = lineEnd.y;
					k++;
				}

				lineEnd.x = relation->GetWidth() + relation->GetX();
				lineEnd.y = relation->GetHeight() + relation->GetY();
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}
				//여기 부터 바깥 사각박스 찾기
				if (dynamic_cast<DirectedAssociation*>(relation) || dynamic_cast<Association*>(relation) ||
					dynamic_cast<Aggregation*>(relation) || dynamic_cast<Aggregations*>(relation)) {
					Long l = 0;
					while (l < 5 && ret == false) {
						if (l == 1) {
							rect.left = relation->rollNamePoints->GetAt(l).x - 40 * zoomRate / 100;
							rect.right = relation->rollNamePoints->GetAt(l).x + 40 * zoomRate / 100;
							rect.top = relation->rollNamePoints->GetAt(l).y - 10 * zoomRate / 100;
							rect.bottom = relation->rollNamePoints->GetAt(l).y + 10 * zoomRate / 100;
						}
						else if (l == 0 || l == 2) {
							rect.left = relation->rollNamePoints->GetAt(l).x - 20 * zoomRate / 100;
							rect.right = relation->rollNamePoints->GetAt(l).x + 20 * zoomRate / 100;
							rect.top = relation->rollNamePoints->GetAt(l).y - 10 * zoomRate / 100;
							rect.bottom = relation->rollNamePoints->GetAt(l).y + 10 * zoomRate / 100;
						}
						else if (l == 3 || l == 4) {
							rect.left = relation->rollNamePoints->GetAt(l).x - 25 * zoomRate / 100;
							rect.right = relation->rollNamePoints->GetAt(l).x + 25 * zoomRate / 100;
							rect.top = relation->rollNamePoints->GetAt(l).y - 10 * zoomRate / 100;
							rect.bottom = relation->rollNamePoints->GetAt(l).y + 10 * zoomRate / 100;
						}

						if (ret == false) {
							ret = finder.FindRectangleByPoint(rect, x, y);
						}
						l++;
					}
				}
				if (ret == true) {
					if (this->length < this->capacity) {
						this->figures.Store(this->length, relation);
					}
					else {
						this->figures.AppendFromRear(relation);
						this->capacity++;
					}
					this->length++;

					index = this->length;
				}
			}
			if (dynamic_cast<SelfRelation*>(composite->GetAt(j))) {
				selfRelation = static_cast<SelfRelation*>(composite->GetAt(j));
				lineStart.x = selfRelation->GetX();
				lineStart.y = selfRelation->GetY();
				lineEnd.x = selfRelation->GetX();
				lineEnd.y = selfRelation->GetY() - 40 * zoomRate / 100;
				if (ret == false) {
					ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
				}
				if (selfRelation->leftRightFlag == 0) {
					lineStart.x = selfRelation->GetX();
					lineStart.y = selfRelation->GetY() - 40 * zoomRate / 100;
					lineEnd.x = selfRelation->GetX() + 80 * zoomRate / 100;
					lineEnd.y = selfRelation->GetY() - 40 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					}

					lineStart.x = selfRelation->GetX() + 80 * zoomRate / 100;
					lineStart.y = selfRelation->GetY() - 40 * zoomRate / 100;
					lineEnd.x = selfRelation->GetX() + 80 * zoomRate / 100;
					lineEnd.y = selfRelation->GetY() + 40 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					}

					lineStart.x = selfRelation->GetX() + 80 * zoomRate / 100;
					lineStart.y = selfRelation->GetY() + 40 * zoomRate / 100;
					lineEnd.x = selfRelation->GetX() + 30 * zoomRate / 100;
					lineEnd.y = selfRelation->GetY() + 40 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					}
				}
				else {
					lineStart.x = selfRelation->GetX();
					lineStart.y = selfRelation->GetY() - 40 * zoomRate / 100;
					lineEnd.x = selfRelation->GetX() - 80 * zoomRate / 100;
					lineEnd.y = selfRelation->GetY() - 40 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					}

					lineStart.x = selfRelation->GetX() - 80 * zoomRate / 100;
					lineStart.y = selfRelation->GetY() - 40 * zoomRate / 100;
					lineEnd.x = selfRelation->GetX() - 80 * zoomRate / 100;
					lineEnd.y = selfRelation->GetY() + 40 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					}

					lineStart.x = selfRelation->GetX() - 80 * zoomRate / 100;
					lineStart.y = selfRelation->GetY() + 40 * zoomRate / 100;
					lineEnd.x = selfRelation->GetX() - 30 * zoomRate / 100;
					lineEnd.y = selfRelation->GetY() + 40 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindLineByPoint(lineStart, lineEnd, x, y);
					}
				}

				//여기 부터 바깥 사각박스 찾기
				if (dynamic_cast<SelfDirectedAssociation*>(selfRelation) || dynamic_cast<SelfAssociation*>(selfRelation) ||
					dynamic_cast<SelfAggregation*>(selfRelation) || dynamic_cast<SelfAggregations*>(selfRelation)) {
					//여기 부터 바깥 사각박스 찾기
					rect.left = selfRelation->rollNamePoints->GetAt(0).x - 10 * zoomRate / 100;
					rect.right = selfRelation->rollNamePoints->GetAt(0).x + 20 * zoomRate / 100;
					rect.top = selfRelation->rollNamePoints->GetAt(0).y - 10 * zoomRate / 100;
					rect.bottom = selfRelation->rollNamePoints->GetAt(0).y + 10 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					rect.left = selfRelation->rollNamePoints->GetAt(1).x - 30 * zoomRate / 100;
					rect.right = selfRelation->rollNamePoints->GetAt(1).x + 30 * zoomRate / 100;
					rect.top = selfRelation->rollNamePoints->GetAt(1).y - 10 * zoomRate / 100;
					rect.bottom = selfRelation->rollNamePoints->GetAt(1).y + 10 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					rect.left = selfRelation->rollNamePoints->GetAt(2).x - 20 * zoomRate / 100;
					rect.right = selfRelation->rollNamePoints->GetAt(2).x + 50 * zoomRate / 100;
					rect.top = selfRelation->rollNamePoints->GetAt(2).y - 10 * zoomRate / 100;
					rect.bottom = selfRelation->rollNamePoints->GetAt(2).y + 10 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					rect.left = selfRelation->rollNamePoints->GetAt(3).x - 20 * zoomRate / 100;
					rect.right = selfRelation->rollNamePoints->GetAt(3).x + 50 * zoomRate / 100;
					rect.top = selfRelation->rollNamePoints->GetAt(3).y - 10 * zoomRate / 100;
					rect.bottom = selfRelation->rollNamePoints->GetAt(3).y + 10 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
					rect.left = selfRelation->rollNamePoints->GetAt(4).x - 20 * zoomRate / 100;
					rect.right = selfRelation->rollNamePoints->GetAt(4).x + 10 * zoomRate / 100;
					rect.top = selfRelation->rollNamePoints->GetAt(4).y - 10 * zoomRate / 100;
					rect.bottom = selfRelation->rollNamePoints->GetAt(4).y + 10 * zoomRate / 100;
					if (ret == false) {
						ret = finder.FindRectangleByPoint(rect, x, y);
					}
				}
				if (ret == true) {
					if (this->length < this->capacity) {
						this->figures.Store(this->length, selfRelation);
					}
					else {
						this->figures.AppendFromRear(selfRelation);
						this->capacity++;
					}
					this->length++;

					index = this->length;
				}
			}
			j++;
		}
		i++;
	}
	return index;
}

void Selection::Accept(Diagram *diagram, Visitor& visitor, Long distanceX, Long distanceY) {
	visitor.Visit(diagram, this, distanceX, distanceY);
}

void Selection::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}

Long Selection::Correct(Figure *figure, Long index) {
	index = this->figures.Modify(index, figure);
	return index;
}
Long Selection::SelectByPointForRelation(Diagram *diagram, Long x, Long y) {
	Finder finder;
	CRect rect;
	FigureComposite *composite;
	
	bool ret = false;
	Long i = 0;
	Long index = -1;


	while (i < diagram->GetLength() && ret == false) {
		composite = static_cast<FigureComposite*>(diagram->GetAt(i));
		if (dynamic_cast<Class*>(composite)) {
			if (dynamic_cast<Class*>(composite)->GetTempletePosition() != -1) {
				Template *object = dynamic_cast<Template*>(composite->GetAt(static_cast<Class*>(composite)->GetTempletePosition()));
				rect.left = composite->GetX();
				rect.top = object->GetY();
				rect.right = object->GetX() + object->GetWidth();
				rect.bottom = composite->GetY() + composite->GetHeight();
				ret = finder.FindRectangleByPoint(rect, x, y);

			}


			else {
				rect.left = composite->GetX();
				rect.top = composite->GetY();
				rect.right = composite->GetX() + composite->GetWidth();
				rect.bottom = composite->GetY() + composite->GetHeight();
				ret = finder.FindRectangleByPoint(rect, x, y);

			}
		}


		//1여기에 템플릿일때 if() 이거하고/2 템플릿일때 작은 사각형 누르기 하고/3 확대하기 


		if (ret == true) {
			if (this->length < this->capacity) {
				this->figures.Store(this->length, composite);
			}
			else {
				this->figures.AppendFromRear(composite);
				this->capacity++;
			}
			this->length++;

			index = this->length;
		}
		i++;
	}
	return index;
}

#include "SmartPointer.h"
#include "MemoBox.h"
#include "MemoLine.h"

Selection* Selection::MakeSelectionBuffer(Selection& selection) {
	Long i;
	Long j;
	Long k;
	Selection *copyBuffer = new Selection(selection);
	i = 0;
	SmartPointer<Figure*>SelectionSmartPointer(selection.CreateIterator());
	//Selection 배열 반복자
	for (SelectionSmartPointer->First(); !SelectionSmartPointer->IsDone(); SelectionSmartPointer->Next()) {
		if (dynamic_cast<FigureComposite*>(SelectionSmartPointer->Current())) {
			FigureComposite *figureComposite = static_cast<FigureComposite*>(SelectionSmartPointer->Current());
			j = 0;
			SmartPointer<Figure*>CompositeSmartPointer(figureComposite->CreateIterator());
			//FigureCompsotie 배열 반복자
			for (CompositeSmartPointer->First(); !CompositeSmartPointer->IsDone(); CompositeSmartPointer->Next()) {
				Figure *figure = CompositeSmartPointer->Current();
				if (figure->GetEndPointFigure() != 0) {
					k = 0;
					//EndPointFigure 위치(index)를 찾는다
					while (k < selection.GetLength() && figure->GetEndPointFigure() != selection.GetAt(k)) {
						k++;
					}
					if (k < selection.GetLength()) {
						FigureComposite *bufferComposite = static_cast<FigureComposite*>(copyBuffer->GetAt(i));
						Figure *bufferRelation = bufferComposite->GetAt(j);
						if (dynamic_cast<Class*>(bufferComposite)) {
							bufferRelation->SetEndPointFigure(static_cast<Class*>(copyBuffer->GetAt(k)));
						}
						else if (dynamic_cast<MemoBox*>(bufferComposite)) {
							bufferRelation->SetEndPointFigure(static_cast<MemoBox*>(copyBuffer->GetAt(k)));
						}
					}
				}
				j++;
			}
		}
		i++;
	}
	return copyBuffer;
}

CPoint Selection::GetTopLeftPoint(Selection& selection) {
	Long i = 0;
	CPoint point = { 0, };
	point.x = selection.GetAt(0)->GetX();
	point.y = selection.GetAt(0)->GetY();

	SmartPointer<Figure*>CopyBufferSmartPointer(selection.CreateIterator());
	for (CopyBufferSmartPointer->First(); !CopyBufferSmartPointer->IsDone(); CopyBufferSmartPointer->Next()) {
		if (dynamic_cast<FigureComposite*>(CopyBufferSmartPointer->Current())) {
			if (CopyBufferSmartPointer->Current()->GetY() < point.y) {   //minimumY
				point.y = CopyBufferSmartPointer->Current()->GetY();
				point.x = CopyBufferSmartPointer->Current()->GetX();
			}
			else if (CopyBufferSmartPointer->Current()->GetY() == point.y && CopyBufferSmartPointer->Current()->GetX() < point.x) {
				point.x = CopyBufferSmartPointer->Current()->GetX();
			}
			i++;
		}
	}

	return point;
}

void Selection::DeleteOutSideRelation(Selection& selection) {
	Long i;
	Long j;


	bool connect;
	//연결되지 않은 선 제거
	SmartPointer<Figure*>SelectionSmartPointer(selection.CreateIterator());
	for (SelectionSmartPointer->First(); !SelectionSmartPointer->IsDone(); SelectionSmartPointer->Next()) {
		if (dynamic_cast<FigureComposite*>(SelectionSmartPointer->Current())) {
			i = 0;
			SmartPointer<Figure*>compositeIterator(static_cast<FigureComposite*>(SelectionSmartPointer->Current())->CreateIterator());
			while (!compositeIterator->IsDone()) {
				if (dynamic_cast<Relation*>(compositeIterator->Current()) || dynamic_cast<MemoLine*>(compositeIterator->Current())) {
					connect = false;
					SmartPointer<Figure*>bufferIterator(selection.CreateIterator());
					while (!bufferIterator->IsDone()) {
						if (dynamic_cast<FigureComposite*>(bufferIterator->Current())) {
							j = 0;
							while (j < selection.GetLength() && compositeIterator->Current()->GetEndPointFigure() != selection.GetAt(j)) {
								j++;
							}
							if (j < selection.GetLength()) {
								connect = true;
							}
						}
						bufferIterator->Next();
					}
					if (connect == true) {
						i++;
						compositeIterator->Next();
					}
					else {
						static_cast<FigureComposite*>(SelectionSmartPointer->Current())->Remove(i);
					}
				}
				else {
					i++;
					compositeIterator->Next();
				}
			}
		}
	}
}

CRect Selection::GetSelectionRect(Selection& selection) {
	Long i = 0;
	CRect rt = { 0, };

	//Selection배열에서 연결되지 않은 선들 제거하기 위해 선택범위 찾기
	SmartPointer<Figure*>CopyBufferSmartPointer(selection.CreateIterator());
	for (CopyBufferSmartPointer->First(); !CopyBufferSmartPointer->IsDone(); CopyBufferSmartPointer->Next()) {
		if (dynamic_cast<FigureComposite*>(CopyBufferSmartPointer->Current())) {
			if (i == 0 || CopyBufferSmartPointer->Current()->GetX() < rt.left) {//minimumX
				rt.left = CopyBufferSmartPointer->Current()->GetX();
			}
			if (i == 0 || CopyBufferSmartPointer->Current()->GetX()            //maximumX
				+ CopyBufferSmartPointer->Current()->GetWidth() > rt.right) {
				rt.right = CopyBufferSmartPointer->Current()->GetX() + CopyBufferSmartPointer->Current()->GetWidth();
			}
			if (i == 0 || CopyBufferSmartPointer->Current()->GetY() < rt.top) {   //minimumY
				rt.top = CopyBufferSmartPointer->Current()->GetY();
			}
			if (i == 0 || CopyBufferSmartPointer->Current()->GetY()            //maximumY
				+ CopyBufferSmartPointer->Current()->GetHeight() > rt.bottom) {
				rt.bottom = CopyBufferSmartPointer->Current()->GetY() + CopyBufferSmartPointer->Current()->GetHeight();
			}
			i++;
		}
	}

	return rt;
}