//OnHScrollEnd.h

#ifndef _ONHSCROLLEND_H
#define _ONHSCROLLEND_H
#include "ScrollAction.h"

class ClassDiagramForm;
class OnHScrollEnd : public ScrollAction {
public:
	OnHScrollEnd();
	OnHScrollEnd(const OnHScrollEnd& sorce);
	virtual ~OnHScrollEnd();

	OnHScrollEnd& operator=(const OnHScrollEnd& source);

	virtual void Scrolling(ClassDiagramForm *classDiagramForm);
};
#endif // !_ONHSCROLLEND_H