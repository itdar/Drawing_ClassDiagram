//SelfAggregations.cpp

#include "SelfAggregations.h"

SelfAggregations::SelfAggregations() :SelfRelation() {

}

SelfAggregations::SelfAggregations(Long x, Long y, Long width, Long height) : SelfRelation(x, y, width, height) {

}

SelfAggregations::SelfAggregations(const SelfAggregations& source) : SelfRelation(source) {

}

SelfAggregations& SelfAggregations::operator=(const SelfAggregations& source) {
	SelfRelation::operator=(source);
	return *this;
}

SelfAggregations::~SelfAggregations() {

}

Figure* SelfAggregations::Clone() const {
	return new SelfAggregations(*this);
}

void SelfAggregations::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}
