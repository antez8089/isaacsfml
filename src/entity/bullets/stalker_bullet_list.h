#ifndef STALKER_BULLET_LIST_H
#define STALKER_BULLET_LIST_H
#include "bullet_list.h"

class StalkerBulletList : public BulletList {
    public:
        virtual void update(const float& dt, sf::Vector2f enemy_position, float attack_speed) override;
        StalkerBulletList() = default;
        virtual ~StalkerBulletList() = default;
};

#endif