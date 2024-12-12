#ifndef ENEMIES_LIST_H
#define ENEMIES_LIST_H
#include "walker.h"
#include "stalker.h"
#include "boss.h"  
#include <vector>
#include <memory>

class EnemiesList {
    private:
        std::vector<std::unique_ptr<Enemy>> enemies;
    public:
        EnemiesList() = default;
        ~EnemiesList() = default;
        void add_enemy();
        void add_boss();
        void add_stalker();
        void add_walker();
        void render(sf::RenderWindow* window);
        void update(const float& dt, Entity& player);
        void init_enemies(int enemies_amount, bool is_boss);
        void update_collisions(Entity& entity);
        std::vector<std::unique_ptr<Enemy>>& get_list();
        void remove_enemy(const std::unique_ptr<Enemy>& enemy);
        int get_size();
        void restart();
};

#endif