//OnHScrollLeft.h

#ifndef _ONHSCROLLLEFT_H
#define _ONHSCROLLLEFT_H
#include "ScrollAction.h"

class ClassDiagramForm;
class OnHScrollLeft : public ScrollAction {
public:
	OnHScrollLeft();
	OnHScrollLeft(const OnHScrollLeft& sorce);
	virtual ~OnHScrollLeft();

	OnHScrollLeft& operator=(const OnHScrollLeft& source);

	virtual void Scrolling(ClassDiagramForm *classDiagramForm);
};
#endif // !_ONHSCROLLLEFT_H