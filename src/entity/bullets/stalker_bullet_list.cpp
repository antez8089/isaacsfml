#include "stalker_bullet_list.h"

void StalkerBulletList::update(const float& dt, sf::Vector2f enemy_position, float attack_speed) {
    for(const std::unique_ptr<Bullet>& bullet: bullets) {
        bullet->set_texture("assets/enemies_bullet.png");
        bullet->update(dt);
    }
}