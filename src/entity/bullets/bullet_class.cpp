#include "bullet_class.h"

Bullet::Bullet(char bullet_direction, sf::Vector2f player_position, float attack_speed): direction(bullet_direction) {
    texture.loadFromFile("assets/bullet.png");
    entity.setTexture(texture);
    movement_speed = attack_speed;
    starting_position = player_position;
    entity.setPosition(player_position.x-(entity.getTexture()->getSize().x/2), player_position.y-(entity.getTexture()->getSize().y/2));
}

void Bullet::update(const float& dt) {
    if(direction == 'U')
        move(0, -1.f, dt);
    else if(direction == 'D')
        move(0, 1.f, dt);
    else if(direction == 'L')
        move(-1.f, 0, dt);
    else
        move(1.f, 0, dt);
}

bool Bullet::is_bullet_out(sf::RenderWindow* window, float range) {
    sf::Vector2f bullet_position = entity.getPosition();
    bool cond_x = bullet_position.x < 50 || bullet_position.x > window->getSize().x-50;
    bool cond_y = bullet_position.y < 50 || bullet_position.y > window->getSize().y-50;
    bool cond_range_x = abs(starting_position.x - entity.getPosition().x) >= range;
    bool cond_range_y = abs(starting_position.y - entity.getPosition().y) >= range;
    return (cond_x || cond_y || cond_range_x || cond_range_y);
}