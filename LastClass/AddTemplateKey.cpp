//AddTemplateKey.cpp

#include "AddTemplateKey.h"
#include "ClassDiagramForm.h"
#include "Selection.h"
#include "Class.h"
#include "TextEdit.h"
#include "HistoryGraphic.h"
#include "SelfRelation.h"
#include "Relation.h"
#include"RollNameBox.h"
#include "Finder.h"
#include "Diagram.h"

AddTemplateKey::AddTemplateKey() {
}

AddTemplateKey::AddTemplateKey(const AddTemplateKey& source) {
}

AddTemplateKey::~AddTemplateKey() {
}

void AddTemplateKey::KeyPress(ClassDiagramForm *classDiagramForm, CDC *cdc) {
	RollNameBox *rollNameBoxesPoint = RollNameBox::Instance();
	CPoint cPoint1;
	CPoint cPoint2;
	CPoint cPoint3;
	CPoint cPoint4;
	CPoint cPoint5;
	if (classDiagramForm->selection->GetLength() == 1 && dynamic_cast<Class*>(classDiagramForm->selection->GetAt(0))) {
		Class *object = static_cast<Class*>(classDiagramForm->selection->GetAt(0));
		if (object->GetTempletePosition() == -1) {
			classDiagramForm->historyGraphic->PushUndo(classDiagramForm->diagram, classDiagramForm->zoomRate);
			classDiagramForm->historyGraphic->redoGraphicArray->Clear();
			classDiagramForm->historyGraphic->redoGraphicZoomRateArray->Clear();

			object->AddTemplate((object->GetX() + object->GetWidth()) - 30 * classDiagramForm->zoomRate / 100,
				object->GetY() - 17 * classDiagramForm->zoomRate / 100,
				(17 * classDiagramForm->zoomRate / 100 + 30 * classDiagramForm->zoomRate / 100),
				34 * classDiagramForm->zoomRate / 100);
			Long i = 0;
			Long startX = object->GetX();
			Long startY = object->GetY();
			Long endX = object->GetX() + object->GetWidth();
			Long endY = object->GetY() + object->GetHeight();
			Long quadrant;
			Finder finder;
			while (i < object->GetLength()) {
				if (object->GetTempletePosition() != -1) {
					if (dynamic_cast<SelfRelation*>(object->GetAt(i))) {
						SelfRelation* selfRelation = static_cast<SelfRelation*>(object->GetAt(i));
						if (selfRelation->GetX() == object->GetX() + object->GetWidth() - classDiagramForm->thirty) {
							selfRelation->Move(0, -(classDiagramForm->seventeen));
							Long k = 0;
							while (k < 5) {
								CPoint cPoint(selfRelation->rollNamePoints->GetAt(k).x, selfRelation->rollNamePoints->GetAt(k).y - classDiagramForm->seventeen);
								selfRelation->rollNamePoints->Modify(k, cPoint);
								k++;
							}
						}
					}
				}

				if (dynamic_cast<Relation*>(object->GetAt(i))) {

					Relation * relation = static_cast<Relation*>(object->GetAt(i));
					quadrant = finder.FindQuadrant(relation->GetX(), relation->GetY(), startX, startY, endX, endY);
					if (relation->GetX() >= object->GetAt(object->GetTempletePosition())->GetX() - 10 && quadrant == 1) {
						relation->Modify(object->GetAt(object->GetTempletePosition())->GetX() - 10, relation->GetY(),
							relation->GetWidth() + relation->GetX() - object->GetAt(object->GetTempletePosition())->GetX() + 10, relation->GetHeight());
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

							if (relation->GetLength() % 2 == 0) {//礎熱

								CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
									relation->GetAt((relation->GetLength() - 1) / 2).y };
								CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
									relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
								cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
								relation->rollNamePoints->Modify(1, cPoint2);

							}
							else {//�汝�

								CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
									relation->GetAt((relation->GetLength() - 1) / 2).y };
								cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
								relation->rollNamePoints->Modify(1, cPoint2);

							}
						}
					}
				}
				i++;
			}
			Long j;
			Diagram * diagram = dynamic_cast<Diagram*>(classDiagramForm->diagram);
			i = 0;
			while (i<diagram->GetLength()) {
				j = 0;
				FigureComposite *figureComposite = dynamic_cast<FigureComposite*>(diagram->GetAt(i));
				while (j < figureComposite->GetLength()) {
					Figure *figure = figureComposite->GetAt(j);
					if (dynamic_cast<Relation*>(figureComposite->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(figureComposite->GetAt(j));
						Long relationEndX = figure->GetX() + figure->GetWidth();
						Long relationEndY = figure->GetY() + figure->GetHeight();
						//if (startX <= relationEndX &&  relationEndX <= endX &&
						//	startY <= relationEndY &&  relationEndY <= endY) {
						if (relation->GetEndPointFigure() == static_cast<Figure*>(object)) {
							quadrant = finder.FindQuadrant(relationEndX, relationEndY,
								startX, startY, endX, endY);

							if (relation->GetX() + relation->GetWidth() >= object->GetAt(object->GetTempletePosition())->GetX() - 10 && quadrant == 1) {

								relation->Modify(relation->GetX(), relation->GetY(), object->GetAt(object->GetTempletePosition())->GetX() - 10 - relation->GetX(),
									relation->GetHeight());

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

									if (relation->GetLength() % 2 == 0) {//礎熱

										CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
											relation->GetAt((relation->GetLength() - 1) / 2).y };
										CPoint endPoint2{ relation->GetAt((relation->GetLength() - 1) / 2 + 1).x,
											relation->GetAt((relation->GetLength() - 1) / 2 + 1).y };
										cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, endPoint2);
										relation->rollNamePoints->Modify(1, cPoint2);

									}
									else {//�汝�

										CPoint startPoint2{ relation->GetAt((relation->GetLength() - 1) / 2).x,
											relation->GetAt((relation->GetLength() - 1) / 2).y };
										cPoint2 = rollNameBoxesPoint->GetSecondRollNamePoint(startPoint2, startPoint2);
										relation->rollNamePoints->Modify(1, cPoint2);

									}
								}
							}
						}
					}
					j++;
				}
				i++;
			}
		}
	}
}

void AddTemplateKey::KeyPress(TextEdit *textEdit) {

}