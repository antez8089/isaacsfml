#include "boss_bullet_list.h"

void BossBulletList::update(const float& dt, sf::Vector2f enemy_position, float attack_speed) {
    if(bullet_clock.getElapsedTime().asSeconds()>=1.5) {
        add_bullet('U', enemy_position, attack_speed);
        add_bullet('D', enemy_position, attack_speed);
        add_bullet('L', enemy_position, attack_speed);
        add_bullet('R', enemy_position, attack_speed);
        add_bullet('P', enemy_position, attack_speed/sqrt(2));
        add_bullet('O', enemy_position, attack_speed/sqrt(2));
        add_bullet('K', enemy_position, attack_speed/sqrt(2));
        add_bullet('Z', enemy_position, attack_speed/sqrt(2));
        bullet_clock.restart();
    }
    for(const std::unique_ptr<Bullet>& bullet: bullets) {
        bullet->set_texture("assets/enemies_bullet.png");
        bullet->update(dt);
    }
}

void BossBulletList::add_bullet(char direction, sf::Vector2f player_position, float attack_speed) {
    std::unique_ptr<BossBullet> added_bullet = std::make_unique<BossBullet>(direction, player_position, attack_speed);
    bullets.push_back(std::move(added_bullet));
}