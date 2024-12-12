#ifndef GAME_H
#define GAME_H
#include "entity/characters/player.h"
#include "entity/characters/enemies_list.h"
#include "menu/menu.h"
#include "entity/health/healthbar.h"
#include "menu/endmenu.h"
#include "room/room.h"
#include "menu/optionsmenu.h"
#include "map/map.h"

class Game {
    private:
        sf::RenderWindow* window;
        sf::Event event;
        sf::Clock clock;
        float dt;
        Player player;
        Map map;
        Menu menu;
        OptionsMenu options_menu;
        EndMenu end_menu;
        int score = 0;
        bool success = false;
        bool is_restart = false;
        bool save = true;
        int bosses_killed = 0;
        void init_window();
        void init_player();
        void init_gamemode(OptionsMenu& options);
    public:
        Game();
        ~Game();
        // void init_music();
        void render();
        void update();
        void run();
        void update_events();
        void update_dt();
        void update_collisions();
        void restart();
        void calculate_score();
        void score_save_to_txt();
        void score_load_from_txt();
        void clear_save();
        void level_save_to_txt();
        void level_load_from_txt();
};
#endif