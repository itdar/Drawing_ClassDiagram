//ClassDiagramForm.cpp

#include "LastClass.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "Selection.h"
#include "Template.h"
#include "ClassName.h"
#include "Method.h"
#include "Attribute.h"
#include "Reception.h"
#include "Line.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "MemoLine.h"
#include "SelfAggregation.h"
#include "SelfAggregations.h"
#include "SelfAssociation.h"
#include "SelfComposition.h"
#include "SelfCompositions.h"
#include "SelfDependency.h"
#include "SelfDirectedAssociation.h"
#include "SelfGeneralization.h"
#include "SelfRelation.h"
#include "Figure.h"
#include "Finder.h"
#include "FigureFactory.h"
#include "DrawingVisitor.h"
#include "MovingVisitor.h"
#include "MouseLButton.h"
#include "HistoryGraphic.h"
#include "KeyBoard.h"
#include "KeyAction.h"
#include "ClassDiagramFormMenu.h"
#include "ToolBar.h"
#include "StatusBar.h"
#include "MenuAction.h"
#include "Scroll.h"
#include "ScrollAction.h"
#include "GraphicCtrlCopyKey.h"
#include "ResizeVisitor.h"
#include "KnockKnock.h"
#include "ScrollMovingObject.h"
#include "OnVScrollPageDown.h"
#include "OnVScrollPageUp.h"
#include "OnHScrollPageRight.h"
#include "OnHScrollPageLeft.h"
#include "SelectionState.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <afxmsg_.h>
#include <afxext.h>
#include <afxdlgs.h>

using namespace std;

Long MemoGab = 20;
Long GabX = 8;
Long GabY = 2;
Long CaretWidth = 2;

BEGIN_MESSAGE_MAP(ClassDiagramForm, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND_RANGE(100, 140, OnMyMenu)
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_NCMOUSEMOVE()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm(LastClass *lastClass) { // 생성자 맞는듯
	this->lastClass = lastClass;
	this->diagram = NULL;
	this->textEdit = NULL;
	this->selection = NULL;
	this->mouseLButton = NULL;
	this->keyBoard = NULL;
	this->historyGraphic = NULL;
	this->scroll = NULL;
	this->classDiagramFormMenu = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->fileName = "";
	this->copyBuffer = NULL;
	this->isCut = 0;
	this->preZoom = 100;
	this->capsLockFlag = 0;
	this->numLockFlag = 0;
	this->zoomRate = 100;
	this->isDown = 0;
	this->startX_ = 0;
	this->startY_ = 0;
	this->currentX_ = 0;
	this->currentY_ = 0;
	this->thirty = 30;
	this->seventeen = 17;
	this->widthGab = 0;
	this->heightGab = 0;
	this->firstDrag = 0;
}

Long ClassDiagramForm::Load() {
	Long position = -1;
	Long i;
	Long x = 0;
	Long y = 0;
	Long width = 0;
	Long height = 0;
	Long length = 0;
	Long minimumWidth = 0;
	Long minimumHeight = 0;
	Long index;
	Long type = 0;
	Long relationLength = 0;
	FigureFactory factory;
	Figure *figure;
	ifstream fTest;
	Long j;
	Long l;
	Long classIndex;
	Long figureIndex;
	Long endPointIndex;
	Long rowLength = 0;
	Long fontSize = 0;
	string temp1;
	string temp2;
	Array<Long> classIndexArray(50000);
	Array<Long> figureIndexArray(50000);
	Array<Long> endPointIndexArray(50000);
	Long zoomRate;
	SCROLLINFO vScinfo = { 0, };
	SCROLLINFO hScinfo = { 0, };
	int vertCurPos;
	int horzCurPos;
	int maxVScroll;
	int maxHScroll;
	fTest.open(this->fileName);
	//fTest.open("text.txt");
	//종류 구별을 위한 마지막 칸 
	// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 6 = Dependency(의존), 7 = Association(연관화),
	// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관), 13 = MemoLine
	// 14 = ClassName , 15 = Attribute , 16 = Method , 17 = Reception

	if (fTest.is_open()) {
		getline(fTest, temp1);
		sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d", &zoomRate, &horzCurPos, &maxHScroll, &vertCurPos, &maxVScroll);
		this->zoomRate = zoomRate;
		vScinfo.cbSize = sizeof(SCROLLINFO);
		vScinfo.fMask = SIF_ALL;
		vScinfo.nMin = 0;
		vScinfo.nMax = maxVScroll;
		vScinfo.nPos = vertCurPos;
		hScinfo.cbSize = sizeof(SCROLLINFO);
		hScinfo.fMask = SIF_ALL;
		hScinfo.nMin = 0;
		hScinfo.nMax = maxHScroll;
		hScinfo.nPos = horzCurPos;
		this->SetScrollInfo(SB_VERT, &vScinfo);
		this->SetScrollInfo(SB_HORZ, &hScinfo);
		getline(fTest, temp1);
		sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d %d %d %d", &length, &x, &y, &width, &height, &minimumWidth, &minimumHeight, &type);
		while (!fTest.eof()) {
			figure = factory.Create(x, y, width, height, minimumWidth, minimumHeight, type);
			position = this->diagram->Add(figure);
			FigureComposite *figureComposite = static_cast<FigureComposite*>(this->diagram->GetAt(position));
			if (type == 7) {   //메모박스이면
				getline(fTest, temp1);
				sscanf_s((CString)temp1.c_str(), "%d %d", &fontSize, &rowLength);
				j = 0;
				temp2.clear();
				while (j < rowLength) {
					getline(fTest, temp1);
					temp2.append(temp1);
					temp2.append("\n");
					j++;
				}
				Long k = temp2.find_last_of('\n');
				temp2.replace(k, 1, "\0");
				figureComposite->ReplaceString(temp2, fontSize);

			}
			i = 0;
			while (position != -1 && i < length) {
				getline(fTest, temp1);
				sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d %d %d", &x, &y, &width, &height, &minimumWidth, &minimumHeight, &type); //말단객체
				figure = factory.Create(x, y, width, height, minimumWidth, minimumHeight, type);

				if (type < 7 && type != 2) {
					getline(fTest, temp1);
					sscanf_s((CString)temp1.c_str(), "%d %d", &fontSize, &rowLength);
					temp2.clear();
					j = 0;
					while (j < rowLength) {
						getline(fTest, temp1);
						temp2.append(temp1);
						temp2.append("\n");
						j++;
					}
					Long k = temp2.find_last_of('\n');
					temp2.replace(k, 1, "\0");
					figure->ReplaceString(temp2, fontSize);
					if (type == 3) {
						static_cast<Class*>(figureComposite)->Add(static_cast<Attribute*>(figure));
					}
					else if (type == 4) {
						static_cast<Class*>(figureComposite)->Add(static_cast<Method*>(figure));
					}
					else if (type == 5) {
						static_cast<Class*>(figureComposite)->Add(static_cast<Reception*>(figure));
					}
					else if (type == 6) {
						static_cast<Class*>(figureComposite)->Add(static_cast<Template*>(figure));
					}
					else {
						figureComposite->Add(figure);
					}
				}
				if (type >= 8 && type <= 17) {
					getline(fTest, temp1);
					sscanf_s((CString)temp1.c_str(), "%d %d %d %d", &relationLength, &classIndex, &figureIndex, &endPointIndex);
					classIndexArray.AppendFromFront(classIndex);
					figureIndexArray.AppendFromFront(figureIndex);
					endPointIndexArray.AppendFromFront(endPointIndex);
					Long cPointX;
					Long cPointY;
					CPoint cPoint;
					index = figureComposite->Add(figure);
					Relation *relation = static_cast<Relation*>(figureComposite->GetAt(index));
					j = 0;
					while (j < relationLength) {
						getline(fTest, temp1);
						sscanf_s((CString)temp1.c_str(), "%d %d", &cPointX, &cPointY);
						cPoint.x = cPointX;
						cPoint.y = cPointY;
						relation->Add(cPoint);
						j++;
					}
					if (type != 8) {
						l = 0;
						while (l < 5) {
							getline(fTest, temp1);
							if (temp1 != "") {
								relation->rollNames->Modify(l, temp1);
							}
							getline(fTest, temp1);
							sscanf_s((CString)temp1.c_str(), "%d %d", &cPointX, &cPointY);
							cPoint.x = cPointX;
							cPoint.y = cPointY;
							relation->rollNamePoints->Modify(l, cPoint);
							l++;
						}
					}
				}
				if (type >= 18 && type <= 25) {
					Long cPointX;
					Long cPointY;
					CPoint cPoint;
					index = figureComposite->Add(figure);
					SelfRelation *selfRelation = static_cast<SelfRelation*>(figureComposite->GetAt(index));
					l = 0;
					if (selfRelation->GetX() < figureComposite->GetX() + (figureComposite->GetWidth() / 2)) {
						selfRelation->leftRightFlag = 1;
					}
					while (l < 5) {
						getline(fTest, temp1);
						if (temp1 != "") {
							selfRelation->rollNames->Modify(l, temp1);
						}
						getline(fTest, temp1);
						sscanf_s((CString)temp1.c_str(), "%d %d", &cPointX, &cPointY);
						cPoint.x = cPointX;
						cPoint.y = cPointY;
						selfRelation->rollNamePoints->Modify(l, cPoint);
						l++;
					}
				}
				if (type == 2) {
					figureComposite->Add(figure);
				}
				i++;
			}
			getline(fTest, temp1);
			sscanf_s((CString)temp1.c_str(), "%d %d %d %d %d %d %d %d", &length, &x, &y, &width, &height, &minimumWidth, &minimumHeight, &type);
		}

		i = 0;
		while (i < endPointIndexArray.GetLength()) {
			FigureComposite *figureComposite = static_cast<FigureComposite*>(diagram->GetAt(classIndexArray.GetAt(i)));
			Relation *relation = static_cast<Relation*>(figureComposite->GetAt(figureIndexArray.GetAt(i)));
			relation->SetEndPointFigure(diagram->GetAt(endPointIndexArray.GetAt(i)));
			i++;
		}
		ScrollMovingObject moving;
		//moving.MovingObject(this->diagram, -hScinfo.nPos, -vScinfo.nPos);
	}

	fTest.close();

	return this->diagram->GetLength();
}

Long ClassDiagramForm::Save() {
	Long k;
	Long i = 0;
	Long j;
	Long l;
	Long rowLength;
	Long fontSize;
	FigureComposite *object = 0;
	Figure *figure = 0;
	SelfRelation *selfRelation = 0;
	CPoint cPoint;
	string saveText;
	ofstream fTest;
	ScrollMovingObject moving;
	SCROLLINFO hScinfo;
	SCROLLINFO vScinfo;

	fTest.open(this->fileName);
	if (fTest.is_open()) {
		Long zoomRate = this->zoomRate;
		this->GetScrollInfo(SB_HORZ, &hScinfo);
		this->GetScrollInfo(SB_VERT, &vScinfo);
		//moving.MovingObject(this->diagram, hScinfo.nPos, vScinfo.nPos);
		fTest << zoomRate << " " << hScinfo.nPos << " " << hScinfo.nMax << " " << vScinfo.nPos << " " << vScinfo.nMax << endl;
		while (i < this->diagram->GetLength()) {
			//종류 구별을 위한 마지막 칸 
			// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 
			//6 = Dependency(의존), 7 = Association(연관화),
			// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 
			//11 =  Composition(합성), 12 = Compositions(복합연관), 13 = MemoLine
			// 14 = ClassName , 15 = Attribute , 16 = Method , 17 = Reception , 18 =SelfGeneralization ,
			//19 = SelfDependency , 20 = SelfAssociation , 21 = SelfDirectedAssociation
			// 22 = SelfAggregation , 23 = SelfAggregations , 24 =SelfComposition , 25 = SelfCompositions
			j = 0;
			if (dynamic_cast<Class*>(this->diagram->GetAt(i))) {
				object = static_cast<FigureComposite*>(this->diagram->GetAt(i));
				fTest << object->GetLength() << " " << object->GetX() << " " << object->GetY()
					<< " " << object->GetWidth() << " " << object->GetHeight() << " " << object->GetMinimumWidth() << " " << object->GetMinimumHeight() << " " << 0 << endl;
				while (j < object->GetLength())
				{
					k = 0;
					l = 0;
					if (dynamic_cast<ClassName*>(object->GetAt(j))) {
						figure = static_cast<ClassName*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 1 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Line*>(object->GetAt(j))) {
						figure = object->GetAt(j);
						fTest << figure->GetX() << " " << figure->GetY() << " " <<
							figure->GetWidth() << " " << figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 2 << endl;
					}
					else if (dynamic_cast<Attribute*>(object->GetAt(j))) {
						figure = static_cast<Attribute*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 3 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Method*>(object->GetAt(j))) {
						figure = static_cast<Method*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 4 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Reception*>(object->GetAt(j))) {
						figure = static_cast<Reception*>(object->GetAt(j));
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " << figure->GetWidth() << " "
							<< figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 5 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<Template*>(object->GetAt(j))) {
						figure = object->GetAt(j);
						fontSize = figure->GetFontSize();
						rowLength = figure->GetRowCount(figure->GetContent());
						fTest << figure->GetX() << " " << figure->GetY() << " " <<
							figure->GetWidth() << " " << figure->GetHeight() << " " << figure->GetMinimumWidth() << " " << figure->GetMinimumHeight() << " " << 6 << endl;
						fTest << fontSize << " " << rowLength << endl;
						fTest << figure->GetContent() << endl;
					}
					else if (dynamic_cast<MemoLine*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 8 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
					}
					else if (dynamic_cast<Generalization*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 9 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Realization*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 10 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Dependency*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 11 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Association*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 12 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<DirectedAssociation*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 13 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Aggregation*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 14 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Aggregations*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 15 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}

					else if (dynamic_cast<Composition*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 16 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<Compositions*>(object->GetAt(j))) {
						Relation *relation = static_cast<Relation*>(object->GetAt(j));
						Long index = 0;
						while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
							index++;
						}
						fTest << relation->GetX() << " " << relation->GetY() << " " <<
							relation->GetWidth() << " " << relation->GetHeight() << " " << index << " " << relation->GetMinimumHeight() << " " << 17 << endl;
						fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
						while (k < relation->GetLength()) {
							cPoint = relation->GetAt(k);
							fTest << cPoint.x << " " << cPoint.y << endl;
							k++;
						}
						while (l < 5) {
							fTest << relation->rollNames->GetAt(l) << endl;;
							fTest << relation->rollNamePoints->GetAt(l).x << " " << relation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}

					else if (dynamic_cast<SelfGeneralization*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " "
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 18 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfDependency*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " "
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 19 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}

					}
					else if (dynamic_cast<SelfAssociation*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " "
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 20 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfDirectedAssociation*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " "
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 21 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfAggregation*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " "
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 22 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					else if (dynamic_cast<SelfAggregations*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " "
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 23 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						};

					}
					else if (dynamic_cast<SelfComposition*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " "
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 24 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}

					}
					else if (dynamic_cast<SelfCompositions*>(object->GetAt(j))) {
						selfRelation = static_cast<SelfRelation*>(object->GetAt(j));
						fTest << selfRelation->GetX() << " " << selfRelation->GetY() << " " << selfRelation->GetWidth() << " " << selfRelation->GetHeight() << " "
							<< selfRelation->GetMinimumWidth() << " " << selfRelation->GetMinimumHeight() << " " << 25 << endl;
						while (l < 5) {
							fTest << selfRelation->rollNames->GetAt(l) << endl;;
							fTest << selfRelation->rollNamePoints->GetAt(l).x << " " << selfRelation->rollNamePoints->GetAt(l).y << endl;
							l++;
						}
					}
					j++;
				}
			}
			else if (dynamic_cast<MemoBox*>(this->diagram->GetAt(i))) {
				object = static_cast<FigureComposite*>(this->diagram->GetAt(i));
				fontSize = object->GetFontSize();
				rowLength = object->GetRowCount(object->GetContent());
				fTest << object->GetLength() << " " << object->GetX() << " " << object->GetY()
					<< " " << object->GetWidth() << " " << object->GetHeight() << " " << object->GetMinimumWidth() << " " << object->GetMinimumHeight() << " " << 7 << endl;;
				fTest << fontSize << " " << rowLength << endl;
				fTest << object->GetContent() << endl;
				while (j < object->GetLength()) {
					Relation *relation = static_cast<Relation*>(object->GetAt(j));
					Long index = 0;
					while (relation->GetEndPointFigure() != diagram->GetAt(index)) {
						index++;
					}
					fTest << relation->GetX() << " " << relation->GetY() << " " <<
						relation->GetWidth() << " " << relation->GetHeight() << " " << relation->GetMinimumWidth() << " " << relation->GetMinimumHeight() << " " << 8 << endl;
					fTest << relation->GetLength() << " " << i << " " << j << " " << index << endl;
					while (k < relation->GetLength()) {
						cPoint = relation->GetAt(k);
						fTest << cPoint.x << " " << cPoint.y << endl;
						k++;
					}
					j++;
				}
			}
			i++;
		}
		//moving.MovingObject(this->diagram, -hScinfo.nPos, -vScinfo.nPos);
		fTest.close();
	}
	if (this->historyGraphic->undoGraphicArray->GetLength() != 0) {
		this->historyGraphic->undoGraphicArray->Clear();
		this->historyGraphic->redoGraphicArray->Clear();
	}

	return this->diagram->GetLength();
}
CString ClassDiagramForm::SetFileName(CString fileName) {
	this->fileName = fileName;
	return this->fileName;
}

int ClassDiagramForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {

	CWnd::OnCreate(lpCreateStruct); //코드재사용 오버라이딩 //상속에서
	CWnd::SetFocus();                        //1.1. 다이어그램을 준비한다

	this->diagram = new Diagram();
	this->selection = new Selection();
	this->mouseLButton = new MouseLButton;
	this->historyGraphic = new HistoryGraphic;
	this->keyBoard = new KeyBoard;
	this->scroll = new Scroll;
	this->classDiagramFormMenu = new ClassDiagramFormMenu(this);
	CRect rect;
	this->GetClientRect(&rect);
	ModifyStyle(0, WS_CLIPCHILDREN);

	SCROLLINFO vScinfo;
	SCROLLINFO hScinfo;
	vScinfo.cbSize = sizeof(vScinfo);
	vScinfo.fMask = SIF_ALL;
	vScinfo.nMin = 0;
	vScinfo.nMax = 2000;
	vScinfo.nPage = rect.bottom;
	vScinfo.nPos = 0;
	this->SetScrollInfo(SB_VERT, &vScinfo);

	hScinfo.cbSize = sizeof(hScinfo);
	hScinfo.fMask = SIF_ALL;
	hScinfo.nMin = 0;
	hScinfo.nMax = 4000;
	hScinfo.nPage = rect.right;
	hScinfo.nTrackPos = 0;
	hScinfo.nPos = 0;
	this->SetScrollInfo(SB_HORZ, &hScinfo);

	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) {
		this->capsLockFlag = 1;
	}
	else {
		this->capsLockFlag = 0;
	}
	if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
		this->numLockFlag = 1;
	}
	else {
		this->numLockFlag = 0;
	}


	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);
	CDC memDC;
	CBitmap *pOldBitmap;
	CBitmap bitmap;
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(CRect(0, 0, rect.Width(), rect.Height()), RGB(255, 255, 255));
	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	int ih = MulDiv(14 * this->zoomRate / 100, GetDeviceCaps(dc, LOGPIXELSY), 72);
	cFont.CreateFont(ih, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
	SetFont(&cFont, TRUE);
	CFont *oldFont = memDC.SelectObject(&cFont);
	if (this->currentX_2 != 0 && this->currentY_2 != 0 && this->currentX != 0 && this->currentY != 0) {
		this->mouseLButton->MouseLButtonDrag(this->mouseLButton, this, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY, &memDC);
	}
	DrawingVisitor drawingVisitor(this->zoomRate);
	this->diagram->Accept(drawingVisitor, &memDC);
	if (this->selection->GetLength() > 0) {
		this->selection->Accept(drawingVisitor, &memDC);
	}
	ScrollMovingObject movingObject;
	Long xlimit = 0;
	xlimit = movingObject.GetHorizontalMax(this->diagram);
	SCROLLINFO hScinfo;
	this->GetScrollInfo(SB_HORZ, &hScinfo);
	if (hScinfo.nMax - hScinfo.nPos <= xlimit) {
		hScinfo.nMax = hScinfo.nPos + xlimit + 20;
		this->SetScrollInfo(SB_HORZ, &hScinfo);
	}
	if (hScinfo.nPage > xlimit) {
		hScinfo.nMax = hScinfo.nPos + hScinfo.nPage;
		if (hScinfo.nMax < 4000 * this->zoomRate / 100) {
			hScinfo.nMax = 4000 * this->zoomRate / 100;
		}
		if (hScinfo.nMax < hScinfo.nPage) {
			hScinfo.nMax = hScinfo.nPage;
		}
		this->SetScrollInfo(SB_HORZ, &hScinfo);
	}

	Long ylimit = 0;
	ylimit = movingObject.GetVerticalMax(this->diagram);
	SCROLLINFO vScinfo;
	this->GetScrollInfo(SB_VERT, &vScinfo);
	if (vScinfo.nMax - vScinfo.nPos <= ylimit) {
		vScinfo.nMax = vScinfo.nPos + ylimit + 20;
		this->SetScrollInfo(SB_VERT, &vScinfo);
	}
	if (vScinfo.nPage > ylimit) {
		vScinfo.nMax = vScinfo.nPos + vScinfo.nPage;
		if (vScinfo.nMax < 2000 * this->zoomRate / 100) {
			vScinfo.nMax = 2000 * this->zoomRate / 100;
		}
		if (vScinfo.nMax < vScinfo.nPage) {
			vScinfo.nMax = vScinfo.nPage;
		}
		this->SetScrollInfo(SB_VERT, &vScinfo);
	}
	dc.BitBlt(0, 0, rect.right, rect.bottom, &memDC, 0, 0, SRCCOPY);
}

void ClassDiagramForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == 0 || nChar == 49 || nChar == 81 || nChar == 50 || nChar == 55 || nChar == 56 || nChar == 53 ||
		nChar == 57 || nChar == 48 || nChar == 52 || nChar == 54 || nChar == 87 || nChar == 51) {
		this->mouseLButton->ChangeState(nChar);
	}
	if (nChar == VK_CAPITAL) {
		if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) {
			this->capsLockFlag = 1;
		}
		else {
			this->capsLockFlag = 0;
		}
		this->lastClass->statusBar->DestroyStatus();
		this->lastClass->statusBar->MakeStatusBar(this->lastClass, this->lastClass->GetSafeHwnd(), 0, 0, 5);
	}
	if (nChar == VK_NUMLOCK) {
		if ((GetKeyState(VK_NUMLOCK) & 0x0001) != 0) {
			this->numLockFlag = 1;
		}
		else {
			this->numLockFlag = 0;
		}
		this->lastClass->statusBar->DestroyStatus();
		this->lastClass->statusBar->MakeStatusBar(this->lastClass, this->lastClass->GetSafeHwnd(), 0, 0, 5);
	}

	CClientDC dc(this);
	CFont cFont;//CreateFont에 값18을 textEdit의 rowHight로 바꿔야함
	cFont.CreateFont(14 * this->zoomRate / 100 * 120 / 72, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET,// 글꼴 설정
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "굴림체");
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont);
	KeyAction *keyAction = this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);
	if (keyAction != 0) {
		keyAction->KeyPress(this, &dc);
		Invalidate(false);
	}
	dc.SelectObject(oldFont);
	cFont.DeleteObject();
}

void ClassDiagramForm::OnSetFocus(CWnd* pOldWnd) {
	CWnd::OnSetFocus(pOldWnd);
	CWnd::SetFocus();
	Invalidate(false);
}
void ClassDiagramForm::OnSize(UINT nType, int cx, int cy) {
	CWnd::OnSize(nType, cx, cy);
	CPaintDC dc(this);

	CRect rect;
	this->GetClientRect(&rect);
	SCROLLINFO vScinfo;
	SCROLLINFO hScinfo;
	this->GetScrollInfo(SB_VERT, &vScinfo);
	this->GetScrollInfo(SB_HORZ, &hScinfo);

	vScinfo.nPage = rect.Height();
	hScinfo.nPage = rect.Width();


	this->SetScrollInfo(SB_VERT, &vScinfo);
	this->SetScrollInfo(SB_HORZ, &hScinfo);

	Invalidate(false);
}

void ClassDiagramForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	SetFocus();
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
	Long pos = this->GetScrollPos(SB_VERT);
	ScrollAction *scrollAction = this->scroll->MoveVScroll(this, nSBCode, nPos, pScrollBar);
	if (scrollAction != 0) {
		scrollAction->Scrolling(this);
	}
	Long cPos = this->GetScrollPos(SB_VERT);
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) {
		ScrollMovingObject movingObject;
		movingObject.MovingObject(this->diagram, 0, pos - cPos);
		if (pos - cPos>0) {
			SCROLLINFO vScinfo;
			this->GetScrollInfo(SB_VERT, &vScinfo);
			int vMax = vScinfo.nMax;
			bool ret = movingObject.FindHorizontal(this->diagram, vScinfo.nPage);
			if (ret == false)
				vScinfo.nMax = vScinfo.nMax - (pos - cPos);
			if (vScinfo.nMax < vMax) {
				vScinfo.nMax = vMax;
			}
			this->SetScrollInfo(SB_VERT, &vScinfo);
		}
	}
	Invalidate(false);
}

void ClassDiagramForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	SetFocus();
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
	Long pos = this->GetScrollPos(SB_HORZ);
	ScrollAction *scrollAction = this->scroll->MoveHScroll(this, nSBCode, nPos, pScrollBar);
	if (scrollAction != 0) {
		scrollAction->Scrolling(this);
	}
	Long cPos = this->GetScrollPos(SB_HORZ);
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) {
		ScrollMovingObject movingObject;
		movingObject.MovingObject(this->diagram, pos - cPos);
		if (pos - cPos>0) {
			SCROLLINFO vScinfo;
			this->GetScrollInfo(SB_HORZ, &vScinfo);
			int hMax = vScinfo.nMax;
			bool ret = movingObject.FindHorizontal(this->diagram, vScinfo.nPage);
			if (ret == false)
				vScinfo.nMax = vScinfo.nMax - (pos - cPos);
			if (vScinfo.nMax < hMax) {
				vScinfo.nMax = hMax;
			}
			this->SetScrollInfo(SB_HORZ, &vScinfo);
		}
	}
	Invalidate(false);
}
void ClassDiagramForm::OnRButtonUp(UINT nFlags, CPoint point) {
	SetFocus();

	int hPos = this->GetScrollPos(SB_HORZ);
	int vPos = this->GetScrollPos(SB_VERT);
	this->startX = point.x + hPos;
	this->startY = point.y + vPos;
	this->currentX = point.x;
	this->currentY = point.y;


	CMenu *menu = 0;
	if (this->selection->GetLength() == 1) {
		menu = this->classDiagramFormMenu->menu2;
		Figure *figure = this->selection->GetAt(0);
		if ((dynamic_cast<Class*>(figure))) {
			Class *object = static_cast<Class*>(figure);
			if (object->GetAttributePosition() != -1) {
				menu->EnableMenuItem(135, MF_DISABLED);
				menu->EnableMenuItem(131, MF_ENABLED);//135추가 131 제거
			}
			else {
				menu->EnableMenuItem(131, MF_DISABLED);
				menu->EnableMenuItem(135, MF_ENABLED);
			}
			if (object->GetMethodPosition() != -1) {
				menu->EnableMenuItem(130, MF_DISABLED);
				menu->EnableMenuItem(132, MF_ENABLED);//130 추가 132 제거
			}
			else {
				menu->EnableMenuItem(132, MF_DISABLED);
				menu->EnableMenuItem(130, MF_ENABLED);
			}
			if (object->GetReceptionPosition() != -1) {
				menu->EnableMenuItem(134, MF_ENABLED);
				menu->EnableMenuItem(133, MF_DISABLED);
				//133추가 134 제거
			}
			else {
				menu->EnableMenuItem(134, MF_DISABLED);
				menu->EnableMenuItem(133, MF_ENABLED);
			}
			if (object->GetTempletePosition() != -1) {
				//127 추가 128 제거
				menu->EnableMenuItem(128, MF_ENABLED);
				menu->EnableMenuItem(127, MF_DISABLED);
			}
			else {
				menu->EnableMenuItem(128, MF_DISABLED);
				menu->EnableMenuItem(127, MF_ENABLED);
			}

		}
		else {
			menu->EnableMenuItem(127, MF_DISABLED);
			menu->EnableMenuItem(135, MF_DISABLED);
			menu->EnableMenuItem(130, MF_DISABLED);
			menu->EnableMenuItem(133, MF_DISABLED);
			menu->EnableMenuItem(128, MF_DISABLED);
			menu->EnableMenuItem(131, MF_DISABLED);
			menu->EnableMenuItem(132, MF_DISABLED);
			menu->EnableMenuItem(134, MF_DISABLED);
		}
	}
	else  if (this->selection->GetLength() == 0) {
		menu = this->classDiagramFormMenu->menu1;
	}
	else if (this->selection->GetLength() > 1) {
		menu = this->classDiagramFormMenu->menu3;
	}

	if (this->historyGraphic->undoGraphicArray->GetLength() == 0) {
		menu->EnableMenuItem(123, MF_DISABLED);
	}
	else {
		menu->EnableMenuItem(123, MF_ENABLED);
	}
	if (this->historyGraphic->redoGraphicArray->GetLength() == 0) {
		menu->EnableMenuItem(136, MF_DISABLED);
	}
	else {
		menu->EnableMenuItem(136, MF_ENABLED);
	}

	ClientToScreen(&point); //스크린 기준으로 들어가야함.
	menu->TrackPopupMenu(TPM_LEFTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);
	Invalidate(false);
}
void ClassDiagramForm::OnRButtonDown(UINT nFlags, CPoint point) {
	SetFocus();

	int hPos = this->GetScrollPos(SB_HORZ);
	int vPos = this->GetScrollPos(SB_VERT);
	this->startX = point.x + hPos;
	this->startY = point.y + vPos;
	this->currentX = point.x;
	this->currentY = point.y;

	Long index = this->selection->SelectByPoint(startX, startY);
	if (index == -1) {
		this->selection->DeleteAllItems();
		this->selection->SelectByPoint(this->diagram, this->currentX, this->currentY);
	}
	if (this->selection->GetLength() == 0) {
		this->mouseLButton->ChangeDefault();
	}
	else if (this->selection->GetLength() == 1) {
		this->mouseLButton->ChangeSelectionState();
	}
	else if (this->selection->GetLength() >= 2) {
		this->mouseLButton->ChangeMultipleState();
	}

	Invalidate(false);
}

BOOL ClassDiagramForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	CWnd::SetFocus();
	SetFocus();
	bool ret = false;
	Long zoomRate_ = this->zoomRate;
	// nWheelScrollLines 휠 한번에 이동하는 줄 수 (Reg에서 읽어 온다)
	HKEY hKey = 0;
	DWORD dwType = REG_BINARY;
	DWORD dwSize = 10;
	BYTE* pByte = new BYTE[dwSize];

	ZeroMemory(pByte, dwSize);

	RegOpenKey(HKEY_CURRENT_USER, "Control Panel\\Desktop", &hKey);
	RegQueryValueEx(hKey, "WheelScrollLines", NULL, &dwType, pByte, &dwSize);
	RegCloseKey(hKey);

	int nWheelScrollLines = atoi((char*)pByte);
	delete pByte;

	int vertPos = GetScrollPos(SB_VERT);
	int horzPos = GetScrollPos(SB_HORZ);
	int vertCurPos;
	if (GetKeyState(VK_CONTROL) >= 0 && GetKeyState(VK_MENU) >= 0) {
		if (zDelta <= 0) { //마우스 휠 다운
			vertCurPos = vertPos + nWheelScrollLines * 30;
			OnVScrollPageDown onVScrollPageDown;
			onVScrollPageDown.Scrolling(this);
		}
		else {  //마우스 휠 업
			vertCurPos = vertPos - nWheelScrollLines * 30;
			OnVScrollPageUp onVScrollPageUp;
			onVScrollPageUp.Scrolling(this);
		}
		ret = true;
	}
	else if (GetKeyState(VK_CONTROL) < 0) {
		if (this->selection->GetLength() > 0) {
			this->selection->DeleteAllItems();
		}
		this->preZoom = this->zoomRate;
		if (zDelta <= 0) { //마우스 휠 다운
			this->zoomRate -= 10;
			if (this->zoomRate < 10) {
				this->zoomRate = 10;
			}
		}
		else {  //마우스 휠 업
			this->zoomRate += 10;
			if (this->zoomRate > 150) {
				this->zoomRate = 150;
			}
		}
		this->SetMemoGab(20 * this->zoomRate / 100);
		this->SetGabX(10 * this->zoomRate / 100);
		this->SetGabY(2);
		this->SetCaretWidth(2);

		this->thirty = this->thirty*this->zoomRate / this->preZoom;
		this->seventeen = this->seventeen*this->zoomRate / this->preZoom;

		SCROLLINFO vScinfo;
		SCROLLINFO hScinfo;

		ScrollMovingObject moving;
		this->GetScrollInfo(SB_VERT, &vScinfo);
		this->GetScrollInfo(SB_HORZ, &hScinfo);
		CRect rect;
		this->GetClientRect(&rect);

		moving.MovingObject(this->diagram, hScinfo.nPos, vScinfo.nPos);
		vScinfo.nMax = vScinfo.nMax * this->zoomRate / this->preZoom;
		hScinfo.nMax = hScinfo.nMax * this->zoomRate / this->preZoom;
		if (vScinfo.nMax < vScinfo.nPage) {
			vScinfo.nMax = vScinfo.nPage;
		}
		if (hScinfo.nMax < hScinfo.nPage) {
			hScinfo.nMax = hScinfo.nPage;
		}
		if (vScinfo.nPos > vScinfo.nMax - vScinfo.nPage) {
			vScinfo.nPos = vScinfo.nMax - vScinfo.nPage;
		}
		if (hScinfo.nPos > hScinfo.nMax - hScinfo.nPage) {
			hScinfo.nPos = hScinfo.nMax - hScinfo.nPage;
		}
		this->SetScrollInfo(SB_VERT, &vScinfo);
		this->SetScrollInfo(SB_HORZ, &hScinfo);

		CDC memDC;
		ResizeVisitor resizeVisitor(this->preZoom, this->zoomRate);
		this->diagram->Accept(resizeVisitor, &memDC);
		if (this->copyBuffer != NULL) {
		   this->copyBuffer->Accept(resizeVisitor, &memDC);
		}

		KnockKnock knocking;
		knocking.Knocking(this);

		moving.MovingObject(this->diagram, -hScinfo.nPos, -vScinfo.nPos);
		if ((zoomRate_ != 10 || this->zoomRate != 10) && (zoomRate_ != 200 || this->zoomRate != 200)) {
			this->lastClass->statusBar->DestroyStatus();
			this->lastClass->statusBar->MakeStatusBar(this->lastClass, this->lastClass->GetSafeHwnd(), 0, 0, 5);
		}
	}
	ret = true;
	Invalidate(false);

	return ret;
}
void ClassDiagramForm::OnNcMouseMove(UINT nHitTest, CPoint point) {

	CRect rect;
	this->GetWindowRect(&rect);
	bool ret = rect.PtInRect(CPoint(this->startX, this->startY));
	if (this->startX != 0 && this->startY != 0) {
		switch (nHitTest) {
		case HTTOP: this->zoomRate++; break;
		case HTTOPLEFT:; break;
		case HTTOPRIGHT:; break;
		case HTLEFT:; break;
		case HTRIGHT:; break;
		case HTBOTTOM:; break;
		case HTBOTTOMLEFT:; break;
		case HTBOTTOMRIGHT:; break;
		default: break;
		}
	}
	Invalidate(false);
}

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CWnd::SetFocus();
	SetFocus();

	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;
	SetTimer(1, 1, NULL);
	while (elapseTime < dblclkTime) {
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
			KillTimer(1);
		}
		elapseTime++;
	}
	int hPos = this->GetScrollPos(SB_HORZ);
	int vPos = this->GetScrollPos(SB_VERT);
	this->startX = point.x + hPos;
	this->startY = point.y + vPos;
	this->currentX = point.x;
	this->currentY = point.y;

	this->currentX_2 = point.x;
	this->currentY_2 = point.y;

	this->mouseLButton->MouseLButtonDown(this->mouseLButton, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
	
	KillTimer(1);
	SetCapture();
	Invalidate(false);
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	MSG msg;
	UINT dblclkTime = GetDoubleClickTime();
	UINT elapseTime = 0;
	PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	if (msg.message == WM_LBUTTONDBLCLK || msg.message == WM_RBUTTONDBLCLK) {
		return;
	}
	int vertCurPos = GetScrollPos(SB_VERT);
	int horzCurPos = GetScrollPos(SB_HORZ);

	this->currentX = point.x;
	this->currentY = point.y;

	if (startX != 0 && startY != 0 && currentX != 0 && currentY != 0) {
		this->mouseLButton->MouseLButtonUp(this->mouseLButton, this, this->diagram, this->selection, this->startX, this->startY, this->currentX, this->currentY);
	}

	this->startX_ = this->startX;
	this->startY_ = this->startY;
	this->currentX_ = this->currentX;
	this->currentY_ = this->currentY;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->firstDrag = 0;
	KillTimer(1);

	ReleaseCapture();
	Invalidate(false);

	this->isDown = 1;
}

void ClassDiagramForm::OnMyMenu(UINT parm_control_id) {

	MenuAction* menuAction = this->classDiagramFormMenu->MenuSelected(parm_control_id);
	if (menuAction != 0) {
		menuAction->MenuPress(this->lastClass);
	}
	if (this->selection->GetLength() > 1) {
		this->mouseLButton->ChangeMultipleState();
	}
	else if (this->selection->GetLength() == 1) {
		this->mouseLButton->ChangeSelectionState();
	}
}
void ClassDiagramForm::OnGetMinMaxInfo(MINMAXINFO FAR *lpMMI) {
	lpMMI->ptMinTrackSize.x = 300;
	lpMMI->ptMinTrackSize.y = 300;
	CWnd::OnGetMinMaxInfo(lpMMI);
}
void ClassDiagramForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CPaintDC dc(this);

	int hPos = this->GetScrollPos(SB_HORZ);
	int vPos = this->GetScrollPos(SB_VERT);
	this->startX = point.x + hPos;
	this->startY = point.y + vPos;
	this->currentX = point.x ;
	this->currentY = point.y;

	if (this->zoomRate >= 50) {
		Figure* figure = this->diagram->FindItem(startX - hPos, startY - vPos, this);
		if (figure != NULL && this->selection->GetLength() != 0 && !dynamic_cast<Relation*>(this->selection->GetAt(0)) && !dynamic_cast<SelfRelation*>(figure)) {

			this->textEdit = new TextEdit(this, figure);

			if (dynamic_cast<MemoBox*>(figure) || dynamic_cast<ClassName*>(figure)) {
				this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					figure->GetX() + GabX,
					figure->GetY() + GabY + MemoGab,
					figure->GetX() + figure->GetWidth() - GabX + CaretWidth,
					figure->GetY() + figure->GetHeight() - GabY), this, 10000, NULL);
			}
			else {
				this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					figure->GetX() + GabX,
					figure->GetY() + GabY,
					figure->GetX() + figure->GetWidth() - GabX + CaretWidth,
					figure->GetY() + figure->GetHeight() - GabY), this, 10000, NULL);
			}
		}

		//선택된 relationLine 이 있으면
		Figure* rr = this->selection->GetAt(0);
		if (this->selection->GetLength() == 1 && dynamic_cast<Relation*>(this->selection->GetAt(0))) {//&& !dynamic_cast<MemoLine*>(this->selection->GetAt(0))) {
																									  // relationLine 에서 rollNamePoints array 돌면서 points 에서 박스범위가 더블클린인지 확인한다
			Long i = 0;
			Long index = 0;
			Relation *relation = static_cast<Relation*>(this->selection->GetAt(0));
			Long right;
			Long left;
			Long top;
			Long bottom;
			if (!dynamic_cast<Generalization*>(this->selection->GetAt(0)) && !dynamic_cast<Composition*>(this->selection->GetAt(0)) &&
				!dynamic_cast<Compositions*>(this->selection->GetAt(0)) && !dynamic_cast<Dependency*>(this->selection->GetAt(0)) &&
				!dynamic_cast<Realization*>(this->selection->GetAt(0))) {
				while (i < 5 && index == 0) {
					if (i == 0 || i == 2) {
						right = relation->rollNamePoints->GetAt(i).x + 20 * this->zoomRate / 100;
						left = relation->rollNamePoints->GetAt(i).x - 20 * this->zoomRate / 100;
						top = relation->rollNamePoints->GetAt(i).y - 10 * this->zoomRate / 100;
						bottom = relation->rollNamePoints->GetAt(i).y + 10 * this->zoomRate / 100;
					}
					else if (i == 1) {
						right = relation->rollNamePoints->GetAt(i).x + 40 * this->zoomRate / 100;
						left = relation->rollNamePoints->GetAt(i).x - 40 * this->zoomRate / 100;
						top = relation->rollNamePoints->GetAt(i).y - 10 * this->zoomRate / 100;
						bottom = relation->rollNamePoints->GetAt(i).y + 10 * this->zoomRate / 100;
					}
					else if (i == 3 || i == 4) {
						right = relation->rollNamePoints->GetAt(i).x + 25 * this->zoomRate / 100;
						left = relation->rollNamePoints->GetAt(i).x - 25 * this->zoomRate / 100;
						top = relation->rollNamePoints->GetAt(i).y - 10 * this->zoomRate / 100;
						bottom = relation->rollNamePoints->GetAt(i).y + 10 * this->zoomRate / 100;
					}

					if (startX - hPos< right && startX - hPos> left && startY - vPos > top && startY - vPos < bottom) {
						index++;
					}
					i++;
				}
			}
			if (index > 0) {
				this->textEdit = new TextEdit(this, relation, i - 1);
				this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					left + 1,
					top + 1,
					right - 1,
					bottom - 1), this, 10000, NULL);
			}
		}
		if (this->selection->GetLength() == 1 && dynamic_cast<SelfRelation*>(this->selection->GetAt(0))) {
			// relationLine 에서 rollNamePoints array 돌면서 points 에서 박스범위가 더블클린인지 확인한다
			Long i = 0;
			Long index = 0;
			SelfRelation *selfRelation = static_cast<SelfRelation*>(this->selection->GetAt(0));
			Long right;
			Long left;
			Long top;
			Long bottom;
			if (!dynamic_cast<Generalization*>(this->selection->GetAt(0)) && !dynamic_cast<Composition*>(this->selection->GetAt(0)) &&
				!dynamic_cast<Compositions*>(this->selection->GetAt(0)) && !dynamic_cast<Dependency*>(this->selection->GetAt(0)) &&
				!dynamic_cast<Realization*>(this->selection->GetAt(0))) {
				while (i < 5 && index == 0) {
					if (i == 0) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 20 * this->zoomRate / 100;
						left = selfRelation->rollNamePoints->GetAt(i).x - 10 * this->zoomRate / 100;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10 * this->zoomRate / 100;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10 * this->zoomRate / 100;
					}
					else if (i == 1) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 30 * this->zoomRate / 100;
						left = selfRelation->rollNamePoints->GetAt(i).x - 30 * this->zoomRate / 100;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10 * this->zoomRate / 100;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10 * this->zoomRate / 100;
					}
					else if (i == 2) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 50 * this->zoomRate / 100;
						left = selfRelation->rollNamePoints->GetAt(i).x - 20 * this->zoomRate / 100;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10 * this->zoomRate / 100;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10 * this->zoomRate / 100;
					}
					else if (i == 3) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 50 * this->zoomRate / 100;
						left = selfRelation->rollNamePoints->GetAt(i).x - 20 * this->zoomRate / 100;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10 * this->zoomRate / 100;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10 * this->zoomRate / 100;
					}
					else if (i == 4) {
						right = selfRelation->rollNamePoints->GetAt(i).x + 10 * this->zoomRate / 100;
						left = selfRelation->rollNamePoints->GetAt(i).x - 20 * this->zoomRate / 100;
						top = selfRelation->rollNamePoints->GetAt(i).y - 10 * this->zoomRate / 100;
						bottom = selfRelation->rollNamePoints->GetAt(i).y + 10 * this->zoomRate / 100;
					}

					if (startX - hPos< right && startX - hPos> left && startY - vPos > top && startY - vPos < bottom) {
						index++;
					}
					i++;
				}
			}
			// 확인해서 있으면 그 index 기억해두고 그 박스 사이즈로 textEdit 연다 (textEdit 생성자 따로 만들어야할듯)

			if (index > 0) {
				this->textEdit = new TextEdit(this, selfRelation, i - 1);
				this->textEdit->Create(NULL, "textEdit", WS_CHILD | WS_VISIBLE, CRect(
					left + 1,
					top + 1,
					right - 1,
					bottom - 1), this, 10000, NULL);
				OnKillFocus(NULL);
			}
		}
	}
	if (this->textEdit != NULL) {
		this->textEdit->SetCapture();
	}

	Invalidate(false);
	this->isDown = 0;

}

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {
	int vertCurPos = GetScrollPos(SB_VERT);
	int horzCurPos = GetScrollPos(SB_HORZ);
	int vertNCurPos = GetScrollPos(SB_VERT);
	int horzNCurPos = GetScrollPos(SB_HORZ);
	int scrollMin;
	int scrollMax;
	if (nFlags == MK_LBUTTON) {
		CRect testRect;
		this->GetClientRect(&testRect);

		//좌측
		if (point.x < testRect.left + 20) {
			horzNCurPos = horzCurPos - 20;
			if (horzNCurPos < 0) {
				horzNCurPos = 0;
			}
		}
		if (point.x > testRect.right - 20) {
			horzNCurPos = horzCurPos + 20;
			Long maxpos = this->GetScrollLimit(SB_HORZ);
			if (horzNCurPos > maxpos) {
				this->GetScrollRange(SB_HORZ, &scrollMin, &scrollMax);
				this->SetScrollRange(SB_HORZ, scrollMin, scrollMax + 20);
			}
		}
		if (point.y < testRect.top + 20) {
			vertNCurPos = vertCurPos - 20;
			if (vertNCurPos < 0) {
				vertNCurPos = 0;
			}
		}
		if (point.y > testRect.bottom - 20) {
			vertNCurPos = vertCurPos + 20;
			Long maxpos = this->GetScrollLimit(SB_VERT);
			if (vertNCurPos > maxpos) {
				this->GetScrollRange(SB_VERT, &scrollMin, &scrollMax);
				this->SetScrollRange(SB_VERT, scrollMin, scrollMax + 20);
			}
		}


		SetScrollPos(SB_HORZ, horzNCurPos);
		SetScrollPos(SB_VERT, vertNCurPos);
		//int vertNCurPos = GetScrollPos(SB_VERT);
		//int horzNCurPos = GetScrollPos(SB_HORZ);
		ScrollMovingObject moving;
		moving.MovingObject(this->diagram, horzCurPos - horzNCurPos, vertCurPos - vertNCurPos);
		this->currentX_2 = this->currentX;
		this->currentY_2 = this->currentY;
		this->currentX = point.x;
		this->currentY = point.y;
		Invalidate(false);
		
	}
	//커서모양
	if (nFlags != MK_LBUTTON && this->selection->GetLength() == 1) {
		Long index;
		index = this->selection->SelectByPoint(point.x, point.y);
		if (index == 12 || index == 4 || index == 9) {
			SetCursor(LoadCursor(NULL, IDC_SIZENS));
		}
		else if (index == 3 || index == 10) {
			SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		}
		else if (index == 5 || index == 8) {
			SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		}
		else if (index == 6 || index == 7) {
			SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		}
	}
}
void ClassDiagramForm::OnClose() {

	//6.2. 다이어그램을 지운다.
	if (this->diagram != NULL) {
		delete this->diagram;
		this->diagram = NULL;
	}
	if (this->selection != NULL) {
		delete this->selection;
		this->selection = NULL;
	}
	if (this->mouseLButton != NULL) {
		delete this->mouseLButton;
		this->mouseLButton = NULL;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
		this->keyBoard = NULL;
	}
	if (this->historyGraphic != NULL) {
		delete this->historyGraphic;
		this->historyGraphic = NULL;
	}
	if (this->scroll != NULL) {
		delete this->scroll;
		this->scroll = NULL;
	}
	if (this->copyBuffer != NULL) {
		delete this->copyBuffer;
		this->copyBuffer = NULL;
	}
	if (this->classDiagramFormMenu != NULL) {
		delete this->classDiagramFormMenu;
		this->classDiagramFormMenu = NULL;
	}
	CWnd::OnClose();
}