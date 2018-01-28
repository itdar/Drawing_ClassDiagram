//OnHScrollLineRight.h

#ifndef _ONHSCROLLLINERIGHT_H
#define _ONHSCROLLLINERIGHT_H

#include "ScrollAction.h"

class ClassDiagramForm;
class OnHScrollLineRight : public ScrollAction {
public:
	OnHScrollLineRight();
	OnHScrollLineRight(const OnHScrollLineRight& sorce);
	virtual ~OnHScrollLineRight();

	OnHScrollLineRight& operator=(const OnHScrollLineRight& source);

	virtual void Scrolling(ClassDiagramForm *classDiagramForm);
};

#endif // !_ONHSCROLLLINERIGHT_H