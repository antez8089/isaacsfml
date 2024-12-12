#include "game.h"
#include <fstream>

Game::Game() {
    init_window();
}


void Game::init_window() {
    // init_music();
    window = new sf::RenderWindow(sf::VideoMode(1500, 900), "ISAAC REMAKE");
}

Game::~Game() {
    delete window;
    // delete room;
}

// void Game::init_music() {
//     if(!music.openFromFile("assets/sounds/intro.ogg"))
//     {
//     }
//     music.play();
// }

void Game::run() {
    bool return_to_menu = false;
    while(window->isOpen())
    {
        if (!is_restart) {
            while(window->isOpen()) {
                menu.run(window);
                if (menu.is_exit()) {
                    return;
                } else if(!menu.is_active()) {
                    break;
                }
                else if(menu.is_options())
                {
                    options_menu.set_active(true);
                    break;
                }
            }
            if(options_menu.is_active())
            {
                while(window->isOpen())
                {
                    options_menu.run(window);
                    if(options_menu.is_exit())
                    {
                        return_to_menu = true;
                        break;
                    }
                }
            }
        }
        if(!return_to_menu)
        {
            is_restart = false;
            if (!menu.is_load()) {
                score = 0;
                init_gamemode(options_menu);
                map.get_current_room()->generate();
                init_player();
            } else {
                try {
                    init_gamemode(options_menu);
                    level_load_from_txt();
                    player.restart();
                    map.load_from_csv();
                    player.load_from_file();
                    score_load_from_txt();
                    map.get_current_room()->generate();
                    init_player();
                } catch (std::invalid_argument &e) {
                    save = false;
                }
            }
            while(window->isOpen() && save) {
                update_dt();
                update();
                render();
                if (map.get_current_room()->get_cleared() && map.get_current_room()->get_boss()) {
                    calculate_score();
                    score_save_to_txt();
                    map.restart();
                    score_load_from_txt();
                    map.get_current_room()->generate();
                    player.clear();
                    init_player();
                    if(++bosses_killed == 2) {
                        success = true;
                        clear_save();
                        break;
                    }
                }
                if(!player.is_alive()) {
                    clear_save();
                    calculate_score();
                    break;
                }
                if (is_restart) {
                    break;
                }
            }
            if (!is_restart && save) {
                while(window->isOpen())
                {
                    end_menu.run(window, score, success);
                    if(end_menu.is_exit())
                    {
                        return;
                    }
                    if (!end_menu.is_active())
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            return_to_menu = false;
        }
        restart();
    }
}

void Game::update_dt() {
    dt = clock.restart().asSeconds();
}

void Game::render() {
    window->clear();
    map.get_current_room()->render(window);
    player.render(window);
    window->display();
}

void Game::update_events() {
    while(window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        } if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                is_restart = true;
            } if (event.key.code == sf::Keyboard::Escape) {
                window->close();
            }
        }
    }
}

void Game::update() {
    if (map.get_current_room()->get_cleared() && options_menu.get_if_save()){
        map.save_to_csv();
    }
    level_save_to_txt();
    player.save_to_file();
    player.update(dt);
    update_collisions();
    update_events();
    map.update(dt, &player);
}

void Game::init_player() {
    player.set_position(window->getDefaultView().getSize().x/2-player.get_size().x/2, window->getDefaultView().getSize().y/2-player.get_size().y/2);
}

void Game::update_collisions() {
    player.collisions_with_walls(map.get_current_room());
    player.update_collisions(map.get_current_room()->get_enemies());
}

void Game::restart() {
    map.restart();
    player.restart();
    menu.restart();
    options_menu.restart();
    end_menu.restart();
    score = 0;
    save = true;
    success = false;
    bosses_killed = 0;
}

void Game::calculate_score() {
    for (int i = 0; i < map.get_size(); i++) {
        for (int j = 0; j < map.get_size(); j++) {
            if (map.get_room(i, j)->get_playable() && map.get_room(i, j)->get_cleared()) {
                score += 40;
            }
        }
    }
    score -= 40;
}

void Game::init_gamemode(OptionsMenu& options) {
    if (options.get_is_easy()) {
        Enemy::set_enemies_starting_health(5);
    } else if (options.get_is_medium()) {
        Enemy::set_enemies_starting_health(10);
    } else {
        Enemy::set_enemies_starting_health(10);
        player.set_health(3);
    }
}

void Game::score_save_to_txt() {
    std::ofstream file("save/score.txt");
    file << score << std::endl;
    file.close();
}

void Game::score_load_from_txt() {
    std::ifstream file;
    file.open("save/score.txt");
    std::string line;
    while (std::getline(file, line)) {
        score = std::stoi(line);
    }
    file.close();
}

void Game::level_save_to_txt() {
    std::ofstream file("save/bosses.txt");
    file << bosses_killed << std::endl;
    file.close();
}

void Game::level_load_from_txt() {
    std::ifstream file;
    file.open("save/bosses.txt");
    std::string line;
    while (std::getline(file, line)) {
        bosses_killed = std::stoi(line);
    }
    file.close();
}

void Game::clear_save() {
    std::ofstream file;
    file.open("save/current_room.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.clear();
    file.open("save/player.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.clear();
    file.open("save/rooms.csv", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.clear();
    file.open("save/score.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
    file.open("save/bosses.txt", std::ofstream::out | std::ofstream::trunc);
    file.close();
}