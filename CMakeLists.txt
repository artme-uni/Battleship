cmake_minimum_required(VERSION 3.1)
project(Battleship)

set(CMAKE_CXX_STANDARD 14)

add_executable(Battleship main.cpp Field/Field.cpp Field/Field.h Bots/Bot_Attack.cpp Bots/Bot_Attack.h Bots/Bot_Arrange.cpp Bots/Bot_Arrange.h Field/Ship.cpp Field/Ship.h)
add_executable(Unittests test.cpp Field/Field.cpp Field/Field.h Bots/Bot_Attack.cpp Bots/Bot_Attack.h Bots/Bot_Arrange.cpp Bots/Bot_Arrange.h Field/Ship.cpp Field/Ship.h)