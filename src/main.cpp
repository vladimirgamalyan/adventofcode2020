#include <iostream>
#include <cassert>
#include "day1.h"

int main()
{
    std::cout << day1a() << "\n";
    std::cout << day1b() << "\n";

    assert(day1a() == 646779);
    assert(day1b() == 246191688);
}
