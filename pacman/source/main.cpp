#include "MicroBit.h"
#include <vector>

// TODO: Add difficulty and score scaling
// TODO: Add some form of other input usage

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void handle_player_movement();
void handle_enemy_movement();
void handle_screen_updates();
void track_score();
void initialise_game();
void reset_enemies(MicroBitEvent);
bool check_game_status();

class Player {
public:
    int16_t x;
    int16_t y;
    int score;
    void init() {
        x = 2;
        y = 2;
        score = 0;
    }
};

class Enemy {
public:
    int16_t x;
    int16_t y;
    Enemy() {
        x = rand() % 4;
        y = rand() % 4;
    }
};


MicroBit             uBit;
std::vector<Enemy*>  enemies;
Player               player;
bool                 game_over;

int main() {

    uBit.init();

    while (1) {

        uBit.display.scroll("PACMAN");

        initialise_game();

        while (!game_over) {

            handle_screen_updates();
            game_over = check_game_status();
        }

        uBit.display.clear();
        uBit.display.scroll("GAME OVER");
        uBit.display.scroll("SCORE:");
        uBit.display.print(player.score);

        uBit.sleep(5000);
    }
}

void handle_player_movement() {

    while (!game_over) {

        uBit.sleep(250);

        if (uBit.accelerometer.getX() < -300 && player.x != 0) {

            player.x--;
        }
        else if (uBit.accelerometer.getX() > 300 && player.x != 4) {

            player.x++;
        }
        else if (uBit.accelerometer.getY() < -300 && player.y != 0) {

            player.y--;
        }
        else if (uBit.accelerometer.getY() > 300 && player.y != 4) {

            player.y++;
        }
    }
}

void handle_enemy_movement() {

    uBit.sleep(2000);

    enemies.clear();
    enemies.push_back(new Enemy);

    while (!game_over) {

        uBit.sleep(500);

        if (player.score > 10 && enemies.size() < 2) {

            enemies.push_back(new Enemy());
        }
        else if (player.score > 25 && enemies.size() < 3) {

            enemies.push_back(new Enemy());
        }


        for (Enemy* enemy : enemies) {

            if (player.x < enemy->x && enemy->x != 0) {

                enemy->x--;
            }
            else if (player.x > enemy->x && enemy->x != 4) {

                enemy->x++;
            }
            else if (player.y < enemy->y && enemy->y != 0) {

                enemy->y--;
            }
            else if (player.y > enemy->y && enemy->y != 4) {

                enemy->y++;
            }
        }
    }
}

void handle_screen_updates() {

    uBit.sleep(10);
    uBit.display.clear();
    uBit.display.image.setPixelValue(player.x, player.y, 255);
    for (Enemy* enemy : enemies) {
        uBit.display.image.setPixelValue(enemy->x, enemy->y, 255);
    }
}

void track_score() {

    while (!game_over) {

        uBit.sleep(2500);
        player.score += enemies.size();
    }
}

void initialise_game() {

    game_over = false;

    player.init();
    enemies.clear();
    create_fiber(handle_player_movement);
    create_fiber(handle_enemy_movement);
    create_fiber(track_score);

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, reset_enemies);

    uBit.display.image.setPixelValue(player.x, player.y, 255);
}

void reset_enemies(MicroBitEvent) {

    enemies.clear();
    uBit.sleep(2000);
    enemies.push_back(new Enemy());
}

bool check_game_status() {

    for (Enemy* enemy : enemies) {
        if (player.x == enemy->y && player.y == enemy->y) {
            return true;
        }
    }
    return false;
}

#pragma clang diagnostic pop