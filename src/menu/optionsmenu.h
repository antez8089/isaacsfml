#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>

class OptionsMenu
{
    private:
        struct OptionButton
        {
            sf::Text text;
            bool selected;
        };
        sf::Event optionsevent;
        int selected_item_index[3] = {0, 0};
        bool active = false;
        bool exit = false;
        bool is_easy = true;
        bool is_medium = false;
        bool is_hard = false;
        bool sound_on = true;
        bool save = true;
        sf::Font font;
        std::vector<std::vector<OptionButton>> buttons;
        std::vector<sf::Text> options_menu_texts;
        int selected_option_index;
    public:
        OptionsMenu();
        ~OptionsMenu();
        bool get_is_easy() const;
        bool get_is_medium() const;
        bool get_is_hard() const;
        bool get_sound_on() const;
        bool get_if_save() const;
        bool is_option_button_selected(int row, int index) const;
        void init_options_menu(sf::RenderWindow* window);
        void update_options_events(sf::RenderWindow* window);
        int get_option_index() const;
        int get_selected_item_index(int row) const;
        void draw(sf::RenderWindow* window);
        void move_up();
        void move_down();
        void move_left();
        void move_right();
        bool is_active() const;
        void run(sf::RenderWindow* window);
        bool is_exit() const;
        void restart();
        void set_active(bool active);
};
#endif