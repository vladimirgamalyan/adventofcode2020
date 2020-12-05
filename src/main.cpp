#include <iostream>
#include <cassert>
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"

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
    assert(day5a() == 998);
    assert(day5b() == 676);

    std::cout << day6a() << "\n";
}
