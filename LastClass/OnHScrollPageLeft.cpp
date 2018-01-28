//OnHScrollPageLeft.cpp

#include "OnHScrollPageLeft.h"
#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

OnHScrollPageLeft::OnHScrollPageLeft() : ScrollAction() {
}
OnHScrollPageLeft::OnHScrollPageLeft(const OnHScrollPageLeft& source) : ScrollAction(source) {
}
OnHScrollPageLeft::~OnHScrollPageLeft() {
}
OnHScrollPageLeft& OnHScrollPageLeft::operator=(const OnHScrollPageLeft& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollPageLeft::Scrolling(ClassDiagramForm *classDiagramForm) {
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_HORZ, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_HORZ);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_HORZ);
	int newpos = curpos - 50;
	if (newpos < minpos) {
		newpos = minpos;
	}

	classDiagramForm->SetScrollPos(SB_HORZ, newpos);
	ScrollMovingObject moving;
	moving.MovingObject(classDiagramForm->diagram, curpos - newpos, 0);

	bool ret;
	SCROLLINFO hScinfo;
	classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
	//int hMax = hScinfo.nMax;
	int hMax = 4000 * classDiagramForm->zoomRate / 100;
	ret = moving.FindHorizontal(classDiagramForm->diagram, hScinfo.nPage);
	if (ret == false) {
		SCROLLINFO hScinfo;
		classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
		hScinfo.nMax -= 50;
		if (hScinfo.nMax < hMax) {
			hScinfo.nMax = hMax;
		}
		if (hScinfo.nMax < hScinfo.nPage) {
			hScinfo.nMax = hScinfo.nPage;
		}
		classDiagramForm->SetScrollInfo(SB_HORZ, &hScinfo);
	}
}