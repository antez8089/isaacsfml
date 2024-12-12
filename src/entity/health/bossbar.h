#ifndef BOSSBAR_H
#define BOSSBAR_H
#include "bar.h"
#include "healthbar.h"
#include <vector>

class BossBar
{
    private:
        std::vector<std::unique_ptr<Bar>> bossbar;
        int max_health = 25;
        int current_health = 25;
        bool is_alive = true;
    public:
        BossBar();
        ~BossBar() = default;
        int get_current_health();
        int get_max_health();
        bool get_is_alive();
        void render(sf::RenderWindow* window);
        void add_health();
        void remove_health();
        void set_health(int new_health);
};
#endif