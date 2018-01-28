//MouseButton.cpp

#include "MouseLButton.h"
#include "MouseLButtonAction.h"
#include "DrawingClass.h"
#include "DefaultState.h"
#include "ClassDiagramForm.h"
#include "DrawingClass.h"
#include "DrawingMemoBox.h"
#include "DrawingGeneralization.h" 
#include "DrawingAggregation.h"
#include "DrawingAggregations.h"
#include "LastClass.h"
#include "DrawingAssociation.h"
#include "DrawingComposition.h"
#include "DrawingCompositions.h"
#include "DrawingDependency.h"
#include "DrawingDirectedAssociation.h"
#include "DrawingMemoLine.h"
#include "DrawingRealization.h"
#include "SelectionState.h"
#include "MultipleSelectionState.h"
MouseLButton::MouseLButton() {
	this->state = DefaultState::Instance();
	this->buttonState = 0;
}
void MouseLButton::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	int hPos = classDiagramForm->GetScrollPos(SB_HORZ);
	int vPos = classDiagramForm->GetScrollPos(SB_VERT);
	Long transFormStartX = startX - hPos;
	Long transFormStartY = startY - vPos;
	this->state->MouseLButtonUp(this, classDiagramForm, diagram, selection, transFormStartX, transFormStartY, currentX, currentY);
}
void MouseLButton::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	LastClass* lastclass = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	int hPos = lastclass->classDiagramForm->GetScrollPos(SB_HORZ);
	int vPos = lastclass->classDiagramForm->GetScrollPos(SB_VERT);
	Long transFormStartX = startX - hPos;
	Long transFormStartY = startY - vPos;
	this->state->MouseLButtonDown(this, diagram, selection, transFormStartX, transFormStartY, currentX, currentY);
}
void MouseLButton::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	int hPos = classDiagramForm->GetScrollPos(SB_HORZ);
	int vPos = classDiagramForm->GetScrollPos(SB_VERT);
	Long transFormStartX = startX - hPos;
	Long transFormStartY = startY - vPos;
	this->state->MouseLButtonDrag(this, classDiagramForm, diagram, selection, transFormStartX, transFormStartY, currentX, currentY, pDC);
}
void MouseLButton::ChangeState(UINT nChar) {
	this->buttonState = nChar;
}

void MouseLButton::ChangeDrawingClassState() {
	this->state = DrawingClass::Instance();
}

void MouseLButton::ChangeDrawingMemoBoxState() {
	this->state = DrawingMemoBox::Instance();
}

void MouseLButton::ChangeDrawingAggregationState() {
	this->state = DrawingAggregation::Instance();
}
void MouseLButton::ChangeDrawingAggregationsState() {
	this->state = DrawingAggregations::Instance();
}
void MouseLButton::ChangeDrawingAssociationState() {
	this->state = DrawingAssociation::Instance();
}
void MouseLButton::ChangeDrawingCompositionState() {
	this->state = DrawingComposition::Instance();
}
void MouseLButton::ChangeDrawingCompositionsState() {
	this->state = DrawingCompositions::Instance();
}
void MouseLButton::ChangeDrawingDependencyState() {
	this->state = DrawingDependency::Instance();
}
void MouseLButton::ChangeDrawingDirectedAssociationState() {
	this->state = DrawingDirectedAssociation::Instance();
}
void MouseLButton::ChangeDrawingGeneralizationState() {
	this->state = DrawingGeneralization::Instance();
}
void MouseLButton::ChangeDrawingMemoLineState() {
	this->state = DrawingMemoLine::Instance();
}
void MouseLButton::ChangeDrawingRealizationState() {
	this->state = DrawingRealization::Instance();
}
void MouseLButton::ChangeMultipleState() {
	this->state = MultipleSelectionState::Instance();
}

void MouseLButton::ChangeSelectionState() {
	this->state = SelectionState::Instance();
}


void MouseLButton::ChangeDefault() {
	this->buttonState = 0;
	this->state = DefaultState::Instance();
}
void MouseLButton::ChangeState(MouseLButtonAction *mouseLButtonAction,UINT nChar) {
	this->state = mouseLButtonAction;
	this->buttonState = nChar;
}