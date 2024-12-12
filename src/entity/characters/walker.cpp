#include "walker.h"
#include <random>
#include <iostream>


Walker::Walker() {
    std::random_device rand_dev;
    std::mt19937 rng(rand_dev());
    std::uniform_int_distribution<std::mt19937::result_type> pos_x(300,1200);
    std::uniform_int_distribution<std::mt19937::result_type> pos_y(300,600);
    texture.loadFromFile("assets/Fatty.png");
    entity.setTexture(texture, true);
    movement_speed = 350;
    health = starting_health;
    int start_pos_x = pos_x(rng);
    int start_pos_y = pos_y(rng);
    entity.setPosition(sf::Vector2f(start_pos_x, start_pos_y));
}


void Walker::update_enemy(const float& dt, Entity& player) {
        sf::Vector2f player_position = player.get_middle_position();
        sf::Vector2f enemy_position = get_middle_position();
        float x = player_position.x - enemy_position.x;
        float y = player_position.y - enemy_position.y;
        float length = sqrt(x * x + y * y);
        x /= 2*length;
        y /= 2*length;
        move(x, y, dt);
        if (this->check_collision(player)) {
            if(touching_clock.getElapsedTime().asSeconds() <= dt) {
                player.remove_health();
            } else if((touching_clock.getElapsedTime().asSeconds()>=5)){
                touching_clock.restart();
            }
        } else {
            touching_clock.restart();
        }
        if(health <= 0) {
            kill();
        }
    }

void Walker::update_collisions(Entity& second_entity) {
    bullets->update_collisions(second_entity);
}
