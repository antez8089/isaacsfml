#include "catch_amalgamated.hpp"
#include "../src/menu/menu.h"
#include "../src/exceptions/asset_not_found.h"

TEST_CASE("Menu tests", "[menu]") {
    Menu menu;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    menu.init_menu(&window);
    SECTION("Tests is active") {
        REQUIRE(menu.is_active() == true);
    }
    SECTION("get pressed items") {
        REQUIRE(menu.get_pressed_items() == 0);
    }
    SECTION("test set active")
    {
        menu.set_active(false);
        REQUIRE(menu.is_active() == false);
    }
    SECTION("test move up and move down")
    {
        menu.move_down();
        CHECK(menu.get_pressed_items() == 1);
        menu.move_down();
        CHECK(menu.get_pressed_items() == 2);
        menu.move_down();
        CHECK(menu.get_pressed_items() == 3);
        menu.move_down();
        CHECK(menu.get_pressed_items() == 3);
        menu.move_up();
        CHECK(menu.get_pressed_items() == 2);
        menu.move_up();
        CHECK(menu.get_pressed_items() == 1);
        menu.move_up();
        CHECK(menu.get_pressed_items() == 0);
    }
    SECTION("test restart")
    {
        menu.set_active(false);
        REQUIRE(menu.is_active() == false);
        menu.restart();
        REQUIRE(menu.get_pressed_items() == 0);
        REQUIRE(menu.is_active() == true);
    }

}