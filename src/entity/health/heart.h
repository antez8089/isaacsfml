#ifndef HEART_H
#define HEART_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Heart
{
private:
    sf::Sprite heart;
    sf::Texture texture;
public:
    Heart(sf::Vector2f position);
    virtual ~Heart() = default;
    void set_position(const float x, const float y);
    virtual void render(sf::RenderWindow* window);

};
#endif