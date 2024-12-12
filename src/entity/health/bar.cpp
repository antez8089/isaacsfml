#include "bar.h"

Bar::Bar(sf::Vector2f position) : Heart(position)
{
    bar_texture.loadFromFile("assets/bar.png");
    bar.setTexture(bar_texture);
    bar.setScale(0.3, 0.3);
    bar.setPosition(position);
}

void Bar::render(sf::RenderWindow* window)
{
    window->draw(bar);
}


