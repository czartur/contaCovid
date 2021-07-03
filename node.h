#include <vector>
#include <string>
#include <iterator>
#include "info.h"
using namespace std;

#ifndef NODE_H
#define NODE_H

class node{
private:
	vector <node*> sub;
	vector <info> dados;
    string name;
    int population;
public:
    //@@ctors
    node(string n_name, int n_population=0): name{n_name}, population{n_population}{}
    ~node(){ for(auto p:sub) delete p; }

    //'cereja do bolo' functions
    info total(int inicio, int fim);
    info media(int dia, int janela);
    info tendencia(int inicio, int fim, int janela);

    //access functions
    vector<node*> getsub(){ return sub; }
    vector<info> getdados(){ return dados; }
    string getname(){ return name; }
    int getpopulation(){ return population; }

    //setfunctions
    void addsub(node* novo){ sub.push_back(novo); }
    void adddados(info &novo){ dados.push_back(novo); }

    void fix(); //bring up data
    friend node* search(string& name, node* cur); //find by name
};
#endif