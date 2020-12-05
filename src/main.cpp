#include "utils.h"

int day1a();
int day1b();
int day2a();
int day2b();
int64_t day3a();
int64_t day3b();
int day4a();
int day4b();
int day5a();
int day5b();
int day6a();
int day6b();

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
