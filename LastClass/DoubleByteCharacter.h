//DoubleByteCharacter.h

#ifndef _DOUBLEBYTECHARACTER_H
#define _DOUBLEBYTECHARACTER_H

#include "Character.h"

class DoubleByteCharacter : public Character {
public:
	DoubleByteCharacter();
	DoubleByteCharacter(char(*characters));
	DoubleByteCharacter(const DoubleByteCharacter& source);
	virtual ~DoubleByteCharacter();

	virtual CString MakeCString() const;

	virtual Character* Clone() const;

	DoubleByteCharacter& operator = (const DoubleByteCharacter& source);

	char* GetCharacters() const;
private:
	char characters[2];
};

inline char* DoubleByteCharacter::GetCharacters() const {
	return const_cast<char*>(this->characters);
}
#endif // _DOUBLEBYTECHARACTER_H

