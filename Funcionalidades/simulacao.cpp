#include <bits/stdc++.h>
#include <windows.h>
#include "database.h"
using namespace std;
mt19937 gen(time(nullptr));

string delay;

struct resultado{
    int goals1, goals2;
    int penalties1, penalties2;
    string team1Name, team2Name;
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
void showMatchInfo(resultado res, bool mata_mata) {
    if(!mata_mata || res.goals1 != res.goals2) {
        cout << "\n\n" << centerstr(70) << "Final Score: " << res.team1Name << " " << res.goals1 << " - " << res.goals2 << " " << res.team2Name << endl;
    }
    else{
        cout << "\n\n" << centerstr(70) << "Final Score: " << res.team1Name << " " << res.goals1 << " [" << res.penalties1 << "] - [" << res.penalties2 << "] " << res.goals2 << " " << res.team2Name << endl;
    }
}
resultado simularPartida(clube team1, clube team2, bool fatorcasa, bool mata_mata) {
    resultado res;
    int moment = aleatorio(65, 80);
    res.team1Name = team1.name;
    res.team2Name = team2.name;
    string center = centerstr(80);
    int acrecimo = aleatorio(1, 8);
    double chance1 = (double)(team1.midfield)/(team1.midfield + team2.midfield) * 100;

    double gx1 = int(double(team1.attack - team2.defense)/2.0);
    double gx2 = int(double(team2.attack - team1.defense)/2.0);

    if(fatorcasa){
        gx1 *= 1.5;
        gx2 /= 1.2;
    }

    if(gx1 < 1) gx1 = 1;
    if(gx2 < 1) gx2 = 1;

    res.goals1 = 0;
    res.goals2 = 0;

    int dif = abs(res.goals1 - res.goals2);

    int acumulativo1 = 1, acumulativo2 = 1;
    vector<string> events;
    events.push_back("\n" + center + "===MATCH START!===\n");

    for(int i = 0; i <= 90 + acrecimo; i++) {
        system("cls");
        for(const string& event : events) {
            cout << event << endl;
        }
        if(i > 90) cout << center << centerstr(8) << "90 + " << i - 90 << "'";
        else cout << center << centerstr(8) << i << "'";
        Sleep(1);
        int chance = aleatorio(1, 100);

        if(chance <= chance1) {
            int ChanceDeGol = aleatorio(1, 100);
            if(ChanceDeGol <= gx1/acumulativo1) {
                res.goals1++;
                cout << center << " - " << team1.name << " scored!";
                if(i<=90) events.push_back(center + to_string(i) + "' - " + team1.name + " scored!");
                else events.push_back(center + "90 + " + to_string(i-90) + "' - " + team1.name + " scored!");
                if(res.goals1 > 3 && dif > 2) acumulativo1 *= 2;
                if(res.goals2 > 3 && dif > 2) gx1 *= 2;
            }
        } else {
            int ChanceDeGol = aleatorio(1, 100);
            if(ChanceDeGol <= gx2/acumulativo2) {
                res.goals2++;       
                cout << center << " - " << team2.name << " scored!";
                if(i<=90) events.push_back(center + to_string(i) + "' - " + team2.name + " scored!");
                else events.push_back(center + "90 + " + to_string(i-90) + "' - " + team2.name + " scored!");
                if(res.goals2 > 3 && dif > 2) acumulativo2 *= 2;
                if(res.goals1 > 3 && dif > 2) gx2 *= 2;
            }
        }
        dif = abs(res.goals1 - res.goals2);
        if(i == 85){
            gx1 *= 4;
            gx2 *= 4;
        }
        if(i == 45){
            events.push_back("\n" + centerstr(70) + "45' - HT [" + team1.name + " " + to_string(res.goals1) + " - " + to_string(res.goals2) + " " + team2.name + "]\n");
        }

        if(i == 90 + acrecimo){
            events.push_back(center + "90 + " + to_string(acrecimo) + "' - FT");
             events.push_back("\n" + center + "===MATCH END!===");
        }
        if(i == moment && !(res.goals1 + res.goals2)){
            events.push_back(centerstr(70) + "- the match is getting intense but stil goalless");
            gx1 *= 2;
            gx2 *= 2;
        }
    }
    system("cls");
    for(const string& event : events) {
        cout << event << endl;
    }
    if(mata_mata && res.goals1 == res.goals2){
        cout << "\n\n" << centerstr(75) << "PENALTY SHOOTOUT!\n";
        events.push_back("\n" + center + "===PENALTY SHOOTOUT!===\n");
        res.penalties1 = 0;
        res.penalties2 = 0;
        int penaltyRound = 1;
        while(true){
            system("cls");
            for(const string& event : events) {
                cout << event << endl;
            }
            string a = center + centerstr(7);
            cout << a << "(" << res.penalties1 << " - " << res.penalties2 << ") - " << penaltyRound << "\n";
            a += " ";
            int chance1 = aleatorio(1, 100);
            int chance2 = aleatorio(1, 100);
            cout << center << "   Simulting...\n";
            Sleep(1000);
            if(chance1 <= 70){
                res.penalties1++;
                a += "O";
            }
            else{
                a += "X";
            }
            a += " - ";
            cout << a;
            Sleep(1000);
            if(chance2 <= 70){
                res.penalties2++;
                a += "O";
            }
            else{
                a += "X";
            }
            events.push_back(a);
            int dif = abs(res.penalties1 - res.penalties2);
            if(dif > 5 - penaltyRound && dif != 0){
                system("cls");
                for(const string& event : events) {
                    cout << event << endl;
                } 
                break;
            }
            penaltyRound++;
            if(penaltyRound == 6){
                events.push_back("\n" + center + "===Sudden Death!===\n");
            }
        }
    }

    return res;
}

int main(){
    system("cls");
    clube FLA = teams[2], RMA = teams[61];
    resultado res = simularPartida(FLA, RMA, true, true);
    showMatchInfo(res, true);
}