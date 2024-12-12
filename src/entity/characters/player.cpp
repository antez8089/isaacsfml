#include "player.h"
#include <fstream>
#include <sstream>

Player::Player() {
    texture.loadFromFile("assets/isaac2.png");
    entity.setTexture(texture);
    movement_speed = 300;
}

Player::~Player() {
    delete bullets;
    delete healthbar;
}

void Player::render(sf::RenderWindow* window) {
    window->draw(entity);
    bullets->render(window, range);
    healthbar->render(window);
}

void Player::update(const float& dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        if (can_move_w)
            move(0, -1.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        if (can_move_s)
            move(0, 1.f, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        if (can_move_a)
            move(-1.f, 0, dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        if (can_move_d)
            move(1.f, 0, dt);

    bullets->update(dt, get_middle_position(), attack_speed);
}

float Player::get_range() {
    return range;
}

void Player::update_collisions(EnemiesList* enemies) {
    enemies->update_collisions(*this);
    for (std::unique_ptr<Enemy>& enemy: enemies->get_list()) {
        bullets->update_collisions(*enemy);
    }
}

void Player::remove_health() {
    healthbar->remove_health();
    if (!healthbar->get_current_health()) {
        kill();
    }
}

bool Player::get_alive() {
    return healthbar->get_is_alive();
}

void Player::set_health(int health) {
    healthbar->set_health(health);
}

void Player::restart() {
    set_health(5);
    bullets->clear();
    alive = true;
}

void Player::collisions_with_walls(std::unique_ptr<Room>& room) {
    set_movement_speed(300);
    can_move_a = true;
    can_move_d = true;
    can_move_s = true;
    can_move_w = true;
    sf::FloatRect next_move_w = sf::FloatRect(entity.getPosition().x, entity.getPosition().y-7, entity.getTexture()->getSize().x, entity.getTexture()->getSize().y);
    sf::FloatRect next_move_s = sf::FloatRect(entity.getPosition().x, entity.getPosition().y+7, entity.getTexture()->getSize().x, entity.getTexture()->getSize().y);
    sf::FloatRect next_move_a = sf::FloatRect(entity.getPosition().x-7, entity.getPosition().y, entity.getTexture()->getSize().x, entity.getTexture()->getSize().y);
    sf::FloatRect next_move_d = sf::FloatRect(entity.getPosition().x+7, entity.getPosition().y, entity.getTexture()->getSize().x, entity.getTexture()->getSize().y);
    for(auto &row : room->fields) {
        for (auto &field : row) {
            if(!field->is_passable) {
                if (field->sprite.getGlobalBounds().intersects(next_move_w)) {
                    can_move_w = false;
                }
                if (field->sprite.getGlobalBounds().intersects(next_move_s)) {
                    can_move_s = false;
                }
                if (field->sprite.getGlobalBounds().intersects(next_move_a)) {
                    can_move_a = false;
                }
                if (field->sprite.getGlobalBounds().intersects(next_move_d)) {
                    can_move_d = false;
                }
            }
        }
    }
}

void Player::clear() {
    bullets->clear();
}

void Player::set_attack_speed(float new_attack_speed) {
    attack_speed = new_attack_speed;
}

void Player::set_range(float new_range) {
    range = new_range;
}

float Player::get_attack_speed() {
    return attack_speed;
}

void Player::save_to_file() {
    std::ofstream text_file("save/player.txt");
    text_file << healthbar->get_current_health() << "," << get_range() << "," << entity.getPosition().x << "," << entity.getPosition().y << "," << attack_speed;
    text_file << std::endl;
    text_file.close();
}

void Player::load_from_file() {
    std::ifstream text_file("save/player.txt");
    std::string line;
    std::getline(text_file, line);
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;
    while(std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }
    set_health(std::stoi(tokens[0]));
    set_range(std::stof(tokens[1]));
    set_position(std::stof(tokens[2]), std::stof(tokens[3]));
    set_attack_speed(std::stof(tokens[4]));
    text_file.close();
}