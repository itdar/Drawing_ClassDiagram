//CtrlPasteKey.cpp

#include "CtrlPasteKey.h"
#include "TextEdit.h"
#include "Row.h"
#include "Caret.h"
#include "Text.h"
#include "DoubleByteCharacter.h"
#include "SingleByteCharacter.h"
#include "TextAreaSelected.h"
#include "HistoryText.h"
#include "DeleteTextArea.h"
#include "ClassDiagramForm.h"

CtrlPasteKey::CtrlPasteKey() {
}
CtrlPasteKey::CtrlPasteKey(const CtrlPasteKey& source) {
}
CtrlPasteKey::~CtrlPasteKey() {
}

void CtrlPasteKey::KeyPress(TextEdit *textEdit) {
	textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
	textEdit->historyText->redoTextArray->Clear();
	textEdit->historyText->redoCaretArray->Clear();
	if (textEdit->flagSelection == 1) {
		DeleteTextArea *deleteArea = DeleteTextArea::Instance();
		deleteArea->DeleteArea(textEdit);
	}
	unsigned int priority_list = CF_TEXT;
	char *p_string = NULL;
	if (::GetPriorityClipboardFormat(&priority_list, 1) == CF_TEXT) {
		OpenClipboard(NULL);
		HANDLE h_clipboard_data = ::GetClipboardData(CF_TEXT);
		char *p_clipboard_data = (char *)::GlobalLock(h_clipboard_data);
		::GlobalUnlock(h_clipboard_data);
		::CloseClipboard(); 
		textEdit->copyBuffer = p_clipboard_data;

		Long size = strlen(p_clipboard_data);
		Long i = 0;
		char character[2] = { 0, };
		Long temp = 0;
		char c = '\r';
		temp = ((string)textEdit->copyBuffer).find(c);
		Row *row = textEdit->text->GetAt(textEdit->caret->GetRowIndex());
		Long rowIndex_ = textEdit->caret->GetRowIndex();
		while (i < size) {
			if (i != 0)
			{
				row = new Row;
			}
			while (textEdit->copyBuffer[i] != '\r' && i < size) {
				if (textEdit->copyBuffer[i] & 0x80) {
					character[0] = textEdit->copyBuffer[i];
					character[1] = textEdit->copyBuffer[i + 1];
					i++;
					DoubleByteCharacter doubleTemp(character);
					if (i < temp || temp == -1) {
						if (textEdit->caret->GetCharacterIndex() < row->GetLength()) {
							row->Insert(textEdit->caret->GetCharacterIndex(), doubleTemp.Clone());
						}
						else {
							row->Add(doubleTemp.Clone());
						}
					}
					else {
						row->Add(doubleTemp.Clone());
					}
				}
				else {
					SingleByteCharacter singleTemp(textEdit->copyBuffer[i]);
					if (i < temp || temp == -1) {
						if (textEdit->caret->GetCharacterIndex() < row->GetLength()) {
							row->Insert(textEdit->caret->GetCharacterIndex(), singleTemp.Clone());
						}
						else {
							row->Add(singleTemp.Clone());
						}
					}
					else {
						row->Add(singleTemp.Clone());
					}
				}
				if (i < temp || temp == -1) {
					textEdit->caret->MoveForwardCharacterIndex();
				}
				i++;
			}

			if (i > temp&& temp != -1) {
				if (textEdit->caret->GetRowIndex() + 1 == textEdit->text->GetLength()) {
					textEdit->text->Add(row->Clone());
				}
				else {
					textEdit->text->Insert(textEdit->caret->GetRowIndex() + 1, row->Clone());
				}
				textEdit->caret->MoveForwardRowIndex(1);
			}

			i = i + 2;
		}
		Long j = textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength();
		if (temp != -1) {
			while (textEdit->caret->GetCharacterIndex() < textEdit->text->GetAt(rowIndex_)->GetLength()) {
				Character *character = textEdit->text->GetAt(rowIndex_)->GetAt(textEdit->caret->GetCharacterIndex());
				textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Add(character->Clone());
				textEdit->text->GetAt(rowIndex_)->Remove(textEdit->caret->GetCharacterIndex());
			}
		}
		if (temp != -1 || textEdit->caret->GetCharacterIndex() == textEdit->text->GetAt(rowIndex_)->GetLength()) {
			textEdit->caret->SetCharacterIndex(j);
		}
	}
}

void CtrlPasteKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
}