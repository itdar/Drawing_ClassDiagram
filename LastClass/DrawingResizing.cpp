#include "DrawingResizing.h"
#include "FigureComposite.h"
#include "Selection.h"
#include "Finder.h"
#include "Class.h"
#include "Template.h"
#include "SelectionState.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Diagram.h"
#include "PreciseMoving.h"

DrawingResizing* DrawingResizing::instance = 0;

MouseLButtonAction* DrawingResizing::Instance() {
	if (instance == 0) {
		instance = new DrawingResizing;
	}
	return instance;
}
void DrawingResizing::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	FigureComposite *object = static_cast<FigureComposite*>(selection->GetAt(0));

	bool ret = false;
	Long x = object->GetX();
	Long y = object->GetY();
	Long width = object->GetWidth();
	Long height = object->GetHeight();
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	Long i = 0;
	Finder finder;
	Long length = 0;
	Long k = 0;
	//bool overlapCheck;
	CRect objectRect(object->GetX(), object->GetY(), object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());

	classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
	classDiagramForm->historyGraphic->redoGraphicArray->Clear();
	classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

	CRect rect = diagram->GetCorrectRect(startX, startY, currentX, currentY);

	if (dynamic_cast<Class*>(object) && static_cast<Class*>(object)->GetTempletePosition() != -1) {
		Class *selectedClass = static_cast<Class*>(object);
			Template *templete = static_cast<Template*>(selectedClass->GetAt(selectedClass->GetTempletePosition()));
	 // 좌상단
			CRect rect(selectedClass->GetX() - 3, templete->GetY() - 3, selectedClass->GetX() + 6, templete->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.left += distanceX;
				objectRect.top += distanceY;
				selectedClass->ModifyComponetsToLeftDirection(diagram, distanceX);
				selectedClass->ModifyComponetsToUpDirection(diagram, distanceY);
			}
		if (ret == false) { // 우상단
			CRect rect(templete->GetX() + templete->GetWidth() - 6, templete->GetY() - 3,
				templete->GetX() + templete->GetWidth() + 3, templete->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.top += distanceY;
				objectRect.right += distanceX;
				selectedClass->ModifyComponetsToRightDirection(diagram, distanceX);
				selectedClass->ModifyComponetsToUpDirection(diagram, distanceY);
				
			}
		}
		if (ret == false) { // 좌하단
			CRect rect(selectedClass->GetX() - 3, selectedClass->GetY() + selectedClass->GetHeight() - 6,
				selectedClass->GetX() + 6, selectedClass->GetY() + selectedClass->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.left += distanceX;
				objectRect.bottom += distanceY;
				selectedClass->ModifyComponetsToLeftDirection(diagram, distanceX);
				selectedClass->ModifyComponetsToDownDirection(diagram, distanceY);
			
			}
		}
		if (ret == false) { // 우하단//
			CRect rect(templete->GetX() + templete->GetWidth() - 6, selectedClass->GetY() + selectedClass->GetHeight() - 6,
				templete->GetX() + templete->GetWidth() + 3, selectedClass->GetY() + selectedClass->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.right += distanceX;
				objectRect.bottom += distanceY;
				selectedClass->ModifyComponetsToRightDirection(diagram, distanceX);
				selectedClass->ModifyComponetsToDownDirection(diagram, distanceY);
			
			}
		}
		if (ret == false) { // 상중단//
			CRect rect(selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 - 4, templete->GetY() - 3,
				selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 + 5, templete->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.top += distanceY;
				selectedClass->ModifyComponetsToUpDirection(diagram, distanceY);
			}
		}

		if (ret == false) { // 하중단//
			CRect rect(selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 - 4, selectedClass->GetY() + selectedClass->GetHeight() - 6,
				selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 + 5, selectedClass->GetY() + selectedClass->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.bottom += distanceY;
				selectedClass->ModifyComponetsToDownDirection(diagram, distanceY);
			}
		}

		if (ret == false) { // 좌중단//
			CRect rect(selectedClass->GetX() - 3, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 - 4,
				selectedClass->GetX() + 5, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.left += distanceX;
				selectedClass->ModifyComponetsToLeftDirection(diagram, distanceX);
			}
		}

		if (ret == false) { // 우중단//
			CRect rect(templete->GetX() + templete->GetWidth() - 6, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 - 4,
				templete->GetX() + templete->GetWidth() + 3, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.right += distanceX;
				selectedClass->ModifyComponetsToRightDirection(diagram, distanceX);
			}
		}
	}

	else {
		if (ret == false) { // 좌상단
			CRect rect(object->GetX() - 3, object->GetY() - 3, object->GetX() + 6, object->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.left += distanceX;
				objectRect.top += distanceY;
				object->ModifyComponetsToLeftDirection(diagram, distanceX);
				object->ModifyComponetsToUpDirection(diagram, distanceY);
				
			}
		}
		if (ret == false) { // 우상단
			CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() - 3, object->GetX() + object->GetWidth() + 3, object->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.top += distanceY;
				objectRect.right += distanceX;
				object->ModifyComponetsToRightDirection(diagram, distanceX);
				object->ModifyComponetsToUpDirection(diagram, distanceY);
				
			}
		}
		if (ret == false) { // 좌하단
			CRect rect(object->GetX() - 3, object->GetY() + object->GetHeight() - 6, object->GetX() + 6, object->GetY() + object->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.left += distanceX;
				objectRect.bottom += distanceY;
				object->ModifyComponetsToLeftDirection(diagram, distanceX);
				object->ModifyComponetsToDownDirection(diagram, distanceY);
				
			}
		}
		if (ret == false) { // 우하단
			CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() + object->GetHeight() - 6,
				object->GetX() + object->GetWidth() + 3, object->GetY() + object->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.right += distanceX;
				objectRect.bottom += distanceY;
				object->ModifyComponetsToRightDirection(diagram, distanceX);
				object->ModifyComponetsToDownDirection(diagram, distanceY);
				
			}
		}

		if (ret == false) { // 상중단
			CRect rect(object->GetX() + object->GetWidth() / 2 - 4, object->GetY() - 3, object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.top += distanceY;
				object->ModifyComponetsToUpDirection(diagram, distanceY);
				
			}
		}

		if (ret == false) { // 하중단
			CRect rect(object->GetX() + object->GetWidth() / 2 - 4, object->GetY() + object->GetHeight() - 6,
				object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + object->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.bottom += distanceY;
				object->ModifyComponetsToDownDirection(diagram, distanceY);
			}
		}
		if (ret == false) { // 좌중단
			CRect rect(object->GetX() - 3, object->GetY() + object->GetHeight() / 2 - 4, object->GetX() + 6, object->GetY() + object->GetHeight() / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.left += distanceX;
				object->ModifyComponetsToLeftDirection(diagram, distanceX);
				
			}
		}
		if (ret == false) { // 우중단
			CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() + object->GetHeight() / 2 - 4,
				object->GetX() + object->GetWidth() + 3, object->GetY() + object->GetHeight() / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				objectRect.right += distanceX;
				object->ModifyComponetsToRightDirection(diagram, distanceX);
			}
		}
	}
	this->ChangeState(mouseLButton, SelectionState::Instance());
}

void DrawingResizing::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

}
void DrawingResizing::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {

	FigureComposite *object = static_cast<FigureComposite*>(selection->GetAt(0));
	CRect rect;
	Finder finder;
	bool ret = false;

	PreciseMoving temp;
	temp.ConvertPoint(&currentX, &currentY);

	if (dynamic_cast<Class*>(object) && static_cast<Class*>(object)->GetTempletePosition() != -1) {
		Class *selectedClass = static_cast<Class*>(object);
		Template *templete = static_cast<Template*>(selectedClass->GetAt(selectedClass->GetTempletePosition()));
		if (ret == false) { // 좌상단
			CRect rect(selectedClass->GetX() - 3, templete->GetY() - 3, selectedClass->GetX() + 6, templete->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX() + (currentX - startX), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY() + (currentY - startY));
			}
		}
		if (ret == false) { // 우상단
			CRect rect(templete->GetX() + templete->GetWidth() - 6, templete->GetY() - 3,
				templete->GetX() + templete->GetWidth() + 3, templete->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + (currentY - startY));
			}
		}
		if (ret == false) { // 좌하단
			CRect rect(selectedClass->GetX() - 3, selectedClass->GetY() + selectedClass->GetHeight() - 6,
				selectedClass->GetX() + 6, selectedClass->GetY() + selectedClass->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX() + (currentX - startX), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY());
			}
		}
		if (ret == false) { // 우하단
			CRect rect(templete->GetX() + templete->GetWidth() - 6, selectedClass->GetY() + selectedClass->GetHeight() - 6,
				templete->GetX() + templete->GetWidth() + 3, selectedClass->GetY() + selectedClass->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX(), object->GetY());
			}
		}
		if (ret == false) { // 상중단
			CRect rect(selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 - 4, templete->GetY() - 3,
				selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 + 5, templete->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + (currentY - startY));
			}
		}
		if (ret == false) { // 하중단
			CRect rect(selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 - 4, selectedClass->GetY() + selectedClass->GetHeight() - 6,
				selectedClass->GetX() + (templete->GetX() + templete->GetWidth() - selectedClass->GetX()) / 2 + 5, selectedClass->GetY() + selectedClass->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX(), object->GetY());
			}
		}
		if (ret == false) { // 좌중단
			CRect rect(selectedClass->GetX() - 3, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 - 4,
				selectedClass->GetX() + 5, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX() + (currentX - startX), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY());
			}
		}
		if (ret == false) { // 우중단
			CRect rect(templete->GetX() + templete->GetWidth() - 6, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 - 4,
				templete->GetX() + templete->GetWidth() + 3, templete->GetY() + (selectedClass->GetY() + selectedClass->GetHeight() - templete->GetY()) / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY());
			}
		}
	}
	else {
		if (ret == false) { // 좌상단
			CRect rect(object->GetX() - 3, object->GetY() - 3, object->GetX() + 6, object->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX() + (currentX - startX), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY() + (currentY - startY));
			}
		}
		if (ret == false) { // 우상단
			CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() - 3, object->GetX() + object->GetWidth() + 3, object->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + (currentY - startY));
			}
		}
		if (ret == false) { // 좌하단
			CRect rect(object->GetX() - 3, object->GetY() + object->GetHeight() - 6, object->GetX() + 6, object->GetY() + object->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX() + (currentX - startX), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY());
			}
		}
		if (ret == false) { // 우하단
			CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() + object->GetHeight() - 6,
				object->GetX() + object->GetWidth() + 3, object->GetY() + object->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX(), object->GetY());
			}
		}
		if (ret == false) { // 상중단
			CRect rect(object->GetX() + object->GetWidth() / 2 - 4, object->GetY() - 3, object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + 6);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + (currentY - startY));
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + (currentY - startY));
			}
		}
		if (ret == false) { // 하중단
			CRect rect(object->GetX() + object->GetWidth() / 2 - 4, object->GetY() + object->GetHeight() - 6,
				object->GetX() + object->GetWidth() / 2 + 5, object->GetY() + object->GetHeight() + 3);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight() + (currentY - startY));
				pDC->LineTo(object->GetX(), object->GetY());
			}
		}
		if (ret == false) { // 좌중단
			CRect rect(object->GetX() - 3, object->GetY() + object->GetHeight() / 2 - 4, object->GetX() + 6, object->GetY() + object->GetHeight() / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX() + (currentX - startX), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX() + (currentX - startX), object->GetY());
			}
		}
		if (ret == false) { // 우중단
			CRect rect(object->GetX() + object->GetWidth() - 6, object->GetY() + object->GetHeight() / 2 - 4,
				object->GetX() + object->GetWidth() + 3, object->GetY() + object->GetHeight() / 2 + 5);
			ret = finder.FindRectangleByPoint(rect, startX, startY);
			if (ret == true) {
				pDC->MoveTo(object->GetX(), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY());
				pDC->LineTo(object->GetX() + object->GetWidth() + (currentX - startX), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY() + object->GetHeight());
				pDC->LineTo(object->GetX(), object->GetY());
			}
		}
	}
}
