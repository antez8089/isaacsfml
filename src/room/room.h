#ifndef ROOM_H
#define ROOM_H
#include "game_field.h"
#include "../entity/entity.h"
#include "../entity/characters/enemies_list.h"
#include <vector>
#include <memory>

class Room {
    bool top_doors = false;
    bool down_doors = false;
    bool left_doors = false;
    bool right_doors = false;
    bool is_boss_room = false;
    bool is_playable = false;
    bool is_cleared = false;
    std::vector<sf::Vector2i> exit_pos;
    sf::Vector2i player_pos;
    std::vector<sf::Vector2i> enemy_pos;
    void set_innitial_state();
    void set_enemy_pos();
    void set_tiles();
    EnemiesList enemies;

    public:
    
    bool get_playable();
    bool get_boss();
    bool get_cleared();
    bool get_top_door();
    bool get_down_door();
    bool get_right_door();
    bool get_left_door();
    void set_playable(bool);
    void set_top_door(bool);
    void set_down_door(bool);
    void set_right_door(bool);
    void set_left_door(bool);
    void set_boss(bool);
    void generate();
    std::vector<std::vector<std::unique_ptr<Game_field>>> fields;
    int Length = 15;
    int Height = 9;
    void render(sf::RenderWindow* window);
    Room();
    ~Room() = default;
    std::pair<int, int> player_exit(Entity* player);
    void set_cleared(bool);
    void update(const float& dt, Entity& player);
    bool is_neighbour_boss();
    EnemiesList* get_enemies();

};

#endif