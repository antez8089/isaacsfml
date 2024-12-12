#include "catch_amalgamated.hpp"
#include "../src/map/map.h"
#include "../src/room/room.h"

TEST_CASE("Map testing", "[Map]")
{
    Map map;
    for(int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (i == 3 && j == 3) {
                REQUIRE(map.get_room(i, j)->get_cleared() == true);
            } else {
                REQUIRE(map.get_room(i, j)->get_cleared() == false);
            }
        }
    }
}