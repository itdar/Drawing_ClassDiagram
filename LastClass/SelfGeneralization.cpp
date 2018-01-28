//SelfGeneralization.cpp

#include "SelfGeneralization.h"

SelfGeneralization::SelfGeneralization() :SelfRelation() {

}

SelfGeneralization::SelfGeneralization(Long x, Long y, Long width, Long height) :SelfRelation(x,y,width,height) {

}

SelfGeneralization::SelfGeneralization(const SelfGeneralization& source) : SelfRelation(source) {

}

SelfGeneralization& SelfGeneralization::operator=(const SelfGeneralization& source) {
	SelfRelation::operator=(source);
	return *this;
}

SelfGeneralization::~SelfGeneralization() {

}

Figure* SelfGeneralization::Clone() const {
	return new SelfGeneralization(*this);
}

void SelfGeneralization::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}