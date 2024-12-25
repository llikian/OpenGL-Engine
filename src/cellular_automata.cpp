/***************************************************************************************************
 * @file  cellular_automata.cpp
 * @brief Contains the main program of the CellularAutomata application
 **************************************************************************************************/

#include "applications/CellularAutomataApp.hpp"

#include <iostream>
#include <stdexcept>

int main() {
    try {
        CellularAutomataApp().run();
    } catch(const std::exception& exception) {
        std::cerr << "ERROR : " << exception.what() << '\n';
        return -1;
    }

    return 0;
}