#ifndef BULLET_LIST_H
#define BULLET_LIST_H
#include "bullet_class.h"
#include <vector>
#include <memory>

class BulletList {
    protected:
        sf::Clock bullet_clock;
        std::vector<std::unique_ptr<Bullet>> bullets;
        bool is_pressed = false;
    public:
        BulletList() = default;
        virtual ~BulletList() = default;
        virtual void add_bullet(char direction, sf::Vector2f player_position, float attack_speed);
        void render(sf::RenderWindow* window, float range);
        virtual void update(const float& dt, sf::Vector2f player_position, float attack_speed);
        void check_bullets(sf::RenderWindow* window, float range);
        void remove_bullet(const std::unique_ptr<Bullet>& bullet);
        void update_collisions(Entity& entity);
        void clear();
        int get_size();
};

#endif