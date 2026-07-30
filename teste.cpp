#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct Team{ //Obs: os atributos de um time em campo vão de 40 (Péssimo) a 99 (Perfeito);
    int midfield, attack, defense;
    string name;
};
mt19937 gen(time(nullptr));

int aleatorio(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}

int main() {

    Team team1, team2;
    team1.name = "Flamengo";
    team2.name = "Fluminense";
    team1.midfield = 85;
    team1.attack = 83;
    team1.defense = 81;
    team2.midfield = 75;
    team2.attack = 78;
    team2.defense = 74;

    cout << "Match between " << team1.name << " and " << team2.name << endl;
    cout << "Simulating match... minute a minute." << endl;

    int acrecimo = aleatorio(0, 5);
    double chance1 = (double)(team1.midfield)/(team1.midfield + team2.midfield) * 100;

    int gx1 = (team1.attack - team2.defense)/2;
    int gx2 = (team2.attack - team1.defense)/2;

    if(gx1 < 1) gx1 = 1;
    if(gx2 < 1) gx2 = 1;

    int goals1 = 0, goals2 = 0;

    int acumulativo1 = 1, acumulativo2 = 1;
    vector<string> events;

    for(int i = 0; i <= 90 + acrecimo; i++) {
        system("cls");
        for(const string& event : events) {
            cout << event << endl;
            
        }
        if(i > 90) cout << "90 + " << i - 90 << "'";
        else cout << i << "'";
        Sleep(50);
        int chance = aleatorio(1, 100);

        if(chance <= chance1) {
            int goalChance = aleatorio(1, 100);
            if(goalChance/acumulativo1 <= gx1) {
                goals1++;
                cout << " - " << team1.name << " scored a goal! Total goals: " << goals1;
                events.push_back(to_string(i) + "' " + team1.name + " scored a goal!");
                if(goals1 > 3) acumulativo1 *= 2;
            }
        } else {
            int goalChance = aleatorio(1, 100);
            if(goalChance/acumulativo2 <= gx2) {
                goals2++;
                cout << " - " << team2.name << " scored a goal! Total goals: " << goals2;
                events.push_back(to_string(i) + "' " + team2.name + " scored a goal!");
                if(goals2 > 3) acumulativo2 *= 2;
            }
        }
    }
    cout << " - Match Finished. \nscore: " << team1.name << " [ " << goals1 << " - " << goals2 << " ] " << team2.name << endl;

}