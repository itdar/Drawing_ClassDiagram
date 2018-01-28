#ifndef _ONVSCROLLTHUMBPOSITION_H
#define _ONVSCROLLTHUMBPOSITION_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnVScrollThumbPosition : public ScrollAction {
public:
	OnVScrollThumbPosition();
	OnVScrollThumbPosition(const OnVScrollThumbPosition& source);
	~OnVScrollThumbPosition();
public:
	void Scrolling(ClassDiagramForm* classDiagramForm);
};

#endif // !_ONVSCROLLTHUMBPOSITION_H
