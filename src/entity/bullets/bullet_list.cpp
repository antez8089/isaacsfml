#include "bullet_list.h"

void BulletList::add_bullet(char direction, sf::Vector2f player_position, float attack_speed) {
    std::unique_ptr<Bullet> added_bullet = std::make_unique<Bullet>(direction, player_position, attack_speed);
    bullets.push_back(std::move(added_bullet));
}

void BulletList::render(sf::RenderWindow* window, float range) {
    for(const std::unique_ptr<Bullet>& bullet: bullets) {
        bullet->render(window);
    }
    check_bullets(window, range);
}

void BulletList::update(const float& dt, sf::Vector2f player_position, float attack_speed) {
    if(bullet_clock.getElapsedTime().asSeconds()>=0.32 || !is_pressed) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        add_bullet('U', player_position, attack_speed);
        is_pressed = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        add_bullet('D', player_position, attack_speed);
        is_pressed = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        add_bullet('L', player_position, attack_speed);
        is_pressed = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        add_bullet('R', player_position, attack_speed);
        is_pressed = true;
    }
    else{
        is_pressed = false;
    }
    bullet_clock.restart();
    }
    for(const std::unique_ptr<Bullet>& bullet: bullets) {
        bullet->update(dt);
    }
}

void BulletList::check_bullets(sf::RenderWindow* window, float range) {
    for (size_t i = 0; i < bullets.size(); i++) {
        if(bullets[i]->is_bullet_out(window, range)) {
            remove_bullet(bullets[i]);
        }
    }
}

void BulletList::remove_bullet(const std::unique_ptr<Bullet>& bullet) {
    bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet));
}

void BulletList::update_collisions(Entity& entity) {
    for (size_t i = 0 ; i < bullets.size(); i++) {
        if(bullets[i]->check_collision(entity)) {
            entity.remove_health();
            remove_bullet(bullets[i]);
        }
    }
}

void BulletList::clear() {
    bullets.clear();
}

int BulletList::get_size() {
    return bullets.size();
}