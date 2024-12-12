#ifndef BULLET_CLASS_H
#define BULLET_CLASS_H
#include "../entity.h"

class Bullet : public Entity {
    protected:
        char direction;
        sf::Vector2f starting_position;
    public:
        Bullet(char direction, sf::Vector2f player_position, float attack_speed);
        virtual ~Bullet() = default;
        virtual void update(const float& dt) override;
        bool is_bullet_out(sf::RenderWindow* window, float range);
};
#endif