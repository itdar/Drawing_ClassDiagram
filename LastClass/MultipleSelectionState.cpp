#include "MultipleSelectionState.h"
#include "Selection.h"
#include "Relation.h"
#include "MovingVisitor.h"
#include "Diagram.h"
#include "SelfRelation.h"
#include "RollNameBox.h"
#include "ClassDiagramForm.h"
#include "HistoryGraphic.h"
#include "Line.h"
#include "Class.h"
#include "MemoBox.h"
#include "SelectionState.h"
#include "PreciseMoving.h"

#include "Generalization.h"
#include "Composition.h"
#include "Compositions.h"
#include "Dependency.h"
#include "Realization.h"

MultipleSelectionState* MultipleSelectionState::instance = 0;

MouseLButtonAction* MultipleSelectionState::Instance() {
	if (instance == 0) {
		instance = new MultipleSelectionState;
	}
	return instance;
}

void MultipleSelectionState::MouseLButtonUp(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long length = selection->GetLength();
	Long i = 0;
	Long j;
	Long k = 0;
	Long l = 0;
	Figure *figure;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;


	bool ret = false;
	while (i < selection->GetLength() && ret == false) {

		figure = selection->GetAt(i);
		if (dynamic_cast<Class*>(figure) || dynamic_cast<MemoBox*>(figure)) {
			CRect cRect1(figure->GetX() + (currentX - startX), figure->GetY() + (currentY - startY), figure->GetX() + (currentX - startX) + figure->GetWidth(), figure->GetY() + (currentY - startY) + figure->GetHeight());

		}
		i++;
	}
	i = 0;
	while (i < length && GetKeyState(VK_SHIFT) >= 0 && ret==false) { // 선택된 개수만큼 반복
		figure = selection->GetAt(i);


		if (dynamic_cast<FigureComposite*>(figure)&&ret ==false) { //클래스나 메모면
			Long startX = figure->GetX();
			Long startY = figure->GetY();
			Long endX = figure->GetX() + figure->GetWidth();
			Long endY = figure->GetY() + figure->GetHeight();
			FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환
			j = 0;
			while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
				figure = figureComposite->GetAt(j);
				
				if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
					Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
					if (relation->GetLength() == 0) {
						CPoint startPoint{ relation->GetX(), relation->GetY() };
						CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(1, cPoint2);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(3, cPoint4);
						relation->rollNamePoints->Modify(4, cPoint5);
					}
					else {
						CPoint startPoint{ relation->GetX(), relation->GetY() };
						CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
						cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
						cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
						relation->rollNamePoints->Modify(0, cPoint1);
						relation->rollNamePoints->Modify(3, cPoint4);

						CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
							relation->GetAt(relation->GetLength() - 1).y };
						CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
						cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
						cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
						relation->rollNamePoints->Modify(2, cPoint3);
						relation->rollNamePoints->Modify(4, cPoint5);

						if (relation->GetLength() % 2 == 0) {//짝수

							CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
								relation->GetAt((relation->GetLength() - 1) / 2).y };
							CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
								relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
							relation->rollNamePoints->Modify(1, cPoint2);

						}
						else {//홀수

							CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
								relation->GetAt((relation->GetLength() - 1) / 2).y };
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
							relation->rollNamePoints->Modify(1, cPoint2);

						}
					}
				}
				j++;
			}
			k = 0;
			while (k < diagram->GetLength()) {
				figureComposite = static_cast<FigureComposite*>(diagram->GetAt(k));
				l = 0;
				while (l < figureComposite->GetLength()) {
					if (dynamic_cast<Relation*>(figureComposite->GetAt(l))) {
						Relation *relation = static_cast<Relation*>(figureComposite->GetAt(l));
						Long relationEndX = relation->GetX() + relation->GetWidth();
						Long relationEndY = relation->GetY() + relation->GetHeight();
						if (relation->GetEndPointFigure() == selection->GetAt(i)) {
							if (relation->GetLength() == 0) {
								CPoint startPoint{ relation->GetX(), relation->GetY() };
								CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
								cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
								cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
								cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
								cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
								cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
								relation->rollNamePoints->Modify(0, cPoint1);
								relation->rollNamePoints->Modify(1, cPoint2);
								relation->rollNamePoints->Modify(2, cPoint3);
								relation->rollNamePoints->Modify(3, cPoint4);
								relation->rollNamePoints->Modify(4, cPoint5);
							}
							else {
								CPoint startPoint{ relation->GetX(), relation->GetY() };
								CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
								cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
								cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
								relation->rollNamePoints->Modify(0, cPoint1);
								relation->rollNamePoints->Modify(3, cPoint4);

								CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
									relation->GetAt(relation->GetLength() - 1).y };
								CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
								cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
								cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
								relation->rollNamePoints->Modify(2, cPoint3);
								relation->rollNamePoints->Modify(4, cPoint5);

								if (relation->GetLength() % 2 == 0) {//짝수

									CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
										relation->GetAt((relation->GetLength() - 1) / 2).y };
									CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
										relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
									cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
									relation->rollNamePoints->Modify(1, cPoint2);

								}
								else {//홀수

									CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
										relation->GetAt((relation->GetLength() - 1) / 2).y };
									cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
									relation->rollNamePoints->Modify(1, cPoint2);

								}
							}
							

						}

					}
					l++;
				}
				k++;
			}

		}
		i++;
	}
	if (startX == currentX && startY == currentY) {
		if (GetKeyState(VK_SHIFT) >= 0) {
			selection->DeleteAllItems();
			selection->SelectByPoint(diagram, currentX, currentY);
			if (selection->GetLength() == 0) {
				classDiagramForm->mouseLButton->ChangeDefault();
			}
			else {
				this->ChangeState(mouseLButton, SelectionState::Instance());
			}
		}
	}
}

#include "Finder.h"
#include "Class.h"
#include "MemoBox.h"

void MultipleSelectionState::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long i = 0;
	Long index = -1;
	Long shiftIndex = -1;

	index = selection->SelectByPoint(startX, startY); // 클릭 위치가 어느 선택박스인지(작은조절박스) 있는지 찾는다
													  //i++;
													  //}
	if (index == -1 && GetKeyState(VK_SHIFT) >= 0) { // 선택된 곳중에 없는데를 눌렀는데, 쉬프트키가 눌려있지 않으면
		selection->DeleteAllItems();
		selection->SelectByPoint(diagram, currentX, currentY);
		if (selection->GetLength() == 0) {
			this->ChangeDefault(mouseLButton);
		}
		else {
			this->ChangeState(mouseLButton, SelectionState::Instance());
		}
	}
	else if (index != -1 && GetKeyState(VK_SHIFT) < 0) {
		Long previousLength = selection->GetLength();
		Finder finder;
		bool ret = false;
		i = 0;
		while (i < selection->GetLength() && ret == false) {
			if (dynamic_cast<Class*>(selection->GetAt(i)) || dynamic_cast<MemoBox*>(selection->GetAt(i))) {
				CRect rct = CRect(selection->GetAt(i)->GetX(), selection->GetAt(i)->GetY(), selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth(),
					selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight());
				ret = finder.FindRectangleByPoint(rct, startX, startY);
			}
			i++;
			if (ret == true) { // 기존에 있던거면 selection 에서 지워야함
				selection->Remove(i - 1);
			}
		}
	}
	else if (index == -1 && GetKeyState(VK_SHIFT) < 0) {
		selection->SelectByPoint(diagram, startX, startY);
	}
}

void MultipleSelectionState::MouseLButtonDrag(MouseLButton *mouseLButton, ClassDiagramForm *classDiagramForm, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *pDC) {
	Long length = selection->GetLength();
	Long i = 0;
	Long j;
	Long k = 0;
	Long l = 0;
	Figure *figure;
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;

	bool ret = false;
	Long startIndex = 0;
	i = 0;
	while (ret == false && i < selection->GetLength()) {
		if ((dynamic_cast<Class*>(selection->GetAt(i)) || dynamic_cast<MemoBox*>(selection->GetAt(i)) &&
			(startX > selection->GetAt(i)->GetX() || startX < selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth()
			|| startY > selection->GetAt(i)->GetY() || startY < selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight()))) {
			startIndex = i;
			ret = true;
		}
		i++;
	}
	if (ret == true) {
		if (classDiagramForm->firstDrag == 0) {
			classDiagramForm->historyGraphic->PushUndo(diagram, classDiagramForm->zoomRate);
			classDiagramForm->historyGraphic->redoGraphicArray->Clear();
			classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

			//선택된 기호들 중에서 맨 처음 클릭된 기호의 index 넣어주면 됨(아래꺼에도) // 선 아니고 기호면 됨
			classDiagramForm->widthGab = startX - selection->GetAt(startIndex)->GetX();
			classDiagramForm->heightGab = startY - selection->GetAt(startIndex)->GetY();
			classDiagramForm->firstDrag = 1;
		}

		Long nextX = currentX - classDiagramForm->widthGab;
		Long nextY = currentY - classDiagramForm->heightGab;

		PreciseMoving temp;
		temp.ConvertPoint(&nextX, &nextY);

		Long distanceX = (nextX - selection->GetAt(startIndex)->GetX());
		Long distanceY = (nextY - selection->GetAt(startIndex)->GetY());

		bool ret2 = false;
		while (i < selection->GetLength() && ret2 == false) {

			figure = selection->GetAt(i);
			if (dynamic_cast<Class*>(figure) || dynamic_cast<MemoBox*>(figure)) {
				CRect cRect1(figure->GetX() + (currentX - startX), figure->GetY() + (currentY - startY), figure->GetX() + (currentX - startX) + figure->GetWidth(), figure->GetY() + (currentY - startY) + figure->GetHeight());
			}
			i++;
		}
		i = 0;
		while (i < length && GetKeyState(VK_SHIFT) >= 0 && ret2 == false) { // 선택된 개수만큼 반복
			figure = selection->GetAt(i);

 
			if (dynamic_cast<FigureComposite*>(figure) && ret2 == false) { //클래스나 메모면
				Long startX = figure->GetX();
				Long startY = figure->GetY();
				Long endX = figure->GetX() + figure->GetWidth();
				Long endY = figure->GetY() + figure->GetHeight();
				figure->Move(distanceX, distanceY); // 해당 클래스나 메모 이동
				FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // 형변환
				j = 0;
				while (j < figureComposite->GetLength()) { // 형변환 한게 관리하면 배열 렝스까지
					figure = figureComposite->GetAt(j);
					figure->Move(distanceX, distanceY);
					if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
						//   
						Long m = 0;
						while (m < relation->GetLength()) {
							CPoint point(relation->GetAt(m).x + distanceX, relation->GetAt(m).y + distanceY);
							relation->Move(m, point);
							m++;
						}
						if (relation->GetLength() == 0) {
							CPoint startPoint{ relation->GetX(), relation->GetY() };
							CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
							cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
							cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
							cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
							cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
							cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
							relation->rollNamePoints->Modify(0, cPoint1);
							relation->rollNamePoints->Modify(1, cPoint2);
							relation->rollNamePoints->Modify(2, cPoint3);
							relation->rollNamePoints->Modify(3, cPoint4);
							relation->rollNamePoints->Modify(4, cPoint5);
						}
						else {
							CPoint startPoint{ relation->GetX(), relation->GetY() };
							CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
							cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
							cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
							relation->rollNamePoints->Modify(0, cPoint1);
							relation->rollNamePoints->Modify(3, cPoint4);

							CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
								relation->GetAt(relation->GetLength() - 1).y };
							CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
							cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
							cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
							relation->rollNamePoints->Modify(2, cPoint3);
							relation->rollNamePoints->Modify(4, cPoint5);

							if (relation->GetLength() % 2 == 0) {//짝수

								CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
									relation->GetAt((relation->GetLength() - 1) / 2).y };
								CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
									relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
								cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
								relation->rollNamePoints->Modify(1, cPoint2);

							}
							else {//홀수

								CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
									relation->GetAt((relation->GetLength() - 1) / 2).y };
								cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
								relation->rollNamePoints->Modify(1, cPoint2);

							}
						}
					}
					if (dynamic_cast<SelfRelation*>(figureComposite->GetAt(j))) {
						SelfRelation *selfRelation = static_cast<SelfRelation*>(figureComposite->GetAt(j));
						cPoint1 = selfRelation->rollNamePoints->GetAt(0);
						cPoint1.x += distanceX;
						cPoint1.y += distanceY;
						cPoint2 = selfRelation->rollNamePoints->GetAt(1);
						cPoint2.x += distanceX;
						cPoint2.y += distanceY;
						cPoint3 = selfRelation->rollNamePoints->GetAt(2);
						cPoint3.x += distanceX;
						cPoint3.y += distanceY;
						cPoint4 = selfRelation->rollNamePoints->GetAt(3);
						cPoint4.x += distanceX;
						cPoint4.y += distanceY;
						cPoint5 = selfRelation->rollNamePoints->GetAt(4);
						cPoint5.x += distanceX;
						cPoint5.y += distanceY;
						selfRelation->rollNamePoints->Modify(0, cPoint1);
						selfRelation->rollNamePoints->Modify(1, cPoint2);
						selfRelation->rollNamePoints->Modify(2, cPoint3);
						selfRelation->rollNamePoints->Modify(3, cPoint4);
						selfRelation->rollNamePoints->Modify(4, cPoint5);
					}
					j++;
				}
				k = 0;
				while (k < diagram->GetLength()) {
					figureComposite = static_cast<FigureComposite*>(diagram->GetAt(k));
					l = 0;
					while (l < figureComposite->GetLength()) {
						if (dynamic_cast<Relation*>(figureComposite->GetAt(l))) {
							Relation *relation = static_cast<Relation*>(figureComposite->GetAt(l));
							Long relationEndX = relation->GetX() + relation->GetWidth();
							Long relationEndY = relation->GetY() + relation->GetHeight();
							if (relation->GetEndPointFigure() == selection->GetAt(i)) {
								relation->EndPointMove(distanceX, distanceY);
								//
								if (relation->GetLength() == 0) {
									CPoint startPoint{ relation->GetX(), relation->GetY() };
									CPoint endPoint{ relation->GetX() + relation->GetWidth(), relation->GetY() + relation->GetHeight() };
									cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
									cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint, endPoint);
									cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint, endPoint);
									cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
									cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint, endPoint);
									relation->rollNamePoints->Modify(0, cPoint1);
									relation->rollNamePoints->Modify(1, cPoint2);
									relation->rollNamePoints->Modify(2, cPoint3);
									relation->rollNamePoints->Modify(3, cPoint4);
									relation->rollNamePoints->Modify(4, cPoint5);
								}
								else {
									CPoint startPoint{ relation->GetX(), relation->GetY() };
									CPoint endPoint{ relation->GetAt(0).x, relation->GetAt(0).y };
									cPoint1 = rollNameBoxesPoint->GetFirstRollNamePoint(startPoint, endPoint);
									cPoint4 = rollNameBoxesPoint->GetFourthRollNamePoint(startPoint, endPoint);
									relation->rollNamePoints->Modify(0, cPoint1);
									relation->rollNamePoints->Modify(3, cPoint4);

									CPoint startPoint3{ relation->GetAt(relation->GetLength() - 1).x,
										relation->GetAt(relation->GetLength() - 1).y };
									CPoint endPoint3{ relation->GetX() + relation->GetWidth() , relation->GetY() + relation->GetHeight() };
									cPoint3 = rollNameBoxesPoint->GetThirdRollNamePoint(startPoint3, endPoint3);
									cPoint5 = rollNameBoxesPoint->GetFifthRollNamePoint(startPoint3, endPoint3);
									relation->rollNamePoints->Modify(2, cPoint3);
									relation->rollNamePoints->Modify(4, cPoint5);

									if (relation->GetLength() % 2 == 0) {//짝수

										CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
											relation->GetAt((relation->GetLength() - 1) / 2).y };
										CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
											relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
										cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
										relation->rollNamePoints->Modify(1, cPoint2);

									}
									else {//홀수

										CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
											relation->GetAt((relation->GetLength() - 1) / 2).y };
										cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
										relation->rollNamePoints->Modify(1, cPoint2);

									}
								}


							}

						}
						l++;
					}
					k++;
				}

			}
			i++;
		}
		i = 0;
		bool ret3 = false;
		while (ret3 != true && i < selection->GetLength()) {
			int vertCurPos = classDiagramForm->GetScrollPos(SB_VERT);
			int horzCurPos = classDiagramForm->GetScrollPos(SB_HORZ);
			if (selection->GetAt(i)->GetX() < -horzCurPos || selection->GetAt(i)->GetY() < -vertCurPos) {
				MovingVisitor movingVisitor;
				selection->Accept(diagram, movingVisitor, -distanceX, -distanceY);
				ret3 = true;
			}
			i++;
		}
	}
}