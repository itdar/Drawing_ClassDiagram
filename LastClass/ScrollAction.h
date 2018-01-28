//ScrollAction.h

#ifndef _SCROLLACTION_H
#define _SCROLLACTION_H

#include <afxwin.h>

typedef signed long int Long;
class ClassDiagramForm;
class ScrollAction {
public:
	ScrollAction();
	ScrollAction(const ScrollAction& sorce);
	virtual ~ScrollAction();

	ScrollAction& operator=(const ScrollAction& source);

	virtual void Scrolling(ClassDiagramForm *classDiagramForm) = 0;
};

#endif // !_SCROLLACTION_H