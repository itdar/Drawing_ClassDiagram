//BackSpaceKey.cpp

#include "BackSpaceKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Character.h"
#include "HistoryText.h"
#include "TextAreaSelected.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "DeleteTextArea.h"
#include "ClassDiagramForm.h"

BackSpaceKey::BackSpaceKey() {
}

BackSpaceKey::BackSpaceKey(const BackSpaceKey& source) {
}

BackSpaceKey::~BackSpaceKey() {
}

void BackSpaceKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagSelection == 1) {
		DeleteTextArea *deleteArea = new DeleteTextArea();
		deleteArea->DeleteArea(textEdit);
		if (deleteArea != 0) {
			delete deleteArea;
		}
	}
	else {
		if (textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() > 0 && textEdit->caret->GetCharacterIndex() > 0) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			textEdit->historyText->redoTextArray->Clear();
			textEdit->historyText->redoCaretArray->Clear();

			textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(textEdit->caret->GetCharacterIndex() - 1);
			textEdit->caret->MoveBackwardCharacterIndex();
		}
		else if (textEdit->caret->GetCharacterIndex() == 0 && textEdit->caret->GetRowIndex() > 0) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			textEdit->historyText->redoTextArray->Clear();
			textEdit->historyText->redoCaretArray->Clear();
			if (textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() == 0) {
				textEdit->text->Remove(textEdit->caret->GetRowIndex());
				textEdit->caret->MoveBackwardRowIndex();
				textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength());
			}
			else {
				textEdit->caret->SetCharacterIndex(textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->GetLength());
				while (textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() > 0) {
					Character *character = textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetAt(0);
					textEdit->text->GetAt(textEdit->caret->GetRowIndex() - 1)->Add(character->Clone());
					textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(0);
				}
				textEdit->text->Remove(textEdit->caret->GetRowIndex());
				textEdit->caret->MoveBackwardRowIndex();
			}
		}
	}
}
void BackSpaceKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}