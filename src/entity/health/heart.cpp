#include "heart.h"

Heart::Heart(sf::Vector2f position)
{
    texture.loadFromFile("assets/health.png");
    heart.setTexture(texture);
    heart.setScale(0.3, 0.3);
    heart.setPosition(position);
}


void Heart::set_position(const float x, const float y)
{
    heart.setPosition(sf::Vector2f(x, y));
}

void Heart::render(sf::RenderWindow* window)
{
    window->draw(heart);
}
