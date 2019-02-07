#include "MicroBit.h"

struct Point {

    int16_t x;
    int16_t y;
};

MicroBit        uBit;
MicroBitImage   grid(5, 5);
int             score;
int             game_over;
int             level;
int             INVADER_SPEED;
int             PLAYER_SPEED;
int             BULLET_SPEED;
Point           player;
Point           bullet;



int main() {

    player.x = 2;
    player.y = 4;

    while (true) {

        uBit.sleep(10);
        uBit.display.image.clear();

        uBit.serial.send(uBit.accelerometer.getX());

        uBit.display.image.setPixelValue(player.x, player.y, 255);
    }
}