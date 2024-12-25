/***************************************************************************************************
 * @file  Cell.cpp
 * @brief Implementation of the Cell class
 **************************************************************************************************/

#include "applications/game_of_life/Cell.hpp"

Cell::Cell() : neighbors(0), state(0), next(0) { }

Cell::Cell(unsigned int state) : neighbors(0), state(state), next(state) { }

void Cell::flip() {
    state = next;
}
