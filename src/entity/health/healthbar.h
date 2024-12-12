#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include "heart.h"
#include <vector>
#include <memory>
class HealthBar
{
    private:
        std::vector<std::unique_ptr<Heart>> healthbar;
        int max_health = 5;
        int current_health = 5;
        bool is_alive = true;
    public:
        HealthBar();
        ~HealthBar() = default;
        int get_current_health();
        int get_max_health();
        bool get_is_alive();
        void add_health();
        void remove_health();
        void render(sf::RenderWindow* window);
        void set_health(int new_health);
};
#endif