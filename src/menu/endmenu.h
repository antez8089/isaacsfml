#ifndef ENDMENU_H
#define ENDMENU_H
#include "menu.h"
class EndMenu
{
    private:
        sf::Event endmenuevent;
        int selected_item_index;
        bool active = true;
        std::vector<sf::Text> buttons;
        std::vector<sf::Text> end_menu_texts;
        sf::Font font;
        bool exit = false;
    public:
        EndMenu();
        ~EndMenu();
        int get_pressed_items();
        void init_end_menu(sf::RenderWindow* window, int score, bool success);
        void update_end_events(sf::RenderWindow* window);
        void draw(sf::RenderWindow* window);
        void move_up();
        void move_down();
        bool is_active() const;
        void run(sf::RenderWindow* window, int score, bool successS);
        bool is_exit() const;
        void restart();
        void set_active(bool active);
};
#endif