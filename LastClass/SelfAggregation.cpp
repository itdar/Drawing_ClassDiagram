//SelfAggregation.cpp

#include "SelfAggregation.h"

SelfAggregation::SelfAggregation() :SelfRelation() {

}

SelfAggregation::SelfAggregation(Long x, Long y, Long width, Long height) : SelfRelation(x, y, width, height) {

}

SelfAggregation::SelfAggregation(const SelfAggregation& source) : SelfRelation(source) {

}

SelfAggregation& SelfAggregation::operator=(const SelfAggregation& source) {
	SelfRelation::operator=(source);
	return *this;
}

SelfAggregation::~SelfAggregation() {

}

Figure* SelfAggregation::Clone() const {
	return new SelfAggregation(*this);
}

void SelfAggregation::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}
