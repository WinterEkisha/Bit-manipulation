// BitManip.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <inttypes.h>
#include <cmath>
#include <iomanip>

void floatToBinary(float f, std::string& str) //code from stack overflow
{

    union { float f; uint32_t i; } u;
    u.f = f;
    str.clear();

    for (int i = 0; i < 32; i++)
    {
        if (u.i % 2)  str.push_back('1');
        else str.push_back('0');
        u.i >>= 1;
    }

    // Reverse the string since now it's backwards
    std::string temp(str.rbegin(), str.rend());
    str = temp;
}

void longToBinary(long x, std::string& str) {
    for (int i = 0; i < 32; i++) {
        if (x % 2) str.push_back('1');
        else str.push_back('0');
        x >>= 1;
    }
    std::string temp(str.rbegin(), str.rend()); // copied from stack overflow code
    str = temp;
}

//calculate the decimal number of a binary number
void binToDecimal(std::string& str) {
    int temp = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '1') { temp <<= 1; temp++; }
        else temp <<= 1;
    }
    str = std::to_string(temp);
}

void floatInfo(std::string bin, std::string& str) {
    int i = 0;
    std::string temp;
    if (bin[i] == '1') str += "negative\n"; else str += "positive\n"; i += 2;

    for (i; i < 10; i++) {
        //exponent
        temp += bin[i];
    }
    i++;
    //temp convert to decimal str
    binToDecimal(temp);
    str += "exponent: " + temp + '\n';
    temp = ""; //empty temp
    for (i; i < 34; i++) {
        //mantissa as decimal
        temp += bin[i];
    }
    binToDecimal(temp); //TODO: Fix me: needs decimal (1.temp) and needs way to calculate it
    str += "mantissa: " + temp + '\n';

}

void binToLong(long x, std::string bin) { //TODO: finish //unnecessary 
}

char askUserInput(float& flt, float& calculator) {
    char chr;
    std::cout << "Select a calculation\n"
        << "(a) Multiply\n"
        << "(b) Divide\n"
        << "(c) Square Root\n";
    std::cin >> chr;
    if (chr == 'a' || chr == 'A') {
        std::cout << "Number to Multiply: ";
        std::cin >> flt;
        std::cout << "Multiplier (WIP: calculated as num * 2^multi): ";
        std::cin >> calculator;
    }
    else if (chr == 'b' || chr == 'B') {
        std::cout << "Number to Divide: ";
        std::cin >> flt;
        std::cout << "Divisor (WIP: calculated as num / 2^div): ";
        std::cin >> calculator;
        calculator *= -1;
    }
    else {
        std::cout << "Number to squareroot (aprox. with ~1.04% accuracy): ";
        std::cin >> flt;
        calculator = 0;
    }

    return chr;
}

//used for making the binary information easier to see
void spaceBin(std::string& str) {
    std::string temp;
    for (int i = 0; i < 32; i++) {
        if (i == 1 || i == 9) temp = temp + ' ';
        temp = temp + str[i];
    }
    str = temp;
}

//used for testing purposes (old)
void printBin(float flt, float target, float result, long i, long copy) {
    std::string x, z;
    std::string f, t, r;
    floatToBinary(flt, f); floatToBinary(target, t); floatToBinary(result, r);
    longToBinary(i, x); longToBinary(copy, z);
    spaceBin(f); spaceBin(r); spaceBin(t); spaceBin(x); spaceBin(z);
    std::cout << "starting float: " << flt
        << "\nbinary for float: " << f
        << "\n\n"
        << "target float: " << target
        << "\nbinary for float: " << t
        << "\n\n"
        << "resulting float: " << result
        << "\nbinary for result: " << r
        << "\n\n"
        << "long as decimal: " << copy
        << "\nafter calculation: " << i
        << "\nas binary: " << z
        << "\n           " << x
        << "\n";

    //exponent & sign correct, mantissa incorrect(kind of) //TODO: fix the mantissa 
    std::string finfo, tinfo, rinfo;
    floatInfo(f, finfo);  floatInfo(t, tinfo); floatInfo(r, rinfo);
    std::cout << "\n\n" << finfo << '\n' << tinfo << '\n' << rinfo << '\n';
}

void printBin(float flt, float target, float result) {
    std::string f, t, r;
    floatToBinary(flt, f); floatToBinary(target, t); floatToBinary(result, r);
    //longToBinary(i, x); longToBinary(copy, z);
    spaceBin(f); spaceBin(r); spaceBin(t); //spaceBin(x); spaceBin(z);
    std::cout << std::fixed << std::setprecision(10)
	<< "starting float: " << flt
	<< "\nbinary for float: " << f
	<< "\n\n"
	<< "target float: " << target
	<< "\nbinary for float: " << t
	<< "\n\n"
	<< "resulting float: " << result
	<< "\nbinary for result: " << r
	<< "\n";
}

// negative for devide, positive for multi, also does num */ 2^multi
void divMulti(float& flt, float multi) {

    multi *= 8388608;

    long i;

    i = *(long*)&flt;
    i += multi;

    flt = *(float*)&i;

}

//approximation of square root by bit manipulation
void squareRootBin(float& result) {
    long i;
    i = *(long*)&result;
    i = i >> 1;
    i += 531956979; //correction magic number
	//how it works:
	// >> 1 divides both exponent and mantissa by 2
	// 528482304 + 3474675 adds back the bias (127) since it is unaffected by the bit shift dividing by two
	// 528482304 is the exponent part of the correction(63.5)
	// which was made to add 63 to the exponent
	// which is the closest correction you could get to the (63.5) on the exponent alone
	// 3474675 is the binary for sqrt(2) (1.01101010000010011110011) but without the decimal
	// which is then added to the mantissa since the 0.5 is what is left in the exponent
	// x^0.5 is sqrt(x), and this is binary so x = 2
	// you add sqrt(2) to the mantissa since its equivlant to adding 0.5 to the exponent
	// i still dont KNOW why, but i kind of guessed that that's what it was supposed to be and it worked
    result = *(float*)&i;
}

int main() {
    float flt = 4.5F, target, result, calculator;

    //long i, copy; //used for testing (old)

    char method = askUserInput(flt, calculator);
    result = flt;

    if (method == 'a' || method == 'A') {
        target = flt * calculator;
        divMulti(result, calculator);
    }
    else if (method == 'b' || method == 'B') {
        target = flt / calculator;
        divMulti(result, calculator);
    }
    else {
        target = sqrt(flt); //accurate calculation for testing purposes
        squareRootBin(result);  //approximation of square root
    }

    printBin(flt, target, result);

    //divMulti(result, -2); // negative for devide, positive for 
    //printBin(flt, target, result, i, copy); //used for testing (old)


    return 0;
}