
#include "healthbar.h"

HealthBar::HealthBar()
{
for (int i = 0; i < max_health; i++) {
        std::unique_ptr<Heart> heart = std::make_unique<Heart>(sf::Vector2f(i * 55.0f, 0));
        healthbar.push_back(std::move(heart));
    }
}

int HealthBar::get_current_health()
{
    return current_health;
}

int HealthBar::get_max_health()
{
    return max_health;
}

bool HealthBar::get_is_alive()
{
    return is_alive;
}

void HealthBar::add_health()
{
    if(current_health<max_health) {
        current_health++;
        std::unique_ptr<Heart> heart = std::make_unique<Heart>(sf::Vector2f((current_health-1) * 55.0f, 0));
        healthbar.push_back(std::move(heart));
    }
}

void HealthBar::remove_health()
{
    if(current_health>0) {
        current_health--;
        healthbar.pop_back();
    }
    if(current_health==0)
    {
        is_alive = false;
    }
}

void HealthBar::render(sf::RenderWindow* window)
{
    for(const std::unique_ptr<Heart>& heart: healthbar) {
        heart->render(window);
    }
}

void HealthBar::set_health(int new_health) {
    if (new_health > max_health) {
        new_health = max_health;
    }
    if(new_health > 0)
    {
        is_alive = true;
    }
    if(new_health <= 0)
    {
        is_alive = false;
    }
    healthbar.clear();
    current_health = 0;
    for(int i = 0; i < new_health; i++) {
        add_health();
    }
}

