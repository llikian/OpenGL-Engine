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
    Cell(bool state);

    operator bool&();

    bool state;
};