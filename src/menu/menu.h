#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Menu
{
    private:
        sf::Sprite background;
        sf::Texture background_texture;
        sf::Event menuevent;
        int selected_item_index;
        bool active = true;
        bool options = false;
        bool load = false;
        std::vector<sf::Text> buttons;
        sf::Font font;
        sf::Text title;
        bool exit = false;
    public:
        Menu();
        int get_pressed_items();
        ~Menu();
        void init_menu(sf::RenderWindow* window);
        void update_events(sf::RenderWindow* window);
        void move_up();
        void move_down();
        void draw(sf::RenderWindow* window);
        bool is_active() const;
        void run(sf::RenderWindow* window);
        bool is_options() const;
        bool is_exit() const;
        bool is_load() const;
        void restart();
        void set_active(bool avtive);
};
#endif