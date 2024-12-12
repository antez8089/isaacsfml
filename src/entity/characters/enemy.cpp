#include "enemy.h"
#include <random>

Enemy::Enemy() {
    std::random_device rand_dev;
    std::mt19937 rng(rand_dev());
    std::uniform_int_distribution<std::mt19937::result_type> pos_x(300,1200);
    std::uniform_int_distribution<std::mt19937::result_type> pos_y(300,600);
    texture.loadFromFile("assets/enemy.png");
    entity.setTexture(texture);
    movement_speed = 350;
    health = get_starting_health();
    int start_pos_x = pos_x(rng);
    int start_pos_y = pos_y(rng);
    entity.setPosition(sf::Vector2f(start_pos_x, start_pos_y));
}

Enemy::~Enemy() {
    delete bullets;
}

void Enemy::render(sf::RenderWindow* window) {
    window->draw(entity);
    bullets->render(window, range);
}

void Enemy::update_enemy(const float& dt, Entity& player) {
    int number = rand() % 4;
    switch(number) {
        case 0:
            if (entity.getPosition().y > 100) {
                move(0, -1.f, dt);
            }
            break;
        case 1:
            if (entity.getPosition().y + get_size().y < 800) {
                move(0, 1.f, dt);
            }
            break;
        case 2:
            if (entity.getPosition().x > 100) {
                move(-1.f, 0, dt);
            }
            break;
        case 3:
            if (entity.getPosition().x + get_size().x< 1400) {
                move(1.f, 0, dt);
            }
            break;
    }

    bullets->update(dt, get_middle_position(), attack_speed);
    if(health <= 0) {
        kill();
    }
}

void Enemy::update_collisions(Entity& second_entity) {
    bullets->update_collisions(second_entity);
}

void Enemy::set_enemies_starting_health(int new_health) {
    starting_health = new_health;
}

int Enemy::get_starting_health() {
    return starting_health;
}