//Template.h

#ifndef _TEMPLATE_H
#define _TEMPLATE_H

#include "Figure.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

class Template : public Figure {
public:
	Template();
	Template(Long x, Long  y, Long width, Long height);
	Template(Long x, Long  y, Long width, Long height, string content);
	Template(const Template& source);
	virtual ~Template();

	Template& operator=(const Template& source);

	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);
};

#endif // !_TEMPLATE_H