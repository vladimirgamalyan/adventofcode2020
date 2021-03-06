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
int day7a();
int day7b();
int day8a();
int day8b();
long long day9a();
long long day9b();
long long day10a();
long long day10b();
int day11a();
int day11b();
int day12a();
int day12b();
int day13a();
uint64_t day13b();
uint64_t day14a();
uint64_t day14b();
int day15a();
int day15b();
int day16a();
long long day16b();
int day17a();
int day17b();
long long day18a();
long long day18b();
long long day19a();
long long day19b();
long long day20a();
long long day20b();
std::pair<int, std::string> day21();

int main(int argc, char** argv)
{
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    int res = context.run();
    if (context.shouldExit())
        return res;
    std::cout << "\n";

    //assert(day1a() == 646779);
    //assert(day1b() == 246191688);
    //assert(day2a() == 416);
    //assert(day2b() == 688);
    //assert(day3a() == 218);
    //assert(day3b() == 3847183340);
    //assert(day4a() == 196);
    //assert(day4b() == 114);
    //assert(day5a() == 998);
    //assert(day5b() == 676);
    //assert(day6a() == 6457);
    //assert(day6b() == 3260);
    //assert(day7a() == 121);
    //assert(day7b() == 3805);
    //assert(day8a() == 1814);
    //assert(day8b() == 1056);
    //assert(day9a() == 21806024);
    //assert(day9b() == 2986195);
    //assert(day10a() == 2432);
    //assert(day10b() == 453551299002368);
    //assert(day11a() == 2354);
    //assert(day11b() == 2072);
    //assert(day12a() == 1177);
    //assert(day12b() == 46530);
    //assert(day13a() == 115);
    //assert(day13b() == 756261495958122);
    //assert(day14a() == 11612740949946);
    //assert(day14b() == 3394509207186);
    //assert(day15a() == 870);
    //assert(day15b() == 9136);
    //assert(day16a() == 23054);
    //assert(day16b() == 51240700105297);
    //assert(day17a() == 362);
    //assert(day17b() == 1980);
    //assert(day18a() == 13976444272545);
    //assert(day18b() == 88500956630893);
    //assert(day19a() == 203);
    //assert(day19b() == 304);
    //assert(day20a() == 16192267830719);
    //assert(day20b() == 1909);
    assert(day21().first == 2170);
    assert(day21().second == "nfnfk,nbgklf,clvr,fttbhdr,qjxxpr,hdsm,sjhds,xchzh");

    //std::cout << day21().first << "\n";
    //std::cout << day21().second << "\n";
}
