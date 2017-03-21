/*
* Author: William Chanrico
* Date: 12-March-2016
* Summary: Class representing rational number
* 
* Tested on gcc version 5.1.0 (i686-posix-dwarf-rev0, Built by MinGW-W64 project)
* >> g++ Demo.cpp Rational.cpp -o a
*/

#include <iostream>
#include "Rational.h"

int main(){
	Rational obj1(-5, 9);
	Rational obj2(-17, 2);

	Rational obj3 = obj1 * obj2;	// obj3 = obj1.multiply(obj2)
	
	std::cout << (std::string) obj3 << "\n";	// obj3.printFraction()
	std::cout << (float) obj3 << "\n";	// obj3.printDecimalFraction()
}
