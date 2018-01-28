//FigureFactory.cpp

#include "FigureFactory.h"
#include "Class.h"
#include "MemoBox.h"
#include "Template.h"
#include "ClassName.h"
#include "Attribute.h"
#include "Method.h"
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


FigureFactory::FigureFactory() {
}
FigureFactory::~FigureFactory() {
}
// 0 = Class, 1 = MemoBox, 2 = Line, 3 = Template, 4 = Generalization(일반화), 5 = Realization(실체화), 6 = Dependency(의존), 7 = Association(연관화),
// 8 = DirectedAssociation(직접연관),  9 = Aggregation(집합), 10 = Aggregations(집합연관), 11 =  Composition(합성), 12 = Compositions(복합연관)
//13 = MemoLine  14 = ClassName , 15 = Attribute , 16 = Method , 17 = Reception
Figure* FigureFactory::Create(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, Long type) {
	if (type == 0) {
		return new Class(x, y, width, height, minimumWidth, minimumHeight);
	}
	if (type == 1) {
		return new ClassName(x, y, width, height, minimumWidth, minimumHeight, "");
	}
	if (type == 2) {
		return new Line(x, y, width, height);
	}
	if (type == 3) {
		return new Attribute(x, y, width, height, minimumWidth, minimumHeight, "");
	}
	if (type == 4) {
		return new Method(x, y, width, height, minimumWidth, minimumHeight, "");
	}
	if (type == 5) {
		return new Reception(x, y, width, height, minimumWidth, minimumHeight, "");
	}
	if (type == 6) {
		return new Template(x, y, width, height);
	}
	if (type == 7) {
		return new MemoBox(x, y, width, height, minimumWidth, minimumHeight);
	}
	if (type == 8) {
		return new MemoLine(x, y, width, height);
	}
	if (type == 9) {
		return new Generalization(x, y, width, height);
	}
	if (type == 10) {
		return new Realization(x, y, width, height);
	}
	if (type == 11) {
		return new Dependency(x, y, width, height);
	}
	if (type == 12) {
		return new Association(x, y, width, height);
	}
	if (type == 13) {
		return new DirectedAssociation(x, y, width, height);
	}
	if (type == 14) {
		return new Aggregation(x, y, width, height);
	}
	if (type == 15) {
		return new Aggregations(x, y, width, height);
	}
	if (type == 16) {
		return new Composition(x, y, width, height);
	}
	if (type == 17) {
		return new Compositions(x, y, width, height);
	}
	if (type == 18) {
		return new SelfGeneralization(x, y, width, height);
	}
	if (type == 19) {
		return new SelfDependency(x, y, width, height);
	}
	if (type == 20) {
		return new SelfAssociation(x, y, width, height);
	}
	if (type == 21) {
		return new SelfDirectedAssociation(x, y, width, height);
	}
	if (type == 22) {
		return new SelfAggregation(x, y, width, height);
	}
	if (type == 23) {
		return new SelfAggregations(x, y, width, height);
	}
	if (type == 24) {
		return new SelfComposition(x, y, width, height);
	}
	if (type == 25) {
		return new SelfCompositions(x, y, width, height);
	}
	return 0;
}


