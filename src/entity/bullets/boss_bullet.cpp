#include "boss_bullet.h"

void BossBullet::update(const float& dt) {
    if(direction == 'U')
        move(0, -1.f, dt);
    else if(direction == 'D')
        move(0, 1.f, dt);
    else if(direction == 'L')
        move(-1.f, 0, dt);
    else if(direction == 'R')
        move(1.f, 0, dt);
    else if(direction == 'P')
        move(1.f, 1.f, dt);
    else if(direction == 'O')
        move(-1.f, 1.f, dt);
    else if(direction == 'K')
        move(1.f, -1.f, dt);
    else
        move(-1.f, -1.f, dt);
}

BossBullet::BossBullet(char bullet_direction, sf::Vector2f player_position, float attack_speed): Bullet(bullet_direction, player_position, attack_speed) {}