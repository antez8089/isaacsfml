#ifndef WALKER_H
#define WALKER_H
#include "enemy.h"
#include <math.h>
class Walker : public Enemy {
    private:
    sf::Clock touching_clock;


    public:
    Walker();
    ~Walker() = default;
    virtual void update_enemy(const float& dt, Entity& player) override;
    virtual void update_collisions(Entity& second_entity) override;
};


#endif