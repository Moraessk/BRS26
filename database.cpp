#include "Database.h" //.cpp

std::vector<clube> teams = {
    {"World Class", 99, 99, 99, 0}, //Aqui ta nessa ordem: nome, meio campo, ataque e defesa
    //Brasileirão 1 - 20
    {"Palmeiras", 80, 81, 83, 1}, {"Flamengo", 77, 84, 81, 2}, {"Corinthians", 74, 76, 77, 3}, {"Fluminense", 73, 78, 76, 4}, {"Bahia", 71, 76, 74, 5}, 
    {"Botafogo", 70, 74, 75, 6}, {"Athletico Paranaense", 72, 73, 73, 7}, {"Atletico Mineiro", 70, 74, 73, 8}, {"Red Bull Bragantino", 69, 72, 72, 9}, 
    {"Sao Paulo", 71, 72, 70, 10}, {"Gremio", 68, 71, 71, 11}, {"Cruzeiro", 67, 70, 71, 12}, {"Internacional", 68, 69, 68, 13}, {"Santos", 65, 69, 72, 14}, 
    {"Vasco da Gama", 65, 68, 68, 15}, {"Coritiba", 65, 66, 67, 16}, {"Vitoria", 64, 66, 67, 17}, {"Mirassol", 64, 65, 66, 18}, {"Remo", 63, 65, 66, 19}, 
    {"Chapecoense", 63, 65, 66, 20},

    //Bundesliga 21 - 40
    {"Bayern Munich", 85, 89, 91, 21}, {"Borussia Dortmund", 80, 83, 85, 22}, {"RB Leipzig", 79, 82, 83, 23}, {"Bayer Leverkusen", 81, 84, 84, 24}, 
    {"VfB Stuttgart", 76, 79, 80, 25}, {"Eintracht Frankfurt", 74, 78, 79, 26}, {"TSG Hoffenheim", 71, 74, 76, 27}, {"SC Freiburg", 75, 75, 73, 28}, 
    {"Mainz 05", 73, 72, 72, 29}, {"Werder Bremen", 70, 72, 74, 30}, {"Borussia Monchengladbach", 70, 72, 73, 31}, {"1. FC Koln", 69, 68, 70, 32}, 
    {"Union Berlin", 72, 69, 68, 33}, {"Hamburger SV", 68, 69, 71, 34}, {"FC Augsburg", 68, 67, 68, 35}, {"Schalke 04", 66, 68, 69, 36}, {"Elversberg", 64, 65, 66, 37}, 
    {"Paderborn", 63, 65, 66, 38}, {"NA", 0, 0, 0, 39}, {"NA", 0, 0, 0, 40},
    
    //eredivise 41 - 60
    {"PSV Eindhoven", 78, 84, 82, 41}, {"Ajax", 77, 82, 80, 42}, {"Feyenoord", 76, 81, 80, 43}, {"AZ Alkmaar", 74, 78, 76, 44}, {"FC Twente", 72, 75, 74, 45}, 
    {"FC Utrecht", 70, 73, 72, 46}, {"NEC Nijmegen", 68, 70, 71, 47}, {"SC Heerenveen", 68, 70, 69, 48}, {"FC Groningen", 67, 68, 69, 49}, {"Sparta Rotterdam", 67, 67, 68, 50}, 
    {"Go Ahead Eagles", 66, 67, 69, 51}, {"PEC Zwolle", 65, 67, 67, 52}, {"Fortuna Sittard", 65, 65, 67, 53}, {"Excelsior", 64, 65, 67, 54}, {"Willem II", 64, 65, 66, 55}, 
    {"ADO Den Haag", 64, 65, 66, 56}, {"SC Cambuur", 63, 65, 66, 57}, {"Telstar", 63, 65, 66, 58}, {"NA", 0, 0, 0, 59}, {"NA", 0, 0, 0, 60},

    //Laliga 61 - 80
    {"Real Madrid", 85, 89, 91, 61}, {"Barcelona", 83, 87, 88, 62}, {"Atletico de Madrid", 84, 84, 82, 63}, {"Villarreal", 76, 79, 79, 64}, {"Real Betis", 73, 77, 76, 65}, 
    {"Athletic Bilbao", 78, 75, 74, 66}, {"Real Sociedad", 76, 75, 73, 67}, {"Sevilla", 74, 73, 72, 68}, {"Celta de Vigo", 70, 73, 73, 69}, {"Valencia", 72, 71, 71, 70}, 
    {"Rayo Vallecano", 70, 69, 69, 71}, {"Espanyol", 68, 69, 70, 72}, {"Osasuna", 72, 68, 67, 73}, {"Getafe", 74, 66, 64, 74}, {"Deportivo La Coruna", 66, 67, 68, 75}, 
    {"Levante", 65, 66, 68, 76}, {"Alaves", 67, 65, 65, 77}, {"Elche", 64, 65, 66, 78}, {"Malaga", 63, 65, 66, 79}, {"Racing Santander", 63, 65, 66, 80},

    //Liga MX 81 - 100
    {"Deportivo Toluca", 77, 81, 80, 81}, {"Cruz Azul", 76, 80, 79, 82}, {"Club America", 76, 79, 80, 83}, {"Monterrey", 74, 78, 79, 84}, {"Tigres UANL", 75, 77, 78, 85}, 
    {"Guadalajara", 73, 76, 77, 86}, {"Pachuca", 72, 76, 76, 87}, {"Pumas UNAM", 70, 73, 74, 88}, {"Club Tijuana", 68, 72, 73, 89}, {"Club Leon", 69, 71, 72, 90}, 
    {"Atlas", 68, 70, 70, 91}, {"Necaxa", 67, 69, 70, 92}, {"Queretaro", 66, 68, 69, 93}, {"Atlético de San Luis", 65, 67, 69, 94}, {"Santos Laguna", 64, 66, 68, 95}, 
    {"FC Juarez", 64, 66, 67, 96}, {"Puebla", 63, 65, 66, 97}, {"Atlante", 63, 65, 66, 98}, {"NA", 0, 0, 0, 99}, {"NA", 0, 0, 0, 100},

    //Liga NOS.
    {"FC Porto", 78, 84, 82, 101}, {"Benfica", 77, 83, 82, 102}, {"Sporting CP", 78, 82, 81, 103}, {"SC Braga", 73, 77, 75, 104}, {"Vitória Guimaraes", 70, 73, 72, 105}, 
    {"Famalicao", 68, 71, 70, 106}, {"Rio Ave", 67, 69, 69, 107}, {"Gil Vicente", 66, 68, 69, 108}, {"Estoril", 65, 68, 68, 109}, {"Arouca", 65, 67, 68, 110}, 
    {"Santa Clara", 65, 67, 67, 111}, {"Moreirense", 66, 66, 66, 112}, {"Casa Pia", 64, 66, 66, 113}, {"Nacional", 64, 65, 66, 114}, {"Alverca", 63, 65, 66, 115}, 
    {"Estrela Amadora", 63, 65, 65, 116}, {"Académico Viseu", 63, 65, 66, 117}, {"Marítimo", 63, 65, 66, 118}, {"NA", 0, 0, 0, 119}, {"NA", 0, 0, 0, 120},

     //league one 121 - 140
     {"Paris Saint-Germain", 87, 91, 94, 121}, {"AS Monaco", 77, 82, 81, 122}, {"Olympique Marseille", 76, 79, 79, 123}, {"LOSC Lille", 78, 79, 78, 124}, 
     {"Olympique Lyon", 74, 78, 77, 125}, {"RC Strasbourg", 72, 75, 75, 126}, {"Stade Rennais", 72, 75, 74, 127}, {"RC Lens", 76, 74, 73, 128}, 
     {"OGC Nice", 74, 73, 72, 129}, {"FC Toulouse", 68, 72, 72, 130}, {"Paris FC", 67, 69, 70, 131}, {"Stade Brestois", 71, 68, 68, 132}, {"FC Lorient", 66, 68, 69, 133}, 
     {"AJ Auxerre", 65, 67, 68, 134}, {"Angers SCO", 65, 66, 67, 135}, {"Le Havre", 66, 64, 64, 136}, {"Troyes", 63, 65, 66, 137}, {"Le Mans", 63, 65, 66, 138}, {"NA", 0, 0, 0, 139}, {"NA", 0, 0, 0, 140},

     //LPF 141 - 160
    {"River Plate", 82, 79, 80, 141}, {"Boca Juniors", 79, 77, 76, 142}, {"Racing Club", 77, 81, 82, 143}, {"Independiente", 76, 79, 78, 144}, {"San Lorenzo", 75, 77, 76, 145},
    {"Estudiantes de La Plata", 76, 78, 77, 146}, {"Velez Sarsfield", 75, 78, 77, 147}, {"Rosario Central", 74, 76, 76, 148}, {"Talleres", 73, 76, 77, 149}, {"Lanus", 72, 74, 74, 150}, 
    {"Newell's Old Boys", 71, 73, 73, 151}, {"Argentinos Juniors", 71, 74, 72, 152}, {"Defensa y Justicia", 70, 73, 73, 153}, {"Belgrano", 70, 72, 73, 154}, {"Huracan", 70, 71, 71, 155}, 
    {"Gimnasia La Plata", 68, 69, 70, 156}, {"Platense", 68, 69, 69, 157}, {"Instituto", 67, 68, 69, 158}, {"Union", 66, 68, 68, 159}, {"Central Cordoba", 65, 67, 68, 160},

    //MLS 161 - 180
    {"Inter Miami", 82, 84, 87, 161}, {"Los Angeles FC", 80, 82, 83, 162}, {"FC Cincinnati", 78, 80, 81, 163}, {"Columbus Crew", 79, 79, 80, 164}, {"Orlando City", 77, 78, 79, 165}, 
    {"Seattle Sounders", 78, 77, 78, 166}, {"Atlanta United", 74, 78, 80, 167}, {"New York City FC", 76, 77, 77, 168}, {"Portland Timbers", 73, 76, 78, 169}, {"Philadelphia Union", 77, 75, 74, 170}, 
    {"San Diego FC", 72, 75, 76, 171}, {"Real Salt Lake", 74, 74, 74, 172}, {"New York Red Bulls", 75, 73, 73, 173}, {"Nashville SC", 76, 72, 72, 174}, {"Chicago Fire", 70, 73, 75, 175}, 
    {"Colorado Rapids", 71, 73, 73, 176}, {"Charlotte FC", 70, 72, 74, 177}, {"New England Revolution", 70, 72, 73, 178}, {"Vancouver Whitecaps", 71, 71, 72, 179}, {"FC Dallas", 69, 71, 72, 180},

    //Premiere League 181 - 200
    {"Arsenal", 85, 89, 88, 181}, {"Liverpool", 82, 85, 87, 182}, {"Manchester City", 84, 87, 89, 183}, {"Manchester United", 77, 81, 82, 184}, {"Chelsea", 78, 81, 82, 185}, 
    {"Tottenham Hotspur", 74, 78, 80, 186}, {"Newcastle United", 77, 78, 79, 187}, {"Aston Villa", 76, 78, 78, 188}, {"Brighton", 73, 76, 77, 189}, {"Crystal Palace", 74, 73, 74, 190}, 
    {"Brentford", 72, 74, 75, 191}, {"Nottingham Forest", 72, 73, 74, 192}, {"Everton", 73, 70, 70, 193}, {"Fulham", 70, 72, 72, 194}, {"AFC Bournemouth", 69, 72, 74, 195}, 
    {"Leeds United", 67, 69, 71, 196}, {"Sunderland", 65, 67, 69, 197}, {"Ipswich Town", 64, 66, 68, 198}, {"Coventry City", 63, 65, 67, 199}, {"Hull City", 61, 64, 66, 200},

    //Serie A 201 - 220
    {"Inter Milan", 83, 87, 86, 201}, {"Juventus", 80, 83, 82, 202}, {"Napoli", 79, 82, 83, 203}, {"AS Roma", 76, 80, 80, 204}, {"AC Milan", 78, 80, 81, 205}, {"Atalanta", 77, 79, 80, 206}, 
    {"Como 1907", 73, 77, 78, 207}, {"Fiorentina", 74, 76, 76, 208}, {"Bologna", 73, 75, 75, 209}, {"Lazio", 74, 74, 73, 210}, {"Udinese", 69, 70, 71, 211}, {"Parma", 68, 70, 71, 212}, 
    {"Genoa", 69, 69, 70, 213}, {"Sassuolo", 68, 69, 71, 214}, {"Torino", 71, 68, 68, 215}, {"Cagliari", 67, 68, 69, 216}, {"Lecce", 65, 66, 68, 217}, {"Venezia", 64, 66, 67, 218}, 
    {"Frosinone", 63, 65, 67, 219}, {"Monza", 63, 65, 66, 220},

    //Saudi Pro League 221 - 240
    {"Al-Hilal", 79, 81, 83, 221}, {"Al-Ahli", 79, 80, 81, 222}, {"Al-Nassr", 79, 84, 86, 223}, {"Al-Ittihad", 78, 81, 82, 224}, {"Al-Qadsiah", 75, 79, 80, 225}, {"NEOM SC", 72, 75, 77, 226}, 
    {"Al-Shabab", 70, 72, 73, 227}, {"Al-Ettifaq", 68, 70, 71, 228}, {"Al-Taawoun", 68, 69, 70, 229}, {"Al-Khaleej", 66, 67, 69, 230}, {"Al-Fayha", 66, 67, 68, 231}, {"Al-Kholood", 64, 66, 68, 232}, 
    {"Al-Diriyah", 64, 66, 67, 233}, {"Al-Fateh", 63, 65, 67, 234}, {"Al-Faisaly", 63, 65, 66, 235}, {"Abha", 63, 65, 66, 236}, {"Al-Riyadh", 62, 64, 66, 237}, {"Al-Hazem", 62, 64, 66, 238}, 
    {"NA", 0, 0, 0, 239}, {"NA", 0, 0, 0, 240},

    //Internacional FIFA.
    {"Spain", 88, 92, 94, 241}, {"Argentina", 86, 91, 92, 242}, {"France", 87, 90, 93, 243}, {"England", 85, 89, 90, 244}, {"Brazil", 84, 88, 91, 245}, {"Portugal", 83, 87, 89, 246},
    {"Netherlands", 82, 85, 87, 247}, {"Germany", 82, 85, 86, 248}, {"Belgium", 80, 83, 85, 249}, {"Italy", 80, 82, 84, 250}, {"Colombia", 79, 83, 85, 251}, {"Croatia", 79, 81, 82, 252},
    {"Morocco", 78, 81, 83, 253}, {"Uruguay", 78, 82, 83, 254}, {"Japan", 76, 79, 81, 255}, {"Switzerland", 77, 79, 80, 256}, {"Denmark", 76, 79, 80, 257}, {"Senegal", 76, 80, 82, 258},
    {"Mexico", 75, 78, 80, 259}, {"United States", 73, 77, 79, 260}
    //Borussia Monchengladbach é o time com + caracteries 26 no total.
};
