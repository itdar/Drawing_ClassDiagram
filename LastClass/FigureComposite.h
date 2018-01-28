
//FigureComposite.h

#ifndef _FIGURECOMPOSITE_H
#define _FIGURECOMPOSITE_H

#include "Array.h"
#include "Figure.h"
#include "ArrayIterator.h"
//#include "SmartPointer.h"

typedef signed long int Long;
class Diagram;
class FigureComposite : public Figure {
public:

	FigureComposite(Long capcity = 50000);
	FigureComposite(const FigureComposite& source);
	ArrayIterator<Figure*>* CreateIterator() const;
	FigureComposite& operator = (const FigureComposite& source);

	Figure* ModifyComponetsToRightDirection(Diagram *diagram, Long distanceX);
	Figure* ModifyComponetsToDownDirection(Diagram *diagram, Long distanceY);
	Figure* ModifyComponetsToLeftDirection(Diagram *diagram, Long distanceX);
	Figure* ModifyComponetsToUpDirection(Diagram *diagram, Long distanceX);



	virtual ~FigureComposite() = 0;
	virtual Figure* Clone() const = 0;
	virtual	Long Add(Figure *figure) = 0; //2개가 좋을듯
	virtual Long Remove(Long index) = 0;
	virtual Figure* GetAt(Long index) = 0;
	Long Correct(Long index, Figure *figure);


	Long GetCapacity();
	Long GetLength();

protected:
	Array<Figure*> figures;
	Long capacity;
	Long length;
};

inline Long FigureComposite::GetCapacity() {
	return this->capacity;
}
inline Long FigureComposite::GetLength() {
	return this->length;
}

#endif //_FIGURECOMPOSITE_H