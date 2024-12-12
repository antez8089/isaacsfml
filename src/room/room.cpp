#include "room.h"

Room::Room() {}

void Room::set_playable(bool is) {
    is_playable = is;
}

bool Room::get_top_door() {
    return top_doors;
}

bool Room::get_down_door() {
    return down_doors;
}

bool Room::get_right_door() {
    return right_doors;
}   

bool Room::get_left_door() {
    return left_doors;
}   

bool Room::get_cleared() {
    return is_cleared;
}

bool Room::get_playable() {
    return is_playable;
}

bool Room::get_boss() {
    return is_boss_room;
}

void Room::set_innitial_state() {
    player_pos = sf::Vector2i(Length-1, Length-1);
}

void Room::set_top_door(bool is) {
    top_doors = is;
}

void Room::set_down_door(bool is) {
    down_doors = is;
}

void Room::set_right_door(bool is) {
    right_doors = is;
}

void Room::set_left_door(bool is) {
    left_doors = is;
}

void Room::set_boss(bool is) {
    is_boss_room = is;
}


void Room::generate() {
    srand((unsigned) time(NULL));
    for (int i = 0; i < Length; ++i) {
        std::vector<std::unique_ptr<Game_field>> temp;
        for (int j = 0; j < Height; ++j) {
            if (i == Length/2 && j == 0 && top_doors == true) {
                if(!is_cleared) {
                    std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/drzwi.png",i,j, 0, 1);
                    temp.push_back(std::move(field));
                } else {
                    std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/drzwi.png",i,j, 1, 1);
                    temp.push_back(std::move(field));
                }
            } else if (i == Length/2 && j == Height -1  && down_doors == true) {
                if(!is_cleared) {
                    std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/drzwi.png",i,j, 0, 1);
                    field->sprite.setRotation(180);
                    field->sprite.move(100, 100);
                    temp.push_back(std::move(field));  
                } else {
                    std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/drzwi.png",i,j, 1, 1);
                    field->sprite.setRotation(180);
                    field->sprite.move(100, 100);
                    temp.push_back(std::move(field));
                }
            } else if (i == 0 && j == Height/2 && left_doors == true) {
                if(!is_cleared) {
                    std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/drzwi.png",i,j, 0, 1);
                    field->sprite.setRotation(270);
                    field->sprite.move(0, 100);
                    temp.push_back(std::move(field));  
                } else {
                    std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/drzwi.png",i,j, 1, 1);
                    field->sprite.setRotation(270);
                    field->sprite.move(0, 100);
                    temp.push_back(std::move(field));
                }
            } else if (i == Length -1 && j == Height/2 && right_doors == true) {
                if(!is_cleared) {
                    std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/drzwi.png",i,j, 0, 1);
                    field->sprite.setRotation(90);
                    field->sprite.move(100, 0);
                    temp.push_back(std::move(field)); 
                } else {
                    std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/drzwi.png",i,j, 1, 1);
                    field->sprite.setRotation(90);
                    field->sprite.move(100, 0);
                    temp.push_back(std::move(field));
                }
            } else if (i == 0 || j == 0 || i ==Length-1 || j == Height-1) {
                std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/sciana.png",i,j, 0, 0);
                temp.push_back(std::move(field));
            } else {
                std::unique_ptr<Game_field> field = std::make_unique<Game_field>("assets/podloga.png",i,j, 1, 0);
                temp.push_back(std::move(field));
            }
        }
        fields.push_back(std::move(temp));
    }
    if (!is_cleared)
        enemies.init_enemies(4, is_boss_room);
   
}

void Room::render(sf::RenderWindow* window) {
    for(const std::vector<std::unique_ptr<Game_field>>& row: fields) {
        for (const std::unique_ptr<Game_field>& field: row) {
            field->render(window);
        }
    }
    enemies.render(window);
}

std::pair<int, int> Room::player_exit(Entity* player) {
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Length; j++) {
            if (fields[j][i]->is_door) {
                if (player->global_bounds().intersects(fields[j][i]->sprite.getGlobalBounds())) {
                    if (j == Length-1) {
                        player->set_position(fields[1][i]->sprite.getPosition().x + 10, fields[1][i]->sprite.getPosition().y);
                        player->clear();
                        player->enter_room = true;
                        player->set_movement_speed(0);
                        return std::make_pair(0, 1);
                    } else if (j == 0) {
                        player->set_position(fields[Length-2][i]->sprite.getPosition().x - 10, fields[Length-2][i]->sprite.getPosition().y);
                        player->clear();
                        player->enter_room = true;
                        player->set_movement_speed(0);
                        return std::make_pair(0, -1);
                    } else if (i == 0) {
                        player->set_position(fields[j][Height-2]->sprite.getPosition().x, fields[j][Height-2]->sprite.getPosition().y - 10);
                        player->clear();
                        player->enter_room = true;
                        player->set_movement_speed(0);
                        return std::make_pair(-1, 0);
                    } else {
                        player->set_position(fields[j][1]->sprite.getPosition().x, fields[j][1]->sprite.getPosition().y + 10);
                        player->clear();
                        player->enter_room = true;
                        player->set_movement_speed(0);
                        return std::make_pair(1, 0);
                    }
                    
                }
            }

        }
    }
    return std::make_pair(0, 0);
}

void Room::set_cleared(bool cleared) {
    is_cleared = cleared;
}

void Room::update(const float& dt, Entity& player) {
    enemies.update(dt, player);
    if (!enemies.get_size()) {
        if (fields[0][4]->is_door) {
            fields[0][4]->is_passable = true;
        }
        if (fields[14][4]->is_door) {
            fields[14][4]->is_passable = true;
        }
        if (fields[7][0]->is_door) {
            fields[7][0]->is_passable = true;
        }
        if (fields[7][8]->is_door) {
            fields[7][8]->is_passable = true;
        }
        is_cleared = true;
    }
}

EnemiesList* Room::get_enemies() {
    return &enemies;
}