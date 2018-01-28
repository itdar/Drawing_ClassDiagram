//OnHScrollRight.h

#ifndef _ONHSCROLLRIGHT_H
#define _ONHSCROLLRIGHT_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnHScrollRight : public ScrollAction {
public:
	OnHScrollRight();
	OnHScrollRight(const OnHScrollRight& sorce);
	virtual ~OnHScrollRight();

	OnHScrollRight& operator=(const OnHScrollRight& source);

	virtual void Scrolling(ClassDiagramForm *classDiagramForm);
};
#endif // !_ONHSCROLLRIGHT_H