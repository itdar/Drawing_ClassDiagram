//DoubleClickTextAreaProcess.cpp

#include "DoubleClickTextAreaProcess.h"
#include "TextEdit.h"
#include "Text.h"
#include "Caret.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

DoubleClickTextAreaProcess::DoubleClickTextAreaProcess() {
}
DoubleClickTextAreaProcess::DoubleClickTextAreaProcess(const DoubleClickTextAreaProcess& source) {
}
DoubleClickTextAreaProcess::~DoubleClickTextAreaProcess() {
}

Long DoubleClickTextAreaProcess::DoubleClickStartIndex(TextEdit *textEdit) {
	Row *currentRow = textEdit->text->GetAt(textEdit->caret->GetRowIndex());
	Long StartIndex = textEdit->caret->GetCharacterIndex();

	while (StartIndex > 0 && currentRow->GetAt(StartIndex - 1)->MakeCString() != ' '&&currentRow->GetAt(StartIndex - 1)->MakeCString() != ':'
		&&currentRow->GetAt(StartIndex - 1)->MakeCString() != '-'&&currentRow->GetAt(StartIndex - 1)->MakeCString() != '+'
		&&currentRow->GetAt(StartIndex - 1)->MakeCString() != ')'&&currentRow->GetAt(StartIndex - 1)->MakeCString() != '('
		&&currentRow->GetAt(StartIndex - 1)->MakeCString() != '*'&&currentRow->GetAt(StartIndex - 1)->MakeCString() != ',') {
		StartIndex--;
	}
	return StartIndex;
}

Long DoubleClickTextAreaProcess::DoubleClickEndIndex(TextEdit *textEdit) {
	Row *currentRow = textEdit->text->GetAt(textEdit->caret->GetRowIndex());
	Long endIndex = textEdit->caret->GetCharacterIndex();

	while (endIndex < currentRow->GetLength() && currentRow->GetAt(endIndex)->MakeCString() != ' '&&currentRow->GetAt(endIndex)->MakeCString() != ':'
		&&currentRow->GetAt(endIndex)->MakeCString() != '-'&&currentRow->GetAt(endIndex)->MakeCString() != '+'
		&&currentRow->GetAt(endIndex)->MakeCString() != ')'&&currentRow->GetAt(endIndex)->MakeCString() != '('
		&&currentRow->GetAt(endIndex)->MakeCString() != '*'&&currentRow->GetAt(endIndex)->MakeCString() != ',') {
		endIndex++;
	}

	return endIndex;
}