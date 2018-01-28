//OnHScrollLineLeft.cpp

#include "OnHScrollLineLeft.h"
#include "ClassDiagramForm.h"
#include "ScrollMovingObject.h"

OnHScrollLineLeft::OnHScrollLineLeft() : ScrollAction() {
}
OnHScrollLineLeft::OnHScrollLineLeft(const OnHScrollLineLeft& source) : ScrollAction(source) {
}
OnHScrollLineLeft::~OnHScrollLineLeft() {
}
OnHScrollLineLeft& OnHScrollLineLeft::operator=(const OnHScrollLineLeft& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollLineLeft::Scrolling(ClassDiagramForm *classDiagramForm) {
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	bool ret;
	ScrollMovingObject moving;
	classDiagramForm->GetScrollRange(SB_HORZ, &minpos, &maxpos);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_HORZ);
	int newpos = curpos - 100;
	if (newpos < minpos) {
		newpos = minpos;
	}
	classDiagramForm->SetScrollPos(SB_HORZ, newpos);
	moving.MovingObject(classDiagramForm->diagram,curpos - newpos);


	SCROLLINFO hScinfo;
	classDiagramForm->GetScrollInfo(SB_HORZ, &hScinfo);
	ret = moving.FindHorizontal(classDiagramForm->diagram, hScinfo.nPage);
	//int hMax = hScinfo.nMax;
	int hMax = 4000 * classDiagramForm->zoomRate / 100;
	if (ret == false) {;
		hScinfo.nMax -= 100;
		if (hScinfo.nMax < hMax) {
			hScinfo.nMax = hMax;
		}
		if (hScinfo.nMax < hScinfo.nPage) {
			hScinfo.nMax = hScinfo.nPage;
		}
		classDiagramForm->SetScrollInfo(SB_HORZ, &hScinfo);
		//classDiagramForm->SetScrollPos(SB_HORZ, curpos);
		//moving.MovingObject(classDiagramForm->diagram, newpos - curpos);
	}

}