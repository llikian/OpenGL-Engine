/***************************************************************************************************
 * @file  Cell.cpp
 * @brief Implementation of the Cell class
 **************************************************************************************************/

#include "applications/game_of_life/Cell.hpp"

Cell::Cell(bool state) : state(state) { }

Cell::operator bool&() {
    return state;
}
