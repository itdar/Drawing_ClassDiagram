//Caret.cpp

#include "Caret.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "ClassDiagramForm.h"

Caret::Caret() {
	characterIndex = 0;
	rowIndex = 0;
	currentCaretX = 0;
	currentCaretY = 0;
}

Caret::Caret(const Caret& source) {
	characterIndex = source.characterIndex;
	rowIndex = source.rowIndex;
	currentCaretX = source.currentCaretX;
	currentCaretY = source.currentCaretY;
}

Caret::~Caret() {
}

void Caret::MoveToIndex(TextEdit *textEdit, CDC *pDC) {
	Long pointX = 0;													 //가로
	Long pointY = this->rowIndex * textEdit->GetRowHeight();         //세로
	CString str;
	Long column = 0;
	Long tabWidth = 0;
	Long i = 0;

	pointX += textEdit->text->GetAt((this->rowIndex))->GetRowWidth(pDC, this->characterIndex);

	textEdit->CreateSolidCaret(CaretWidth, textEdit->GetRowHeight());
	if (textEdit->GetFlagBuffer() == 1) {
		textEdit->CreateSolidCaret(-pDC->GetTextExtent(textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex - 1)->MakeCString()).cx, textEdit->GetRowHeight());
	}
	if (textEdit->GetFlagInsert() == 1 && this->characterIndex < textEdit->text->GetAt(this->rowIndex)->GetLength()) {
		textEdit->CreateSolidCaret(pDC->GetTextExtent(textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex)->MakeCString()).cx, textEdit->GetRowHeight());
	}
	this->currentCaretX = pointX;
	this->currentCaretY = pointY;
	textEdit->SetCaretPos(CPoint(pointX, pointY));
	textEdit->ShowCaret();
}

void Caret::MoveToPoint(TextEdit *textEdit, CDC *pDC, CPoint point) {
	Long x = point.x;
	Long y = point.y;
	CString str;
	this->characterIndex = 0;
	this->rowIndex = 0;

	Long height = 0;
	while (y > 0 && height <= y && this->rowIndex < textEdit->text->GetLength()) {
		height += textEdit->GetRowHeight();
		this->rowIndex++;
	}
	if (y > 0 && textEdit->text->GetLength() > 0) {
		this->rowIndex--;
	}
	Long width = 0;
	while (this->characterIndex < textEdit->text->GetAt(this->rowIndex)->GetLength() && x > 0 && width <= x) {
		str = textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex)->MakeCString();
		width += pDC->GetTextExtent(str).cx;
		this->characterIndex++; // -1 안하면 다음꺼
	}
	if (this->characterIndex > 0) {
		str = textEdit->text->GetAt(this->rowIndex)->GetAt(this->characterIndex - 1)->MakeCString();
		Long textWidth = pDC->GetTextExtent(str).cx;
		if (x > 0 && x < width - textWidth / 2) {
			this->characterIndex--;
		}
	}
}

void Caret::MoveForwardRowIndex(Long index) {
	this->rowIndex += index;
}
void Caret::MoveBackwardRowIndex(Long index) {
	this->rowIndex -= index;
}
void Caret::MoveForwardCharacterIndex(Long index) {
	this->characterIndex += index;
}
void Caret::MoveBackwardCharacterIndex(Long index) {
	this->characterIndex -= index;
}
void Caret::SetCharacterIndex(Long index) {
	this->characterIndex = index;
}
void Caret::SetRowIndex(Long index) {
	this->rowIndex = index;
}

Caret& Caret::operator = (const Caret& source) {
	this->characterIndex = source.characterIndex;
	this->rowIndex = source.rowIndex;
	this->currentCaretX = source.currentCaretX;
	this->currentCaretY = source.currentCaretY;

	return *this;
}