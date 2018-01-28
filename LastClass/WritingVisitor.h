//WritingVisitor.h

#ifndef _WRITINGVISITOR_H
#define _WRITINGVISITOR_H

#include "Visitor.h" 

class WritingVisitor : public Visitor {
public:
	WritingVisitor(Long zoomRate);
	~WritingVisitor();
	void Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY);
	void Visit(Class *object, CDC* pDC);
	void Visit(MemoBox* memoBox, CDC* pDC);
	void Visit(Selection *selection, CDC *pDC);

	void Visit(Template *object, CDC *pDC);
	void Visit(ClassName* className, CDC* pDC);
	void Visit(Attribute* attribute, CDC* pDC);
	void Visit(Method* method, CDC* pDC);
	void Visit(Reception* reception, CDC* pDC);
	void Visit(Line *line, CDC* pDC);

	void Visit(Generalization *generalization, CDC* pDC); //일반화
	void Visit(Realization * realization, CDC* pDC);		//실체화
	void Visit(Dependency *dependency, CDC* pDC);		//의존
	void Visit(Association *association, CDC* pDC);		//연관화
	void Visit(DirectedAssociation *directedAssociation, CDC* pDC);		//직접연관
	void Visit(Aggregation *aggregation, CDC* pDC);		//집합
	void Visit(Aggregations *aggregations, CDC* pDC);		//집합연관
	void Visit(Composition *composition, CDC* pDC);		//합성
	void Visit(Compositions *compositions, CDC* pDC);		//복합연관
	void Visit(MemoLine* memobox, CDC *pDC); //메모선
	void Visit(SelfGeneralization *selfGeneralization, CDC *pDC);
	void Visit(SelfAggregation *selfAggregation, CDC *pDC);
	void Visit(SelfDependency *selfdependency, CDC *pDC);
	void Visit(SelfAssociation *selfAssociation, CDC *pDC);
	void Visit(SelfAggregations *selfAggregations, CDC *pDC);
	void Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *pDC);
	void Visit(SelfComposition *selfComposition, CDC *pDC);
	void Visit(SelfCompositions *selfCompositions, CDC *pDC);

	void Visit(SelfRelation *selfRelation, CDC *pDC);
	void Visit(Relation *relation, CDC *pDC);

	void Visit(Class *object, Long distanceX, Long distanceY);
	void Visit(MemoBox *memoBox, Long distanceX, Long distanceY);

	void Visit(Text* text, CDC* pDC);
private:
	Long zoomRate;
};

#endif // _WRITINGVISITOR_H