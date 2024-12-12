#include "endmenu.h"
#include <iostream>
#include "../exceptions/asset_not_found.h"
#include <string>
EndMenu::EndMenu(): selected_item_index(0), active(true) {
}
EndMenu::~EndMenu() {
}

int EndMenu::get_pressed_items()
{
    return selected_item_index;
}

void EndMenu::init_end_menu(sf::RenderWindow* window, int score, bool success)
{
    if(!font.loadFromFile("assets/fonts/upheavtt.ttf"))
    {
        throw AssetNotFoundException("Could not load assets/fonts/upheavtt.ttf");
    }
    std::string text;
    if(success)
    {
        text = "You Won!!!";
    }
    else
    {
        text = "Game Over!!!";
    }
    sf::Text game_over_text(text, font, 100);
    game_over_text.setPosition(window->getDefaultView().getSize().x / 2, window->getDefaultView().getSize().y / 2 - 200);
    game_over_text.setFillColor(
        sf::Color::Yellow
    );
    game_over_text.setOrigin(
        game_over_text.getGlobalBounds().width / 2,
        game_over_text.getGlobalBounds().height / 2
    );
    end_menu_texts.push_back(game_over_text);

    sf::Text total_score_text("Total Score: " + std::to_string(score), font, 50);
    total_score_text.setPosition(window->getDefaultView().getSize().x / 2, window->getDefaultView().getSize().y / 2 - 50);
    total_score_text.setFillColor(
        sf::Color::Yellow
    );
    total_score_text.setOrigin(
        total_score_text.getGlobalBounds().width / 2,
        total_score_text.getGlobalBounds().height / 2
    );
    end_menu_texts.push_back(total_score_text);

    sf::Text question_text("Do you want to play again?", font, 50);
    question_text.setPosition(window->getDefaultView().getSize().x / 2, window->getDefaultView().getSize().y / 2 + 50);
    question_text.setFillColor(
        sf::Color::Yellow
    );
    question_text.setOrigin(
        question_text.getGlobalBounds().width / 2,
        question_text.getGlobalBounds().height / 2
    );
    end_menu_texts.push_back(question_text);

    sf::Text yes_button("Yes", font, 50);
    yes_button.setPosition(window->getDefaultView().getSize().x / 2 - 100, window->getDefaultView().getSize().y / 2 + 100);
    yes_button.setFillColor(
        sf::Color::Red
    );
    yes_button.setOrigin(
        yes_button.getGlobalBounds().width / 2,
        yes_button.getGlobalBounds().height / 2
    );
    buttons.push_back(yes_button);

    sf::Text no_button("No", font, 50);
    no_button.setPosition(window->getDefaultView().getSize().x / 2 + 60, window->getDefaultView().getSize().y / 2 + 100);
    no_button.setFillColor(
        sf::Color::White
    );
    no_button.setOrigin(
        no_button.getGlobalBounds().width / 2,
        no_button.getGlobalBounds().height / 2
    );
    buttons.push_back(no_button);

    buttons[selected_item_index].setFillColor(sf::Color::Red);
}

void EndMenu::update_end_events(sf::RenderWindow* window)
{
    while(window->pollEvent(endmenuevent))
    {
        if(endmenuevent.type == sf::Event::Closed)
            window->close();
        if(endmenuevent.type == sf::Event::KeyPressed)
        {
            if(endmenuevent.key.code == sf::Keyboard::Left)
            {
                move_up();
            }
            else if(endmenuevent.key.code == sf::Keyboard::Right)
            {
                move_down();
            }
            else if(endmenuevent.key.code == sf::Keyboard::Return)
            {
                switch(selected_item_index)
                {
                    case 0:
                        active = false;
                        break;
                    case 1:
                        exit = true;
                        break;
                }
            }
        }
    }
}

void EndMenu::move_up()
{
    if(selected_item_index - 1 >= 0)
    {
        buttons[selected_item_index].setFillColor(sf::Color::White);
        selected_item_index--;
        buttons[selected_item_index].setFillColor(sf::Color::Red);
    }
}

void EndMenu::move_down()
{
    if(selected_item_index + 1 < (int) buttons.size())
    {
        buttons[selected_item_index].setFillColor(sf::Color::White);
        selected_item_index++;
        buttons[selected_item_index].setFillColor(sf::Color::Red);
    }
}

void EndMenu::draw(sf::RenderWindow* window)
{
    for(auto& text : end_menu_texts)
    {
        window->draw(text);
    }
    for(auto& button : buttons)
    {
        window->draw(button);
    }
}

bool EndMenu::is_active() const
{
    return active;
}

bool EndMenu::is_exit() const
{
    return exit;
}

void EndMenu::run(sf::RenderWindow* window, int score, bool success)
{
    init_end_menu(window, score, success);
    while(window->isOpen())
    {
        update_end_events(window);
        window->clear();
        draw(window);
        window->display();
        if(exit || !active)
        {
            return;
        }
    }
}

void EndMenu::restart()
{
    selected_item_index = 0;
    active = true;
    exit = false;
    buttons.clear();
    end_menu_texts.clear();
}

void EndMenu::set_active(bool new_active) {
    active = new_active;
}
