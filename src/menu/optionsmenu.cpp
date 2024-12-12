#include "optionsmenu.h"
#include <iostream>
#include "../exceptions/asset_not_found.h"
OptionsMenu::OptionsMenu() : selected_option_index(0)
{

}
OptionsMenu::~OptionsMenu()
{
}

bool OptionsMenu::get_is_easy() const
{
    return is_easy;
}

bool OptionsMenu::get_is_medium() const
{
    return is_medium;
}

bool OptionsMenu::get_is_hard() const
{
    return is_hard;
}

bool OptionsMenu::get_sound_on() const
{
    return sound_on;
}

bool OptionsMenu::get_if_save() const
{
    return save;
}

int OptionsMenu::get_selected_item_index(int row) const
{
    return selected_item_index[row];
}

int OptionsMenu::get_option_index() const
{
    return selected_option_index;
}

bool OptionsMenu::is_option_button_selected(int row, int index) const
{
    return buttons[row][index].selected;
}

void OptionsMenu::init_options_menu(sf::RenderWindow* window)
{
    if(!font.loadFromFile("assets/fonts/upheavtt.ttf"))
    {
        throw AssetNotFoundException("Could not load assets/fonts/upheavtt.ttf");
    }
    std::vector<OptionButton> difficulty_buttons;
    sf::Text difficulty_text("Difficulty", font, 50);
    difficulty_text.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2 - 300);
    difficulty_text.setFillColor(
        sf::Color::Yellow
    );
    difficulty_text.setOrigin(
        difficulty_text.getGlobalBounds().width / 2,
        difficulty_text.getGlobalBounds().height / 2
    );
    options_menu_texts.push_back(difficulty_text);

    sf::Text easy_button("Easy", font, 50);
    easy_button.setPosition(window->getDefaultView().getSize().x / 2 - 220, window->getDefaultView().getSize().y / 2 - 250);
    if(selected_item_index[0] == 0)
    {
        easy_button.setFillColor(
            sf::Color::Red
        );
    }
    else
    {
        easy_button.setFillColor(
            sf::Color::White
        );
    }
    easy_button.setOrigin(
        easy_button.getGlobalBounds().width / 2,
        easy_button.getGlobalBounds().height / 2
    );
    difficulty_buttons.push_back({easy_button, true});

    sf::Text medium_button("Medium", font, 50);
    medium_button.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2 - 250);
    if(selected_item_index[0] == 1)
    {
        medium_button.setFillColor(
            sf::Color::Red
        );
    }
    else
    {
        medium_button.setFillColor(
            sf::Color::White
        );
    }
    medium_button.setOrigin(
        medium_button.getGlobalBounds().width / 2,
        medium_button.getGlobalBounds().height / 2
    );
    difficulty_buttons.push_back({medium_button, false});

    sf::Text hard_button("Hard", font, 50);
    hard_button.setPosition(window->getDefaultView().getSize().x / 2 + 180, window->getDefaultView().getSize().y / 2 -250);
    if(selected_item_index[0] == 2)
    {
        hard_button.setFillColor(
            sf::Color::Red
        );
    }
    else
    {
        hard_button.setFillColor(
            sf::Color::White
        );
    }
    hard_button.setOrigin(
        hard_button.getGlobalBounds().width / 2,
        hard_button.getGlobalBounds().height / 2
    );
    difficulty_buttons.push_back({hard_button, false});

    buttons.push_back(difficulty_buttons);

    std::vector<OptionButton> sound_buttons;
    sf::Text sound_text("Sound", font, 50);
    sound_text.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2 - 150);
    sound_text.setFillColor(
        sf::Color::White
    );
    sound_text.setOrigin(
        sound_text.getGlobalBounds().width / 2,
        sound_text.getGlobalBounds().height / 2
    );
    options_menu_texts.push_back(sound_text);

    sf::Text on_button("On", font, 50);
    on_button.setPosition(window->getDefaultView().getSize().x / 2 - 70, window->getDefaultView().getSize().y / 2 - 100);
    if(selected_item_index[1] == 0)
    {
        on_button.setFillColor(
            sf::Color::Red
        );
    }
    else
    {
        on_button.setFillColor(
            sf::Color::White
        );
    }
    on_button.setOrigin(
        on_button.getGlobalBounds().width / 2,
        on_button.getGlobalBounds().height / 2
    );
    sound_buttons.push_back({on_button, true});

    sf::Text off_button("Off", font, 50);
    off_button.setPosition(window->getDefaultView().getSize().x / 2 + 30, window->getDefaultView().getSize().y / 2 -100);
    if(selected_item_index[1] == 1)
    {
        off_button.setFillColor(
            sf::Color::Red
        );
    }
    else
    {
        off_button.setFillColor(
            sf::Color::White
        );
    }
    off_button.setOrigin(
        off_button.getGlobalBounds().width / 2,
        off_button.getGlobalBounds().height / 2
    );
    sound_buttons.push_back({off_button, false});
    buttons.push_back(sound_buttons);


    std::vector<OptionButton> save_buttons;
    sf::Text save_text("Autosave", font, 50);
    save_text.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2 );
    save_text.setFillColor(
        sf::Color::White
    );
    save_text.setOrigin(
        save_text.getGlobalBounds().width / 2,
        save_text.getGlobalBounds().height / 2
    );
    options_menu_texts.push_back(save_text);

    sf::Text yes_button("Yes", font, 50);
    yes_button.setPosition(window->getDefaultView().getSize().x / 2 - 70, window->getDefaultView().getSize().y / 2 + 50);
    if(selected_item_index[2] == 0)
    {
        yes_button.setFillColor(
            sf::Color::Red
        );
    }
    else
    {
        yes_button.setFillColor(
            sf::Color::White
        );
    }
    yes_button.setOrigin(
        yes_button.getGlobalBounds().width / 2,
        yes_button.getGlobalBounds().height / 2
    );
    save_buttons.push_back({yes_button, true});

    sf::Text no_button("No", font, 50);
    no_button.setPosition(window->getDefaultView().getSize().x / 2 + 30, window->getDefaultView().getSize().y / 2 + 50);
    if(selected_item_index[2] == 1)
    {
        no_button.setFillColor(
            sf::Color::Red
        );
    }
    else
    {
        no_button.setFillColor(
            sf::Color::White
        );
    }
    no_button.setOrigin(
        no_button.getGlobalBounds().width / 2,
        no_button.getGlobalBounds().height / 2
    );
    save_buttons.push_back({no_button, false});
    buttons.push_back(save_buttons);

    sf::Text back_button("Back", font, 50);
    back_button.setPosition(window->getDefaultView().getSize().x / 2 - 20, window->getDefaultView().getSize().y / 2 + 150) ;
    back_button.setFillColor(
        sf::Color::White
    );
    back_button.setOrigin(
        back_button.getGlobalBounds().width / 2,
        back_button.getGlobalBounds().height / 2
    );
    options_menu_texts.push_back(back_button);
}

void OptionsMenu::update_options_events(sf::RenderWindow* window)
{
    while(window->pollEvent(optionsevent))
    {
        if(optionsevent.type == sf::Event::Closed)
        {
            window->close();
        }
        if(optionsevent.type == sf::Event::KeyPressed)
        {
            if(optionsevent.key.code == sf::Keyboard::Up)
            {
                move_up();
            }
            else if(optionsevent.key.code == sf::Keyboard::Down)
            {
                move_down();
            }
            else if(optionsevent.key.code == sf::Keyboard::Left)
            {
                if(selected_option_index != (int) options_menu_texts.size() - 1)
                    {
                        move_left();
                    }
            }
            else if(optionsevent.key.code == sf::Keyboard::Right)
            {
                if(selected_option_index != (int) options_menu_texts.size() - 1 )
                {
                    move_right();
                }
            }
            else if(optionsevent.key.code == sf::Keyboard::Return)
            {
                if(selected_option_index == (int) options_menu_texts.size() - 1)
                {

                    switch(selected_item_index[0])
                    {
                        case 0:
                            is_easy = true;
                            is_medium = false;
                            is_hard = false;
                            break;
                        case 1:
                            is_easy = false;
                            is_medium = true;
                            is_hard = false;
                            break;
                        case 2:
                            is_easy = false;
                            is_medium = false;
                            is_hard = true;
                            break;
                    }
                    switch(selected_item_index[1])
                    {
                        case 0:
                            sound_on = true;
                            break;
                        case 1:
                            sound_on = false;
                            break;
                    }
                    switch(selected_item_index[2])
                    {
                        case 0:
                            save = true;
                            break;
                        case 1:
                            save = false;
                            break;
                    }
                    active = false;
                    exit = true;
                }
            }
            else if(optionsevent.key.code == sf::Keyboard::Escape)
            {
                exit = true;
            }
        }
    }
}

void OptionsMenu::move_up()
{
    if(selected_option_index - 1 >= 0)
    {
        options_menu_texts[selected_option_index].setFillColor(sf::Color::White);
        selected_option_index--;
        options_menu_texts[selected_option_index].setFillColor(sf::Color::Yellow);
    }
}

void OptionsMenu::move_down()
{
    if(selected_option_index + 1 < (int) options_menu_texts.size())
    {
        options_menu_texts[selected_option_index].setFillColor(sf::Color::White);
        selected_option_index++;
        options_menu_texts[selected_option_index].setFillColor(sf::Color::Yellow);
    }
}

void OptionsMenu::move_left()
{
    if(selected_item_index[selected_option_index] - 1 >= 0)
    {
        buttons[selected_option_index][selected_item_index[selected_option_index]].text.setFillColor(sf::Color::White);
        buttons[selected_option_index][selected_item_index[selected_option_index]].selected = false;
        selected_item_index[selected_option_index]--;
        buttons[selected_option_index][selected_item_index[selected_option_index]].text.setFillColor(sf::Color::Red);
        buttons[selected_option_index][selected_item_index[selected_option_index]].selected = true;
    }
}

void OptionsMenu::move_right()
{
    if(selected_item_index[selected_option_index] + 1 < (int) buttons[selected_option_index].size())
    {
        buttons[selected_option_index][selected_item_index[selected_option_index]].text.setFillColor(sf::Color::White);
        buttons[selected_option_index][selected_item_index[selected_option_index]].selected = false;
        selected_item_index[selected_option_index]++;
        buttons[selected_option_index][selected_item_index[selected_option_index]].text.setFillColor(sf::Color::Red);
        buttons[selected_option_index][selected_item_index[selected_option_index]].selected = true;
    }
}

bool OptionsMenu::is_active() const
{
    return active;
}

void OptionsMenu::run(sf::RenderWindow* window)
{
    init_options_menu(window);
    while(window->isOpen())
    {
        update_options_events(window);
        window->clear();
        draw(window);
        window->display();
        if(exit|| !active)
        {
            return;
        }
    }
}

bool OptionsMenu::is_exit() const
{
    return exit;
}

void OptionsMenu::draw(sf::RenderWindow* window)
{
    for(auto& button : options_menu_texts)
    {
        window->draw(button);
    }
    for(int j = 0; j < (int) buttons.size(); j++)
    {
        for(int i = 0; i < (int) buttons[j].size(); i++)
        {
        window->draw(buttons[j][i].text);
        }
    }
}

void OptionsMenu::restart()
{
    // selected_item_index[0] = 0;
    // selected_item_index[1] = 0;
    selected_option_index = 0;
    active = false;
    exit = false;
    options_menu_texts.clear();
    buttons.clear();
}

void OptionsMenu::set_active(bool new_active)
{
    active = new_active;
}


