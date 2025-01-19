/***************************************************************************************************
 * @file  Ruleset.cpp
 * @brief Implementation of the Ruleset class
 **************************************************************************************************/

#include "applications/cellular_automata/Ruleset.hpp"

#include <iostream>

Ruleset::Ruleset(const std::string& ruleset) : ruleset(ruleset) {
    int index = 0;

    read_values(read_rule(ruleset, index), survival);
    read_values(read_rule(ruleset, index), birth);
    statesAmount = std::stoi(read_rule(ruleset, index));

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

void Ruleset::read_values(const std::string& rule, std::unordered_set<unsigned int>& values) {
    std::string buf1;
    std::string buf2;
    unsigned int value;

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

            value = std::stoi(buf2);
            for(unsigned int j = std::stoi(buf1) ; j <= value ; ++j) {
                values.emplace(j);
            }

            buf1.clear();
            buf2.clear();
        }
    }
}

void Ruleset::print_rules() const {
    static auto print_int_unordered_set = [](const std:: string& name, const std::unordered_set<unsigned int>& values) {
        std::cout << name << ": ";

        for(const unsigned int& val : values) {
            std::cout << val << ' ';
        }

        std::cout << '\n';
    };

    std::cout << "Ruleset: " << ruleset << '\n';

    print_int_unordered_set("Survival", survival);
    print_int_unordered_set("Birth", birth);
    std::cout << "States Amount: " << statesAmount << '\n';
    std::cout << "Neighborhood Type: ";
    switch(neighborhoodType) {
        case NeighborhoodType::Moore:
            std::cout << "Moore";
            break;
        case NeighborhoodType::VonNeumann:
            std::cout << "Von Neumann";
            break;
    }
    std::cout << '\n';
}

bool Ruleset::survives(unsigned int neighbors) const {
    return survival.contains(neighbors);
}

bool Ruleset::isBorn(unsigned int neighbors) const {
    return birth.contains(neighbors);
}

bool Ruleset::isAlive(unsigned int state) const {
    return state == (statesAmount - 1);
}

unsigned int Ruleset::getStatesAmount() const {
    return statesAmount;
}

NeighborhoodType Ruleset::getNeighborhoodType() const {
    return neighborhoodType;
}
