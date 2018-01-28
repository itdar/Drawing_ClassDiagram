//SelfComposition.cpp

#include "SelfComposition.h"

SelfComposition::SelfComposition() :SelfRelation() {

}

SelfComposition::SelfComposition(Long x, Long y, Long width, Long height) : SelfRelation(x, y, width, height) {

}

SelfComposition::SelfComposition(const SelfComposition& source) : SelfRelation(source) {

}

SelfComposition& SelfComposition::operator=(const SelfComposition& source) {
	SelfRelation::operator=(source);
	return *this;
}

SelfComposition::~SelfComposition() {

}

Figure* SelfComposition::Clone() const {
	return new SelfComposition(*this);
}

void SelfComposition::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}
