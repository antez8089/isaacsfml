#include "game_field.h"

Game_field::Game_field(std::string texture_name, float x, float y, bool passable, bool door) {
    if (!set_sprite(texture_name)) {
        return;
    }
    pos = sf::Vector2f(x*100,y*100);
    sprite.setPosition(pos);
    is_passable = passable;
    is_door = door;
}

bool Game_field::set_sprite(std::string texture_id){
    if (!texture.loadFromFile(texture_id)) {
        return false;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    return true;
}

void Game_field::render(sf::RenderWindow* window) {
    window->draw(sprite);
}

sf::Vector2f Game_field::get_middle_position() {
    return sf::Vector2f(sprite.getPosition().x+sprite.getTexture()->getSize().x/2,
                        sprite.getPosition().y+sprite.getTexture()->getSize().x/2);
}