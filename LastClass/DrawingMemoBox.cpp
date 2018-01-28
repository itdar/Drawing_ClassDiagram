
#include "Diagram.h"
#include "Class.h"
#include "DrawingMemoBox.h"
#include "Figure.h"
#include "DefaultState.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Selection.h"
#include "LastClass.h"
#include "StatusBar.h"

DrawingMemoBox* DrawingMemoBox::instance = 0;

MouseLButtonAction* DrawingMemoBox::Instance() {
	if (instance == 0) {
		instance = new DrawingMemoBox;
	}
	return instance;
}
void DrawingMemoBox::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long index;

	classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
	classDiagramForm->historyGraphic->redoGraphicArray->Clear();
	classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

	CRect rect = diagram->GetCorrectRect(startX, startY, currentX, currentY);

	if (rect.Width() < 120 * classDiagramForm->zoomRate / 100) {
		rect.right = rect.left + 120 * classDiagramForm->zoomRate / 100;
	}
	if (rect.Height() < 80 * classDiagramForm->zoomRate / 100) {
		rect.bottom = rect.top + 80* classDiagramForm->zoomRate / 100;
	}

	index = diagram->AddMemoBox(rect.left, rect.top, rect.Width(), rect.Height());
	

	classDiagramForm->lastClass->statusBar->DestroyStatus();
	classDiagramForm->lastClass->statusBar->MakeStatusBar(classDiagramForm->lastClass, classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);

	this->ChangeDefault(mouseLButton);
}
void DrawingMemoBox::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	selection->DeleteAllItems();
}
void DrawingMemoBox::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	pDC->Rectangle(startX, startY, currentX, currentY);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}