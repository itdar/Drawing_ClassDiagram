//SelfDirectedAssociation.h
#ifndef _SELFDIRECTEDASSOCIATION_H
#define _SELFDIRECTEDASSOCIATION_H

#include "SelfRelation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class SelfDirectedAssociation :public SelfRelation {
public:
	SelfDirectedAssociation();
	SelfDirectedAssociation(Long x, Long y, Long width, Long height);
	SelfDirectedAssociation(const SelfDirectedAssociation& source);
	SelfDirectedAssociation& operator = (const SelfDirectedAssociation& source);

	virtual ~SelfDirectedAssociation();
	Figure* Clone() const;
	void Accept(Visitor& visitor, CDC *pDC);

};
#endif // !_SELFDIRECTEDASSOCIATION_H
