//OnVScrollLineUp.h

#ifndef _ONVSCROLLLINEUP_H
#define _ONVSCROLLLINEUP_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnVScrollLineUp : public ScrollAction {
public:
	OnVScrollLineUp();
	OnVScrollLineUp(const OnVScrollLineUp& source);
	~OnVScrollLineUp();
public:
	void Scrolling(ClassDiagramForm* classDiagramForm);
};

#endif // _ONVSCROLLTOP_H