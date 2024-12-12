#ifndef PLAYER_H
#define PLAYER_H
#include "../entity.h"
#include "../health/healthbar.h"
#include "../bullets/bullet_list.h"
#include "enemies_list.h"
#include "../../room/room.h"
#include "../health/bossbar.h"
class Player : public Entity {
    private:
        BulletList* bullets = new BulletList();
        float attack_speed = 600;
        HealthBar* healthbar = new HealthBar();
        float range = 600;
        bool can_move_a = true;
        bool can_move_d = true;
        bool can_move_s = true;
        bool can_move_w = true;
    public:
        Player();
        ~Player();
        void render(sf::RenderWindow* window) override;
        void update(const float& dt) override;
        float get_range();
        void update_collisions(EnemiesList* enemies);
        void remove_health() override;
        bool get_alive();
        void set_health(int health);
        void restart();
        void collisions_with_walls(std::unique_ptr<Room>& room);
        void clear() override;
        void set_range(float new_range);
        float get_attack_speed();
        void set_attack_speed(float new_attack_speed);
        void save_to_file();
        void load_from_file();
};

#endif
