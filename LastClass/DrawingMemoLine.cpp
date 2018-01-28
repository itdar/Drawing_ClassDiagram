#include "DrawingMemoLine.h"
#include "DefaultState.h"
#include "Figure.h"
#include "Selection.h"
#include "Class.h"
#include "Finder.h"
#include "MemoLine.h"
#include "Diagram.h"
#include "MemoBox.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"

DrawingMemoLine* DrawingMemoLine::instance = 0;

MouseLButtonAction* DrawingMemoLine::Instance() {
	if (instance == 0) {
		instance = new DrawingMemoLine;
	}
	return instance;
}

void DrawingMemoLine::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long index;
	Figure *figure = 0;

	classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
	classDiagramForm->historyGraphic->redoGraphicArray->Clear();
	classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

	if (selection->GetLength() == 1 && dynamic_cast<FigureComposite*>(selection->GetAt(0))) {

		selection->SelectByPoint(diagram, currentX, currentY);
		if (selection->GetLength() == 2 && selection->GetAt(0) != selection->GetAt(1) && (dynamic_cast<MemoBox*>(selection->GetAt(0)) || dynamic_cast<MemoBox*>(selection->GetAt(1)))) {

			CPoint lineStart(startX, startY);
			CPoint lineEnd(currentX, currentY);

			CRect rect(selection->GetAt(0)->GetX(), selection->GetAt(0)->GetY(),
				selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth(),
				selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight());

			Finder finder;
			CPoint cross1 = finder.GetCrossPoint(lineStart, lineEnd, rect);

			rect.left = selection->GetAt(1)->GetX();
			rect.top = selection->GetAt(1)->GetY();
			rect.right = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
			rect.bottom = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
			CPoint cross2 = finder.GetCrossPoint(lineStart, lineEnd, rect);

			MemoLine object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
			index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
			figure = static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);
			figure->SetEndPointFigure(selection->GetAt(1));
		}
	}

	selection->DeleteAllItems();
	this->ChangeDefault(mouseLButton);
}

void DrawingMemoLine::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
}

void DrawingMemoLine::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	if (startX == currentX&&startY == currentY) {
		selection->DeleteAllItems();
		selection->SelectByPoint(diagram, currentX, currentY);
	}

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	pDC->MoveTo(startX, startY);
	pDC->LineTo(currentX, currentY);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();

}