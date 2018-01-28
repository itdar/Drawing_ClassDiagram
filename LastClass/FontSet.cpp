//FontSet.cpp

#include "FontSet.h"

FontSet::FontSet() {
	this->fontWeight = 400;
	this->faceName = "±¼¸²Ã¼";
}

FontSet::FontSet(const FontSet& source) {
	this->fontWeight = source.fontWeight;
	this->faceName = source.faceName;
}

FontSet::~FontSet() {
}

void FontSet::SetFontWeight(Long fontWeight) {
	this->fontWeight = fontWeight;
}

void FontSet::SetFaceName(string faceName) {
	this->faceName = faceName;
}