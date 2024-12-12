#include "map.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>

Map::Map(){
    current_room = std::make_pair((size-1)/2, (size-1)/2);
    refresh_map();
    generate();
}


void Map::refresh_map(){
    std::vector<std::vector<std::unique_ptr<Room>>> new_rooms;
    for (int i = 0; i < size; i++) {
        std::vector<std::unique_ptr<Room>> row;
        for (int j = 0; j < size; j++) {
            std::unique_ptr<Room> room_to_add = std::make_unique<Room>();
            row.push_back(std::move(room_to_add));
        }
        new_rooms.push_back(std::move(row));
    }
    rooms = std::move(new_rooms);
}



void Map::generate() {
    std::vector<std::pair<int, int>> dead_ends;
    int room_count = 1;
    srand(static_cast<unsigned>(time(nullptr)));
    int x = size / 2;
    int y = size / 2;
    rooms[x][y]->set_playable(true);
    rooms[x][y]->set_cleared(true);
    std::queue<std::pair<int, int>> queue;
    queue.push(std::make_pair(x, y));

    while (room_count < number_of_rooms) {
        if (queue.empty()) {
            dead_ends = calculate_dead_ends();
            queue.push(std::make_pair(x, y));
            if (rooms[x - 1][y]->get_playable()) {
                queue.push(std::make_pair(x-1,y));
            }
            if (rooms[x +1][y]->get_playable()) {
                queue.push(std::make_pair(x+11,y));
            }
            if (rooms[x][y -1]->get_playable()) {
                queue.push(std::make_pair(x,y -1));
            }
            if (rooms[x ][y +1]->get_playable()) {
                queue.push(std::make_pair(x,y + 1));
            }
            for(size_t i = 0; i < dead_ends.size(); i++) {
                queue.push(dead_ends[i]);
            }
        }
        std::pair<int, int> current = queue.front();
        queue.pop();

        for (int i = 0; i < 4; i++) {
            int new_x = current.first;
            int new_y = current.second;

            if (room_count == number_of_rooms) {
                continue;
            }
            if (i == 0) {
                new_x--;
            } else if (i == 1) {
                new_x++;
            } else if (i == 2) {
                new_y--;
            } else if (i == 3) {
                new_y++;
            }
            if (new_x < 0 || new_x >= size || new_y < 0 || new_y >= size) {
                continue;
            }

            if (rooms[new_x][new_y]->get_playable()) {
                continue;
            }

            if (get_neighbours(new_x, new_y) > 1) {
                continue;
            }

            if (!(rand() % 2)) {
                continue;
            }

            rooms[new_x][new_y]->set_playable(true);
            room_count++;
            queue.push(std::make_pair(new_x, new_y));
        }
    }

    dead_ends = calculate_dead_ends();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            if (rooms[i][j]->get_playable()) {
                calculate_top_dors(i,j);
                calculate_bottom_dors(i,j);
                calculate_left_dors(i,j);
                calculate_right_dors(i,j);
            } else {
                continue;

            }
        }
    }

    int boss = rand() % dead_ends.size();
    std::pair<int, int> boss_room = dead_ends[boss];


    rooms[boss_room.first][boss_room.second]->set_boss(true);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            if (rooms[i][j]->get_playable()) {
                if (rooms[i][j]->get_boss()) {
                    std::cout << "B ";
                } else {
                    std::cout << "X ";
                }
            } else {
                std::cout << "O ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << room_count <<std::endl;
}


std::vector<std::pair<int, int>> Map::calculate_dead_ends() {
    std::vector<std::pair<int, int>> dead_ends;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (!rooms[i][j]->get_playable()) {
                continue;
            }
            if (get_neighbours(i, j) != 1) {
                continue;
            }
            if ( i == size/2 && j == size/2) {
                continue;
            }
            dead_ends.push_back(std::make_pair(i, j));
        }
    }
    return dead_ends;
}

int Map::get_neighbours(int x, int y) {
    int neighbours = 0;
    if (x > 0) {
        if (rooms[x-1][y]->get_playable()) {
            neighbours++;
        }
    }
    if (x < size - 1) {
        if (rooms[x+1][y]->get_playable()) {
            neighbours++;
        }
    }
    if (y > 0) {
        if (rooms[x][y-1]->get_playable()) {
            neighbours++;
        }
    }
    if (y < size - 1) {
        if (rooms[x][y+1]->get_playable()) {
            neighbours++;
        }
    }
    return neighbours;
}

void Map::calculate_top_dors(int x, int y) {
    if (x-1 < 0 || x-1 >= size || y < 0 || y >= size) {
        return;
    }
    if (rooms[x-1][y]->get_playable()) {
        rooms[x][y]->set_top_door(true);
        return;
    }
}

void Map::calculate_bottom_dors(int x, int y) {
     if (x+1 < 0 || x+1 >= size || y < 0 || y >= size) {
        return;
    }
    if (rooms[x+1][y]->get_playable()) {
        rooms[x][y]->set_down_door(true);
        return;
    }
}

void Map::calculate_left_dors(int x, int y) {
    if (x < 0 || x >= size || y - 1< 0 || y -1  >= size) {
        return;
    }
    if (rooms[x][y - 1]->get_playable()) {
        rooms[x][y]->set_left_door(true);
        return;
    }
}

void Map::calculate_right_dors(int x, int y) {
    if (x < 0 || x >= size || y + 1< 0 || y + 1  >= size) {
        return;
    }
    if (rooms[x][y+1]->get_playable()) {
        rooms[x][y]->set_right_door(true);
        return;
    }
}

int Map::get_size() {
    return size;
}

std::unique_ptr<Room>& Map::get_room(int x, int y)  {
    return rooms[x][y];
}

std::unique_ptr<Room>& Map::get_current_room() {
    return rooms[current_room.first][current_room.second]; 
}

void Map::update(const float& dt, Entity* player) {
    rooms[current_room.first][current_room.second]->update(dt, *player);
    if (!rooms[current_room.first][current_room.second]->get_enemies()->get_size()) {
        std::pair<int, int> room_step = rooms[current_room.first][current_room.second]->player_exit(player);
        if (player->enter_room) {
            int old_x = current_room.first;
            int old_y = current_room.second;
            current_room = std::make_pair(old_x+room_step.first, old_y+room_step.second);
            player->enter_room = false;
            get_current_room()->generate();
        }
    }
}

void Map::restart() {
    current_room = std::make_pair((size-1)/2, (size-1)/2);
    rooms.clear();
    refresh_map();
    generate();
}



void Map::save_to_csv() {
    std::vector<std::vector<std::string>> map_data;
    for (int i = 0; i < size; i++) {
        std::vector<std::string> temp;
        map_data.push_back(temp);
        for (int j = 0; j <size; j++) {
            std::string room_data;
            if (rooms[i][j]->get_playable()) {
                room_data += "1";
            } else {
                room_data += "0";
            }
            room_data += "|";
            if (rooms[i][j]->get_boss()) {
                room_data += "1";
            } else {
                room_data += "0";
            }
            room_data += "|";
            if (rooms[i][j]->get_cleared()) {
                room_data += "1";
            } else {
                room_data += "0";
            }
            room_data += "|";
            if (rooms[i][j]->get_top_door()) {
                room_data += "1";
            } else {
                room_data += "0";
            }
            room_data += "|";
            if (rooms[i][j]->get_right_door()) {
                room_data += "1";
            } else {
                room_data += "0";
            }
            room_data += "|";
            if (rooms[i][j]->get_down_door()) {
                room_data += "1";
            } else {
                room_data += "0";
            }
            room_data += "|";
            if (rooms[i][j]->get_left_door()) {
                room_data += "1";
            } else {
                room_data += "0";
            }
            map_data[i].push_back(room_data);
        }
    }
    std::ofstream csv_file("save/rooms.csv");
    for (std::vector<std::string> row : map_data) {
        for (std::string field : row) {
            csv_file << field << ",";
        }
        csv_file << std::endl;
    }
    csv_file.close();

    std::ofstream text_file("save/current_room.txt");
    text_file << current_room.first << "," << current_room.second;
    text_file << std::endl;
    text_file.close();
}


void Map::load_from_csv() {
    std::ifstream csv_file("save/rooms.csv");
    std::string line;
    std::vector<std::vector<std::string>> map_data;
    while (std::getline(csv_file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ',')) {
            row.push_back(field);
        }
        map_data.push_back(row);
    }
    csv_file.close();

    for (int i = 0; i < (int)map_data.size(); i++) {
        for (int j = 0; j < (int)map_data[i].size(); j++) {
            std::vector<std::string> room_data;
            std::string data = map_data[i][j];
            std::stringstream ss(data);
            std::string field;
            while (std::getline(ss, field, '|')) {
                room_data.push_back(field);
            }
            if (room_data[0] == "1") {
                rooms[i][j]->set_playable(true);
            } else {
                rooms[i][j]->set_playable(false);
            }
            if (room_data[1] == "1") {
                rooms[i][j]->set_boss(true);
            } else {
                rooms[i][j]->set_boss(false);
            }
            if (room_data[2] == "1") {
                rooms[i][j]->set_cleared(true);
            } else {
                rooms[i][j]->set_cleared(false);
            }
            if (room_data[3] == "1") {
                rooms[i][j]->set_top_door(true);
            } else {
                rooms[i][j]->set_top_door(false);
            }
            if (room_data[4] == "1") {
                rooms[i][j]->set_right_door(true);
            } else {
                rooms[i][j]->set_right_door(false);
            }
            if (room_data[5] == "1") {
                rooms[i][j]->set_down_door(true);
            } else {
                rooms[i][j]->set_down_door(false);
            }
            if (room_data[6] == "1") {
                rooms[i][j]->set_left_door(true);
            } else {
                rooms[i][j]->set_left_door(false);
            }
        }
    }

    std::ifstream text_file("save/current_room.txt");
    std::string text;
    std::getline(text_file, text);
    std::stringstream ss(text);
    std::string field;
    std::getline(ss, field, ',');
    current_room.first = std::stoi(field);
    std::getline(ss, field, ',');
    current_room.second = std::stoi(field);
    text_file.close();
}