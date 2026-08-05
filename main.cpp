#include "Database.cpp"

mt19937 gen(time(nullptr));



struct resultado{
    int gols1 = 0, gols2 = 0, golspenalti1 = 0, golspenalti2 = 0;
    clube t1, t2;
    vector<string> melhores_momentos;
};

string centerstr(const string &a, const int &screensize){ //Tamanho da tela: 261 caracters
    int tamanho = a.size();
    string b = "";
    for(int i = 0; i < (screensize - tamanho)/2; i++){
        b += " ";
    }
    b += a;
    return b;
}

string barstr(const string &a, const int &screensize){ //Tamanho da tela: 261 caracters
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

int gx(const clube time1, const clube time2, int minute){
    int g = time1.ataque - time2.defesa;

    if(minute > 85){
        g += 4;
    }
    if(g < 1) g = 1;
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

clube simular_penaltis(resultado res, const clube &time1, const clube &time2){
    string frase = "=========[DECISAO POR PENALTIS]==========";
    res.melhores_momentos.push_back(centerstr(frase, 261));
    int penaltyRound = 1;
    while(true){

        int dif = abs(res.golspenalti1 - res.golspenalti2);
            if(dif > 5 - penaltyRound && dif != 0){
                break;
            }
            penaltyRound++;
    }

}
/*
TERMINAR
*/

resultado simular_partida(const clube &time1, const clube &time2, bool fatorcasa, bool mata_mata){
    resultado placar_final;
    placar_final.t1 = time1;
    placar_final.t2 = time2;
    string match_started = "MATCH EVENTS";
    vector<string> eventos;
    string bar = repeat("-", 50);
    string frase_inicio = addbar(match_started, (int)32);
    string space = repeat(" ", 261);
    eventos.push_back(space);
    eventos.push_back(centerstr(bar, 261));
    bar = repeat("-", 30);
    eventos.push_back(centerstr(addbar(frase_inicio, 52), 261));
    eventos.push_back(centerstr(addbar(bar, 52), 261));
    bar = repeat("-", 50);
    string ax = "";
    eventos.push_back(centerstr(addbar(ax, 52), 261));

    int acrecimos = aleatorio(0,8);

    for(int i = 0; i <= 90 + acrecimos; i++){
        system("cls");
        rendelizarcentro(placar(placar_final, 20), 261);
        rendelizar(eventos);
        string minuto = to_string(i) + "'";
        cout << centerstr(addbar(minuto, 52), 261);
        Sleep(100);
        clube favevent = calcularevento(time1, time2);

        if(favevent.id == time1.id){
            int GolsExperados = gx(time1, time2, i);
            if(fatorcasa) GolsExperados += 3;
            int converter = aleatorio(1, 100);
            if(converter <= GolsExperados){
                placar_final.gols1++;;
                string frase = minuto + " " + time1.nome + " Scored!";
                eventos.push_back(centerstr(addbar(frase, 52), 261));
            }
        }
        else{
            int GolsExperados = gx(time2, time1, i);
            int converter = aleatorio(1, 100);
            if(converter <= GolsExperados){
                placar_final.gols2++;
                string frase = minuto + " " + time2.nome + " Scored!";
                eventos.push_back(centerstr(addbar(frase, 52), 261));
            }
        }
        if(i == 90 + acrecimos){
            eventos.push_back(centerstr(addbar(ax, 52), 261));
            eventos.push_back(centerstr(bar, 261));
        }
        if(i == 45){
            string t1 = time1.nome, t2 = time2.nome;
            eventos.push_back(centerstr(addbar(ax, 52), 261));
            ax = "[HALF TIME : " + abreviar(t1) + " " + to_string(placar_final.gols1) + " x " + to_string(placar_final.gols2) + " " + abreviar(t2) + "]";
            ax = barstr(ax, 50);
            eventos.push_back(centerstr(addbar(ax, 52), 261));
            ax = "";
            eventos.push_back(centerstr(addbar(ax, 52), 261));
        }
        placar_final.melhores_momentos = eventos;
    }
    system("cls");
    rendelizarcentro(placar(placar_final, 20), 261);
    cout << "\n";
    rendelizar(eventos);
    string lixo;
    cin >> lixo;
    

    system("cls");
    return placar_final;
}

int main(){
    clube time1 = teams[1], time2 = teams[2];
    resultado r;
    simular_penaltis(r, time1, time2);

}