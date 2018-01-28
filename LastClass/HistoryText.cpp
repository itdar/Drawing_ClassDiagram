//HistoryText.cpp

#include "HistoryText.h"
#include "Text.h"
#include "Caret.h"

HistoryText::HistoryText() {
	this->undoTextArray = new Array<Text*>(0);
	this->redoTextArray = new Array<Text*>(0);
	this->undoCaretArray = new Array<Caret*>(0);
	this->redoCaretArray = new Array<Caret*>(0);
}

HistoryText::HistoryText(const HistoryText& source) {
	this->undoTextArray = source.undoTextArray;
	this->redoTextArray = source.redoTextArray;
	this->undoCaretArray = source.undoCaretArray;
	this->redoCaretArray = source.redoCaretArray;
}

HistoryText::~HistoryText() {
	delete this->undoTextArray;
	delete this->redoTextArray;
	delete this->undoCaretArray;
	delete this->redoCaretArray;
}

void HistoryText::PushUndo(Text *text, Caret *caret) {
	Caret *tempCaret = new Caret(*caret);
	if (this->undoTextArray->GetCapacity() < 200) {
		this->undoTextArray->AppendFromFront(static_cast<Text*>(text->Clone()));
		this->undoCaretArray->AppendFromFront(tempCaret);
	}
	else {
		this->undoTextArray->Insert(0, static_cast<Text*>(text->Clone()));
		this->undoTextArray->DeleteFromRear();
		this->undoCaretArray->Insert(0, tempCaret);
		this->undoCaretArray->DeleteFromRear();
	}
}

Text* HistoryText::PopUndoText() {
	Text *text = 0;
	if (this->undoTextArray->GetLength() > 0) {
		text = this->undoTextArray->GetAt(0);
		this->undoTextArray->Delete(0);
	}
	return text;
}

Caret* HistoryText::PopUndoCaret() {
	Caret *caret = 0;
	if (this->undoCaretArray->GetLength() > 0) {
		caret = this->undoCaretArray->GetAt(0);
		this->undoCaretArray->Delete(0);
	}
	return caret;
}

void HistoryText::PushRedo(Text *text, Caret *caret) {
	Caret *tempCaret = new Caret(*caret);
	if (this->redoTextArray->GetCapacity() < 200) {
		this->redoTextArray->AppendFromFront(static_cast<Text*>(text->Clone()));
		this->redoCaretArray->AppendFromFront(tempCaret);
	}
	else {
		this->redoTextArray->Insert(0, static_cast<Text*>(text->Clone()));
		this->redoTextArray->DeleteFromRear();
		this->redoCaretArray->Insert(0, tempCaret);
		this->redoCaretArray->DeleteFromRear();
	}
}

Text* HistoryText::PopRedoText() {
	Text *text = 0;
	if (this->redoTextArray->GetLength() > 0) {
		text = this->redoTextArray->GetAt(0);
		this->redoTextArray->Delete(0);
	}
	return text;
}

Caret* HistoryText::PopRedoCaret() {
	Caret *caret = 0;
	if (this->redoCaretArray->GetLength() > 0) {
		caret = this->redoCaretArray->GetAt(0);
		this->redoCaretArray->Delete(0);
	}
	return caret;
}
