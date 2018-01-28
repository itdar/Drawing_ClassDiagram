//Figure.h

#ifndef _FIGURE_H //가드선언
#define _FIGURE_H

#include <string>
using namespace std;

typedef signed long int Long;

class Figure {
public:
	Figure();
	Figure(Long x, Long y, Long width, Long height);
	Figure(Long x, Long y, Long width, Long height, string content);
	Figure(Long x, Long y, Long width, Long height, Long minimumWidth, Long minimumHeight, string content);
	Figure(const Figure& source);
	Figure& operator = (const Figure& source);
	virtual ~Figure() = 0;

	virtual Figure* Clone() const = 0;
	Long GetRowCount(string object);
	void ReplaceString(string content, Long fontSize);
	void SetX(Long x);
	void SetY(Long y);
	void SetWidth(Long width);
	void SetHeight(Long height);
	void SetMinimumWidth(Long minimumWidth);
	void SetMinimumHeight(Long minimumHeight);
	Figure* Move(Long distanceX, Long distanceY);
	Figure* EndPointMove(Long distanceX, Long distanceY);

	Figure* Modify(Long x, Long y, Long width, Long height);

	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
	Long GetLeft() const;
	Long GetTop() const;
	Long GetRight() const;
	Long GetBottom() const;
	string& GetContent() const;
	Long GetMinimumHeight() const;
	Long GetMinimumWidth() const;
	Long GetFontSize() const;
	Figure* GetEndPointFigure() const;
	Figure* SetEndPointFigure(Figure *figure);
protected:
	Long x;
	Long y;
	Long width;
	Long height;
	string content;
	Long minimumWidth;
	Long minimumHeight;
	Long fontSize;
	Figure *endPointFigure;
};

inline Long Figure::GetX() const {
	return this->x;
}
inline Long Figure::GetY() const {
	return this->y;
}
inline Long Figure::GetWidth() const {
	return this->width;
}
inline Long Figure::GetHeight() const {
	return this->height;
}
inline Long Figure::GetLeft() const {
	return this->x;
}
inline Long Figure::GetTop() const {
	return this->y;
}
inline Long Figure::GetRight() const {
	return this->x + this->width;
}
inline Long Figure::GetBottom() const {
	return this->y + this->height;
}
inline string& Figure::GetContent() const {
	return const_cast<string&>(this->content);
}
inline Long Figure::GetMinimumWidth() const {
	return this->minimumWidth;
}
inline Long Figure::GetMinimumHeight() const {
	return this->minimumHeight;
}
inline Long Figure::GetFontSize()const {
	return this->fontSize;
}
inline Figure* Figure::GetEndPointFigure()const {
	return this->endPointFigure;
}
#endif //_FIGURE_H