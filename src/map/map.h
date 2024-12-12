#ifndef MAP_H
#define MAP_H
#include "../room/room.h"
#include <vector>
#include <memory>

class Map {
    private:

        std::vector<std::vector<std::unique_ptr<Room>>> rooms;
        int number_of_rooms = 9;
        int size = 7;
        std::pair<int, int> current_room;

    public:

        Map();
        void generate();
        void refresh_map();
        void calculate_top_dors(int x, int y);
        void calculate_bottom_dors(int x, int y);
        void calculate_left_dors(int x, int y);
        void calculate_right_dors(int x, int y);
        std::vector<std::pair<int, int>> calculate_dead_ends();
        int get_neighbours(int x, int y);
        void set_neighbours(int x, int y);
        int get_size();
        std::unique_ptr<Room>& get_room(int x, int y);
        std::unique_ptr<Room>& get_current_room();
        void update(const float& dt, Entity* player);
        void save_to_csv();
        void load_from_csv();
        void restart();
};

#endif