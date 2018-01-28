//OnScrollEnd.cpp

#include "OnHScrollEnd.h"
#include "ClassDiagramForm.h"

OnHScrollEnd::OnHScrollEnd() : ScrollAction() {
}
OnHScrollEnd::OnHScrollEnd(const OnHScrollEnd& source) : ScrollAction(source) {
}
OnHScrollEnd::~OnHScrollEnd() {
}
OnHScrollEnd& OnHScrollEnd::operator=(const OnHScrollEnd& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnHScrollEnd::Scrolling(ClassDiagramForm *classDiagramForm) {
}