#include "catch_amalgamated.hpp"
#include "../src/menu/endmenu.h"
#include "../src/exceptions/asset_not_found.h"

TEST_CASE("end menu tests", "[end_menu]")
{
    EndMenu endmenu;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    endmenu.init_end_menu(&window, 0, true);
    SECTION("Tests is exit")
    {
        CHECK(endmenu.is_exit() == false);
    }
    SECTION("Tests setters and restart")
    {
        CHECK(endmenu.get_pressed_items() == 0);
        CHECK(endmenu.is_active() == true);
        endmenu.set_active(false);
        CHECK(endmenu.is_active() == false);
    }
    SECTION("tests move up and down functions")
    {
        CHECK(endmenu.get_pressed_items() == 0);
        endmenu.move_down();
        CHECK(endmenu.get_pressed_items() == 1);
        endmenu.move_down();
        CHECK(endmenu.get_pressed_items() == 1);
        endmenu.move_up();
        CHECK(endmenu.get_pressed_items() == 0);
        endmenu.move_up();
        CHECK(endmenu.get_pressed_items() == 0);
    }

}