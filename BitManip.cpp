// BitManip.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>
#include <string>
#include <inttypes.h>

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

void askUserInput(float &ref){
    std::cout << "insert number to half: ";
    std::cin >> ref;
}

int main()
{   
    float flt = 4.5F, target, result;
    
    long i, copy;

    long* lp = nullptr;
    float* fp = nullptr;


    askUserInput(flt);
    target = flt / 2;
    
    
    lp = (long*) &flt;

    i = *(long*)  &flt;

    fp = (float*) &i;
    

    
    copy = i;
    i = i - 8388608;
    
    result = *fp;
    

    std::bitset<32> x(i), z(copy);
    std::string y, t, r;
    floatToBinary(flt, y);
    floatToBinary(target, t);
    floatToBinary(result, r);
    /*std::cout << i << ' ' << *lp << ' ' << *fp << ' ' << flt
              << '\n' << x << ' ' << y
              << '\n' << t << ' ' << z;
    */
    std::cout << "starting float: " << flt 
              << "\nbinary for float: " << y
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
              << "\n           " << x;
              << "\n";

    return 0;
}
