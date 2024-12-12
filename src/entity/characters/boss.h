#ifndef BOSS_H
#define BOSS_H
#include "stalker.h"
#include "../health/bossbar.h"
#include "../bullets/boss_bullet_list.h"
class Boss : public Stalker {
    private:
    sf::Clock shooting_clock;
    sf::Clock touching_clock;
    sf::Clock charging_clock;
    StalkerBulletList* stalker_bullets = new StalkerBulletList();
    BossBulletList* boss_bullets = new BossBulletList();
    BossBar* bossbar = new BossBar();

    public:
    Boss();
    ~Boss();
    void update_enemy(const float& dt, Entity& player) override;
    void render(sf::RenderWindow* window) override;
    void remove_health() override;
    bool get_if_boss_alive();
    void update_collisions(Entity& second_entity) override;
};


#endif