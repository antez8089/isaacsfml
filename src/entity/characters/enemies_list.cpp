#include "enemies_list.h"

void EnemiesList::add_enemy() {
    std::unique_ptr<Enemy> added_enemy = std::make_unique<Enemy>();
    enemies.push_back(std::move(added_enemy));
}

void EnemiesList::add_boss() {
    std::unique_ptr<Boss> added_enemy = std::make_unique<Boss>();
    enemies.push_back(std::move(added_enemy));
}

void EnemiesList::add_walker() {
    std::unique_ptr<Walker> added_enemy = std::make_unique<Walker>();
    enemies.push_back(std::move(added_enemy));
}

void EnemiesList::add_stalker() {
    std::unique_ptr<Stalker> added_enemy = std::make_unique<Stalker>();
    enemies.push_back(std::move(added_enemy));
}

void EnemiesList::render(sf::RenderWindow* window) {
    for (const std::unique_ptr<Enemy>& enemy: enemies) {
        enemy->render(window);
    }
}

void EnemiesList::update(const float& dt, Entity& player) {
    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i]->update_enemy(dt, player);
        if(!enemies[i]->is_alive()) {
            remove_enemy(enemies[i]);
        }
    }
}

void EnemiesList::init_enemies(int enemies_amount, bool is_boss) {
    srand((unsigned)time(NULL));
    if(!is_boss){
        for (int i = 0; i < enemies_amount; i++) {
            int number = rand()%3;
            if (number == 0) {
                add_enemy();
            } else if(number == 1) {
                add_stalker();
            } else {
                add_walker();
            }
        }
    } else {
        add_boss();
    }
}

void EnemiesList::update_collisions(Entity& entity) {
    for (const std::unique_ptr<Enemy>& enemy: enemies) {
        enemy->update_collisions(entity);
    }
}

std::vector<std::unique_ptr<Enemy>>& EnemiesList::get_list() {
    return enemies;
}

void EnemiesList::remove_enemy(const std::unique_ptr<Enemy>& enemy) {
    enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy));
}

int EnemiesList::get_size() {
    return enemies.size();
}

void EnemiesList::restart() {
    enemies.clear();
}