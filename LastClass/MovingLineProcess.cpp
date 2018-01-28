//MovingLineProcess.cpp

#include "MovingLineProcess.h"
#include "Finder.h"
#include "Class.h"
#include "ClassDiagramForm.h"

MovingLineProcess* MovingLineProcess::instance = 0;

MovingLineProcess* MovingLineProcess::Instance() {
	if (instance == 0) {
		instance = new MovingLineProcess;
	}
	return instance;
}

MovingLineProcess::MovingLineProcess() {
}
MovingLineProcess::MovingLineProcess(const MovingLineProcess& source) {
}
MovingLineProcess::~MovingLineProcess() {
}

void MovingLineProcess::MoveUpAttributeLine(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY) {
	bool ret = false;
	Finder finder;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	CPoint startPoint(0, 0);
	CPoint endPoint(0, 0);
	CRect rect{ startX - 4, startY - 4, startX + 4, startY + 4 };

	startPoint.x = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetX();
	startPoint.y = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY();
	endPoint.x = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetWidth();
	endPoint.y = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY();
	ret = finder.FindLineByArea(startPoint, endPoint, rect);

	if (ret == true) {
		selectedClass->GetAt(0)->SetHeight(currentY - selectedClass->GetAt(0)->GetY());
		if (selectedClass->GetAt(0)->GetHeight() < selectedClass->GetAt(0)->GetMinimumHeight() + GabY + MemoGab) {
			selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(0)->GetMinimumHeight() + GabY + MemoGab);
			distanceY = selectedClass->GetY() + selectedClass->GetAt(0)->GetHeight() - startPoint.y;
		}
		selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->Move(0, distanceY); // 선 이동

		selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(
			selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() + selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() -
			selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY());
		selectedClass->GetAt(selectedClass->GetAttributePosition())->SetY(
			selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY());
	}
}

void MovingLineProcess::MoveUpMethodLine(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY) {
	bool ret = false;
	Finder finder;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	CPoint startPoint(0, 0);
	CPoint endPoint(0, 0);
	CRect rect{ startX - 4, startY - 4, startX + 4, startY + 4 };

	startPoint.x = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetX();
	startPoint.y = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY();
	endPoint.x = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetWidth();
	endPoint.y = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY();
	ret = finder.FindLineByArea(startPoint, endPoint, rect);

	if (ret == true) {
		if (selectedClass->GetAttributePosition() != -1) { // attribute exist
			selectedClass->GetAt(selectedClass->GetAttributePosition())->
				SetHeight(currentY - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
			if (selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() < selectedClass->GetAt(selectedClass->GetAttributePosition())->GetMinimumHeight() + GabY) {
				selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetMinimumHeight() + GabY);
				distanceY = selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() + selectedClass->GetAt(selectedClass->GetAttributePosition())
					->GetHeight() - startPoint.y;
			}
		}
		else { // className exist
			selectedClass->GetAt(0)->SetHeight(currentY - selectedClass->GetAt(0)->GetY());
			if (selectedClass->GetAt(0)->GetHeight() < selectedClass->GetAt(0)->GetMinimumHeight() + GabY + MemoGab) {
				selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(0)->GetMinimumHeight() + GabY + MemoGab);
				distanceY = selectedClass->GetY() + selectedClass->GetAt(0)->GetHeight() - startPoint.y;
			}
		}
		selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->Move(0, distanceY);
		selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(
			selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() -
			selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY());
		selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(
			selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY());
	}
}

void MovingLineProcess::MoveUpReception(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY) {
	bool ret = false;
	Finder finder;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	CPoint startPoint(0, 0);
	CPoint endPoint(0, 0);
	CRect rect{ startX - 4, startY - 4, startX + 4, startY + 4 };

	startPoint.x = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetX();
	startPoint.y = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY();
	endPoint.x = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetWidth();
	endPoint.y = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY();

	ret = finder.FindLineByArea(startPoint, endPoint, rect);
	if (ret == true) {
		if (selectedClass->GetMethodPosition() != -1) {
			selectedClass->GetAt(selectedClass->GetMethodPosition())->
				SetHeight(currentY - selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY());
			if (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() < selectedClass->GetAt(selectedClass->GetMethodPosition())->GetMinimumHeight() + GabY) {
				selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetMinimumHeight() + GabY);
				distanceY = selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + selectedClass->GetAt(selectedClass->GetMethodPosition())
					->GetHeight() - startPoint.y;
			}
		}
		else {
			if (selectedClass->GetAttributePosition() != -1) {
				selectedClass->GetAt(selectedClass->GetAttributePosition())->
					SetHeight(currentY - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
				if (selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() <
					selectedClass->GetAt(selectedClass->GetAttributePosition())->GetMinimumHeight() + GabY) {
					selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetMinimumHeight() + GabY);
					distanceY = selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() + selectedClass->GetAt(selectedClass->GetAttributePosition())
						->GetHeight() - startPoint.y;
				}
			}
			else {
				selectedClass->GetAt(0)->SetHeight(currentY - selectedClass->GetAt(0)->GetY());
				if (selectedClass->GetAt(0)->GetHeight() < selectedClass->GetAt(0)->GetMinimumHeight() + GabY + MemoGab) {
					selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(0)->GetMinimumHeight() + GabY + MemoGab);
					distanceY = selectedClass->GetY() + selectedClass->GetAt(0)->GetHeight() - startPoint.y;
				}
			}
		}
		selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->Move(0, distanceY);
		selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(
			selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() -
			selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY());
		selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(
			selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY());
	}
}

void MovingLineProcess::MoveDownAttributeLine(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY) {
	bool ret = false;
	Finder finder;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	CPoint startPoint(0, 0);
	CPoint endPoint(0, 0);
	CRect rect{ startX - 4, startY - 4, startX + 4, startY + 4 };

	startPoint.x = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetX();
	startPoint.y = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY();
	endPoint.x = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetWidth();
	endPoint.y = selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->GetY();
	ret = finder.FindLineByArea(startPoint, endPoint, rect);

	if (ret == true) { // attribute Line
		selectedClass->GetAt(selectedClass->GetAttributePosition())->SetY(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() + distanceY);
		selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() - distanceY);
		selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() - selectedClass->GetY());

		if (selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() + selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight()
			- (selectedClass->GetAt(selectedClass->GetAttributePosition())->GetMinimumHeight() + GabY) <
			selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY()) {
			selectedClass->GetAt(selectedClass->GetAttributePosition())->SetY(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY()
				+ selectedClass->GetAt(selectedClass->GetAttributePosition())->GetHeight() - (selectedClass->GetAt(selectedClass->GetAttributePosition())->GetMinimumHeight() + GabY));
			selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetMinimumHeight() + GabY);
			//요거 위에거 헤이트를 (밑에거 겟X - 위에거 겟x)로 바꾸면됨
			selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() - selectedClass->GetY());
			//
			distanceY = selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY() - startPoint.y;
		}
		selectedClass->GetAt(selectedClass->GetAttributePosition() - 1)->Move(0, distanceY); // 선 이동
	}
}

void MovingLineProcess::MoveDownMethodLine(Class *selectedClass, Long startX, Long startY, Long currentX, Long currentY) {
	bool ret = false;
	Finder finder;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	CPoint startPoint(0, 0);
	CPoint endPoint(0, 0);
	CRect rect{ startX - 4, startY - 4, startX + 4, startY + 4 };

	startPoint.x = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetX();
	startPoint.y = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY();
	endPoint.x = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetWidth();
	endPoint.y = selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->GetY();
	ret = finder.FindLineByArea(startPoint, endPoint, rect);

	if (ret == true) { // method line
		if (selectedClass->GetAttributePosition() != -1) {
			selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + distanceY);
			selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - distanceY);
			selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
			if (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight()
				- (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetMinimumHeight() + GabY) <
				selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY()) {
				selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY()
					+ selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetMinimumHeight() + GabY));
				selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetMinimumHeight() + GabY);
				selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
				distanceY = selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - startPoint.y;
			}
		}
		else {
			selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + distanceY);
			selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - distanceY);
			selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - selectedClass->GetY());
			if (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() + selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight()
				- (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetMinimumHeight() + GabY) <
				selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY()) {
				selectedClass->GetAt(selectedClass->GetMethodPosition())->SetY(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY()
					+ selectedClass->GetAt(selectedClass->GetMethodPosition())->GetHeight() - (selectedClass->GetAt(selectedClass->GetMethodPosition())->GetMinimumHeight() + GabY));
				selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetMinimumHeight() + GabY);
				selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - selectedClass->GetY());
				distanceY = selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY() - startPoint.y;
			}
		}
		selectedClass->GetAt(selectedClass->GetMethodPosition() - 1)->Move(0, distanceY);
	}
}

void MovingLineProcess::MoveDownReception(Class *selectedClass, Long  startX, Long startY, Long currentX, Long currentY) {
	bool ret = false;
	Finder finder;
	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	CPoint startPoint(0, 0);
	CPoint endPoint(0, 0);
	CRect rect{ startX - 4, startY - 4, startX + 4, startY + 4 };

	startPoint.x = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetX();
	startPoint.y = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY();
	endPoint.x = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetX() + selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetWidth();
	endPoint.y = selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->GetY();

	ret = finder.FindLineByArea(startPoint, endPoint, rect);
	if (ret == true) {
		if (selectedClass->GetMethodPosition() != -1) {
			selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + distanceY);
			selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - distanceY);
			selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY());
			if (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight()
				- (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetMinimumHeight() + GabY) <
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()) {
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()
					+ selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetMinimumHeight() + GabY));
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetMinimumHeight() + GabY);
				selectedClass->GetAt(selectedClass->GetMethodPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetAt(selectedClass->GetMethodPosition())->GetY());
				distanceY = selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - startPoint.y;
			}
		}

		else if (selectedClass->GetMethodPosition() == -1 && selectedClass->GetAttributePosition() != -1) {
			selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + distanceY);
			selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - distanceY);
			selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
			if (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight()
				- (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetMinimumHeight() + GabY) <
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()) {
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()
					+ selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetMinimumHeight() + GabY));
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetMinimumHeight() + GabY);
				selectedClass->GetAt(selectedClass->GetAttributePosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetAt(selectedClass->GetAttributePosition())->GetY());
				distanceY = selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - startPoint.y;
			}
		}
		else if (selectedClass->GetMethodPosition() == -1 && selectedClass->GetAttributePosition() == -1) {
			selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + distanceY);
			selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - distanceY);
			selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetY());
			if (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() + selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight()
				- (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetMinimumHeight() + GabY) <
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()) {
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetY(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY()
					+ selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetHeight() - (selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetMinimumHeight() + GabY));
				selectedClass->GetAt(selectedClass->GetReceptionPosition())->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetMinimumHeight() + GabY);
				selectedClass->GetAt(0)->SetHeight(selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - selectedClass->GetY());
				distanceY = selectedClass->GetAt(selectedClass->GetReceptionPosition())->GetY() - startPoint.y;
			}
		}
		selectedClass->GetAt(selectedClass->GetReceptionPosition() - 1)->Move(0, distanceY);
	}
}