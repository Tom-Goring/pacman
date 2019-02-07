cmake_minimum_required(VERSION 3.9.6)
project(pacman)

set(CMAKE_CXX_STANDARD 11)
cmake_policy(SET CMP0054 OLD)

file(GLOB_RECURSE sources
        pacman/source/*.h
        pacman/source/*.cpp)

file(GLOB_RECURSE project
        .gitignore
        pacman/.yotta.json
        pacman/config.json
        pacman/LICENSE
        pacman/Makefile
        pacman/module.json
        pacman/README.md)

include_directories(pacman/yotta_modules/microbit/inc
        pacman/yotta_modules/microbit-dal/inc/bluetooth
        pacman/yotta_modules/microbit-dal/inc/core
        pacman/yotta_modules/microbit-dal/inc/drivers
        pacman/yotta_modules/microbit-dal/inc/platform
        pacman/yotta_modules/microbit-dal/inc/types
        pacman/yotta_modules/microbit-dal/source/asm
        pacman/yotta_modules/microbit-dal/source/bluetooth
        pacman/yotta_modules/microbit-dal/source/core
        pacman/yotta_modules/microbit-dal/source/drivers
        pacman/yotta_modules/microbit-dal/source/types
        pacman/yotta_modules/ble)

add_executable(pacman ${sources})
