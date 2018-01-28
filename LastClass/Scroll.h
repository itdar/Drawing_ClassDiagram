//Scroll.h

#ifndef _SCROLL_H
#define _SCROLL_H
#include <afxwin.h>

typedef signed long int Long;

class ClassDiagramForm;
class ScrollAction;
class Scroll {
public:
	Scroll();
	Scroll(const Scroll& source);
	~Scroll();

	Scroll& operator = (const Scroll& source);

	ScrollAction* MoveVScroll(ClassDiagramForm *classDiagramForm, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	ScrollAction* MoveHScroll(ClassDiagramForm *classDiagramForm, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
protected:
	ScrollAction *scrollAction;
};

#endif // !_SCROLL_H