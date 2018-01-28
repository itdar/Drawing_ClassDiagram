//SelfCompositions.cpp

#include "SelfCompositions.h"

SelfCompositions::SelfCompositions() :SelfRelation() {
	
}

SelfCompositions::SelfCompositions(Long x, Long y, Long width, Long height) : SelfRelation(x, y, width, height) {

}

SelfCompositions::SelfCompositions(const SelfCompositions& source) : SelfRelation(source) {

}

SelfCompositions& SelfCompositions::operator=(const SelfCompositions& source) {
	SelfRelation::operator=(source);
	return *this;
}

SelfCompositions::~SelfCompositions() {

}

Figure* SelfCompositions::Clone() const {
	return new SelfCompositions(*this);
}

void SelfCompositions::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}
