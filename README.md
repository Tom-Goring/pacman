# Pacman

Simple game that could form the basis of an actual pacman implementation 
(with a bigger display anyway).

## Getting Started

You will need the full dir of MicroBit headers + mbed.h and associated in order
to build. These can be obtained in multiple ways (mostly by googling how).

In order to compile and load onto a MicroBit, you should just be able to run 
"make" on a linux terminal from the pacman dir (the one with the MakeFile). 
If this does not for some reason work, the source file "main.cpp" can be copied
into a new or pre-existing project and compiled using yotta with the following:

1. Ensure header files exist.
2. CD to dir that would contain MakeFile.
2. Set target using "yt target bbc-microbit-classic-gcc".
3. Build with "yt build".

### Game Mechanics

The game is very simple, consisting of moving a single pixel (player character)
around the 5x5 grid, while avoiding a slowly increasing number of enemies. Due
to limited screen size, the game will very likely end somewhere around the
region of 25-30 score.

The player character is moved around using the MicroBit's onboard accelerometer,
and will "fall" towards whatever edge is closest to the ground. The enemies will
move towards the player at a steady pace, and their spawn locations are randomly
decided (which at this stage does mean they can spawn on top of you!).