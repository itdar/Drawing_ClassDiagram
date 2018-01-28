
//Line.h

#ifndef _LINE_H
#define _LINE_H

#include "Figure.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

class Line : public Figure {

public:
	Line();
	Line(Long x, Long y, Long width, Long height);
	Line(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight,string content);
	Line(const Line& source);
	virtual ~Line();

	Line& operator = (const Line& source);
	Figure* Move(Long distanceX, Long distanceY);
	void Accept(Visitor& visitor, CDC *pDC);
	Figure* Clone() const;
};

#endif // _LINE_H