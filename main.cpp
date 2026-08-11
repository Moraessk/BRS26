//Feito TOTALMENTE SEM IA!!
#include "Database.cpp"

mt19937 gen(time(nullptr));

const vector<string> leagues = {"Brasileirao", "Bundesliga", "Eredivise", "LaLiga", "Liga MX", "Liga NOS", "League ONE", "LPF", "MLS", "Premier League", "Serie A", "Saudi Pro League", "Internacional FIFA", "Voltar"};
const vector<string> menu_inicial = {"Jogo Rapido", "Torneio", "Configuracoes", "Sair"};



//configurações globais(terminar depois).
int screensize = 261;
int buttonsize = 30;




struct resultado{
    int gols1 = 0, gols2 = 0, golspenalti1 = 0, golspenalti2 = 0;
    clube t1 = {}, t2 = {}, vencedor = {};
    vector<string> melhores_momentos = {};
};

struct infotorneio{
    int qtd_equipes;
    vector<clube> equipes;
    vector<clube> vencedor;
    vector<resultado> jogos;
};

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

vector<string> nivelar(vector<string> frame){
    int size;
    int maxsize = frame[0].size();
    for(string &line : frame){
        size = line.size();
        maxsize = max(size, maxsize);
    }

    for(string &line : frame){
        int x = line.size();
        while(x < maxsize){
            line += " ";
            x = line.size();
        }
    }

    return frame;
}

int gx(resultado res, int minute, int ordem){ //0 nao muda e 1 muda
    int g = res.t1.ataque - res.t2.defesa;
    int acumulativo = 1;
    if(ordem) g = res.t2.ataque - res.t1.defesa;

    if(minute > 85){
        g += 10;
    }
    if(g < 1) g = 1;

    int dif = abs(res.gols1 - res.gols2);
    if(dif > 2 && res.gols1 > res.gols2){
        while(dif > 2){
            dif--;
            acumulativo++;
        }
        g /= acumulativo;
    }
    if(g > 12) g = 12;
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
        Sleep(300);
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
        Sleep(300);
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
        Sleep(300);
        system("cls");



        int dif = abs(res.golspenalti1 - res.golspenalti2);
            if(dif > 5 - penaltyRound && dif != 0){
                break;
            }
            penaltyRound++;
    }
    string score = res.t1.nome + " " + to_string(res.gols1) + " [" + to_string(res.golspenalti1) + "] x [" + to_string(res.golspenalti2) + "] " + to_string(res.gols2) + " " + res.t2.nome;
    res.melhores_momentos.push_back("");
    res.melhores_momentos.push_back(centerstr(score, screensize));
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
        rendelizarcentro(placar(placar_final, 20), screensize);
        rendelizar(eventos);
        string minuto = to_string(i) + "'";
        if(i > 90) minuto = "90' + " + to_string(i - 90);
        cout << centerstr(addbar(minuto, 52), screensize);
        Sleep(100);
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
    if(mata_mata && placar_final.gols1 == placar_final.gols2){
        placar_final.vencedor = simular_penaltis(placar_final);
    }
    rendelizarcentro(placar(placar_final, 20), screensize);
    cout << "\n";
    rendelizar(placar_final.melhores_momentos);
    string lixo;
    cin >> lixo;
    

    system("cls");
    return placar_final;
}

int gerarmenu(vector<string> lista){
    vector<string> menu;
    int ret;
    int maior = 50;
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
    cout << centerstr("[  Decisao  ]:", screensize);
    cin >> ret;
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

void init_tournament(infotorneio& info){
    vector<string> options = {"4 times", "8 times", "16 times", "32 times", "64 times"};
    cout << "\n\n\n";
    info.qtd_equipes = gerarmenu(options);
    system("cls");
    info.qtd_equipes = (int)(pow(2, (info.qtd_equipes+1)));

    vector<clube> tournament_teams(info.qtd_equipes, {"", 0, 0, 0, -1}); //Inicializa todos os times com status zerados e com id -1 (o 0 é o World class!), é só para nao dar B.O.
    info.equipes = tournament_teams;

    vector<resultado> jg(info.qtd_equipes - 1);
    info.jogos = jg;

    vector<clube> winners((info.qtd_equipes/2) - 1, {"", 0, 0, 0, -1});
    for(clube& eqp : info.equipes){
        int ID = selecionartime();
        eqp = teams[ID];
    }
    embaralhar(info.equipes);
     for(int k = 0; k < info.qtd_equipes; k += 2){
        info.jogos[k/2].t1 = info.equipes[k];
        info.jogos[k/2].t2 = info.equipes[k+1];
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
            future_conections.push_back(chaveamento.size() - 1);
            chaveamento.push_back("");
        }
        j++;
    }
    conect = false;
    nivelar(chaveamento);
    
    //Daqui para cima nao mecher! Ta tudo correto (Acabei de Mecher, ferrou td pqp)

    // Use o /* para poder usar, essa parte ta incompleta.
    int gamecont = torn.qtd_equipes/2 - 1;
    while(!future_conections.empty()){
        int x = future_conections.size();
        vector<int> atual_conections;
        for(int i = 0; i < future_conections.size(); i++){
            atual_conections.push_back(future_conections[i]);
            future_conections.erase(future_conections.begin() + i);
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
                conect = !conect;
            }
            else{
                if(conect) chaveamento[i] += (bar + "|");
                else chaveamento[i] += (bar);
            }
        }

        for(int& line : atual_conections){
            chaveamento[line] += bar1;
        }
        nivelar(chaveamento);
    }

    return chaveamento;
}

int main(){
     infotorneio torn;
    init_tournament(torn);
    vector<string> chaveamento = gerarchaveamento(torn);
    cout << "\n";
    rendelizar(chaveamento);
}
