//RollNameBox.h

#ifndef _ROLLNAMEBOX_H
#define _ROLLNAMEBOX_H

#include "Array.h"
#include "afxwin.h"

class Relation;
class RollNameBox {
public:
	static RollNameBox* Instance();
public:
	RollNameBox();
	RollNameBox(const RollNameBox& source);
	~RollNameBox();
public:
	CPoint GetFirstRollNamePoint(CPoint startPoint, CPoint endPoint);
	CPoint GetSecondRollNamePoint(CPoint startPoint, CPoint endPoint);
	CPoint GetThirdRollNamePoint(CPoint startPoint, CPoint endPoint);
	CPoint GetFourthRollNamePoint(CPoint startPoint, CPoint endPoint);
	CPoint GetFifthRollNamePoint(CPoint startPoint, CPoint endPoint);

	CPoint GetSelfRelationFirstRollNamePoint(CPoint startPoint, CPoint endPoint);
	CPoint GetSelfRelationSecondRollNamePoint(CPoint startPoint, CPoint endPoint);
	CPoint GetSelfRelationThirdRollNamePoint(CPoint startPoint, CPoint endPoint);
	CPoint GetSelfRelationFourthRollNamePoint(CPoint startPoint, CPoint endPoint);
	CPoint GetSelfRelationFifthRollNamePoint(CPoint startPoint, CPoint endPoint);
private:
	static RollNameBox* instance;
};

#endif // _ROLLNAMEBOX_H