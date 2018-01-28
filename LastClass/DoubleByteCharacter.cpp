//DoubleByteCharacter.cpp

#include "DoubleByteCharacter.h"

DoubleByteCharacter::DoubleByteCharacter() {
	this->characters[0] = ' ';
	this->characters[1] = ' ';
}
DoubleByteCharacter::DoubleByteCharacter(char(*characters)) {
	this->characters[0] = characters[0];
	this->characters[1] = characters[1];
}
DoubleByteCharacter::DoubleByteCharacter(const DoubleByteCharacter& source) {
	this->characters[0] = source.characters[0];
	this->characters[1] = source.characters[1];
}
DoubleByteCharacter::~DoubleByteCharacter() {
}
CString DoubleByteCharacter::MakeCString() const {
	char newChar[3];
	newChar[0] = this->characters[0];
	newChar[1] = this->characters[1];
	newChar[2] = '\0';

	CString cs(newChar);
	return cs;
}
Character* DoubleByteCharacter::Clone() const {
	return new DoubleByteCharacter(*this);
}
DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source) {
	this->characters[0] = source.characters[0];
	this->characters[1] = source.characters[1];

	return *this;
}