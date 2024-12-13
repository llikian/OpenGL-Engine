/***************************************************************************************************
 * @file  game_of_life.cpp
 * @brief Contains the main program of the GameOfLife application
 **************************************************************************************************/

#include "applications/GameOfLifeApp.hpp"

#include <iostream>
#include <stdexcept>

int main() {
    try {
        GameOfLifeApp().run();
    } catch(const std::exception& exception) {
        std::cerr << "ERROR : " << exception.what() << '\n';
        return -1;
    }

    return 0;
}