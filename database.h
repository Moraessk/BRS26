#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <queue>
#include <Windows.h>
using namespace std;

struct clube{
    std::string nome;
    int ataque = 0, meio_campo = 0, defesa = 0;
    int id = -1; // Adicionei o campo id para identificar cada time
};

extern std::vector<clube> teams;
/*
    aproveitando que aqui tem pouca coisa, vou explicar o codigo:
    no geral, funções q tem função de centralizar (addbar, barstr, centerstr e rendelizarcenter)
    vão ter a seguinte sintaxe: função(frase, tamanho do que vc quer ocupar).

*/
