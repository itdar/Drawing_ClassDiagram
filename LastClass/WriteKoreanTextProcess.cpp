//WriteKoreanTextProcess.cpp

#pragma comment(lib,"imm32")

#include "WriteKoreanTextProcess.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "DoubleByteCharacter.h"
#include "Caret.h"

WriteKoreanTextProcess::WriteKoreanTextProcess() {
}
WriteKoreanTextProcess::WriteKoreanTextProcess(const WriteKoreanTextProcess& source) {
}
WriteKoreanTextProcess::~WriteKoreanTextProcess() {
}

void WriteKoreanTextProcess::EndComposition(TextEdit *textEdit, Long bufferLength, char (*buffer)) {
	Long i = 0;
	char(*tempChar) = new char[bufferLength];
	while (i < bufferLength) {
		tempChar[i] = buffer[i];
		i++;
	}
	DoubleByteCharacter doubleByteCharacter(tempChar);
	delete[] tempChar;

	textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Modify(textEdit->caret->GetCharacterIndex() - 1, doubleByteCharacter.Clone());
	textEdit->flagBuffer = 0;
}

void WriteKoreanTextProcess::StartComposition(TextEdit *textEdit, Long bufferLength, char(*buffer)) {
	Long i = 0;
	char(*tempChar) = new char[bufferLength];
	while (i < bufferLength) {
		tempChar[i] = buffer[i];
		i++;
	}
	DoubleByteCharacter doubleByteCharacter(tempChar);
	delete[] tempChar;

	if (textEdit->caret->GetCharacterIndex() == textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()) {
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Add(doubleByteCharacter.Clone());
	}
	else if (textEdit->caret->GetCharacterIndex() < textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() && textEdit->flagInsert == 0) {
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Insert(textEdit->caret->GetCharacterIndex(), doubleByteCharacter.Clone());
	}
	else if (textEdit->caret->GetCharacterIndex() < textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength() && textEdit->flagInsert == 1) {
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Modify(textEdit->caret->GetCharacterIndex(), doubleByteCharacter.Clone());
	}
	textEdit->caret->MoveForwardCharacterIndex();
	textEdit->flagBuffer = 1;
}

void WriteKoreanTextProcess::DuringComposition(TextEdit *textEdit, Long bufferLength, char (*buffer)) {
	Long i = 0;
	if (bufferLength > 0) {
		char(*tempChar) = new char[bufferLength];
		while (i < bufferLength) {
			tempChar[i] = buffer[i];
			i++;
		}
		DoubleByteCharacter doubleByteCharacter(tempChar);
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Modify(textEdit->caret->GetCharacterIndex() - 1, doubleByteCharacter.Clone());
		delete[] tempChar;
	}
	else if (bufferLength == 0) {
		textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(textEdit->caret->GetCharacterIndex() - 1);
		textEdit->caret->MoveBackwardCharacterIndex();
		textEdit->flagBuffer = 0;
	}
}