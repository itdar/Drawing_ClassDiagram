//TextAreaSelectedProcess.h

#ifndef _TEXTAREASELECTEDPROCESS_H
#define _TEXTAREASELECTEDPROCESS_H

#include <afxwin.h>

typedef signed long int Long;

class TextEdit;
class TextAreaSelected;
class TextAreaSelectedProcess {
public:
	TextAreaSelectedProcess();
	TextAreaSelectedProcess(const TextAreaSelectedProcess& source);
	~TextAreaSelectedProcess();

public:
	void GetRange(TextEdit* textEdit);
	void SingleLineSelected(TextEdit *textEdit, CDC *pDC, CString *cstr, RECT *rt);
	void FirstMultiLineSelected(TextEdit *textEdit, CDC *pDC, CString *cstr, RECT *rt);
	void MiddleMultiLineSelected(TextEdit *textEdit, CDC *pDC, CString *cstr, RECT *rt);
	void EndMultiLineSelected(TextEdit *textEdit, CDC *pDC, CString *cstr, RECT *rt);

	Long GetStartCharacterIndex() const;
	Long GetStartRowIndex() const;
	Long GetEndCharacterIndex() const;
	Long GetEndRowIndex() const;
private:
	Long startCharacterIndex;
	Long startRowIndex;
	Long endCharacterIndex;
	Long endRowIndex;
};

inline Long TextAreaSelectedProcess::GetStartCharacterIndex() const {
	return this->startCharacterIndex;
}
inline Long TextAreaSelectedProcess::GetStartRowIndex() const {
	return this->startRowIndex;
}
inline Long TextAreaSelectedProcess::GetEndCharacterIndex() const {
	return this->endCharacterIndex;
}
inline Long TextAreaSelectedProcess::GetEndRowIndex() const {
	return this->endRowIndex;
}

#endif // !_TEXTAREASELECTEDPROCESS_H