
#include "Diagram.h"
#include "Class.h"
#include "DrawingClass.h"
#include "DefaultState.h"
#include "Selection.h"
#include "Finder.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "LastClass.h"
#include "StatusBar.h"

DrawingClass* DrawingClass::instance = 0;

MouseLButtonAction* DrawingClass::Instance() {
	if (instance == 0) {
		instance = new DrawingClass;
	}
	return instance;
}
void DrawingClass::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {

	classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
	classDiagramForm->historyGraphic->redoGraphicArray->Clear();
	classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

	CRect rect = diagram->GetCorrectRect(startX, startY, currentX, currentY);

	if (rect.Width() < 120 * classDiagramForm->zoomRate / 100) {
		rect.right = rect.left + 120 * classDiagramForm->zoomRate / 100;
	}
	if (rect.Height() < 150 * classDiagramForm->zoomRate / 100) {
		rect.bottom = rect.top + 150 * classDiagramForm->zoomRate / 100;
	}
		Long index = diagram->AddClass(rect.left, rect.top, rect.Width(), rect.Height());
		Class *object = static_cast<Class*>(diagram->GetAt(index));
		object->Initialize();
	

	classDiagramForm->lastClass->statusBar->DestroyStatus();
	classDiagramForm->lastClass->statusBar->MakeStatusBar(classDiagramForm->lastClass, classDiagramForm->lastClass->GetSafeHwnd(), 0, 0, 5);

	this->ChangeDefault(mouseLButton);
}

void DrawingClass::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){
	selection->DeleteAllItems();
	
}

void DrawingClass::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	pDC->Rectangle(startX, startY, currentX, currentY);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}