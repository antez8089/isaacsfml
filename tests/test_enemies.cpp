#include "catch_amalgamated.hpp"
#include "../src/entity/characters/enemies_list.h"
#include "../src/entity/characters/enemy.h"
#include "../src/exceptions/asset_not_found.h"
#include "../src/game.h"
TEST_CASE("Enemiestests", "[enemies]")
{
    EnemiesList enemies_list;
    Enemy enemy;

    SECTION("Tests getters and setters")
    {
        enemy.set_enemies_starting_health(100);
        CHECK(enemy.get_starting_health() == 100);
    }
    SECTION("Tests add and remove")
    {
        enemies_list.add_enemy();
        CHECK(enemies_list.get_size() == 1);
        enemies_list.restart();
        CHECK(enemies_list.get_size() == 0);
    }
}