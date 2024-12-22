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
    moore = ruleset[index] == 'M';

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
    static auto print_int_unordered_set = [](const std:: string& name, const std::unordered_set<int>& values) {
        std::cout << name << ": ";

        for(const int& val : values) {
            std::cout << val << ' ';
        }

        std::cout << '\n';
    };

    std::cout << "Ruleset: " << ruleset << '\n';
    print_int_unordered_set("Survival", survival);
    print_int_unordered_set("Birth", birth);
    print_int_unordered_set("Death", death);
    std::cout << "Neighbourhood: " << (moore ? "Moore" : "Other") << '\n';
}

bool Ruleset::survives(int neighbours) {
    return survival.contains(neighbours);
}

bool Ruleset::isBorn(int neighbours) {
    return birth.contains(neighbours);
}

bool Ruleset::dies(int neighbours) {
    return death.contains(neighbours);
}
