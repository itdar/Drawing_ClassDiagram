//KnockKnock.cpp

#include "KnockKnock.h"
#include "ClassDiagramForm.h"
#include "Diagram.h"
#include "Class.h"
#include "Selection.h"
#include "Attribute.h"
#include "Reception.h"
#include "Method.h"
#include "MemoBox.h"
#include "ClassName.h"
#include "TextEdit.h"

KnockKnock::KnockKnock() {
}

KnockKnock::KnockKnock(const KnockKnock& source) {
}

KnockKnock::~KnockKnock() {
}

void KnockKnock::Knocking(ClassDiagramForm *classDiagramForm) {
	int vertCurPos = classDiagramForm->GetScrollPos(SB_VERT);
	int horzCurPos = classDiagramForm->GetScrollPos(SB_HORZ);
	classDiagramForm->selection->DeleteAllItems();
	Long i = 0;
	while (i < classDiagramForm->diagram->GetLength()) {
		if (dynamic_cast<Class*>(classDiagramForm->diagram->GetAt(i))) { // 클래스이면
			Class* testClass = static_cast<Class*>(classDiagramForm->diagram->GetAt(i));
			classDiagramForm->selection->Add(testClass);
		
			Figure* figure = testClass->GetAt(0);
			if (figure->GetContent() != "") {
				classDiagramForm->textEdit = new TextEdit(classDiagramForm, figure);

				classDiagramForm->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					figure->GetX() + GabX,
					figure->GetY() + GabY+ MemoGab,
					figure->GetX() + figure->GetWidth() +CaretWidth,
					figure->GetY() + figure->GetHeight() - GabY), classDiagramForm, 10000, NULL);
				classDiagramForm->textEdit->OnKeyDown(VK_CONTROL, 0, 0);
				classDiagramForm->textEdit->OnClose();
			}
			if (testClass->GetAttributePosition() != -1) {
				figure = testClass->GetAt(testClass->GetAttributePosition());

				classDiagramForm->textEdit = new TextEdit(classDiagramForm, figure);
				classDiagramForm->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					figure->GetX() + GabX,
					figure->GetY() + GabY,
					figure->GetX() + figure->GetWidth() + CaretWidth - GabX,
					figure->GetY() + figure->GetHeight() - GabY), classDiagramForm, 10000, NULL);
				classDiagramForm->textEdit->OnKeyDown(VK_CONTROL, 0, 0);
				classDiagramForm->textEdit->OnClose();
			}
			if (testClass->GetMethodPosition() != -1) {
				figure = testClass->GetAt(testClass->GetMethodPosition());
				classDiagramForm->textEdit = new TextEdit(classDiagramForm, figure);
				classDiagramForm->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					figure->GetX() + GabX,
					figure->GetY() + GabY,
					figure->GetX() + figure->GetWidth() + CaretWidth - GabX,
					figure->GetY() + figure->GetHeight() - GabY), classDiagramForm, 10000, NULL);
				classDiagramForm->textEdit->OnKeyDown(VK_CONTROL, 0, 0);
				classDiagramForm->textEdit->OnClose();
			}
			if (testClass->GetReceptionPosition() != -1 ) {
				figure = testClass->GetAt(testClass->GetReceptionPosition());
				classDiagramForm->textEdit = new TextEdit(classDiagramForm, figure);
				classDiagramForm->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					figure->GetX() + GabX,
					figure->GetY() + GabY + MemoGab,
					figure->GetX() + figure->GetWidth() + CaretWidth - GabX,
					figure->GetY() + figure->GetHeight() - GabY), classDiagramForm, 10000, NULL);
				classDiagramForm->textEdit->OnKeyDown(VK_CONTROL, 0, 0);
				classDiagramForm->textEdit->OnClose();
			}
		}
		else if (dynamic_cast<MemoBox*>(classDiagramForm->diagram->GetAt(i))) {
			classDiagramForm->selection->Add(classDiagramForm->diagram->GetAt(i));
			classDiagramForm->textEdit = new TextEdit(classDiagramForm, classDiagramForm->diagram->GetAt(i));
			classDiagramForm->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
				classDiagramForm->diagram->GetAt(i)->GetX() + GabX,
				classDiagramForm->diagram->GetAt(i)->GetY() + GabY + MemoGab,
				classDiagramForm->diagram->GetAt(i)->GetX() + classDiagramForm->diagram->GetAt(i)->GetWidth() + CaretWidth - GabX,
				classDiagramForm->diagram->GetAt(i)->GetY() + classDiagramForm->diagram->GetAt(i)->GetHeight() - GabY), classDiagramForm, 10000, NULL);
			classDiagramForm->textEdit->OnKeyDown(VK_CONTROL, 0, 0);
			classDiagramForm->textEdit->OnClose();
		}
		classDiagramForm->selection->DeleteAllItems();
		i++;
	}
}