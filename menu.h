#include <iostream>
#include <iomanip>
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
            cout << opcoes[i] << "\n";
        }
        if(opcoes.size()) cout << endl;
    }
};

class tLevel:public Menu{
public:
    vector <info(*)(node*)> input;
    void result(const info& res, bool is_tend=0){
        cout << fixed;
        cout << "casos--> " << setprecision(2) << res.getcasos();
        if(is_tend) cout << "%";
        cout << endl;
        cout << "obitos--> " << setprecision(2) << res.getobitos();
        if(is_tend) cout << "%";
        cout << endl;
    }
    tLevel(const vector<info(*)(node*)> &n_input) : Menu("", vector<string>({})), input{n_input} {}
    void flow(node* local, int mode){
            display();
            info candidate = input[mode-1](local);
            if(candidate.getcasos() == -1 && candidate.getobitos() == inf){
                cout << "\nInvalid option! " << endl;
                return;
            }
            result(candidate, mode==3);
    }
};

class sLevel:public Menu{
public:
    sLevel(const vector<string> &n_opcoes) : Menu("", n_opcoes) {}
    void flow(node* local, tLevel m3){
        int inp;
        do{ 
            string subheader[3] = {"Total", "Media", "Tendencia"}; 
            display();
            cin >> inp;
            if(inp == 0) {
                fflush(stdin);
                getc(stdin);
                break;
            }
            else if(inp > 3 || inp<0) cout << "Invalid option! " << endl;
            else {
                m3.header = ">> " + local->name + " (" + subheader[inp-1] + ") <<";
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
                m2.header = ">> " + local->name + " <<";
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
