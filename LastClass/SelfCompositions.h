//SelfCompositions.h
#ifndef _SELFCOMPOSITIONS_H
#define _SELFCOMPOSITIONS_H

#include "SelfRelation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class SelfCompositions :public SelfRelation {
public:
	SelfCompositions();
	SelfCompositions(Long x, Long y, Long width, Long height);
	SelfCompositions(const SelfCompositions& source);
	SelfCompositions& operator = (const SelfCompositions& source);

	virtual ~SelfCompositions();
	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);

};
#endif // !_SELFCOMPOSITIONS_H
