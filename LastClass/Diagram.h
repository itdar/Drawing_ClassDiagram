//Diagram.h

#ifndef _DIAGRAM_H
#define _DIAGRAM_H

#include"FigureComposite.h"
#include"DrawingVisitor.h"
#include "ClassDiagramForm.h"

class ClassDiagramForm;
class Diagram : public FigureComposite {
public:
	Diagram(Long capacity = 50000);
	Diagram(const Diagram& source);
	virtual ~Diagram();

	Diagram& operator = (const Diagram& source);
	Figure* operator [] (Long index);

	//Long Find(Long x, Long y);
	virtual Long Add(Figure *figure);
	Long AddClass(Long x, Long y, Long width, Long height);
	Long AddMemoBox(Long x, Long y, Long width, Long height);
	Figure* FindItem(Long x, Long y,ClassDiagramForm* classDiagramForm);
	virtual Long Remove(Long index);
	CRect GetCorrectRect(Long startX, Long startY, Long currentX, Long currentY);

	string FindLongString(string str);

	virtual Figure* GetAt(Long index);
	virtual Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);


};

#endif // !_DIAGRAM_H