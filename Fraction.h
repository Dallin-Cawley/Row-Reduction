#pragma once
#pragma once

class Fraction {
private:
	bool reduce(int numerator, int denominator, int i);

public:
	float numerator;
	int denominator;

	Fraction() {
		numerator = 1;
		denominator = 1;
	}

	Fraction(float numerator) {
		this->numerator = numerator;
		this->denominator = 100;
	}

	void toFraction() {

		int gcd_Numerator = numerator * 100;


		reduce(gcd_Numerator, denominator, 0);
	}


};