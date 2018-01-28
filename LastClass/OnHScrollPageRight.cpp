//OnHScrollPageRight.cpp

#include "OnHScrollPageRight.h"
#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

OnHScrollPageRight::OnHScrollPageRight() : ScrollAction() {
}
OnHScrollPageRight::OnHScrollPageRight(const OnHScrollPageRight& source) : ScrollAction(source) {
}
OnHScrollPageRight::~OnHScrollPageRight() {
}
OnHScrollPageRight& OnHScrollPageRight::operator=(const OnHScrollPageRight& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollPageRight::Scrolling(ClassDiagramForm *classDiagramForm) {
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_HORZ, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_HORZ);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_HORZ);

	// Get the page size. 
	SCROLLINFO   info;
	classDiagramForm->GetScrollInfo(SB_HORZ, &info, SIF_ALL);
	info.nPage = 50;

	if (curpos < maxpos) {
		curpos = min(maxpos, curpos + (int)info.nPage);
	}

	classDiagramForm->SetScrollPos(SB_HORZ, curpos);
	ScrollMovingObject moving;
	moving.MovingObject(classDiagramForm->diagram, -50);
}