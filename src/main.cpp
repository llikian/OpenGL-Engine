/***************************************************************************************************
 * @file  main.cpp
 * @brief Contains the main program of the engine
 **************************************************************************************************/

#include "Application.hpp"

Application app;

#include <iostream>
#include <stdexcept>

int main() {
    try {
        app.run();
    } catch(const std::exception& exception) {
        std::cout << exception.what() << '\n';
        return -1;
    }

    return 0;
}