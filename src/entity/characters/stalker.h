#ifndef STALKER_H
#define STALKER_H
#include "walker.h"
#include "../bullets/stalker_bullet_list.h"
#include <math.h>
#include <random>

class Stalker : public Walker {
    private:
    sf::Clock shooting_clock;
    sf::Clock touching_clock;
    StalkerBulletList* stalker_bullets = new StalkerBulletList();


    public:
    Stalker();
    ~Stalker();
    virtual void update_enemy(const float& dt, Entity& player) override;
    virtual void render(sf::RenderWindow* window) override;
    virtual void update_collisions(Entity& second_entity) override;
};


#endif