//OnVScrollLineDown.h

#ifndef _ONVSCROLLLINEDOWN_H
#define _ONVSCROLLLINEDOWN_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnVScrollLineDown : public ScrollAction {
public:
	OnVScrollLineDown();
	OnVScrollLineDown(const OnVScrollLineDown& source);
	~OnVScrollLineDown();
public:
	void Scrolling(ClassDiagramForm* classDiagramForm);
};

#endif // _ONVSCROLLLINEDOWN_H