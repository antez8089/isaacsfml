#ifndef BOSS_BULLET_LIST_H
#define BOSS_BULLET_LIST_H
#include "boss_bullet.h"
#include "stalker_bullet_list.h"
#include <math.h>

class BossBulletList : public StalkerBulletList {
    public:
        BossBulletList() = default;
        ~BossBulletList() = default;
        void update(const float& dt, sf::Vector2f enemy_position, float attack_speed) override;
        void add_bullet(char direction, sf::Vector2f player_position, float attack_speed) override;
        
};

#endif