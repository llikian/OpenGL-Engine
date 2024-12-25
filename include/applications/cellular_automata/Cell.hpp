/***************************************************************************************************
 * @file  Cell.hpp
 * @brief Declaration of the Cell class
 **************************************************************************************************/

#pragma once

/**
 * @class Cell
 * @brief
 */
struct Cell {
public:
    Cell();
    Cell(unsigned int state);

    void flip();

    unsigned int neighbors;
    unsigned int state;
    unsigned int next;
};