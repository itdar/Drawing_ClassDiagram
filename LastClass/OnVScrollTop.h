//OnVScrollTop.h

#ifndef _ONVSCROLLTOP_H
#define _ONVSCROLLTOP_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnVScrollTop : public ScrollAction {
public:
	OnVScrollTop();
	OnVScrollTop(const OnVScrollTop& source);
	~OnVScrollTop();
public:
	void Scrolling(ClassDiagramForm* classDiagramForm);
};

#endif // _ONVSCROLLTOP_H