//DeleteTextArea.cpp

#include "DeleteTextArea.h"
#include "DeleteTextAreaSelected.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "TextAreaSelected.h"
#include "TextAreaSelectedProcess.h"
#include "HistoryText.h"
#include "Caret.h"

DeleteTextArea* DeleteTextArea::instance = 0;

DeleteTextArea* DeleteTextArea::Instance() {
	if (instance == 0) {
		instance = new DeleteTextArea;
	}
	return instance;
}
DeleteTextArea::DeleteTextArea() {
}
DeleteTextArea::DeleteTextArea(const DeleteTextArea& source) {
}
DeleteTextArea::~DeleteTextArea() {
}

void DeleteTextArea::DeleteArea(TextEdit *textEdit) {
	DeleteTextAreaSelected *deleteLines = 0;
	if (deleteLines != 0) {
		delete deleteLines;
		deleteLines = 0;
	}
	deleteLines = new DeleteTextAreaSelected();
	Long i = 0;
	if (textEdit->textAreaSelected->selected->GetStartRowIndex() == textEdit->textAreaSelected->selected->GetEndRowIndex()) {
		textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
		textEdit->historyText->redoTextArray->Clear();
		textEdit->historyText->redoCaretArray->Clear();
		deleteLines->DeleteSingleLineSelected(textEdit);
	}
	else if (textEdit->textAreaSelected->selected->GetStartRowIndex() < textEdit->textAreaSelected->selected->GetEndRowIndex()) { // 여러줄이면
		textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
		textEdit->historyText->redoTextArray->Clear();
		textEdit->historyText->redoCaretArray->Clear();
		deleteLines->DeleteFirstMultiLineSelected(textEdit);
		deleteLines->DeleteMiddleMultiLineSelected(textEdit);
		Long copyCount = textEdit->text->GetAt(textEdit->textAreaSelected->selected->GetStartRowIndex() + 1)->GetLength() - textEdit->textAreaSelected->selected->GetEndCharacterIndex();
		deleteLines->DeleteEndMultiLineSelected(textEdit);
		deleteLines->ConnectRemains(textEdit, copyCount);
	}
	textEdit->caret->SetRowIndex(textEdit->textAreaSelected->selected->GetStartRowIndex());
	textEdit->caret->SetCharacterIndex(textEdit->textAreaSelected->selected->GetStartCharacterIndex());
	textEdit->flagSelection = 0;
}