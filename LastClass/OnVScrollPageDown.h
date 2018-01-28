//OnVScrollPageDown.h

#ifndef _ONVSCROLLPAGEDOWN_H
#define _ONVSCROLLPAGEDOWN_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnVScrollPageDown : public ScrollAction {
public:
	OnVScrollPageDown();
	OnVScrollPageDown(const OnVScrollPageDown& source);
	~OnVScrollPageDown();
public:
	void Scrolling(ClassDiagramForm* classDiagramForm);
};

#endif // _ONVSCROLLPAGEDOWN_H