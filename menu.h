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
