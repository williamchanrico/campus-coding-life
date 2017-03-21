/*
* Author: William Chanrico
* Date: 12-March-2016
* Summary: Class representing rational number
* 
* Tested on gcc version 5.1.0 (i686-posix-dwarf-rev0, Built by MinGW-W64 project)
* >> g++ Demo.cpp Rational.cpp -o a
*/

#include <iostream>
#include <sstream>
#include "Rational.h"

Rational::Rational(int numerator, int denominator){
    int reducer = GCD(numerator, denominator);

    this->numerator = numerator / reducer;
    this->denominator = denominator / reducer;

    if(this->denominator < 0){
    	this->numerator *= -1;
    	this->denominator *= -1;
    }
}

int Rational::GCD(int x, int y){ return (y == 0) ? x : GCD(y, x % y); }

void Rational::printFraction() const{
	std::cout << (std::string) *this;
}

void Rational::printDecimalFraction() const{
	std::cout << (float) *this;
}

Rational Rational::operator+(const Rational &other) const{
	int ansNumerator = (numerator * other.denominator) + (other.numerator * denominator);
	int ansDenominator = denominator * other.denominator;

    Rational ans(ansNumerator, ansDenominator);

    return ans;
}

Rational Rational::operator-(const Rational &other) const{
	int ansNumerator = (numerator * other.denominator) - (other.numerator * denominator);
	int ansDenominator = denominator * other.denominator;

    Rational ans(ansNumerator, ansDenominator);

    return ans;
}

Rational Rational::operator*(const Rational &other) const{
	int ansNumerator = (numerator * other.numerator);
	int ansDenominator = (denominator * other.denominator);

	Rational ans(ansNumerator, ansDenominator);

    return ans;
}

Rational Rational::operator/(const Rational &other) const{
	Rational divider(other.denominator, other.numerator);

	int ansNumerator = (numerator * divider.numerator);
	int ansDenominator = (denominator * divider.denominator);

	Rational ans(ansNumerator, ansDenominator);

    return ans;
}

Rational::operator std::string() const{
	std::stringstream ss;

	ss << numerator << "/" << denominator;

	return ss.str();
}

Rational::operator float() const{
	return (float) numerator / denominator;
}
