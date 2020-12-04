#include <iostream>
#include <cassert>
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"

int main()
{
    assert(day1a() == 646779);
    assert(day1b() == 246191688);
    assert(day2a() == 416);
    assert(day2b() == 688);
    assert(day3a() == 218);
    assert(day3b() == 3847183340);
    assert(day4a() == 196);
    assert(day4b() == 114);

    std::cout << day4a() << "\n";
    std::cout << day4b() << "\n";
}
