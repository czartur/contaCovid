#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include "node.h"
using namespace std;

#ifndef MENU_H
#define MENU_H
const int inf = 0x3f3f3f3f;
void wait(){
    cout << "press anything to continue... ";
    fflush(stdin);
    fgetc(stdin);
    getchar();
}

class Menu{
public:
    string header;
    vector <string> opcoes;
    Menu(const string &n_header, const vector<string> &n_opcoes): header{n_header}, opcoes{n_opcoes} {}
    void display(){
        system("clear");
        cout << header << endl;
        for(int i=0; i<opcoes.size(); i++){
            cout << i << ". " << opcoes[i] << "\n";
        }
        if(opcoes.size()) cout << endl;
    }
};

class tLevel:public Menu{ //to do next --> exceptions
public:
    vector <vector<int>(*)(node*)> input;
    void result(const info& res, bool is_tend=0){
        cout << fixed;
        cout << "casos--> " << setprecision(2) << res.getcasos();
        if(is_tend) cout << "%";
        cout << endl;
        cout << "obitos--> " << setprecision(2) << res.getobitos();
        if(is_tend) cout << "%";
        cout << endl;
    }
    info inpTOres(node*local, vector<int> &candidate, int mode){
        info res;
        switch (mode)
        {
        case 1:
            res = local->total(candidate[0], candidate[1]);
            break;
        case 2:
            res = local->media(candidate[0], candidate[1]);
            break;
        case 3:
            res = local->tendencia(candidate[0], candidate[1], candidate[2]);
            break;
        default: 
            break;
        }
        return res;
    }
    tLevel(const vector<vector<int>(*)(node*)> &n_input) : Menu("", vector<string>({})), input{n_input} {}
    void flow(node* local, int mode){
        display();
        if(mode == 4){
            if(local->getsub().empty()){
                cout << "Por favor, selecione um estado ou país para essa opção!" << endl;
                return;
            }
            int rankopcao;
            cout << "0. Voltar\n1. [rank] Total\n2. [rank] Media\n3. [rank] Tendencia" << endl;
            //HERE
            cin >> rankopcao;
            if(!rankopcao) return;
            //HERE
            vector<int> candidate = input[rankopcao-1](local);
            if(candidate.empty()){
                cout << "\nInvalid option! " << endl;
                return;
            }
            vector<pair<double, node*>> rank;
            for(auto p:local->getsub()){
                if(p->getname() == "Outras") continue;
                rank.push_back({inpTOres(p, candidate, rankopcao).getcasos(), p});
            }
            sort(rank.begin(), rank.end());
            /*
            vector<pair<double, node*>>::iterator it;
            for(it=rank.end(); it!=rank.begin(); it--){
                cout << rank.end()-it + 1 << ". " << (*it).second->name << "\n";
            }
            */
            cout << fixed;
            /*
            vector<pair<double, node*>>::iterator it;
            for(it=rank.end(); it!=rank.begin(); it--){
                cout << rank.end() - it + 1 << ". "  << ((*it).second)->getname() << " [" << setprecision(2) << (*it).first << "]\n";
            }
            */
            
            for(int i=rank.size()-1; i>=0; i--){
                cout << rank.size()-i << ". " << rank[i].second->getname() << " [" << setprecision(2) << rank[i].first << "]\n";
            }
            
            cout << endl;
        }
        else{
            vector<int> candidate = input[mode-1](local);
            if(candidate.empty()){
                cout << "\nInvalid option! " << endl;
                return;
            }
            result(inpTOres(local, candidate, mode), mode==3);
        }
    }
};
class sLevel:public Menu{ //to do next--> exceptions
public:
    sLevel(const vector<string> &n_opcoes) : Menu("", n_opcoes) {}
    void flow(node* local, tLevel m3){
        int inp;
        do{ 
            display();
            cin >> inp;
            //HERE
            if(inp == 0) {
                fflush(stdin);
                getc(stdin);
                break;
            }
            else if(inp > opcoes.size()-1 || inp<0) cout << "Invalid option! " << endl;
            else {
                m3.header = ">> " + local->getname() + " (" + opcoes[inp] + ") <<";
                m3.flow(local, inp);
            }
            wait();
        }while(inp != 0);
    }
};

class pLevel:public Menu{
public:
    pLevel(const string &n_header) : Menu(n_header, vector<string>({})) {}
    void flow(node* head, sLevel m2, tLevel m3){
        string inp;
        do{
            display();
            cout << "[0] para sair\nLocal: "; 
            getline(cin, inp);
            node* local = search(inp, head); 
            if(local) {
                m2.header = ">> " + local->getname() + " <<";
                m2.flow(local, m3);
            }
            else{
                cout << "Local não encontrado, tentar novamente?(s/n) ";
                cin >> inp;
                if(inp == "n") break;
                fflush(stdin);
                getc(stdin);
            }
        }while(inp != "0");
    }
}; 

#endif 

// >>ESBOÇO<<

// # Menu 0 (p)
// Escolher um local (ou sair)

//# Menu 1 (s)
// 0. voltar
// 1. total de casos
// 2. media movel
// 3. tedencia 

//# Menu 2.1 (t)
// Escoher 2 datas (ou voltar)
// --> resultado

//# Menu 2.2 (t)
// Escolher 1 data e 1 janela (ou voltar)
// --> resultado

//# Menu 2.3 (t)
// Escolher 2 datas e 1 janela (ou voltar)
// --> resultado
