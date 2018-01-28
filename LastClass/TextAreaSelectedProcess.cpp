//TextAreaSelectedProcess.cpp

#include "TextAreaSelectedProcess.h"
#include "TextEdit.h"
#include "Caret.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "Figure.h"

TextAreaSelectedProcess::TextAreaSelectedProcess() {
}

TextAreaSelectedProcess::TextAreaSelectedProcess(const TextAreaSelectedProcess& source) {
}

TextAreaSelectedProcess::~TextAreaSelectedProcess() {
}

void TextAreaSelectedProcess::GetRange(TextEdit* textEdit) {
	if (textEdit->selectedY == textEdit->caret->GetRowIndex()) {            // 한줄에서 끝나는거면
		if (textEdit->selectedX < textEdit->caret->GetCharacterIndex()) {
			this->startCharacterIndex = textEdit->selectedX;
			this->startRowIndex = textEdit->selectedY;
			this->endCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->endRowIndex = textEdit->caret->GetRowIndex();
		}
		else {
			this->startCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->startRowIndex = textEdit->caret->GetRowIndex();
			this->endCharacterIndex = textEdit->selectedX;
			this->endRowIndex = textEdit->selectedY;
		}
	}
	else {                                                      // 여러줄 선택이면
		if (textEdit->selectedY < textEdit->caret->GetRowIndex()) {
			this->startCharacterIndex = textEdit->selectedX;
			this->startRowIndex = textEdit->selectedY;
			this->endCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->endRowIndex = textEdit->caret->GetRowIndex();
		}
		else {
			this->startCharacterIndex = textEdit->caret->GetCharacterIndex();
			this->startRowIndex = textEdit->caret->GetRowIndex();
			this->endCharacterIndex = textEdit->selectedX;
			this->endRowIndex = textEdit->selectedY;
		}
	}
}

void TextAreaSelectedProcess::SingleLineSelected(TextEdit *textEdit, CDC *pDC, CString *cstr, RECT *rt) {
	Long i = startCharacterIndex;

	while (i < endCharacterIndex) { // 첫줄
		*cstr += textEdit->text->GetAt(startRowIndex)->GetAt(i)->MakeCString();
		i++;
	}
	Long width = textEdit->text->GetAt(this->startRowIndex)->GetRowWidth(pDC, this->endCharacterIndex, this->startCharacterIndex);
	Long x = textEdit->text->GetAt(this->startRowIndex)->GetRowWidth(pDC, this->startCharacterIndex);

	*rt = { x, startRowIndex * textEdit->rowHeight, x + width, startRowIndex * textEdit->rowHeight + textEdit->rowHeight };
}   //메모리버퍼 사용안할때 사용할 rt

void TextAreaSelectedProcess::FirstMultiLineSelected(TextEdit *textEdit, CDC *pDC, CString *cstr, RECT *rt) {
	Long i = startCharacterIndex;

	while (i < textEdit->text->GetAt(this->startRowIndex)->GetLength()) { // 첫줄
		*cstr += textEdit->text->GetAt(this->startRowIndex)->GetAt(i)->MakeCString();
		i++;
	}
	*cstr += "\r\n";
	Long width = textEdit->text->GetAt(this->startRowIndex)->GetRowWidth(pDC,
		textEdit->text->GetAt(this->startRowIndex)->GetLength(), this->startCharacterIndex);
	Long x = textEdit->text->GetAt(this->startRowIndex)->GetRowWidth(pDC, this->startCharacterIndex);

	*rt = { x, this->startRowIndex * textEdit->rowHeight, x + width, this->startRowIndex * textEdit->rowHeight + textEdit->rowHeight };
}   //메모리버퍼 사용안할때 사용할 rt

void TextAreaSelectedProcess::MiddleMultiLineSelected(TextEdit *textEdit, CDC *pDC, CString *cstr, RECT *rt) {
	Long i = this->startRowIndex + 1;

	while (i < this->endRowIndex) {
		*cstr += textEdit->text->GetAt(i)->PrintRowString().c_str();
		*cstr += "\r\n";
		i++;
	}
	
	*rt = { 0, (this->startRowIndex + 1) * textEdit->rowHeight, textEdit->GetFigure()->GetX() + textEdit->GetFigure()->GetWidth(),
		(this->endRowIndex - 1) * textEdit->rowHeight + textEdit->rowHeight };
}   //메모리버퍼 사용안할때 사용할 rt

void TextAreaSelectedProcess::EndMultiLineSelected(TextEdit *textEdit, CDC *pDC, CString *cstr, RECT *rt) {
	Long i = 0;

	while (i < this->endCharacterIndex) { // 끝줄
		*cstr += textEdit->text->GetAt(this->endRowIndex)->GetAt(i)->MakeCString();
		i++;
	}
	Long width = textEdit->text->GetAt(this->endRowIndex)->GetRowWidth(pDC, this->endCharacterIndex);
	
	*rt = { 0, this->endRowIndex * textEdit->rowHeight, width, this->endRowIndex * textEdit->rowHeight + textEdit->rowHeight };
}   //메모리버퍼 사용안할때 사용할 rt