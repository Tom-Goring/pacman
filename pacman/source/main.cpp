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
void check_game_status();

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


MicroBit            uBit;
std::vector<Enemy*>  enemies;
Player              player;
bool                game_over;


int main() {

    while (1) {

        uBit.init();

        initialise_game();

        while (!game_over) {

            handle_screen_updates();
            check_game_status();
        }

        uBit.serial.send(game_over);

        uBit.display.scroll("GAME OVER");
        uBit.display.scroll("SCORE:");
        uBit.display.print(player.score);
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

    while (!game_over) {

        uBit.sleep(500);

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

        // TODO: add a score modifier here (number of enemies && speed?)
        uBit.sleep(2500);
        player.score++;
    }
}

void initialise_game() {

    player.init();
    create_fiber(handle_player_movement);

    uBit.sleep(2500);

    enemies.clear();
    enemies.push_back(new Enemy);
    create_fiber(handle_enemy_movement);

    create_fiber(track_score);

    game_over = false;
    uBit.display.image.setPixelValue(player.x, player.y, 255);


}

void check_game_status() {

    for (Enemy* enemy : enemies) {

        if (player.x == enemy->y && player.y == enemy->y) {

            game_over = true;
        }
    }
}

#pragma clang diagnostic pop