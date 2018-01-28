//OnHScrollLeft.cpp

#include "OnHScrollLeft.h"
#include "ClassDiagramForm.h"

OnHScrollLeft::OnHScrollLeft() : ScrollAction() {
}
OnHScrollLeft::OnHScrollLeft(const OnHScrollLeft& source) : ScrollAction(source) {
}
OnHScrollLeft::~OnHScrollLeft() {
}
OnHScrollLeft& OnHScrollLeft::operator=(const OnHScrollLeft& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollLeft::Scrolling(ClassDiagramForm *classDiagramForm) {
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_HORZ, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_HORZ);

	int curpos = classDiagramForm->GetScrollPos(SB_HORZ);

	curpos = minpos;

	classDiagramForm->SetScrollPos(SB_HORZ, curpos);
}