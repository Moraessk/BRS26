//Feito TOTALMENTE SEM IA!!
#include "Database.cpp"

mt19937 gen(time(nullptr));

const vector<string> leagues = {"Brasileirao", "Bundesliga", "Eredivise", "LaLiga", "Liga MX", "Liga NOS", "League ONE", "LPF", "MLS", "Premier League", "Serie A", "Saudi Pro League", "Internacional FIFA", "Voltar"};
const vector<string> menu_inicial = {"Jogo Rapido", "Torneio", "Configuracoes", "Sair"};



//configurações globais(terminar depois).
int screensize = 261;




struct resultado{
    int gols1 = 0, gols2 = 0, golspenalti1 = 0, golspenalti2 = 0;
    clube t1, t2, vencedor;
    vector<string> melhores_momentos;
};

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
    idret = num + nx;

    return idret;
}

int main(){
    /*int fluxo_de_menu = gerarmenu(menu_inicial);
    system("cls");
    if(fluxo_de_menu == 1){

    }
    */
   cout << selecionartime();

}
