#include "entity.h"

Entity::Entity() {
    movement_speed = 250.f;
}

void Entity::move(const float x, const float y, const float& dt) {
    entity.move(x * movement_speed * dt, y * movement_speed * dt);
}

void Entity::render(sf::RenderWindow* window) {
    window->draw(entity);
}

void Entity::update(const float& dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        move(0, -1.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move(0, 1.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        move(-1.f, 0, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        move(1.f, 0, dt);
}

sf::Vector2u Entity::get_size() {
    return entity.getTexture()->getSize();
}

void Entity::set_position(const float x, const float y) {
    entity.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Entity::get_middle_position() {
    return sf::Vector2f(entity.getPosition().x+get_size().x/2, entity.getPosition().y+get_size().x/2);
}

bool Entity::check_collision(Entity& second_entity) {
    return entity.getGlobalBounds().intersects(second_entity.entity.getGlobalBounds());
}

void Entity::remove_health() {
    health--;
}

void Entity::set_texture(std::string path) {
    texture.loadFromFile(path);
    entity.setTexture(texture, true);
}

bool Entity::is_alive() {
    return alive;
}

void Entity::kill() {
    alive = false;
}

sf::FloatRect Entity::global_bounds() {
    return entity.getGlobalBounds();
}

void Entity::clear() {};

void Entity::set_health(int new_health) {
    health = new_health;
}

void Entity::set_movement_speed(float new_movement_speed) {
    movement_speed = new_movement_speed;
}