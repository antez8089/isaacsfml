#include "menu.h"
#include <iostream>
#include "../exceptions/asset_not_found.h"

Menu::Menu() : selected_item_index(0), active(true) {
}
Menu::~Menu() {
}
int Menu::get_pressed_items()
{
    return selected_item_index;
}

void Menu::init_menu(sf::RenderWindow* window)
{
    if(!font.loadFromFile("assets/fonts/upheavtt.ttf"))
    {
        throw AssetNotFoundException("Could not load assets/fonts/upheavtt.ttf");
    }


    if(!background_texture.loadFromFile("assets/isaacbackground.jpg"))
    {
        throw AssetNotFoundException("Could not load assets/isaacbackground.jpg");
    }
    background.setTexture(background_texture);
    background.setPosition(0, 0);
    background.setScale(
        window->getDefaultView().getSize().x / background_texture.getSize().x,
        window->getDefaultView().getSize().y / background_texture.getSize().y
    );

    title.setString("The Binding of Isaac");
    title.setFont(font);
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2 - 200);
    title.setOrigin(
        title.getGlobalBounds().width / 2,
        title.getGlobalBounds().height / 2
    );

    sf::Text play_button("New game", font, 50);
    play_button.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2);
    play_button.setFillColor(
        sf::Color::Magenta
    );
    play_button.setOrigin(
        play_button.getGlobalBounds().width / 2,
        play_button.getGlobalBounds().height / 2
    );
    buttons.push_back(play_button);

    sf::Text load_button("Load game", font, 50);
    load_button.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2 + 100);
    load_button.setFillColor(
        sf::Color::White
    );
    load_button.setOrigin(
        load_button.getGlobalBounds().width / 2,
        load_button.getGlobalBounds().height / 2
    );
    buttons.push_back(load_button);

    sf::Text options_button("Options", font, 50);
    options_button.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2 + 200);
    options_button.setFillColor(
        sf::Color::White
    );
    options_button.setOrigin(
        options_button.getGlobalBounds().width / 2,
        options_button.getGlobalBounds().height / 2
    );
    buttons.push_back(options_button);

    sf::Text exit_button("Exit", font, 50);
    exit_button.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2 + 300);
    exit_button.setFillColor(
        sf::Color::White
    );
    exit_button.setOrigin(
        exit_button.getGlobalBounds().width / 2,
        exit_button.getGlobalBounds().height / 2
    );
    buttons.push_back(exit_button);

    buttons[selected_item_index].setFillColor(sf::Color::Magenta);


}

void Menu::update_events(sf::RenderWindow* window)
{
    while (window->pollEvent(menuevent)) {
        if (menuevent.type == sf::Event::Closed) {
            window->close();
        }
        if(menuevent.type == sf::Event::KeyPressed)
        {
            if(menuevent.key.code == sf::Keyboard::Up)
            {
                move_up();
            }
            else if(menuevent.key.code == sf::Keyboard::Down)
            {
                move_down();
            }
            else if(menuevent.key.code == sf::Keyboard::Return)
            {
                if(get_pressed_items() == 0)
                {
                    active = false;
                }
                else if(get_pressed_items() == 1)
                {
                    load = true;
                    active = false;
                }
                else if(get_pressed_items() == 2)
                {
                    options = true;
                }
                else if(get_pressed_items() == 3)
                {
                    exit = true;
                }
            }
        }
    }
}

void Menu::move_up()
{
    if(selected_item_index - 1 >= 0)
    {
        buttons[selected_item_index].setFillColor(sf::Color::White);
        selected_item_index--;
        buttons[selected_item_index].setFillColor(sf::Color::Magenta);
    }
}

void Menu::move_down()
{
    if(selected_item_index + 1 < (int) buttons.size())
    {
        buttons[selected_item_index].setFillColor(sf::Color::White);
        selected_item_index++;
        buttons[selected_item_index].setFillColor(sf::Color::Magenta);
    }
}


void Menu::draw(sf::RenderWindow* window)
{
    window->draw(background);
    window->draw(title);
    for(auto& button : buttons)
    {
        window->draw(button);
    }
}

bool Menu::is_active() const
{
    return active;
}

void Menu::run(sf::RenderWindow* window) {
    init_menu(window);
    while (window->isOpen()) {
        update_events(window);
        window->clear();
        draw(window);
        window->display();
        if (exit || !active || options) {
            return;
        }
    }
}

bool Menu::is_options() const
{
    return options;
}

bool Menu::is_exit() const
{
    return exit;
}

bool Menu::is_load() const
{
    return load;
}

void Menu::restart()
{
    selected_item_index = 0;
    active = true;
    exit = false;
    load = false;
    options = false;
    buttons.clear();
}

void Menu::set_active(bool new_active) {
    active = new_active;
}