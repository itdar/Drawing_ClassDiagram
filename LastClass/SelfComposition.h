//SelfComposition.h
#ifndef _SELFCOMPOSITION_H
#define _SELFCOMPOSITION_H

#include "SelfRelation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class SelfComposition :public SelfRelation {
public:
	SelfComposition();
	SelfComposition(Long x, Long y, Long width, Long height);
	SelfComposition(const SelfComposition& source);
	SelfComposition& operator = (const SelfComposition& source);

	virtual ~SelfComposition();
	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);

};
#endif // !_SELFCOMPOSITION_H
