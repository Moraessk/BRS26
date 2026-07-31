#pragma once
#include <vector>
#include <string>

struct clube{
    std::string name;
    int midfield, attack, defense;
    int id; // Adicionei o campo id para identificar cada time
};

extern std::vector<clube> teams;