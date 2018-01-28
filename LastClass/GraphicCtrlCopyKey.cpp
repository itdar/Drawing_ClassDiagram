//GraphicCtrlCopyKey.cpp

#include "GraphicCtrlCopyKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "DrawingVisitor.h"
#include "SmartPointer.h"
#include "ArrayIterator.h"
#include "Line.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
#include "MemoBox.h"
#include "Template.h"
#include "Relation.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "Template.h"
#include "SmartPointer.h"
#include "MemoLine.h"
#include "Finder.h"

GraphicCtrlCopyKey::GraphicCtrlCopyKey() {
}

GraphicCtrlCopyKey::GraphicCtrlCopyKey(const GraphicCtrlCopyKey& source) {
}

GraphicCtrlCopyKey::~GraphicCtrlCopyKey() {
}

void GraphicCtrlCopyKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	if (classDiagramForm->copyBuffer != 0) {
		delete classDiagramForm->copyBuffer;
		classDiagramForm->copyBuffer = 0;
	}
	classDiagramForm->copyBuffer = classDiagramForm->selection->MakeSelectionBuffer(*classDiagramForm->selection);
	classDiagramForm->selection->DeleteOutSideRelation(*classDiagramForm->copyBuffer);
	CRect rect = classDiagramForm->selection->GetSelectionRect(*classDiagramForm->copyBuffer);
	Long isOne = 0;
	if (classDiagramForm->selection->GetLength() == 1) {
		isOne = 1;
	}
	Class* objectClass = 0;
	Class* objectClass2 = 0;
	Template* objectTemplate = 0;
	Template* objectTemplate2 = 0;
	CBitmap bitmap;
	CDC memDC;
	CBitmap *OldBitmap = 0;
	CFont *cFont = cdc->GetCurrentFont();
	memDC.CreateCompatibleDC(cdc);
	memDC.SelectObject(cFont);
	Long isLeft = 0;
	Long isRight = 0;
	Long gap = 0;
	SmartPointer<Figure*>smartPointer(classDiagramForm->selection->CreateIterator());
	for (smartPointer->First(); !smartPointer->IsDone(); smartPointer->Next()) {
		if (dynamic_cast<Class*>(smartPointer->Current())) {
			if (/*smartPointer->Current()->GetX() == rect.left&&*/smartPointer->Current()->GetY() == rect.top) {
				objectClass = static_cast<Class*>(smartPointer->Current());
				SmartPointer<Figure*>smartPointer_(objectClass->CreateIterator());
				for (smartPointer_->First(); !smartPointer_->IsDone(); smartPointer_->Next()) {
					if (dynamic_cast<Template*>(smartPointer_->Current())) {
						objectTemplate = static_cast<Template*>(smartPointer_->Current());
						gap = objectTemplate->GetY();
					}
				}
				if (objectTemplate != 0 && isOne == 0) {
					isLeft = 1;//왼쪽거에 템플릿있고 다중선택일때
				}
			}
			if (smartPointer->Current()->GetX() + smartPointer->Current()->GetWidth() == rect.right/*&&
																								   smartPointer->Current()->GetY() + smartPointer->Current()->GetHeight() == rect.bottom*/) {//오른쪽
				objectClass2 = static_cast<Class*>(smartPointer->Current());
				SmartPointer<Figure*>smartPointer2(objectClass2->CreateIterator());
				for (smartPointer2->First(); !smartPointer2->IsDone(); smartPointer2->Next()) {
					if (dynamic_cast<Template*>(smartPointer2->Current())) {
						objectTemplate2 = static_cast<Template*>(smartPointer2->Current());
					}
				}
				if (objectTemplate2 != 0 && isOne == 0) {
					isRight = 1;//오른쪽거에 템플릿있고 다중선택일때
				}
			}
		}
	}

	if (isOne == 1 && objectTemplate != 0) {//선택된게 하나고 템플릿이 있을때 //비트맵의 너비 길이 다 늘려줌//objectClass
		bitmap.CreateCompatibleBitmap(&memDC, rect.Width() + ((objectTemplate->GetX() + objectTemplate->GetWidth())
			- (objectClass->GetX() + objectClass->GetWidth())), rect.Height() + (objectClass->GetY() - objectTemplate->GetY()));
		OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
		memDC.FillSolidRect(CRect(0, 0, rect.right, rect.bottom), RGB(255, 255, 255));
	}
	else if (isLeft == 1 && isRight == 1) {//선택된게 여러개고 왼오다 템플릿이 있을때 //비트맵의 너비 길이 다 늘려줌
		bitmap.CreateCompatibleBitmap(&memDC, rect.Width() + ((objectTemplate2->GetX() + objectTemplate2->GetWidth())
			- (objectClass2->GetX() + objectClass2->GetWidth())), rect.Height() + (objectClass->GetY() - objectTemplate->GetY()));
		OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
		memDC.FillSolidRect(CRect(0, 0, rect.right + ((objectTemplate2->GetX() + objectTemplate2->GetWidth())
			- (objectClass2->GetX() + objectClass2->GetWidth())), rect.bottom + (objectClass->GetY() - objectTemplate->GetY())), RGB(255, 255, 255));
	}
	else if (isLeft == 1) {//왼쪽 선택된것에 템플릿이 있을 때 //비트맵의 길이만 늘려줌//objectClass
		bitmap.CreateCompatibleBitmap(&memDC, rect.Width(), rect.Height() + (objectClass->GetY() - objectTemplate->GetY()));
		OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
		memDC.FillSolidRect(CRect(0, 0, rect.right, rect.bottom + (objectClass->GetY() - objectTemplate->GetY())), RGB(255, 255, 255));
	}
	else if (isRight == 1) {//오른쪽 선택된 것에 템플릿이 있을 때 //비트맵의 너비만 늘려줌//objectClass2
		bitmap.CreateCompatibleBitmap(&memDC, rect.Width() + ((objectTemplate2->GetX() + objectTemplate2->GetWidth())
			- (objectClass2->GetX() + objectClass2->GetWidth())), rect.Height());
		OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
		memDC.FillSolidRect(CRect(0, 0, rect.right + ((objectTemplate2->GetX() + objectTemplate2->GetWidth())
			- (objectClass2->GetX() + objectClass2->GetWidth())), rect.bottom), RGB(255, 255, 255));
	}
	else {//선택된 게 하나이고 펨플릿이 없거나 선택된 게 여러개가 맨왼뽁이나 오른쪽에 템플릿 없을때 //비트맵 늘려주지X//objectClassX
		bitmap.CreateCompatibleBitmap(&memDC, rect.Width(), rect.Height());
		OldBitmap = (CBitmap*)memDC.SelectObject(&bitmap);
		memDC.FillSolidRect(CRect(0, 0, rect.right, rect.bottom), RGB(255, 255, 255));
	}
	MovingVisitor movingVisitor;

	if (objectTemplate != 0 && (isLeft == 1 || isOne == 1)) {
		classDiagramForm->selection->Accept(classDiagramForm->diagram, movingVisitor, -rect.left, -rect.top + (rect.top - gap));
	}
	else {
		classDiagramForm->selection->Accept(classDiagramForm->diagram, movingVisitor, -rect.left, -rect.top);
	}
	DrawingVisitor drawingVisitor(classDiagramForm->zoomRate);
	for (smartPointer->First(); !smartPointer->IsDone(); smartPointer->Next()) {
		if (dynamic_cast<Class*>(smartPointer->Current())) {
			static_cast<Class*>(smartPointer->Current())->Accept(drawingVisitor, &memDC);
		}
		if (dynamic_cast<MemoBox*>(smartPointer->Current())) { // if문 안에 Class로 되어있어서 바꿈 // 맞는지?
			static_cast<MemoBox*>(smartPointer->Current())->Accept(drawingVisitor, &memDC);
		}
	}
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, bitmap.GetSafeHandle());
	CloseClipboard();
	memDC.SelectObject(cFont);
	memDC.SelectObject(OldBitmap);
	bitmap.DeleteObject();
	cFont->DeleteObject();
	memDC.DeleteDC();
	if (objectTemplate != 0 && (isLeft == 1 || isOne == 1)) {
		classDiagramForm->selection->Accept(classDiagramForm->diagram, movingVisitor, +rect.left, +rect.top - (rect.top - gap));
	}
	else {
		classDiagramForm->selection->Accept(classDiagramForm->diagram, movingVisitor, rect.left, rect.top);
	}
}



void GraphicCtrlCopyKey::KeyPress(TextEdit *textEdit) {

}