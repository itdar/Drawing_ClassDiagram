//EnterKey.cpp

#include "EnterKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"
#include "HistoryText.h"
#include "DeleteTextArea.h"
#include "ClassDiagramForm.h"
#include "Template.h"

EnterKey::EnterKey() {
}
EnterKey::EnterKey(const EnterKey& source) {
}
EnterKey::~EnterKey() {
}

void EnterKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagSelection == 1) {
		DeleteTextArea *deleteArea = new DeleteTextArea();
		deleteArea->DeleteArea(textEdit);
		if (deleteArea != 0) {
			delete deleteArea;
		}
	}
	Row row;
	if (!dynamic_cast<Template*>(textEdit->figure)) {
		textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
		textEdit->historyText->redoTextArray->Clear();
		textEdit->historyText->redoCaretArray->Clear();
		if (textEdit->caret->GetCharacterIndex() == 0) {
			textEdit->text->Insert(textEdit->caret->GetRowIndex(), row.Clone());
			textEdit->caret->MoveForwardRowIndex();
			textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
		}
		else {
			textEdit->text->Insert(textEdit->caret->GetRowIndex() + 1, row.Clone());
			textEdit->caret->MoveForwardRowIndex();
			Long j = 0;
			while (textEdit->caret->GetCharacterIndex() < textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->GetLength()) {
				Character *character = textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->GetAt(textEdit->caret->GetCharacterIndex());
				textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Add(character->Clone());
				textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->Remove(textEdit->caret->GetCharacterIndex());
			}
			textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());

		}
		textEdit->caret->SetCharacterIndex(0);
	}
}

void EnterKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}