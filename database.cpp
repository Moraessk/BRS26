#include "Database.h"

std::vector<clube> teams = {
    {"World Class", 99, 99, 99, 0}, //Aqui ta nessa ordem: nome, meio campo, ataque e defesa
    //Brasileirão 1 - 20
    {"Palmeiras", 82, 86, 85, 1}, {"Flamengo", 77, 84, 81, 2}, {"Corinthians", 74, 76, 77, 3}, {"Fluminense", 73, 78, 76, 4}, {"Bahia", 71, 76, 74, 5}, 
    {"Botafogo", 70, 74, 75, 6}, {"Athletico Paranaense", 72, 73, 73, 7}, {"Atlético Mineiro", 70, 74, 73, 8}, {"Red Bull Bragantino", 69, 72, 72, 9}, 
    {"São Paulo", 71, 72, 70, 10}, {"Grêmio", 68, 71, 71, 11}, {"Cruzeiro", 67, 70, 71, 12}, {"Internacional", 68, 69, 68, 13}, {"Santos", 65, 69, 72, 14}, 
    {"Vasco da Gama", 65, 68, 68, 15}, {"Coritiba", 65, 66, 67, 16}, {"Vitória", 64, 66, 67, 17}, {"Mirassol", 64, 65, 66, 18}, {"Remo", 63, 65, 66, 19}, 
    {"Chapecoense", 63, 65, 66, 20},

    //Bundesliga 21 - 40
    {"Bayern Munich", 85, 89, 91, 21}, {"Borussia Dortmund", 80, 83, 85, 22}, {"RB Leipzig", 79, 82, 83, 23}, {"Bayer Leverkusen", 81, 84, 84, 24}, 
    {"VfB Stuttgart", 76, 79, 80, 25}, {"Eintracht Frankfurt", 74, 78, 79, 26}, {"TSG Hoffenheim", 71, 74, 76, 27}, {"SC Freiburg", 75, 75, 73, 28}, 
    {"Mainz 05", 73, 72, 72, 29}, {"Werder Bremen", 70, 72, 74, 30}, {"Borussia Mönchengladbach", 70, 72, 73, 31}, {"1. FC Köln", 69, 68, 70, 32}, 
    {"Union Berlin", 72, 69, 68, 33}, {"Hamburger SV", 68, 69, 71, 34}, {"FC Augsburg", 68, 67, 68, 35}, {"Schalke 04", 66, 68, 69, 36}, {"Elversberg", 64, 65, 66, 37}, 
    {"Paderborn", 63, 65, 66, 38}, {"NA", 0, 0, 0, 39}, {"NA", 0, 0, 0, 40},
    
    //eredivise 41 - 60
    {"PSV Eindhoven", 78, 84, 82, 41}, {"Ajax", 77, 82, 80, 42}, {"Feyenoord", 76, 81, 80, 43}, {"AZ Alkmaar", 74, 78, 76, 44}, {"FC Twente", 72, 75, 74, 45}, 
    {"FC Utrecht", 70, 73, 72, 46}, {"NEC Nijmegen", 68, 70, 71, 47}, {"SC Heerenveen", 68, 70, 69, 48}, {"FC Groningen", 67, 68, 69, 49}, {"Sparta Rotterdam", 67, 67, 68, 50}, 
    {"Go Ahead Eagles", 66, 67, 69, 51}, {"PEC Zwolle", 65, 67, 67, 52}, {"Fortuna Sittard", 65, 65, 67, 53}, {"Excelsior", 64, 65, 67, 54}, {"Willem II", 64, 65, 66, 55}, 
    {"ADO Den Haag", 64, 65, 66, 56}, {"SC Cambuur", 63, 65, 66, 57}, {"Telstar", 63, 65, 66, 58}, {"NA", 0, 0, 0, 59}, {"NA", 0, 0, 0, 60},

    //Laliga 61 - 80
    {"Real Madrid", 85, 89, 91, 61}, {"Barcelona", 83, 87, 88, 62}, {"Atlético de Madrid", 84, 84, 82, 63}, {"Villarreal", 76, 79, 79, 64}, {"Real Betis", 73, 77, 76, 65}, 
    {"Athletic Bilbao", 78, 75, 74, 66}, {"Real Sociedad", 76, 75, 73, 67}, {"Sevilla", 74, 73, 72, 68}, {"Celta de Vigo", 70, 73, 73, 69}, {"Valencia", 72, 71, 71, 70}, 
    {"Rayo Vallecano", 70, 69, 69, 71}, {"Espanyol", 68, 69, 70, 72}, {"Osasuna", 72, 68, 67, 73}, {"Getafe", 74, 66, 64, 74}, {"Deportivo La Coruña", 66, 67, 68, 75}, 
    {"Levante", 65, 66, 68, 76}, {"Alavés", 67, 65, 65, 77}, {"Elche", 64, 65, 66, 78}, {"Málaga", 63, 65, 66, 79}, {"Racing Santander", 63, 65, 66, 80},

    //Liga MX 81 - 100
    {"Deportivo Toluca", 77, 81, 80, 81}, {"Cruz Azul", 76, 80, 79, 82}, {"Club América", 76, 79, 80, 83}, {"Monterrey", 74, 78, 79, 84}, {"Tigres UANL", 75, 77, 78, 85}, 
    {"Guadalajara", 73, 76, 77, 86}, {"Pachuca", 72, 76, 76, 87}, {"Pumas UNAM", 70, 73, 74, 88}, {"Club Tijuana", 68, 72, 73, 89}, {"Club León", 69, 71, 72, 90}, 
    {"Atlas", 68, 70, 70, 91}, {"Necaxa", 67, 69, 70, 92}, {"Querétaro", 66, 68, 69, 93}, {"Atlético de San Luis", 65, 67, 69, 94}, {"Santos Laguna", 64, 66, 68, 95}, 
    {"FC Juárez", 64, 66, 67, 96}, {"Puebla", 63, 65, 66, 97}, {"Atlante", 63, 65, 66, 98}, {"NA", 0, 0, 0, 99}, {"NA", 0, 0, 0, 100},

    //Liga NOS.
    {"FC Porto", 78, 84, 82, 101}, {"Benfica", 77, 83, 82, 102}, {"Sporting CP", 78, 82, 81, 103}, {"SC Braga", 73, 77, 75, 104}, {"Vitória Guimarães", 70, 73, 72, 105}, 
    {"Famalicão", 68, 71, 70, 106}, {"Rio Ave", 67, 69, 69, 107}, {"Gil Vicente", 66, 68, 69, 108}, {"Estoril", 65, 68, 68, 109}, {"Arouca", 65, 67, 68, 110}, 
    {"Santa Clara", 65, 67, 67, 111}, {"Moreirense", 66, 66, 66, 112}, {"Casa Pia", 64, 66, 66, 113}, {"Nacional", 64, 65, 66, 114}, {"Alverca", 63, 65, 66, 115}, 
    {"Estrela Amadora", 63, 65, 65, 116}, {"Académico Viseu", 63, 65, 66, 117}, {"Marítimo", 63, 65, 66, 118}, {"NA", 0, 0, 0, 119}, {"NA", 0, 0, 0, 120},

     

};