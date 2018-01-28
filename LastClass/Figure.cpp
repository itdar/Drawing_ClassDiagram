//Figure.cpp

#include "Figure.h"
#include "Relation.h"

#include "LastClass.h"
#include "ClassDiagramForm.h"

Figure::Figure() {
	LastClass *test = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->content = "";
	this->minimumWidth = 120 * test->classDiagramForm->zoomRate / 100;
	this->minimumHeight = 29 * test->classDiagramForm->zoomRate / 100;
	this->fontSize = 25;
	this->endPointFigure = 0;
}

Figure::Figure(Long x, Long y, Long width, Long height) {
	LastClass *test = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->content = "";
	this->minimumWidth = 120 * test->classDiagramForm->zoomRate / 100;
	this->minimumHeight = 29 * test->classDiagramForm->zoomRate / 100;
	this->fontSize = 25;
	this->endPointFigure = 0;
}

Figure::Figure(Long x, Long y, Long width, Long height, string content) {
	LastClass *test = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->content = content;
	this->minimumWidth = 120 * test->classDiagramForm->zoomRate / 100; //여기도
	this->minimumHeight = 29 * test->classDiagramForm->zoomRate / 100; // 입력받을 문자열에 맞게 값 줘야하는데
	this->fontSize = 25;
	this->endPointFigure = 0;
}

Figure::Figure(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, string content) {
	LastClass *test = (LastClass*)(CFrameWnd::FindWindow(NULL, "lastClass"));
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->content = content;
	this->minimumWidth = minimumHeight;
	this->minimumHeight = minimumHeight;
	this->fontSize = 25;	
	this->endPointFigure = 0;
}

Figure::Figure(const Figure& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->content = source.content;
	this->minimumWidth = source.minimumWidth;
	this->minimumHeight = source.minimumHeight;
	this->fontSize = source.fontSize;
	this->endPointFigure = source.endPointFigure;
}

Long Figure::GetRowCount(string object) {
	Long count = 0;
	Long i = 0;
	while (object[i] != '\0') {
		if (object[i] == '\n') {
			count++;
		}
		i++;
	}
	//if (i != 0) {
		count++; // 한줄이 생략되기때문에 증가해줌.
//	}
	return count;
}

void Figure::ReplaceString(string content, Long fontSize) {
	this->content = content;
	this->fontSize = fontSize;
}
void Figure::SetX(Long x) {
	this->x = x;
}
void Figure::SetY(Long y) {
	this->y = y;
}
void Figure::SetWidth(Long width) {
	this->width = width;
}
void Figure::SetHeight(Long height) {
	this->height = height;
}
void Figure::SetMinimumWidth(Long minimumWidth) {
	this->minimumWidth = minimumWidth;
}
void Figure::SetMinimumHeight(Long minimumHeight) {
	this->minimumHeight = minimumHeight;
}
Figure* Figure::Move(Long distanceX, Long distanceY) {
	this->x = this->x + distanceX;
	this->y = this->y + distanceY;
	if (dynamic_cast<Relation*>(this)) {
		this->width = this->width - distanceX;
		this->height = this->height - distanceY;
	}
	return this;
}

Figure *Figure::EndPointMove(Long distanceX, Long distanceY) {
	this->width = this->width + distanceX;
	this->height = this->height + distanceY;
	return this;
}

Figure* Figure::Modify(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	return this;
}

Figure& Figure::operator = (const Figure& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->minimumWidth = source.minimumWidth;
	this->minimumHeight = source.minimumHeight;
	this->fontSize = source.fontSize;
	this->endPointFigure = source.endPointFigure;

	return *this;
}
 Figure* Figure::SetEndPointFigure(Figure *figure) {
	this->endPointFigure = figure;
	return this->endPointFigure;
}
Figure::~Figure() {
}