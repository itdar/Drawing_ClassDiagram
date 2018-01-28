#ifndef _CLASSNAME_H
#define _CLASSNAME_H

#include "Figure.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

class ClassName : public Figure {

public:
	ClassName();
	ClassName(Long x, Long y, Long width, Long height, string content);
	ClassName(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, string content);
	ClassName(const ClassName& source);
	virtual ~ClassName();

	ClassName& operator = (const ClassName& source);

	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);
};

#endif // !_CLASSNAME_H