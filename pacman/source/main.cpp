#include "MicroBit.h"
#include <vector>

/*
 * Precursor to Pacman created on a MicroBit. Created by Tom Goring for IoT challenge 1.
 * Full Documentation can be found in README.md
 *
 * Hopefully anything difficult to understand is commented, but to be honest, the code tells most the story here.
 */

void handle_player_movement();
void handle_enemy_movement();
void handle_screen_updates();
void track_score();
void initialise_game();
void reset_enemies(MicroBitEvent);
void check_game_over();

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
        x = static_cast<int16_t>(rand() % 4); // conversion just to make CLion happy
        y = static_cast<int16_t>(rand() % 4);
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

        initialise_game(); // creates all fibers and sets initial variables

        while (!game_over) { // small sleep to prevent execution from locking
            uBit.sleep(10);
        }

        uBit.display.clear();
        uBit.display.scroll("GAME OVER");
        uBit.display.scroll("SCORE:");
        uBit.display.print(player.score);

        uBit.sleep(5000);
    }
}

// Polls accelerometers every 250ms and moves player coords in accordance - for use with a fiber, otherwise will lock
// execution.
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

// Loops through each enemy every 500ms and move them each towards the x/y coords of the player. also creates a
// new enemy at score 10 and 25
void handle_enemy_movement() {

    uBit.sleep(2000);

    enemies.clear();
    enemies.push_back(new Enemy); // new enemies are spawned on a random tile

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

// Displays the current game state onto the grid every 10ms.
void handle_screen_updates() {

    while (!game_over) {

        uBit.sleep(10);
        uBit.display.clear();
        uBit.display.image.setPixelValue(player.x, player.y, 255);
        for (Enemy *enemy : enemies) {
            uBit.display.image.setPixelValue(enemy->x, enemy->y, 255);
        }
    }
}

// Increments score by number of enemies every 2.5 seconds.
void track_score() {

    while (!game_over) {

        uBit.sleep(2500);
        player.score += enemies.size();
    }
}

void initialise_game() {

    game_over = false;

    player.init(); // set player initial coords to 2,2 (middle of grid)
    enemies.clear();
    create_fiber(handle_player_movement);
    create_fiber(handle_enemy_movement);
    create_fiber(track_score);
    create_fiber(check_game_over);
    create_fiber(handle_screen_updates);

    // resets enemies if AB is detected
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, reset_enemies);

    uBit.display.image.setPixelValue(player.x, player.y, 255);
}

// Clears all enemies from the grid
void reset_enemies(MicroBitEvent) {

    enemies.clear();
    uBit.sleep(2000);
    enemies.push_back(new Enemy());
}

// Checks if any enemy occupies the same tile as the player, then sets the game_over flag accordingly.
void check_game_over() {

    while (!game_over) {

        uBit.sleep(10);
        for (Enemy* enemy : enemies) {
            if (player.x == enemy->x && player.y == enemy->y) {
                game_over = true;
            }
        }
    }
}