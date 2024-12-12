#include "boss.h"
#include <random>

Boss::Boss() {
    std::random_device rand_dev;
    std::mt19937 rng(rand_dev());
    texture.loadFromFile("assets/Boss.png");
    entity.setTexture(texture, true);
    movement_speed = 200;
    health = 25;
    int start_pos_x = 611;
    int start_pos_y = 325;
    entity.setPosition(sf::Vector2f(start_pos_x, start_pos_y));
    touching_clock.restart();
}

Boss::~Boss() {
    delete bossbar;
    delete stalker_bullets;
    delete boss_bullets;
}
void Boss::update_enemy(const float& dt, Entity& player) {
        sf::Vector2f player_position = player.get_middle_position();
        sf::Vector2f enemy_position = get_middle_position();
        float x = player_position.x - enemy_position.x;
        float y = player_position.y - enemy_position.y;
        float length = sqrt(x * x + y * y);
        x /= 2*length;
        y /= 2*length;
        move(x, y, dt);
        if (shooting_clock.getElapsedTime().asSeconds() >= 4) {
            if(x > 0 && abs(y) < 0.3) {
                stalker_bullets->add_bullet('R', enemy_position, 500);
                shooting_clock.restart();
            } else if(x < 0 && abs(y) < 0.3) {
                stalker_bullets->add_bullet('L', enemy_position, 500);
                shooting_clock.restart();
            } else if(abs(x) < 0.3 && y > 0) {
                stalker_bullets->add_bullet('U', enemy_position, 500);
                shooting_clock.restart();
            } else if(abs(x) < 0.3 && y < 0) {
                stalker_bullets->add_bullet('D', enemy_position, 500);
                shooting_clock.restart();
            }
        }
        stalker_bullets->update(dt, enemy_position, 500);
        boss_bullets->update(dt, enemy_position, attack_speed);
        if (this->check_collision(player)) {
            if(touching_clock.getElapsedTime().asSeconds() <= dt) {
                player.remove_health();
            } else if((touching_clock.getElapsedTime().asSeconds()>=5)){
                touching_clock.restart();
            }
        } else {
            touching_clock.restart();
        }
        // if(health <= 0) {
        //     kill();
        // }
        if(!get_if_boss_alive()) {
            kill();
        }
}


void Boss::render(sf::RenderWindow* window) {
    window->draw(entity);
    stalker_bullets->render(window, range);
    bullets->render(window, range);
    boss_bullets->render(window, range);
    bossbar->render(window);
}

void Boss::remove_health() {
    health--;
    bossbar->remove_health();
}

bool Boss::get_if_boss_alive() {
    return bossbar->get_is_alive();
}

void Boss::update_collisions(Entity& second_entity) {
    boss_bullets->update_collisions(second_entity);
    stalker_bullets->update_collisions(second_entity);

}