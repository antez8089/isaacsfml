#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>


class Entity {
    protected:
        sf::Sprite entity;
        sf::Texture texture;
        float movement_speed;
        int health;
        bool alive = true;
    public:
        Entity();
        virtual ~Entity() = default;
        void move(const float x, const float y, const float& dt);
        virtual void render(sf::RenderWindow* window);
        virtual void update(const float& dt);

        sf::Vector2u get_size();
        sf::Vector2f get_middle_position();
        void set_position(const float x, const float y);
        bool check_collision(Entity& second_entity);
        virtual void remove_health();
        void set_texture(std::string path);
        bool is_alive();
        void kill();
        sf::FloatRect global_bounds();
        virtual void clear();
        bool enter_room = false;
        void set_health(int new_health);
        void set_movement_speed(float new_movement_speed);
};

#endif