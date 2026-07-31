#include <bits/stdc++.h>
#include <windows.h>
#include "Database.cpp"
using namespace std;
mt19937 gen(time(nullptr));

string delay;

struct resultado{
    int goals1, goals2;
    int penalties1, penalties2;
};
struct infotorneio{
    int numberOfTeams;
    vector<clube> teams;
};

int aleatorio(int a, int b) {
    uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}
string centerstr(int width){
    string s = "";
    for(int i = 0; i < width; i++) s += " ";
    return s;
}
resultado simularPartida(clube team1, clube team2) {
    resultado res;
    string center = centerstr(80);
    int acrecimo = aleatorio(0, 5);
    double chance1 = (double)(team1.midfield)/(team1.midfield + team2.midfield) * 100;

    int gx1 = int(double(team1.attack - team2.defense)/2.0);
    int gx2 = int(double(team2.attack - team1.defense)/2.0);

    if(gx1 < 1) gx1 = 1;
    if(gx2 < 1) gx2 = 1;

    res.goals1 = 0;
    res.goals2 = 0;

    int dif = abs(res.goals1 - res.goals2);

    int acumulativo1 = 1, acumulativo2 = 1;
    vector<string> events;

    for(int i = 0; i <= 90 + acrecimo; i++) {
        system("cls");
        for(const string& event : events) {
            cout << event << endl;
        }
        if(i > 90) cout << center << "90 + " << i - 90 << "'";
        else cout << center << i << "'";
        Sleep(50);
        int chance = aleatorio(1, 100);

        if(chance <= chance1) {
            int ChanceDeGol = aleatorio(1, 100);
            if(ChanceDeGol <= gx1/acumulativo1) {
                res.goals1++;
                cout << center << " - " << team1.name << " scored a goal! Total goals: " << res.goals1;
                events.push_back(center + to_string(i) + "' - " + team1.name + " scored!");
                if(res.goals1 > 3 && dif > 2) acumulativo1 *= 2;
                if(res.goals2 > 3 && dif > 2) gx1 *= 2;
            }
        } else {
            int ChanceDeGol = aleatorio(1, 100);
            if(ChanceDeGol <= gx2/acumulativo2) {
                res.goals2++;       
                cout << center << " - " << team2.name << " scored a goal! Total goals: " << res.goals2;
                events.push_back(center + to_string(i) + "' - " + team2.name + " scored!");
                if(res.goals2 > 3 && dif > 2) acumulativo2 *= 2;
                if(res.goals1 > 3 && dif > 2) gx2 *= 2;
            }
        }
        dif = abs(res.goals1 - res.goals2);
        if(i == 85){
            gx1 *= 4;
            gx2 *= 4;
        }
    }
    cout << " - Match Finished!";

    return res;
}

int main(){
    system("cls");

}