//SingleByteCharacter.cpp

#include "SingleByteCharacter.h"

SingleByteCharacter::SingleByteCharacter() {
	this->character = ' ';
}
SingleByteCharacter::SingleByteCharacter(char character) {
	this->character = character;
}
SingleByteCharacter::SingleByteCharacter(const SingleByteCharacter& source) {
	this->character = source.character;
}
SingleByteCharacter::~SingleByteCharacter() {
}
CString SingleByteCharacter::MakeCString() const {
	char tempChar[2];
	tempChar[0] = this->character;
	tempChar[1] = '\0';

	CString cs(tempChar);
	
	return cs;
}
Character* SingleByteCharacter::Clone() const {
	return new SingleByteCharacter(*this);
}
SingleByteCharacter& SingleByteCharacter::operator = (const SingleByteCharacter& source) {
	this->character = source.character;
	
	return *this;
}
