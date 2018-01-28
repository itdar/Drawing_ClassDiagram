//OnVScrollBottom.h

#ifndef _ONVSCROLLBOTTOM_H
#define _ONVSCROLLBOTTOM_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnVScrollBottom : public ScrollAction {
public:
	OnVScrollBottom();
	OnVScrollBottom(const OnVScrollBottom& source);
	~OnVScrollBottom();
public:
	void Scrolling(ClassDiagramForm* classDiagramForm);
};

#endif // _ONVSCROLLBOTTOM_H