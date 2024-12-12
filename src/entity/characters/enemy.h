#ifndef ENEMY_H
#define ENEMY_H
#include "../entity.h"
#include "../bullets/enemies_bullet_list.h"

class Enemy : public Entity {
    protected:
        EnemiesBulletList* bullets = new EnemiesBulletList();
        float attack_speed = 450;
        float range = 500;
        inline static int starting_health;
    public:
        Enemy();
        virtual ~Enemy();
        virtual void render(sf::RenderWindow* window) override;
        virtual void update_enemy(const float& dt, Entity& player);
        virtual void update_collisions(Entity& second_entity);
        static void set_enemies_starting_health(int new_health);
        static int get_starting_health();
};

#endif