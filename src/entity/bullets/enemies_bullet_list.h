#ifndef ENEMIES_BULLET_LIST_H
#define ENEMIES_BULLET_LIST_H
#include "bullet_list.h"

class EnemiesBulletList : public BulletList {
    public:
        virtual void update(const float& dt, sf::Vector2f enemy_position, float attack_speed);
        EnemiesBulletList() = default;
        virtual ~EnemiesBulletList() = default;
};

#endif