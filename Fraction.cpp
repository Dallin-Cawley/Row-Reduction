#include "Fraction.h"


bool Fraction::reduce(int numerator, int denominator, int i) {
	
	if (i >= 9) {
		return false;
	}
	int j = 2;

	for (; j < 10; j++) {

		if (numerator % j == 0 && denominator % j == 0) {
			this->numerator = numerator / j;
			this->denominator = numerator / j;
			break;
		}
	}

	reduce(this->numerator, this->denominator, j);

	return false;
}