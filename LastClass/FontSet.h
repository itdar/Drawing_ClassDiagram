//FontSet.h

#ifndef _FONTSET_H
#define _FONTSET_H

#include <string>
using namespace std;

typedef signed long int Long;

class FontSet {
public:
	FontSet();
	FontSet(const FontSet& source);
	~FontSet();
public:
	void SetFontWeight(Long index);
	void SetFaceName(string faceName);

	Long GetFontWeight();
	string GetFaceName();
private:
	Long fontWeight;
	string faceName;
};

inline Long FontSet::GetFontWeight() {
	return this->fontWeight;
}
inline string FontSet::GetFaceName() {
	return this->faceName;
}

#endif // _FONTSET_H