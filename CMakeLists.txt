cmake_minimum_required(VERSION 3.21)
project(goldfish)

set(CMAKE_CXX_STANDARD 17)

add_executable(goldfish src/main.cpp src/Card.h src/Goldfish/Goldfish.cpp src/Goldfish/Goldfish.h ../old/Land.h ../old/Nonland.h src/Card.cpp src/Goldfish/goldfish_cardData.cpp src/GameResult.cpp src/GameResult.h src/stack/LinkedStack.tpp src/stack/LinkedStack.h src/Goldfish/goldfish_gameFuncs.cpp src/Goldfish/goldfish_interface.cpp src/Goldfish/goldfish_landFuncs.cpp src/Goldfish/goldfish_fileFuncs.cpp)
