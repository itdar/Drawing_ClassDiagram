//OnVScrollEnd.cpp

#include "OnVScrollEnd.h"
#include "ClassDiagramForm.h"

OnVScrollEnd::OnVScrollEnd() : ScrollAction() {
}
OnVScrollEnd::OnVScrollEnd(const OnVScrollEnd& source) : ScrollAction(source) {
}
OnVScrollEnd::~OnVScrollEnd() {
}
OnVScrollEnd& OnVScrollEnd::operator=(const OnVScrollEnd& source) {
	ScrollAction::operator=(source);
	return *this;
}
void OnVScrollEnd::Scrolling(ClassDiagramForm *classDiagramForm) {
}