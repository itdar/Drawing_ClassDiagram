//OnHScrollLineLeft.h

#ifndef _ONHSCROLLLINELEFT_H
#define _ONHSCROLLLINELEFT_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnHScrollLineLeft : public ScrollAction {
public:
	OnHScrollLineLeft();
	OnHScrollLineLeft(const OnHScrollLineLeft& sorce);
	virtual ~OnHScrollLineLeft();

	OnHScrollLineLeft& operator=(const OnHScrollLineLeft& source);

	virtual void Scrolling(ClassDiagramForm *classDiagramForm);
};

#endif // !_ONHSCROLLLINELEFT_H