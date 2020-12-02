#include <iostream>
#include <cassert>
#include "day1.h"
#include "day2.h"

int main()
{
    assert(day1a() == 646779);
    assert(day1b() == 246191688);
    assert(day2a() == 416);
    assert(day2b() == 688);

    std::cout << day2a() << "\n";
    std::cout << day2b() << "\n";
}
