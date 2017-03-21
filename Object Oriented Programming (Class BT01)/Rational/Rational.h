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

    int GCD(int x, int y); // Finding greatest commond divisor to calculate reduced form of rationals

public:
    Rational(int numerator = 1, int denominator = 1); // Constructor

    void printFraction() const; // Print rational in form "numerator/denominator"
    void printDecimalFraction() const; // Print rational in decimal fraction format

    Rational add(const Rational &other) const; // Calculate addition
    Rational subtract(const Rational &other) const; // Calculate subtraction
    Rational multiply(const Rational &other) const; // Calculate multiplication
    Rational divide(const Rational &other) const; // Calculate division

    // Operator overloading for convenient use
    Rational operator+(const Rational &other) const;
    Rational operator-(const Rational &other) const;
    Rational operator*(const Rational &other) const;
    Rational operator/(const Rational &other) const;

    operator std::string() const;
    operator float() const;
};

#endif /* RATIONAL_H */