#ifndef BAR_H
#define BAR_H
#include "heart.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Bar : public Heart
{
    private:
        sf::Sprite bar;
        sf::Texture bar_texture;
    public:
        Bar(sf::Vector2f position);
        void render(sf::RenderWindow* window) override;
};
#endif