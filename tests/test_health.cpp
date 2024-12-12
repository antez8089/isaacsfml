#include "catch_amalgamated.hpp"
#include "../src/entity/health/heart.h"
#include "../src/entity/health/healthbar.h"

TEST_CASE("Healthbar tests", "[healthbar]") {
    HealthBar healthbar;
    SECTION("Tests is alive") {
        REQUIRE(healthbar.get_is_alive() == true);
    }
    SECTION("Tests max health") {
        REQUIRE(healthbar.get_max_health() == 5);
    }
    SECTION("Test if has 5 hearts") {
        REQUIRE(healthbar.get_current_health() == 5);
    }
    SECTION("Test set health") {
        healthbar.set_health(3);
        REQUIRE(healthbar.get_current_health() == 3);
    }
    SECTION("Test add health") {
        healthbar.set_health(3);
        healthbar.add_health();
        REQUIRE(healthbar.get_current_health() == 4);
    }
    SECTION("Test remove health") {
        healthbar.set_health(3);
        healthbar.remove_health();
        REQUIRE(healthbar.get_current_health() == 2);
    }
    SECTION("Test if is alive") {
        healthbar.set_health(0);
        REQUIRE(healthbar.get_is_alive() == false);
    }
}