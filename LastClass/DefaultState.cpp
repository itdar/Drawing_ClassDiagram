//DefaultState.cpp

#include "ClassDiagramForm.h"
#include "Diagram.h"
#include "Class.h"
#include "DefaultState.h"
#include "Finder.h"
#include "Selection.h"
#include "SelectionState.h"
#include "DrawingClass.h"
#include "DrawingMemoBox.h"
#include "DrawingGeneralization.h" 
#include "DrawingAggregation.h"
#include "DrawingAggregations.h"
#include "DrawingAssociation.h"
#include "DrawingComposition.h"
#include "DrawingCompositions.h"
#include "DrawingDependency.h"
#include "DrawingDirectedAssociation.h"
#include "DrawingMemoLine.h"
#include "DrawingRealization.h"
#include "MultipleSelectionState.h"
#include "DrawingRelationPoint.h"
#include "MovingRelation.h"
#include "MovingObject.h"
DefaultState* DefaultState::instance = 0;

MouseLButtonAction* DefaultState::Instance() {
	if (instance == 0) {
		instance = new DefaultState;
	}
	return instance;
}
void DefaultState::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

	Finder finder;
	CRect area = diagram->GetCorrectRect(startX, startY, currentX, currentY);
	selection->DeleteAllItems();
	if (startX != 0||startY!=0 ) {
		selection->SelectByArea(diagram, area);
	}
	Long i;
	if (selection->GetLength() == 1) {
		this->ChangeState(mouseLButton, SelectionState::Instance());
		i = 0;
		while (i < classDiagramForm->diagram->GetLength()) {
			FigureComposite *tempFigureComposite = static_cast<FigureComposite*>(classDiagramForm->diagram->GetAt(i));
			if (static_cast<FigureComposite*>(selection->GetAt(0)) == tempFigureComposite) {
				
			}
			i++;
		}
	}
	if (selection->GetLength() > 1) {
		this->ChangeState(mouseLButton, MultipleSelectionState::Instance());
	}

}
void DefaultState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	UINT object = mouseLButton->GetButtonState();
	if (object == 49) {
		this->ChangeState(mouseLButton, DrawingClass::Instance(), 49);
	}
	if (object == 81) {
		this->ChangeState(mouseLButton, DrawingMemoBox::Instance(), 81);
	}
	if (object == 50) {
		this->ChangeState(mouseLButton, DrawingGeneralization::Instance(), 50);
	}
	if (object == 55) {
		this->ChangeState(mouseLButton, DrawingAggregation::Instance(), 55);
	}
	if (object == 56) {
		this->ChangeState(mouseLButton, DrawingAggregations::Instance(), 56);
	}
	if (object == 53) {
		this->ChangeState(mouseLButton, DrawingAssociation::Instance(), 53);
	}
	if (object == 57) {
		this->ChangeState(mouseLButton, DrawingComposition::Instance(), 57);
	}
	if (object == 48) {
		this->ChangeState(mouseLButton, DrawingCompositions::Instance(), 48);
	}
	if (object == 52) {
		this->ChangeState(mouseLButton, DrawingDependency::Instance(), 52);
	}
	if (object == 54) {
		this->ChangeState(mouseLButton, DrawingDirectedAssociation::Instance(), 54);
	}
	if (object == 87) {
		this->ChangeState(mouseLButton, DrawingMemoLine::Instance(), 87);
	}
	if (object == 51) {
		this->ChangeState(mouseLButton, DrawingRealization::Instance(), 51);
	}
	if (object == 0) {

		Long index = selection->SelectByPoint(startX, startY);
		//if (index != -1 && selection->GetLength() > 1) { // 기호가 여러개 선택되어있을때, 어느 선택박스가 잡히면 // 지워야할듯
		//	this->ChangeState(mouseLButton, MultipleSelectionState::Instance());
		//}

		//else { // 선택박스가 안잡혔거나 // 아니면 기호 한개나, 한개도 선택이 안되어있을 때 // 위에 지우고 아래만 남김
		if (index == -1 && selection->GetLength() == 0) {
			selection->DeleteAllItems();
			selection->SelectByPoint(diagram, startX, startY);
			if (selection->GetLength() == 1) {
				this->ChangeState(mouseLButton, SelectionState::Instance());
			}
		}
	}
}

void DefaultState::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection,Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);

	pDC->MoveTo(startX, startY);
	pDC->LineTo(currentX, startY);
	pDC->LineTo(currentX, currentY);
	pDC->LineTo(startX, currentY);
	pDC->LineTo(startX, startY);

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}