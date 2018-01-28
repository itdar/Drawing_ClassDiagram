//OnVScrollPageUp.h

#ifndef _ONVSCROLLPAGEUP_H
#define _ONVSCROLLPAGEUP_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnVScrollPageUp : public ScrollAction {
public:
	OnVScrollPageUp();
	OnVScrollPageUp(const OnVScrollPageUp& source);
	~OnVScrollPageUp();
public:
	void Scrolling(ClassDiagramForm* classDiagramForm);
};

#endif // _ONVSCROLLPAGEUP_H