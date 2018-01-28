//PreciseMoving.cpp

#include "PreciseMoving.h"

#include <afxwin.h>

PreciseMoving::PreciseMoving() {
}

PreciseMoving::PreciseMoving(const PreciseMoving& source) {
}

PreciseMoving::~PreciseMoving() {
}

void PreciseMoving::ConvertPoint(Long *x, Long *y, Long extent) {
	if (GetKeyState(VK_MENU) < 0) {
		if (*x % extent != 0) {
			if (*x % extent < extent/2) {
				*x -= *x % extent;
			}
			else {
				*x += (extent - *x % extent);
			}
		}
		if (*y % extent != 0) {
			if (*y % extent < extent/2) {
				*y -= *y % extent;
			}
			else {
				*y += (extent - *y % extent);
			}
		}
	}
}