//OnHScrollPageRight.h

#ifndef _ONHSCROLLPAGERIGHT_H
#define _ONHSCROLLPAGERIGHT_H
#include "ScrollAction.h"

class ClassDiagramForm;
class OnHScrollPageRight : public ScrollAction {
public:
	OnHScrollPageRight();
	OnHScrollPageRight(const OnHScrollPageRight& sorce);
	virtual ~OnHScrollPageRight();

	OnHScrollPageRight& operator=(const OnHScrollPageRight& source);

	virtual void Scrolling(ClassDiagramForm *classDiagramForm);
};

#endif // !_ONHSCROLLPAGERIGHT_H