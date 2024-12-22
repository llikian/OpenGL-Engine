/***************************************************************************************************
 * @file  Ruleset.cpp
 * @brief Implementation of the Ruleset class
 **************************************************************************************************/

#include "applications/game_of_life/Ruleset.hpp"

#include <iostream>

Ruleset::Ruleset(const std::string& ruleset) : ruleset(ruleset) {
    int index = 0;

    read_values(read_rule(ruleset, index), survival);
    read_values(read_rule(ruleset, index), birth);
    read_values(read_rule(ruleset, index), death);

    switch(ruleset[index]) {
        case 'M':
            neighborhoodType = NeighborhoodType::Moore;
            break;
        case 'N':
            neighborhoodType = NeighborhoodType::VonNeumann;
            break;
        default:
            throw std::runtime_error(std::string("Unknown neighborhood type: '") + ruleset[index] + "'");
    }

    print_rules();
}

std::string Ruleset::read_rule(const std::string& ruleset, int& index) {
    std::string rule;

    while(ruleset[index] != '/') {
        if(ruleset[index] == ',' || ruleset[index] == '-' || (ruleset[index] >= '0' && ruleset[index] <= '9')) {
            rule += ruleset[index];
        }

        index++;
    }

    index++;

    rule += ',';

    return rule;
}

void Ruleset::read_values(const std::string& rule, std::unordered_set<int>& values) {
    std::string buf1;
    std::string buf2;

    for(unsigned int i = 0 ; i < rule.size() ; ++i) {
        if(rule[i] >= '0' && rule[i] <= '9') {
            buf1 += rule[i];
        } else if(rule[i] == ',') {
            values.emplace(std::stoi(buf1));
            buf1.clear();
        } else if(rule[i] == '-') {
            i++;

            while(rule[i] >= '0' && rule[i] <= '9') {
                buf2 += rule[i];
                i++;
            }

            int val1 = std::stoi(buf1);
            int val2 = std::stoi(buf2);

            for(int j = val1 ; j <= val2 ; ++j) {
                values.emplace(j);
            }

            buf1.clear();
            buf2.clear();
        }
    }
}

void Ruleset::print_rules() const {
    static auto print_int_unordered_set = [](const std:: string& name, const std::unordered_set<int>& values) -> void {
        std::cout << name << ": ";

        for(const int& val : values) {
            std::cout << val << ' ';
        }

        std::cout << '\n';
    };

    static auto print_neighborhood_type = [](NeighborhoodType type) -> void {
        std::cout << "Neighborhood Type: ";

        switch(type) {
            case NeighborhoodType::Moore:
                std::cout << "Moore";
                break;
            case NeighborhoodType::VonNeumann:
                std::cout << "Von Neumann";
                break;
        }

        std::cout << '\n';
    };

    std::cout << "Ruleset: " << ruleset << '\n';
    print_int_unordered_set("Survival", survival);
    print_int_unordered_set("Birth", birth);
    print_int_unordered_set("Death", death);
    print_neighborhood_type(neighborhoodType);
}

bool Ruleset::survives(int neighbors) {
    return survival.contains(neighbors);
}

bool Ruleset::isBorn(int neighbors) {
    return birth.contains(neighbors);
}

bool Ruleset::dies(int neighbors) {
    return death.contains(neighbors);
}
