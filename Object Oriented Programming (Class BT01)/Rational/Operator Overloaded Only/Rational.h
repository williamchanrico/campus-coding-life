/*
* Author: William Chanrico
* Date: 12-March-2016
* Summary: Class representing rational number
* 
* Tested on gcc version 5.1.0 (i686-posix-dwarf-rev0, Built by MinGW-W64 project)
* >> g++ Demo.cpp Rational.cpp -o a
*/

#ifndef RATIONAL_H
#define RATIONAL_H

class Rational{
private:
    int numerator;
    int denominator;

    int GCD(int x, int y);
    
public:
    Rational(int numerator = 1, int denominator = 1);

    void printFraction() const; 
    void printDecimalFraction() const; 

    Rational operator+(const Rational &other) const;
    Rational operator-(const Rational &other) const;
    Rational operator*(const Rational &other) const;
    Rational operator/(const Rational &other) const;

    operator std::string() const;
    operator float() const;
};

#endif /* RATIONAL_H */