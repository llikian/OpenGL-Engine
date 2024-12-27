/***************************************************************************************************
 * @file  Cell.cpp
 * @brief Implementation of the Cell class
 **************************************************************************************************/

#include "applications/cellular_automata/Cell.hpp"

Cell::Cell() : neighbors(0), state(0), next(0) { }

Cell::Cell(unsigned int state) : neighbors(0), state(state), next(state) { }
