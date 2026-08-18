#include "Database.cpp"
#include "ASCII.cpp"

mt19937 gen(time(nullptr));

const vector<string> leagues = {"Brasileirao", "Bundesliga", "Eredivise", "LaLiga", "Liga MX", "Liga NOS", "League ONE", "LPF", "MLS", "Premier League", "Serie A", "Saudi Pro League", "Internacional FIFA"};



//configurações globais(terminar depois).
int screensize = 244;
int buttonsize = 30;
int Gamespeed = 100;




struct resultado{
    int gols1 = 0, gols2 = 0, golspenalti1 = 0, golspenalti2 = 0;
    clube t1 = {}, t2 = {}, vencedor = {};
    vector<string> melhores_momentos = {};
    string resume;
};

struct infotorneio{
    int qtd_equipes;
    vector<clube> equipes;
    vector<resultado> jogos;
};

struct pontos{
    clube equipe;
    int pts = 0;
    int GF = 0, GA = 0, SG = 0;
    int V = 0, D = 0, E = 0;
};

struct rodada{
    resultado jogos[10];
};

struct infoleagues{
    vector<rodada> r;
    vector<pontos> competidores;

};

vector<string> nivelar(vector<string> frame){
    int size;
    int maxsize = frame[0].size();
    for(string &line : frame){
        size = line.size();
        maxsize = max(size, maxsize);
    }

    for(string &line : frame){
        int x = line.size();
        //if(x == maxsize) continue;
        while(x < maxsize){
            line += " ";
            x = line.size();
        }
    }

    return frame;
}

void embaralhar(vector<clube>& a){
    for(int i = 0; i < 90; i++){
        shuffle(a.begin(), a.end(), gen);
    }
}

string centerstr(const string &a, const int &screensize){ //Tamanho da tela: screensize caracters
    int tamanho = a.size();
    string b = "";
    for(int i = 0; i < (screensize - tamanho)/2; i++){
        b += " ";
    }
    b += a;
    return b;
}

string barstr(const string &a, const int &screensize){ //Tamanho da tela: screensize caracters
    int tamanho = a.size();
    string b = "";
    for(int i = 0; i < (screensize - tamanho)/2; i++){
        b += "=";
    }
    b += a;
    int x = b.size();
    while(x < screensize){
        b += "=";
        x = b.size();
    }
    return b;
}

int aleatorio(const int &inicio, const int &fim){
    uniform_int_distribution<int> dist(inicio, fim);
    return dist(gen);
}

clube calcularevento(const clube &a, const clube &b){
    double razao = (double)a.meio_campo/(double)(a.meio_campo + b.meio_campo);
    razao *= 100;
    int chance = aleatorio(1, 100);
    if(chance <= razao) return a;
    else return b;
}

void rendelizar(const vector<string> &dados){
    for(const string &line : dados){
        cout << line << "\n";
    }
}

void rendelizarcentro(const vector<string> &dados, int size){
    for(const string &line : dados){
        cout << centerstr(line, size) << "\n";
    }
}

string addbar(string &a, int size){
    size -= 2;
    string ret = "|";
    int tamanho = a.size();
    if(tamanho % 2 == 1){ 
        ret += " ";
    }

    for(int i = 0; i < (size - tamanho)/2; i++){
        ret += " ";
    }

    ret += a;

    for(int i = 0; i < (size - tamanho)/2; i++){
        ret += " ";
    }

    ret += "|";

    return ret;
}


void structured_menu(vector<string> lista){
    int maior = 60;
    for(string x : lista){
        int aux = x.size();
        maior = max(maior, aux);
    }
    maior += 4;
    string bar = "";
    for(string& x : lista){
        bool kbum = false;
        if(x.size()%2) kbum = true;;
        string space = "";
        int dif = maior - x.size();
        dif /= 2;
        for(int i = 0; i < dif; i++) space += " ";
        x = space + x + space;
        if(kbum) x.pop_back();
    }
    nivelar(lista);
    maior = lista[0].size();
    for(int i = 0; i < maior; i++) bar += "-";
    vector<string> menu;
    menu.push_back(bar);
    for(const string& x : lista){
        menu.push_back("|" + x + "|");
        menu.push_back(bar);
    }
    rendelizarcentro(menu, screensize);
}



int gx(resultado res, int minute, int ordem){ //0 nao muda e 1 muda
    int g = (res.t1.ataque - res.t2.defesa)/2;
    int acumulativo = 1;
    if(ordem) g = res.t2.ataque - res.t1.defesa;
    int qtdgols = res.gols1 + res.gols2;
    int dif = abs(res.gols1 - res.gols2);

    if(minute > 80){
        g += 5;
    }
    if(g < 1) g = 1;

    if(dif > 2 && res.gols1 > res.gols2){
        while(dif > 2){
            dif--;
            acumulativo++;
        }
        g /= acumulativo;
    }
    if(qtdgols > 5) g /= 3;
    if(g > 6) g = 6;
    return g;
}


vector<string> placar(resultado &r, int mai){
    vector<string> plac;
    int maior = mai;
    if(true){
        int a = r.t1.nome.size();
        int b = r.t2.nome.size();
        maior = max(a, maior);
        maior = max(b, maior);
    }
    string a = r.t1.nome;
    if(a.size()%2) a += " ";
    a = addbar(a, maior + 4);
    string b = r.t2.nome;
    if(b.size()%2) b += " ";
    b = addbar(b, maior + 4);

    string bar = " ";
    int x = a.size();
    for(int i = 0; i < x - 2; i++){
        bar += "-";
    }
    bar += " ";
    a += " [" + to_string(r.gols1) + "]";
    b += " [" + to_string(r.gols2) + "]";
    plac.push_back(bar);
    plac.push_back(a);
    plac.push_back(bar);
    plac.push_back(b);
    plac.push_back(bar);

    plac = nivelar(plac);

    return plac;

}

string repeat(string a, int qtd){
    string d = "";
    for(int i = 0; i < qtd; i++){
        d += a;
    }
    return d;
}

string abreviar(string &a){
    string ret = "";
    if(a.size() > 3){
        for(int i = 0; i < 3; i++){
        ret += a[i];
        }
        ret += ".";
    }
    else{
        ret += a;
    }
    
    return ret;
}

clube simular_penaltis(resultado &res){
    res.melhores_momentos.push_back("");
    string frase = "=========[DECISAO POR PENALTIS]==========";
    res.melhores_momentos.push_back(centerstr(frase, screensize));
    int penaltyRound = 1;
    while(true){
        res.melhores_momentos.push_back(centerstr("Round "+ to_string(penaltyRound) + ": ", screensize - 6));
        rendelizar(res.melhores_momentos);
        Sleep(10*Gamespeed);
        system("cls");
        int x = res.melhores_momentos.size() - 1;
        auto gol = aleatorio(1,100);
        if(gol <= 75){
            res.golspenalti1++;
            res.melhores_momentos[x] += "| O ";
        }
        else{
            res.melhores_momentos[x] += "| X ";
        }

        res.melhores_momentos[x] += "|";
        rendelizar(res.melhores_momentos);
        Sleep(10*Gamespeed);
        system("cls");
        gol = aleatorio(1, 100);

        if(gol <= 75){
            res.golspenalti2++;
            res.melhores_momentos[x] += " O |";
        }
        else{
            res.melhores_momentos[x] += " X |";
        }

        rendelizar(res.melhores_momentos);
        Sleep(10*Gamespeed);
        system("cls");



        int dif = abs(res.golspenalti1 - res.golspenalti2);
            if(dif > 5 - penaltyRound && dif != 0){
                break;
            }
            penaltyRound++;
    }
    res.resume = res.t1.nome + " " + to_string(res.gols1) + " [" + to_string(res.golspenalti1) + "] x [" + to_string(res.golspenalti2) + "] " + to_string(res.gols2) + " " + res.t2.nome;
    res.melhores_momentos.push_back("");
    if(res.golspenalti1 > res.golspenalti2){
        return res.t1;
    }
    else{
        return res.t2;
    }

}


resultado simular_partida(const clube &time1, const clube &time2, bool fatorcasa, bool mata_mata){
    resultado placar_final;
    placar_final.t1 = time1;
    placar_final.t2 = time2;
    string match_started = "MATCH EVENTS";
    vector<string> eventos;
    string bar = repeat("-", 50);
    string frase_inicio = addbar(match_started, (int)32);
    string space = repeat(" ", screensize);
    eventos.push_back(space);
    eventos.push_back(centerstr(bar, screensize));
    bar = repeat("-", 30);
    eventos.push_back(centerstr(addbar(frase_inicio, 52), screensize));
    eventos.push_back(centerstr(addbar(bar, 52), screensize));
    bar = repeat("-", 50);
    string ax = "";
    eventos.push_back(centerstr(addbar(ax, 52), screensize));

    int acrecimos = aleatorio(0,8);

    for(int i = 0; i <= 90 + acrecimos; i++){
        system("cls");
        rendelizarcentro(placar(placar_final, buttonsize), screensize);
        rendelizar(eventos);
        string minuto = to_string(i) + "'";
        if(i > 90) minuto = "90' + " + to_string(i - 90);
        cout << centerstr(addbar(minuto, 52), screensize);
        Sleep(Gamespeed);
        clube favevent = calcularevento(time1, time2);

        if(favevent.id == time1.id){
            int GolsExperados = gx(placar_final, i, 0);
            if(fatorcasa) GolsExperados += 3;
            int converter = aleatorio(1, 100);
            if(converter <= GolsExperados){
                placar_final.gols1++;;
                string frase = minuto + " " + time1.nome + " Scored!";
                eventos.push_back(centerstr(addbar(frase, 52), screensize));
            }
        }
        else{
            int GolsExperados = gx(placar_final, i, 1);
            if(fatorcasa) GolsExperados -= 3;
            int converter = aleatorio(1, 100);
            if(converter <= GolsExperados){
                placar_final.gols2++;
                string frase = minuto + " " + time2.nome + " Scored!";
                eventos.push_back(centerstr(addbar(frase, 52), screensize));
            }
        }
        if(i == 90 + acrecimos){
            eventos.push_back(centerstr(addbar(ax, 52), screensize));
            eventos.push_back(centerstr(bar, screensize));
        }
        if(i == 45){
            string t1 = time1.nome, t2 = time2.nome;
            eventos.push_back(centerstr(addbar(ax, 52), screensize));
            ax = "[HALF TIME : " + abreviar(t1) + " " + to_string(placar_final.gols1) + " x " + to_string(placar_final.gols2) + " " + abreviar(t2) + "]";
            ax = barstr(ax, 50);
            eventos.push_back(centerstr(addbar(ax, 52), screensize));
            ax = "";
            eventos.push_back(centerstr(addbar(ax, 52), screensize));
        }
        placar_final.melhores_momentos = eventos;
    }
    system("cls");
    placar_final.resume = time1.nome + " " + to_string(placar_final.gols1) +" x " + to_string(placar_final.gols2) + " " + time2.nome;
    if(mata_mata && placar_final.gols1 == placar_final.gols2){
        placar_final.vencedor = simular_penaltis(placar_final);
    }
    rendelizarcentro(placar(placar_final, buttonsize), screensize);
    cout << "\n";
    rendelizar(placar_final.melhores_momentos);
    if(placar_final.gols1 > placar_final.gols2) placar_final.vencedor = placar_final.t1;
    else if(placar_final.gols1 < placar_final.gols2) placar_final.vencedor = placar_final.t2;
    else if(mata_mata){
        if(placar_final.golspenalti1 > placar_final.golspenalti2) placar_final.vencedor = placar_final.t1;
        else placar_final.vencedor = placar_final.t2;
    }
    cout << centerstr(placar_final.resume, screensize) << "\n";
    string lixo;
    cin >> lixo;
    

    system("cls");
    return placar_final;
}

int gerarmenu(vector<string> lista){
    int ret;
    bool correct = false;
    while(!correct){
        vector<string> menu;
        int maior = buttonsize + (buttonsize/2);
        if(maior%2) maior++;
        for(const string &x : lista){
            int num = x.size();
            maior = max(num, maior);
        }
        string bar = repeat("-", maior);
        string div = addbar(bar, maior + 2);
    
        menu.push_back(centerstr(bar, screensize));
        for(string x : lista){
            menu.push_back(centerstr(div, screensize));
            menu.push_back(centerstr(addbar(x, maior + 2), screensize));
        }
        menu.erase(menu.begin() + 1);
        menu.push_back(centerstr(bar, screensize));
        nivelar(menu);
    
        int cont = 1;
        int percorrer = menu.size();
        for(int i = 0; i < percorrer; i++){
            if(i%2){
                menu[i] += " [" + to_string(cont) + "]";
                cont++;
            }
        }

        nivelar(menu);

        rendelizar(menu);
        cout << centerstr("[  Decisao  ]: ", screensize);
        cin >> ret;
        system("cls");
        if(ret >= 1 && ret < cont) correct = !correct;
        else{ cout << "INVALID DECISION! TRY AGAIN!\n\n"; }
    }
    return ret;
}

int selecionartime(){
    int idret;
    int num = gerarmenu(leagues);
    num--;
    num = num*20;
    vector<string> equipes;
    for(int i = 1 + num; i <= 20 + num; i++){
        equipes.push_back(teams[i].nome);
    }
    system("cls");
    int nx = gerarmenu(equipes);
    system("cls");
    idret = num + nx;

    return idret;
}

vector<string> title(vector<string>& ASCII){
    vector<string> titulo;
    string bar = "";
    for(int i = 0; i < screensize; i++){
        bar += "=";
    }
    titulo.push_back(bar);
    for(string& x : ASCII){
        titulo.push_back(x);
    }
    titulo.push_back(bar);
    titulo.push_back("");
    titulo.push_back("");
    titulo.push_back("");
    titulo.push_back("");
    titulo.push_back("");
    return titulo;
    
}

void init_tournament(infotorneio& info){
    rendelizarcentro(title(tournament_logo), screensize);
    vector<string> options = {"4 times", "8 times", "16 times", "32 times"};
    vector<string> decision = {"Choose Teams", "Random Teams", "National Cup"};
    cout << "\n\n\n";
    info.qtd_equipes = gerarmenu(options);
    system("cls");
    info.qtd_equipes = (int)(pow(2, (info.qtd_equipes+1)));

    vector<clube> tournament_teams(info.qtd_equipes, {"", 0, 0, 0, -1}); //Inicializa todos os times com status zerados e com id -1 (o 0 é o World class!), é só para nao dar B.O.
    info.equipes = tournament_teams;

    vector<resultado> jg(500);
    info.jogos = jg;
    rendelizarcentro(title(tournament_logo), screensize);
    int decisao = gerarmenu(decision);

    if(decisao == 1){
        for(clube& eqp : info.equipes){
            int ID = selecionartime();
            eqp = teams[ID];
        }
    }
    else if(decisao == 2){
        for(clube& eqp : info.equipes){
            int ID = aleatorio(1,240);
            while(teams[ID].id != ID) ID = aleatorio(1,240);
            eqp = teams[ID];
        }
    }
    else{
        int liga = gerarmenu(leagues);
        liga--;
        int inicio = ((liga*20) + 1), fim = inicio + 19;
        vector<clube> aux;
        for(int i = inicio; i <= fim; i++){
            aux.push_back(teams[i]);
        }
        vector<bool> mark(19, false);
        for(clube& eqp : info.equipes){
            int ID = aleatorio(0, 19);
            while(teams[ID].id != ID) ID = aleatorio(0,19);
            if(info.qtd_equipes <= 16){
                while(mark[ID]){
                    int ax = ID;
                    ID = aleatorio(0, 19);
                    if(teams[ID].id != ID) ID = ax;
                }
                mark[ID] = 1;
            }
            eqp = aux[ID];
        }

    }
    embaralhar(info.equipes);
     for(int k = 0; k < info.qtd_equipes; k += 2){
        //info.jogos[k/2].t1 = info.equipes[k];
        info.jogos[k/2] = {0,0,0,0,info.equipes[k],info.equipes[k+1]}; 
    }
    

}

vector<string> gerarchaveamento(infotorneio& torn){
    vector<string> chaveamento;
    vector<int> future_conections;
    bool conect = true;
    int j = 0;

    string bar1 = "";
    for(int i = 0; i < buttonsize; i++) bar1 += "-";
    string bar = "";
    for(int i = 0; i < buttonsize/2; i++) bar += " ";

    for(int i = 0; i < torn.qtd_equipes; i += 2){
        resultado res = torn.jogos[j];
        vector<string> add = placar(res, buttonsize);
        
        for(string& a : add){
            chaveamento.push_back(a);
        }
        if(conect){ 
            chaveamento.push_back(bar + "|" + bar1);
            conect = false;
        }
        else if(i != torn.qtd_equipes-2){
            conect = true;
            future_conections.push_back(chaveamento.size());
            chaveamento.push_back("");
        }
        j++;
    }
    conect = false;
    chaveamento = nivelar(chaveamento);
    
    //Daqui para cima nao mecher! Ta tudo correto (Acabei de Mecher, ferrou td pqp)

    // Use o /* para poder usar, essa parte ta incompleta.
     ///*
    int gamecont = j;
    int fin;
    while(!future_conections.empty()){
        int x = future_conections.size();
        vector<int> atual_conections;
        if(x == 1){
            atual_conections.push_back(future_conections[0]);
            fin = future_conections[0];
            future_conections.pop_back();
        }
        else{
            for(int i = 0; i < future_conections.size(); i++){
                atual_conections.push_back(future_conections[i]);
                future_conections.erase(future_conections.begin() + i);
            }
        }
        //Temos EXATAMENTE os pontos de onde botar os braquetes nesse nivelamento kk;

        x = chaveamento.size();

        for(int i = 0; i < x; i++){
            if(chaveamento[i][chaveamento[i].size()-1] == '-'){
                resultado res = torn.jogos[gamecont]; 
                i -= 2;
                vector<string> add = placar(res, buttonsize);
                for(string& a : add){
                    chaveamento[i] += a;
                    i++;
                }
                gamecont++;
                conect = !conect;
            }
            if(conect && chaveamento[i+1][chaveamento[i].size()-1] != '-' && chaveamento[i+2][chaveamento[i].size()-1] != '-') chaveamento[i] += (bar + "|");
        }

        for(int& line : atual_conections){
            chaveamento[line] += bar1;
        }
        chaveamento = nivelar(chaveamento);
    }
     //*/

     resultado res = torn.jogos[gamecont]; 
    fin -= 2;
    vector<string> add = placar(res, buttonsize);
    for(string& a : add){
        chaveamento[fin] += a;
        fin++;
    }
    chaveamento = nivelar(chaveamento);


    return chaveamento;
}

void simularcopa(infotorneio &info){
    init_tournament(info);
    int matchcont = info.qtd_equipes/2;
    int roundgames = matchcont;
    int gamecont = 0;
    while(roundgames != 1){
        vector<string> chaveamento = gerarchaveamento(info);
        rendelizarcentro(title(tournament_logo), screensize);
        rendelizar(chaveamento);
        string lixo;
        cin >> lixo;
        system("cls");
        for(int i = 0; i < roundgames; i += 2){
            info.jogos[i + gamecont] = simular_partida(info.jogos[i + gamecont].t1, info.jogos[i + gamecont].t2, false, true);
            info.jogos[i+1 + gamecont] = simular_partida(info.jogos[i+1 + gamecont].t1, info.jogos[i+1 + gamecont].t2, false, true);
            info.jogos[matchcont + (i/2)].t1 = info.jogos[i + gamecont].vencedor;
            info.jogos[matchcont + (i/2)].t2 = info.jogos[i+1 + gamecont].vencedor;
        }
        roundgames /= 2;
        gamecont = matchcont;
        matchcont += roundgames;

        system("cls");
    };
    vector<string> chaveamento = gerarchaveamento(info);
    rendelizarcentro(title(tournament_logo), screensize);
    rendelizar(chaveamento);
    string lixo;
    cin >> lixo;
    info.jogos[gamecont] = simular_partida(info.jogos[gamecont].t1, info.jogos[gamecont].t2, false, true);
    clube winner = info.jogos[gamecont].vencedor; 
    chaveamento = gerarchaveamento(info);
    rendelizarcentro(title(tournament_logo), screensize);
    rendelizar(chaveamento);
    cin >> lixo;
    system("cls");
    rendelizarcentro(title(winner_logo), screensize);

    bool repeat[2] = {false,false};
    for(clube c : info.equipes){
        if(c.id == winner.id && repeat[0]){
            repeat[1] = true;
            break;
        }
        else if(c.id == winner.id){
            repeat[0] = true;
        }
    }

    if(!repeat[1]){
        vector<string> result_vencedor;
        vector<string> fases = {"Final", "Semi Final", "Quarter Final", "Round of 16", "Round of 32"};

        for(int i = 0; i <= gamecont; i++){
            if(info.jogos[i].t1.id == winner.id || info.jogos[i].t2.id == winner.id){
                result_vencedor.push_back(info.jogos[i].resume);
            }
        }
        reverse(result_vencedor.begin(), result_vencedor.end());
        for(int i = 0; i < result_vencedor.size(); i++){
            result_vencedor[i] += " - " + fases[i];
        }

        cout << centerstr("Caminho do(a) " + winner.nome + ":", screensize) << "\n\n\n";

        structured_menu(result_vencedor);
    };
    cin >> lixo;



}

void init_league(infoleagues& info){
    vector<string> decision = {"Choose Teams", "Random Teams", "National Cup"};
    info.r = vector<rodada>(38);
    info.competidores = vector<pontos>(20);

    int decisao = gerarmenu(decision);

        if(decisao == 1){
            for(pontos& eqp : info.competidores){
                int ID = selecionartime();
                eqp.equipe = teams[ID];
            }
        }
        else if(decisao == 2){
            for(pontos& eqp : info.competidores){
                int ID = aleatorio(1,240);
                while(teams[ID].id != ID) ID = aleatorio(1,240);
                eqp.equipe = teams[ID];
            }
        }
        else{
            int liga = gerarmenu(leagues);
            liga--;
            int inicio = ((liga*20) + 1), fim = inicio + 19;
            vector<clube> aux;
            for(int i = inicio; i <= fim; i++){
                aux.push_back(teams[i]);
            }
            vector<bool> mark(19, false);

            int ID = 0;
            for(pontos& eqp : info.competidores){
                eqp.equipe = aux[ID];
                ID++;
            }

        }
}


int main(){
    //A main vai servir como fluxo de menus!
    ///*
    const vector<string> menu_inicial = {"Jogo Rapido", "Torneio", "Configuracoes", "Sair"};
    int fluxo_menu = 1;
    //gamestart:
    do{
        system("cls");
        cout << "\n\n";
        rendelizarcentro(title(game_logo), screensize);
        fluxo_menu = gerarmenu(menu_inicial);
        if(fluxo_menu == 1){
            const vector<string> menu_quickmatch = {"Partida Normal", "Mata-Mata", "Fator Casa","F.Casa + Mata-Mata","Voltar"};
            rendelizarcentro(title(QuickMatch_logo), screensize);
            fluxo_menu = gerarmenu(menu_quickmatch);
            bool Mt_Mt = false;
            bool F_C = false;
            if(fluxo_menu == 2){
                Mt_Mt = true;
            }
            else if(fluxo_menu == 3){
                F_C = true;
            }
            else if(fluxo_menu == 4){
                F_C = true;
                Mt_Mt = true;
            }
            else if(fluxo_menu == 5){
                continue;
            }

            system("cls");
            rendelizarcentro(title(QuickMatch_logo), screensize);
            clube team1 = teams[selecionartime()];
            system("cls");
            rendelizarcentro(title(QuickMatch_logo), screensize);
            clube team2 = teams[selecionartime()];
            system("cls");
            simular_partida(team1, team2, F_C, Mt_Mt);
            rendelizarcentro(title(QuickMatch_logo), screensize);
        }
        else if(fluxo_menu == 2){
            infotorneio info;
            simularcopa(info);
            // fazer amanha.
        }
        else if(fluxo_menu == 3){
            // fazer amanha.
            rendelizarcentro(title(settings_logo), screensize);
            const vector<string> settings_menu = {"Buttons Resize", "Match Speed", "ScreenSize", "More Info", "Voltar"};
            fluxo_menu = gerarmenu(settings_menu);
            if(fluxo_menu == 1){
                rendelizarcentro(title(settings_logo), screensize);
                const vector<string> match_buttons = {"Big", "Normal", "Small", "Voltar"};
                fluxo_menu = gerarmenu(match_buttons);
                if(fluxo_menu == 4) continue;
                else if(fluxo_menu == 3) buttonsize = 25;
                else if(fluxo_menu == 2) buttonsize = 30;
                else if(fluxo_menu == 1) buttonsize = 50;
            }
            else if(fluxo_menu == 2){
                rendelizarcentro(title(settings_logo), screensize);
                const vector<string> match_speeds = {"Super Slow", "Slow", "Normal", "Fast", "Super Fast", "Instant", "Voltar"};
                fluxo_menu = gerarmenu(match_speeds);
                if(fluxo_menu == 7) continue;
                else if(fluxo_menu == 6) Gamespeed = 0;
                else if(fluxo_menu == 5) Gamespeed = 20;
                else if(fluxo_menu == 4) Gamespeed = 50;
                else if(fluxo_menu == 3) Gamespeed = 100;
                else if(fluxo_menu == 2) Gamespeed = 200;
                else if(fluxo_menu == 1) Gamespeed = 400;
            }
            else if(fluxo_menu == 3){
                rendelizarcentro(title(settings_logo), screensize);
                const vector<string> match_screen = {"Big", "Normal", "Small", "Window", "Voltar"};
                fluxo_menu = gerarmenu(match_screen);
                if(fluxo_menu == 5) continue;
                if(fluxo_menu == 4) screensize = 261;
                if(fluxo_menu == 3) screensize = 185;
                if(fluxo_menu == 2) screensize = 244;
                if(fluxo_menu == 1) screensize = 291;
            }
            else if(fluxo_menu == 4){
                
            }
            else{
                continue;
            }

        }
        else{
            system("cls");
            cout << "You leaved here with sucess! Thanks For playing!.";
            fluxo_menu = -1;
        }
    }while(fluxo_menu != -1);
    //*/
}
