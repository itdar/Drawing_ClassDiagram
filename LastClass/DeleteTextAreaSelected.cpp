//DeleteTextAreaSelected.cpp

#include "DeleteTextAreaSelected.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
#include "TextAreaSelectedProcess.h"
#include "Text.h"
#include "Row.h"
#include "DoubleByteCharacter.h"
#include "SingleByteCharacter.h"


DeleteTextAreaSelected::DeleteTextAreaSelected() {
}

DeleteTextAreaSelected::DeleteTextAreaSelected(const DeleteTextAreaSelected& source) {
}

DeleteTextAreaSelected::~DeleteTextAreaSelected() {
}

void DeleteTextAreaSelected::DeleteSingleLineSelected(TextEdit* textEdit) {
	Long i = 0;
	while (i < textEdit->textAreaSelected->selected->GetEndCharacterIndex() - textEdit->textAreaSelected->selected->GetStartCharacterIndex()) {
		textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex())->Remove(textEdit->textAreaSelected->selected->GetStartCharacterIndex());
		i++;
	}
}

void DeleteTextAreaSelected::DeleteFirstMultiLineSelected(TextEdit* textEdit) {
	while (textEdit->textAreaSelected->selected->GetStartCharacterIndex() <
		textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex())->GetLength()) {//첫줄
		textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex())->Remove(textEdit->textAreaSelected->selected->GetStartCharacterIndex());
	}
}

void DeleteTextAreaSelected::DeleteMiddleMultiLineSelected(TextEdit* textEdit) {
	Long i = 0;
	while (i < textEdit->textAreaSelected->selected->GetEndRowIndex() - textEdit->textAreaSelected->selected->GetStartRowIndex() - 1) { // 중간줄 있으면 중간줄
		textEdit->text->Remove(textEdit->textAreaSelected->selected->GetStartRowIndex() + 1);
		i++;
	}
}

void DeleteTextAreaSelected::DeleteEndMultiLineSelected(TextEdit* textEdit) {
	Long i = 0; // 제일 아랫줄
	while (i < textEdit->textAreaSelected->selected->GetEndCharacterIndex()) {
		textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex() + 1)->Remove(0);
		i++;
	}
}

void DeleteTextAreaSelected::ConnectRemains(TextEdit *textEdit, Long copyCount) {
	Long i = 0;
	while (i < copyCount) {
		if (dynamic_cast<DoubleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex() + 1)->GetAt(i))) {
			DoubleByteCharacter *tempDouble = static_cast<DoubleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex() + 1)->GetAt(i));
			textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex())->Add(tempDouble->Clone());
		}
		else if (dynamic_cast<SingleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex() + 1)->GetAt(i))) {
			SingleByteCharacter *tempSingle = static_cast<SingleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex() + 1)->GetAt(i));
			textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex())->Add(tempSingle->Clone());
		}
		i++;
	}
	textEdit->text->Remove(textEdit->textAreaSelected->selected->GetStartRowIndex() + 1);
}