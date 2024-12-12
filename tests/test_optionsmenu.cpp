#include "catch_amalgamated.hpp"
#include "../src/menu/optionsmenu.h"
#include "../src/exceptions/asset_not_found.h"
TEST_CASE("Options menu tests", "[optionsmenu]")
{
    OptionsMenu optionsmenu;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    optionsmenu.init_options_menu(&window);
    SECTION("Tests is active")
    {
        CHECK(optionsmenu.is_active() == false);
    }
    SECTION("Tests is exit")
    {
        CHECK(optionsmenu.is_exit() == false);
    }
    SECTION("Tests setters and restart")
    {
        optionsmenu.set_active(true);
        CHECK(optionsmenu.get_option_index() == 0);
        CHECK(optionsmenu.is_active() == true);
        optionsmenu.restart();
        CHECK(optionsmenu.is_active() == false);
    }
    SECTION("check modes")
    {
        CHECK(optionsmenu.get_is_easy() == true);
        CHECK(optionsmenu.get_is_medium() == false);
        CHECK(optionsmenu.get_is_hard() == false);
        CHECK(optionsmenu.get_sound_on() == true);
        CHECK(optionsmenu.get_if_save() == true);
    }
    SECTION("check move up and down")
    {
        optionsmenu.move_down();
        CHECK(optionsmenu.get_option_index() == 1);
        optionsmenu.move_down();
        CHECK(optionsmenu.get_option_index() == 2);
        optionsmenu.move_down();
        CHECK(optionsmenu.get_option_index() == 3);
        optionsmenu.move_up();
        CHECK(optionsmenu.get_option_index() == 2);
        optionsmenu.move_up();
        CHECK(optionsmenu.get_option_index() == 1);
        optionsmenu.move_up();
        CHECK(optionsmenu.get_option_index() == 0);
        optionsmenu.move_up();
        CHECK(optionsmenu.get_option_index() == 0);
    }
    SECTION("check move left and right")
    {
        CHECK(optionsmenu.get_option_index() == 0);
        optionsmenu.move_right();
        CHECK(optionsmenu.get_selected_item_index(0) == 1);
        optionsmenu.move_right();
        CHECK(optionsmenu.get_selected_item_index(0) == 2);
        optionsmenu.move_right();
        CHECK(optionsmenu.get_selected_item_index(0) == 2);
        optionsmenu.move_down();
        CHECK(optionsmenu.get_option_index() == 1);
        optionsmenu.move_right();
        CHECK(optionsmenu.get_selected_item_index(1) == 1);
        optionsmenu.move_left();
        CHECK(optionsmenu.get_selected_item_index(1) == 0);
        optionsmenu.move_left();
        CHECK(optionsmenu.get_selected_item_index(1) == 0);
        optionsmenu.move_down();
        CHECK(optionsmenu.get_option_index() == 2);
        optionsmenu.move_right();
        CHECK(optionsmenu.get_selected_item_index(2) == 1);
    }

}