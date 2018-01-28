//SelfDependency.cpp

#include "SelfDependency.h"

SelfDependency::SelfDependency() :SelfRelation() {

}

SelfDependency::SelfDependency(Long x, Long y, Long width, Long height) : SelfRelation(x, y, width, height) {

}

SelfDependency::SelfDependency(const SelfDependency& source) : SelfRelation(source) {

}

SelfDependency& SelfDependency::operator=(const SelfDependency& source) {
	SelfRelation::operator=(source);
	return *this;
}

SelfDependency::~SelfDependency() {

}

Figure* SelfDependency::Clone() const {
	return new SelfDependency(*this);
}

void SelfDependency::Accept(Visitor& visitor, CDC *pDC) {
	visitor.Visit(this, pDC);
}
