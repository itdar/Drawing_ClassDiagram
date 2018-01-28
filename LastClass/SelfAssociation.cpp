//SelfDependency.cpp

#include "SelfAssociation.h"

SelfAssociation::SelfAssociation() :SelfRelation() {

}

SelfAssociation::SelfAssociation(Long x, Long y, Long width, Long height) : SelfRelation(x, y, width, height) {

}

SelfAssociation::SelfAssociation(const SelfAssociation& source) : SelfRelation(source) {

}

SelfAssociation& SelfAssociation::operator=(const SelfAssociation& source) {
	SelfRelation::operator=(source);
	return *this;
}

SelfAssociation::~SelfAssociation() {

}

Figure* SelfAssociation::Clone() const {
	return new SelfAssociation(*this);
}

void SelfAssociation::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}
