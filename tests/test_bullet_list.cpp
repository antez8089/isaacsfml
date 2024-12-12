#include "../src/entity/bullets/bullet_list.h"
#include "catch_amalgamated.hpp"
#include "../src/entity/characters/player.h"

TEST_CASE("bullet list test", "[bullet_list]") {
    BulletList bullet_list;

    REQUIRE(!bullet_list.get_size());

    SECTION("adding bullets") {
        bullet_list.add_bullet('U', sf::Vector2f(1, 1), 2);
        REQUIRE(bullet_list.get_size() == 1);
    }

    SECTION("removing bullet") {
        bullet_list.add_bullet('U', sf::Vector2f(1, 1), 2);
        bullet_list.add_bullet('U', sf::Vector2f(1, 1), 2);
        REQUIRE(bullet_list.get_size() == 2);
        bullet_list.clear();
        REQUIRE(!bullet_list.get_size());
    }

    SECTION("collision") {
        Player entity;
        entity.set_position(1, 1);
        bullet_list.add_bullet('U', sf::Vector2f(1, 1), 2);
        bullet_list.add_bullet('U', sf::Vector2f(300, 300), 2);
        REQUIRE(bullet_list.get_size() == 2);
        bullet_list.update_collisions(entity);
        REQUIRE(bullet_list.get_size() == 1);
    }
}