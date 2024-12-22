/***************************************************************************************************
 * @file  Ruleset.hpp
 * @brief Declaration of the Ruleset class
 **************************************************************************************************/

#pragma once

#include <string>
#include <unordered_set>

enum class NeighborhoodType {
    Moore,
    VonNeumann
};

/**
 * @class Ruleset
 * @brief
 */
class Ruleset {
public:
    Ruleset(const std::string& ruleset);

    static std::string read_rule(const std::string& ruleset, int& index);
    static void read_values(const std::string& rule, std::unordered_set<int>& values);

    void print_rules() const;

    bool survives(int neighbors);
    bool isBorn(int neighbors);
    bool dies(int neighbors);

private:
    std::string ruleset;
    std::unordered_set<int> survival;
    std::unordered_set<int> birth;
    std::unordered_set<int> death;
    NeighborhoodType neighborhoodType;
};