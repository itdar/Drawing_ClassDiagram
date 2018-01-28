
//Realization.h
#pragma once
#ifndef _REALIZATION_H
#define _REALIZATION_H


#include "Relation.h"
#include "DrawingVisitor.h"

typedef signed long int Long;
class Realization : public Relation {
public:
	Realization(Long capacity = 10);
	Realization(Long x, Long y, Long width, Long height);
	Realization(const Realization& source);
	virtual ~Realization();

	Realization& operator = (const Realization&  source);
	void Accept(Visitor& visitor, CDC *pDC);
	Figure* Clone() const;

};
#endif // ! _REALIZATION_H