#ifndef GAME_FIELD_H
#define GAME_FIELD_H
#include <SFML/Graphics.hpp>

class Game_field {
    public:
    bool is_passable;
    bool is_door;
    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;
    Game_field(std::string, float, float, bool, bool);
    bool set_sprite(std::string);
    void render(sf::RenderWindow* window);
    sf::Vector2f get_middle_position();
};

#endif