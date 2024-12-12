#include "enemies_bullet_list.h"


void EnemiesBulletList::update(const float& dt, sf::Vector2f enemy_position, float attack_speed) {
    if(bullet_clock.getElapsedTime().asSeconds()>=1.5) {
        add_bullet('U', enemy_position, attack_speed);
        add_bullet('D', enemy_position, attack_speed);
        add_bullet('L', enemy_position, attack_speed);
        add_bullet('R', enemy_position, attack_speed);
        bullet_clock.restart();
    }
    for(const std::unique_ptr<Bullet>& bullet: bullets) {
        bullet->set_texture("assets/enemies_bullet.png");
        bullet->update(dt);
    }
}