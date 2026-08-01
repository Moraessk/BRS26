#include <bits/stdc++.h>
#include <windows.h>
#include "Database.cpp"
using namespace std;
mt19937 gen(time(nullptr));

const vector<string> leagues = {"", "Brasileirao", "Bundesliga", "Eredivisie", "La Liga", "Liga MX", "Liga NOS", "League One", "LPF", "MLS", "Premier League", "Serie A", "Saudi Pro League"};
string Stopatscreen;
struct resultado{
    int goals1, goals2;
    int penalties1, penalties2;
    int team1id, team2id;
    bool jogou = false; // Adicionei o campo jogou para indicar se a partida já foi jogada
};
struct infotorneio{
    int numberOfTeams; 
    vector<clube> teams, vencedores;

    vector<vector<resultado>> jogos; // Adicionei o campo bracket para armazenar os resultados do torneio

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
        cout << "\n\n" << centerstr(70) << "Final Score: " << teams[res.team1id].name << " " << res.goals1 << " - " << res.goals2 << " " << teams[res.team2id].name << endl;
    }
    else{
        cout << "\n\n" << centerstr(70) << "Final Score: " << teams[res.team1id].name << " " << res.goals1 << " [" << res.penalties1 << "] - [" << res.penalties2 << "] " << res.goals2 << " " << teams[res.team2id].name << endl;
    }
}
void embaralhar(vector<clube> &x){
    for(int i = 0; i < 90; i++){
        shuffle(x.begin(), x.end(), gen);
    }
}

void showASCII(int i){
    cout << centerstr(i) << "    [][][] [][][] [][][] [] [][][] [][][] []       [][][] []  [] [][][] [][][] \n";
    cout << centerstr(i) << "   []     []  [] []  [] [] []     []  [] []           [] [] []      [] []      \n";
    cout << centerstr(i) << "  []     [][][] [][][] [] [] [[] []  [] []       [][][] [][]   [][][] [][][]   \n";
    cout << centerstr(i) << " []     []  [] []     [] []  [] []  [] []       []     [] []  []     []  []    \n";
    cout << centerstr(i) << "[][][] []  [] []     [] [][][] [][][] [][][]   [][][] []  [] [][][] [][][]     \n";
    cout << centerstr(i-5) << "======================================================================================== \n";

}

resultado simularPartida(clube team1, clube team2, bool fatorcasa, bool mata_mata) {
    resultado res;
    res.jogou = true; // Vou deixar marcado para nao dar cao la no torneio
    int moment = aleatorio(65, 80);
    res.team1id = team1.id;
    res.team2id = team2.id;
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
    string centerstr73 = centerstr(73), centerstr8 = centerstr(8);

    for(int i = 0; i <= 90 + acrecimo; i++) {
        system("cls");
        cout << centerstr73 << "[" << team1.name << " " << res.goals1 << " x " << res.goals2 << " " << team2.name << "]";
        for(const string& event : events) {
            cout << event << endl;
        }
        if(i > 90) cout << center << centerstr8 << "90 + " << i - 90 << "'";
        else cout << center << centerstr8 << i << "'";
        Sleep(100);
        int chance = aleatorio(1, 100);

        if(chance <= chance1) {
            int ChanceDeGol = aleatorio(1, 100);
            if(ChanceDeGol <= gx1/acumulativo1) {
                res.goals1++;
                cout << center << " - " << team1.name << " scored!";
                if(i<=90) {events.push_back(center + to_string(i) + "' - " + team1.name + " scored!");}
                else if(dif > 1){events.push_back(center + "90 + " + to_string(i-90) + "' - " + team1.name + " scored!");}
                else {events.push_back(center + "90 + " + to_string(i-90) + "' - " + team1.name + " scored! Unbeliveable!");}
                if(res.goals1 > 3 && dif > 2) acumulativo1 *= 2;
                if(res.goals2 > 3 && dif > 2) gx1 *= 2;
            }
        } else {
            int ChanceDeGol = aleatorio(1, 100);
            if(ChanceDeGol <= gx2/acumulativo2) {
                res.goals2++;       
                cout << center << " - " << team2.name << " scored!";
                if(i<=90) {events.push_back(center + to_string(i) + "' - " + team2.name + " scored!");}
                else if(dif > 1){events.push_back(center + "90 + " + to_string(i-90) + "' - " + team2.name + " scored!");}
                else {events.push_back(center + "90 + " + to_string(i-90) + "' - " + team2.name + " scored! Unbeliveable!");}
                if(res.goals2 > 3 && dif > 2) acumulativo2 *= 2;
                if(res.goals1 > 3 && dif > 2) gx2 *= 2;
            }
        }
        dif = abs(res.goals1 - res.goals2);
        if(i == 85){
            gx1 *= 3;
            gx2 *= 3;
        }
        if(i == 45){
            events.push_back("\n" + centerstr(70) + "45' - HT [" + team1.name + " " + to_string(res.goals1) + " - " + to_string(res.goals2) + " " + team2.name + "]\n");
        }

        if(i == 90 + acrecimo){
            events.push_back(centerstr(70) + "90 + " + to_string(acrecimo) + "' - FT");
             events.push_back("\n" + center + "===MATCH END!===");
        }
        if(i == moment && !(res.goals1 + res.goals2)){
            events.push_back(centerstr(70) + "===the match is getting intense but stil goalless===");
            gx1 *= 2;
            gx2 *= 2;
        }
    }
    system("cls");
    showASCII(55);
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
            showASCII(55);
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
                showASCII(55);
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

int selecionarliga(){
    string center = centerstr(80);
    int maior = 0;

    for(const string &x : leagues){
        int y = x.size();
        maior = max(maior, y);
    }
    int j = 0;
    showASCII(66);
    cout << center << " ";
    for(int i = 0; i < maior + 22; i++) cout << "-";
    cout << "\n";
    for(const string &x : leagues){
        if(x != ""){
            string a = "          ";
            int dif = maior - x.size();
            for(int i = 0; i < dif/2; i++) a += " ";
            if(x.size() % 2) a += " ";
            a += x;
            a += "          ";
            for(int i = 0; i < dif/2; i++) a += " ";
            cout << center << "|[" << a << "]| (" << j << ")\n";
            cout << center << " ";
            for(int i = 0; i < maior + 22; i++) cout << "-";
            cout << "\n";
        }
        j++;
    }
    int ret; cout << center << "Liga Selecionada: "; cin >> ret;
    system("cls");
    return ret;
}

int selecionartime(int id){
    system("cls");
    string center = centerstr(80), ctr = centerstr(75);
    int ret;
    int aux = 1 + (20*(id-1));
    int maior = 0;
    for(int j = aux; j < aux + 20; j++){
        if(!(teams[j].defense)) continue;
        string a; int x;
        a = "|[" + teams[j].name + " | ATA: " + to_string(teams[j].attack) + " - DEF: " + to_string(teams[j].defense) + " - MID: " + to_string(teams[j].midfield) + "]   ";
        
        x = a.size();
        maior = max(x, maior);
    }
    int ax = (maior/2) - 8;
    showASCII(69);
    cout << center << centerstr(ax)<< "LEAGUE SELECTOR\n\n";
    ax = (maior/2) - 4 - ((leagues[id].size())/2);
    cout << center << centerstr(ax) << "===[" << leagues[id] << "]===\n";
    cout << center;
    for(int i = 0; i <= maior; i++) cout << "-";
    cout << "\n";
    for(int j = aux; j < aux + 20; j++){
        if(!(teams[j].defense)) continue;
        string a;
        a = "|[" + teams[j].name + " | ATA: " + to_string(teams[j].attack) + " - DEF: " + to_string(teams[j].defense) + " - MID: " + to_string(teams[j].midfield) + "]   ";
        int x = a.size();
        while(x <= maior) {
            a += " ";
            x = a.size();
        }
        cout << center << a << "| ("<< (j-aux+1) <<")\n";
        cout << center;
        for(int i = 0; i <= maior; i++) cout << "-";
        cout << "\n";
    }
    cout << center << "Team selected: "; cin >> ret;
    ret += aux - 1;
    system("cls");
    return ret;
}

int calcularRodadas(int x){
    for(int i = 0; x > 1; i++){
        x /= 2;
        if(x == 1) return i;
    }
    return 0;
}
void inicializarTorneio(infotorneio &info, int numberOfTeams) {
    info.numberOfTeams = numberOfTeams;
    info.teams.clear();
    for(int i = 0; i < numberOfTeams; i++) {
        int teamIndex = selecionartime(selecionarliga());
        info.teams.push_back(teams[teamIndex]);
    }
    embaralhar(info.teams);
    
    vector<vector<resultado>> aux(calcularRodadas(numberOfTeams) + 1);
    int ax = aux.size();
    for(int i = 0; i < ax; i++) {
        int numMatches = numberOfTeams / (1 << (i + 1));
        aux[i].resize(numMatches);
    }
    info.jogos = aux;

    int N = info.numberOfTeams;
    N = round(log2(N));
    int quantidadevencedores = pow(2, N) - 1;
    vector<clube> vencedores(quantidadevencedores, {"", 0, 0, 0, -1});
    info.vencedores = vencedores;
}

vector<string> gerarpartida(const clube &team1, const clube &team2, int maior) { //gera o quadradinho dos dois times no chaveamento(braccet) do mata-mata.
    vector<string> ret;
    string center = centerstr(80);
    
    string a, b;
    
    int x = team1.name.size();
    int som =(maior - x)/2;
    a += "  ";
    for(int j = 1; j <= som; j++) a += " ";
    a += team1.name;
    if(x%2) a += " ";
    for(int j = 1; j <= som; j++) a += " ";
    a += "  ";
    int tamanho = a.size();
    for(int j = 1; j <= tamanho; j++) b += "-";
    ret.push_back(" " + b + " ");
    ret.push_back("|" + a + "|");
    ret.push_back("|" + b + "|");
    a.clear();
    x = team2.name.size();
    som =(maior - x)/2;
    if(x%2) a += " ";
    a += "  ";
    for(int j = 1; j <= som; j++) a += " ";
    a += team2.name;
    for(int j = 1; j <= som; j++) a += " ";
    a += "  ";
    ret.push_back("|" + a + "|");
    tamanho = a.size();
    ret.push_back(" " + b + " ");

    return ret;
}

vector<string> gerarbracket(infotorneio info){
    system("cls");
    vector<string> ret;
    int maior = 0;
    for(const clube &eqp : info.teams){ //descobre o time com o maior nome para poder centralizar os nomes dos times no bracket
        int x = eqp.name.size();
        maior = max(x, maior);
    }
    int mid = (maior + 6)/2;
    if(maior % 2) maior++; // Evita bug de centralização quando o maior nome tem tamanho ímpar
    bool conecta = true;
    int maiorlinha = 0;
    for(int i = 0; i < info.numberOfTeams; i += 2){
        vector<string> partida = gerarpartida(info.teams[i], info.teams[i+1], maior);
        for(const string &linha : partida){
            ret.push_back(linha);
        }
        if(conecta){
            string a;
            a = centerstr(mid) + "  |";
            ret.push_back(a);
            string b = a;
            while(b.size() < maior + 13){
                b += "-";
            }
            ret.push_back(b);
            ret.push_back(a);
            conecta = false;
        }
        else if(i + 2 < info.numberOfTeams){
            conecta = true;
            ret.push_back("");
            ret.push_back("");
            ret.push_back("");
        }
    }
    for(const string &linha : ret){
        maiorlinha = max(maiorlinha, (int)linha.size());
    }
    for(string &linha : ret){
        while(linha.size() < maiorlinha){
            linha += " ";
        }
    }
    queue<int> linhadonovobracket;
    for(int i = 0; i < ret.size(); i++){
        if(ret[i][ret[i].size() - 1] == '-'){
            linhadonovobracket.push(i);
        }
    }
    int winners = 0;
    while(!linhadonovobracket.empty()){
        for(int i = 0; i < ret.size(); i++){
            if(i == linhadonovobracket.front()){
                i -= 2;
                vector<string> match = gerarpartida(info.vencedores[winners], info.vencedores[winners + 1], maior);
                winners += 2;
                for(const string &linha : match){
                    ret[i] += linha;
                    i++;
                }
                linhadonovobracket.pop();
            }
        }
    }


    return ret;
}


int main(){
    system("cls");
    infotorneio info;
    int numberOfTeams = 8;
    inicializarTorneio(info, numberOfTeams);
    vector<string> bracket = gerarbracket(info);
    
    for(const string& line : bracket) {
        cout << line << "\n";
    }
}