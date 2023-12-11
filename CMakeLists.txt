cmake_minimum_required(VERSION 3.24)
project(ZombieHuman)

set(CMAKE_CXX_STANDARD 17)

add_executable(ZombieHuman src/main.cpp inc/City.h src/city.cpp inc/Zombie.h src/human.cpp src/organism.cpp src/zombie.cpp)
