//OnVScrollEnd.h

#ifndef _ONVSCROLLEND_H
#define _ONVSCROLLEND_H
#include "ScrollAction.h"

class ClassDiagramForm;
class OnVScrollEnd : public ScrollAction {
public:
	OnVScrollEnd();
	OnVScrollEnd(const OnVScrollEnd& sorce);
	virtual ~OnVScrollEnd();

	OnVScrollEnd& operator=(const OnVScrollEnd& source);

	virtual void Scrolling(ClassDiagramForm *classDiagramForm);
};
#endif // !_ONVSCROLLEND_H