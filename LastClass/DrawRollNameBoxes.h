//DrawRollNameBoxes.h

#ifndef _DRAWROLLNAMEBOXES_H
#define _DRAWROLLNAMEBOXES_H

#include "Array.h"
#include "afxwin.h"

class Relation;
class SelfRelation;
class DrawRollNameBoxes {
public:
	static DrawRollNameBoxes* Instance();
public:
	DrawRollNameBoxes();
	DrawRollNameBoxes(const DrawRollNameBoxes& source);
	~DrawRollNameBoxes();
public:
	void DrawFirstRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate);
	void DrawSecondRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate);
	void DrawThirdRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate);
	void DrawFourthRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate);
	void DrawFifthRollNameBox(Relation *relationLine, CDC *pDC, Long zoomRate);
	void DrawBoxesWithoutCurvedLine(Relation *relationLine, CDC *pDC, Long zoomRate);

	void DrawSelfRelationRollNameBox(SelfRelation *SelfRelationLine, CDC *pDC, Long zoomRate);

private:
	static DrawRollNameBoxes* instance;
};

#endif // _DRAWROLLNAMEBOXES_H