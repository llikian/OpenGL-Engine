/***************************************************************************************************
 * @file  Cell.hpp
 * @brief Declaration of the Cell class
 **************************************************************************************************/

#pragma once

#include <cstdlib>

/**
 * @class Cell
 * @brief
 */
struct Cell {
public:
    Cell();
    Cell(unsigned int state);

    u_int8_t neighbors;
    u_int8_t state;
    u_int8_t next;
};