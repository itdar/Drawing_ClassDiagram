//OnHScrollPageLeft.h

#ifndef _ONHSCROLLPAGELEFT_H
#define _ONHSCROLLPAGELEFT_H
#include "ScrollAction.h"

class ClassDiagramForm;
class OnHScrollPageLeft : public ScrollAction {
public:
	OnHScrollPageLeft();
	OnHScrollPageLeft(const OnHScrollPageLeft& sorce);
	virtual ~OnHScrollPageLeft();

	OnHScrollPageLeft& operator=(const OnHScrollPageLeft& source);

	virtual void Scrolling(ClassDiagramForm *classDiagramForm);
};

#endif // !_ONHSCROLLPAGELEFT_H