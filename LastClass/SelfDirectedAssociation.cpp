//SelfDirectedAssociation.cpp

#include "SelfDirectedAssociation.h"

SelfDirectedAssociation::SelfDirectedAssociation() :SelfRelation() {

}

SelfDirectedAssociation::SelfDirectedAssociation(Long x, Long y, Long width, Long height) : SelfRelation(x, y, width, height) {

}

SelfDirectedAssociation::SelfDirectedAssociation(const SelfDirectedAssociation& source) : SelfRelation(source) {

}

SelfDirectedAssociation& SelfDirectedAssociation::operator=(const SelfDirectedAssociation& source) {
	SelfRelation::operator=(source);
	return *this;
}

SelfDirectedAssociation::~SelfDirectedAssociation() {

}

Figure* SelfDirectedAssociation::Clone() const {
	return new SelfDirectedAssociation(*this);
}

void SelfDirectedAssociation::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}
