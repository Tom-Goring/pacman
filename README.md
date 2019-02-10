# Pacman

Simple game that could form the basis of an actual pacman implementation 
(with a bigger display anyway).

## Getting Started

You will need the full dir of MicroBit headers + mbed.h and associated in order
to build. These can be obtained in multiple ways (mostly by googling how).

In order to compile and load onto a MicroBit, you should just be able to run 
"make" on a linux terminal from the pacman dir (the one with the MakeFile). 

You WILL need to edit the MICROBIT_PATH variable in the MakeFile to whatever dir
path your MicroBit resides on. For me this is:

    /media/tom/MICROBIT

however this can vary depending on environment.

If this does not for some reason work, the source file "main.cpp" can be copied
into a new or pre-existing project and compiled using yotta with the following:

1. Ensure header files exist.
2. CD to dir that would contain MakeFile.
2. Set target using "yt target bbc-microbit-classic-gcc".
3. Build with "yt build".

The source file should in theory work when just copy pasted into the src dir
of a different MicroBit project.

### Game Mechanics

The game is very simple, consisting of moving a single pixel (player character)
around the 5x5 grid, while avoiding a slowly increasing number of enemies. Due
to limited screen size, the game will very likely end somewhere around the
region of 25-30 score.

The player character is moved around using the MicroBit's onboard accelerometer,
and will "fall" towards whatever edge is closest to the ground. The enemies will
move towards the player at a steady pace, and their spawn locations are randomly
decided (which at this stage does mean they can spawn on top of you!).

When the grid gets a little too crowded, or you come too close to an enemy, you
can press both the buttons on the MicroBit (A&B) together, and the field will be
cleared of enemies. The number of points you score however, is tied to the
number of enemies on the grid, so a balance must be struck.

### Misc Details

The project was coded in CLion using a combination of CMakeLists and a MakeFile
to automatically run the commands necessary. Should you wish to replicate this,
you need to create a CMakeLists.txt file similar to mine with the correct source
dirs referenced, a MakeFile with the commands necessary to build and load the
binaries onto the device, and then create a config in CLion that runs the
MakeFile when you "run" the project.