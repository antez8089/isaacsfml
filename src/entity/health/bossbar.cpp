#include "bossbar.h"

BossBar::BossBar()
{
    max_health = 25;
    current_health = 25;
    for(int i = 0;i < max_health;i++)
    {
        std::unique_ptr<Bar> bar = std::make_unique<Bar>(sf::Vector2f(i * 11.0f + 300.0f, 0));
        bossbar.push_back(std::move(bar));
    }
}


int BossBar::get_current_health()
{
    return current_health;
}

int BossBar::get_max_health()
{
    return max_health;
}

bool BossBar::get_is_alive()
{
    return is_alive;
}

void BossBar::remove_health()
{
    if(current_health>0) {
        current_health--;
        bossbar.pop_back();
    }
    if(current_health==0)
    {
        is_alive = false;
    }
}

void BossBar::add_health()
{
    if(current_health<max_health) {
        current_health++;
        std::unique_ptr<Bar> bar = std::make_unique<Bar>(sf::Vector2f((current_health-1) * 11.0f + 300.0f, 0));
        bossbar.push_back(std::move(bar));
    }
}

void BossBar::render(sf::RenderWindow* window)
{
    for(const std::unique_ptr<Bar>& bar: bossbar) {
        bar->render(window);
    }
}

void BossBar::set_health(int new_health) {
    if (new_health > max_health) {
        new_health = max_health;
    }
    if(new_health > 0)
    {
        is_alive = true;
    }
    if(new_health < 0)
    {
        is_alive = false;
    }
    bossbar.clear();
    current_health = 0;
    for(int i =0; i < new_health; i++)
    {
        add_health();
    }
}
