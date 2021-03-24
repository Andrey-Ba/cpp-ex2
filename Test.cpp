#include <iostream>
#include "doctest.h"
#include "Board.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Check post input")
{
    Board b;
    CHECK_NOTHROW(b.post(1,2,Direction::Vertical, "Hello"));
    CHECK_THROWS(b.post(1,-1,Direction::Vertical,"Hi"));
    CHECK_THROWS(b.post(-1,1,Direction::Vertical,"Hi"));
    CHECK_THROWS(b.post(1,-1,Direction::Horizontal,"Hi"));
    CHECK_THROWS(b.post(-1,1,Direction::Horizontal,"Hi"));
    CHECK_NOTHROW(b.post(5,7,Direction::Vertical, "Hi"));
}

TEST_CASE("Test read input")
{
    Board b;
    CHECK_THROWS(b.read(0,-1,Direction::Horizontal,5));
    CHECK_THROWS(b.read(-1,0,Direction::Horizontal,5));
    CHECK_NOTHROW(b.post(100,200,Direction::Horizontal,"Test"));
    CHECK_THROWS(b.read(0,-1,Direction::Vertical,100));
    CHECK_THROWS(b.read(-1,0,Direction::Vertical,100));
}

TEST_CASE("Test read output")
{
    Board b;
    CHECK("_____" == b.read(0,0,Direction::Horizontal,5));
    b.post(0,0,Direction::Horizontal,"TestTH3 Board");
    CHECK("TestTH3 Board" == b.read(0,0,Direction::Horizontal,13));
    CHECK("TestTH3 B" == b.read(0,0,Direction::Horizontal,9));
    CHECK("tTH3 Board" == b.read(0,3,Direction::Horizontal,10));
    b.post(0,12, Direction::Vertical, "ReadMe, Very Importent{}**");
    CHECK("ReadMe, Very Importent{}**" == b.read(0,12,Direction::Vertical,26));
    CHECK("TestTH3 BoarR" == b.read(0,0,Direction::Horizontal,13));
    CHECK(b.read(4,0,Direction::Horizontal,13)=="____________M");
    b.post(3,12,Direction::Horizontal,"TEEESSSTTT");
    CHECK("SSSTTT______" == b.read(3, 16, Direction::Horizontal,12));
    CHECK("__________" == b.read(100,200,Direction::Vertical,10));
    // b.show();
}