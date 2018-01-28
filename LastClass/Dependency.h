
//Dependency.h
#pragma once
#ifndef _DEPENDENCY_H
#define _DEPENDENCY_H


#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class Dependency : public Relation {
public:
	Dependency(Long capacity = 10);
	Dependency(Long x, Long y, Long width, Long height);
	Dependency(const Dependency& source);
	virtual ~Dependency();

	Dependency& operator = (const Dependency&  source);
	void Accept(Visitor& visitor, CDC *pDC);
	Figure* Clone() const;

};
#endif // !_DEPENDENCY_H
