//Caret.h

#ifndef _CARET_H
#define _CARET_H

#include <afxwin.h>

typedef signed long int Long;

class TextEdit;
class Caret {
public:
	Caret();
	Caret(const Caret& source);
	~Caret();

	void MoveToIndex(TextEdit *textEdit, CDC *cPaintDc);
	void MoveToPoint(TextEdit *textEdit, CDC *cPaintDc, CPoint point);
	void MoveForwardRowIndex(Long index = 1);
	void MoveBackwardRowIndex(Long index = 1);
	void MoveForwardCharacterIndex(Long index = 1);
	void MoveBackwardCharacterIndex(Long index = 1);

	void SetCharacterIndex(Long index);
	void SetRowIndex(Long index);

	Long GetCurrentCaretX() const;
	Long GetCurrentCaretY() const;
	Long GetRowIndex() const;
	Long GetCharacterIndex() const;

	Caret& operator = (const Caret& source);
private:
	Long characterIndex;
	Long rowIndex;
	Long currentCaretX;
	Long currentCaretY;
};

inline Long Caret::GetRowIndex() const {
	return this->rowIndex;
}
inline Long Caret::GetCharacterIndex() const {
	return this->characterIndex;
}
inline Long Caret::GetCurrentCaretX() const {
	return this->currentCaretX;
}
inline Long Caret::GetCurrentCaretY() const {
	return this->currentCaretY;
}
#endif // _CARET_H