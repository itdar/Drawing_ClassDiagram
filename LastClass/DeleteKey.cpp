//DeleteKey.cpp

#include "DeleteKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "HistoryText.h"
#include "TextAreaSelected.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "DeleteTextArea.h"
#include "ClassDiagramForm.h"

DeleteKey::DeleteKey() {
}

DeleteKey::DeleteKey(const DeleteKey& source) {
}

DeleteKey::~DeleteKey() {
}

void DeleteKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagSelection == 1) {
		DeleteTextArea *deleteArea = new DeleteTextArea();
		deleteArea->DeleteArea(textEdit);
		if (deleteArea != 0) {
			delete deleteArea;
		}
	}
	else {
		if (textEdit->caret->GetCharacterIndex() < textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			textEdit->historyText->redoTextArray->Clear();
			textEdit->historyText->redoCaretArray->Clear();
			textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(textEdit->caret->GetCharacterIndex());
		}
		else if (textEdit->caret->GetCharacterIndex() == textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()
			&& textEdit->caret->GetRowIndex() < textEdit->text->GetLength() - 1) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			textEdit->historyText->redoTextArray->Clear();
			textEdit->historyText->redoCaretArray->Clear();
			Long i = 0;
			while (i < textEdit->text->GetAt(textEdit->caret->GetRowIndex() + 1)->GetLength()) {
				textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Add(textEdit->text->GetAt(textEdit->caret->GetRowIndex() + 1)->GetAt(i));
				i++;
			}
			textEdit->text->Remove(textEdit->caret->GetRowIndex() + 1);
		}
	}
}

void DeleteKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}