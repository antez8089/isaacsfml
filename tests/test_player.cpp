#include "catch_amalgamated.hpp"
#include "../src/entity/characters/player.h"
#include "../src/exceptions/asset_not_found.h"
TEST_CASE("Player tests", "[player]")
{
    Player player;
    SECTION("Tests getters")
    {
        CHECK(player.get_range() == 600);
        CHECK(player.get_alive() == true);
    }
    SECTION("Tests setters")
    {
        player.set_range(500);
        CHECK(player.get_range() == 500);
        player.set_attack_speed(500);
        CHECK(player.get_attack_speed() == 500);
    }
}