#ifndef BOSS_BULLET_H
#define BOSS_BULLET_H
#include "bullet_class.h"

class BossBullet : public Bullet {

    public:
    BossBullet(char direction, sf::Vector2f player_position, float attack_speed);
    ~BossBullet() = default;
    void update(const float& dt) override;

};

#endif