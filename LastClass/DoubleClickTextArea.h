//DoubleClickTextArea.h

#ifndef _DOUBLECLICKTEXTAREA_H
#define _DOUBLECLICKTEXTAREA_H

class TextEdit;
class DoubleClickTextArea {
public:
	static DoubleClickTextArea* Instance();
public:
	DoubleClickTextArea();
	DoubleClickTextArea(const DoubleClickTextArea& source);
	~DoubleClickTextArea();
public:
	void FindDoubleClickAreaIndex(TextEdit *textEdit);
private:
	static DoubleClickTextArea* instance;
};

#endif // _DOUBLECLICKTEXTAREA_H