//SelfDependency.h
#ifndef _SELFDEPENDENCY_H
#define _SELFDEPENDENCY_H

#include "SelfRelation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class SelfDependency :public SelfRelation {
public:
	SelfDependency();
	SelfDependency(Long x, Long y, Long width, Long height);
	SelfDependency(const SelfDependency& source);
	SelfDependency& operator = (const SelfDependency& source);

	virtual ~SelfDependency();
	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);

};
#endif // !_SELFDEPENDENCY_H
