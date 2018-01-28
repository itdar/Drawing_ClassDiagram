//OnHScrollRight.cpp

#include "OnHScrollRight.h"
#include "ClassDiagramForm.h"

OnHScrollRight::OnHScrollRight() : ScrollAction() {
}
OnHScrollRight::OnHScrollRight(const OnHScrollRight& source) : ScrollAction(source) {
}
OnHScrollRight::~OnHScrollRight() {
}
OnHScrollRight& OnHScrollRight::operator=(const OnHScrollRight& source) {
	ScrollAction::operator=(source);
	return *this;
}

void OnHScrollRight::Scrolling(ClassDiagramForm *classDiagramForm) {
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_HORZ, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_HORZ);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_HORZ);

	curpos = maxpos;

	classDiagramForm->SetScrollPos(SB_HORZ, curpos);
}