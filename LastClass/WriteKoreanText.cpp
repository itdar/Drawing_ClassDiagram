//WriteKoreanText.cpp

#include "WriteKoreanText.h"
#include "TextEdit.h"
#include "WriteKoreanTextProcess.h"
#include "HistoryText.h"

WriteKoreanText* WriteKoreanText::instance = 0;

WriteKoreanText* WriteKoreanText::Instance() {
	if (instance == 0) {
		instance = new WriteKoreanText;
	}
	return instance;
}
WriteKoreanText::WriteKoreanText() {
}
WriteKoreanText::WriteKoreanText(const WriteKoreanText& source) {
}
WriteKoreanText::~WriteKoreanText() {
}

void WriteKoreanText::WriteHanguel(WPARAM wParam, LPARAM lParam, HIMC hIMC, TextEdit *textEdit) {
	Long bufferLength;
	char buffer[8];

	if (lParam & GCS_RESULTSTR) { // 조합 끝 메세지일때
		bufferLength = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);
		ImmGetCompositionString(hIMC, GCS_RESULTSTR, buffer, bufferLength);
		WriteKoreanTextProcess *koreanProcess = new WriteKoreanTextProcess();
		koreanProcess->EndComposition(textEdit, bufferLength, buffer);
		if (koreanProcess != 0) {
			delete koreanProcess;
		}
	}
	else if (lParam & GCS_COMPSTR) {
		bufferLength = ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0);
		ImmGetCompositionString(hIMC, GCS_COMPSTR, buffer, bufferLength);
		if (textEdit->flagBuffer == 0) { // 조합중에서 시작일때
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			textEdit->historyText->redoTextArray->Clear();
			textEdit->historyText->redoCaretArray->Clear();
			WriteKoreanTextProcess *koreanProcess = new WriteKoreanTextProcess();
			koreanProcess->StartComposition(textEdit, bufferLength, buffer);
			if (koreanProcess != 0) {
				delete koreanProcess;
			}
		}
		else { // 조합중에서 조합중일때
			WriteKoreanTextProcess *koreanProcess = new WriteKoreanTextProcess();
			koreanProcess->DuringComposition(textEdit, bufferLength, buffer);
			if (koreanProcess != 0) {
				delete koreanProcess;
			}
		}
	}
}