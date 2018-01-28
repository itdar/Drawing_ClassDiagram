//SelfAggregation.h
#ifndef _SELFAGGREGATION_H
#define _SELFAGGREGATION_H

#include "SelfRelation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class SelfAggregation :public SelfRelation {
public:
	SelfAggregation();
	SelfAggregation(Long x, Long y, Long width, Long height);
	SelfAggregation(const SelfAggregation& source);
	SelfAggregation& operator = (const SelfAggregation& source);

	virtual ~SelfAggregation();
	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);

};
#endif // !_SELFAGGREGATION_H
