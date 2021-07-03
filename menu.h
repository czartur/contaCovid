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

class tLevel:public Menu{ 
public:
    vector <vector<int>(*)(node*)> input;
    tLevel(const vector<vector<int>(*)(node*)> &n_input) : Menu("", vector<string>({})), input{n_input} {}
    void result(const info& res, bool is_tend);
    info inpTOres(node* loca, vector<int> &candidate, int mode);
    void flow(node* loval, int mode);
};

class sLevel:public Menu{ 
public:
    sLevel(const vector<string> &n_opcoes) : Menu("", n_opcoes) {}
    void flow(node* local, tLevel m3);
};

class pLevel:public Menu{
public:
    pLevel(const string &n_header) : Menu(n_header, vector<string>({})) {}
    void flow(node* head, sLevel m2, tLevel m3);
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
// 4. ranking

//# Menu 2.1 (t)
// Escoher 2 datas (ou voltar)
// --> resultado

//# Menu 2.2 (t)
// Escolher 1 data e 1 janela (ou voltar)
// --> resultado

//# Menu 2.3 (t)
// Escolher 2 datas e 1 janela (ou voltar)
// --> resultado
