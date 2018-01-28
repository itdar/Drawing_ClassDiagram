//DeleteTextArea.h

#ifndef _DELETETEXTAREA_H
#define _DELETETEXTAREA_H

class TextEdit;
class DeleteTextArea {
public:
	static DeleteTextArea* Instance();
public:
	DeleteTextArea();
	DeleteTextArea(const DeleteTextArea& source);
	~DeleteTextArea();
public:
	void DeleteArea(TextEdit *textEdit);
private:
	static DeleteTextArea* instance;
};

#endif // _DELETETEXTAREA_H