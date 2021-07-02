#include <vector>
#include <string>
#include <iterator>
#include "info.h"
using namespace std;

#ifndef NODE_H
#define NODE_H

class node{
public:
    vector <node*> sub;
    vector <info> dados;
    string name;
    int population;
    node(string n_name, int n_population=0): name{n_name}, population{n_population}{}
    ~node(){ for(auto p:sub) delete p; }
    info total(int inicio, int fim){
        fim--, inicio--;
        return dados[fim] - dados[inicio-1];
    }
    info media(int dia, int janela){
        dia--;
        double casos = (double) (dados[dia].getcasos()-dados[dia-janela].getcasos())/((double)janela);
        double obitos = (double) (dados[dia].getobitos()-dados[dia-janela].getobitos())/((double)janela);
        return (dados[dia]-dados[dia-janela])/info(janela, janela);
    }
    info tendencia(int inicio, int fim, int janela){
        fim--, inicio--;
        info m_inicio = media(inicio, janela);
        info m_fim = media(fim, janela);
        return (m_fim-m_inicio)/m_inicio;
    }

    vector<node*> getsub(){ return sub; }
    vector<info> getdados(){ return dados; }
    string getname(){ return name; }
    int getpopulation(){ return population; }

    void addsub(node* novo){ sub.push_back(novo); }
    void adddados(info &novo){ dados.push_back(novo); }

    void fix(){
        for(auto f:sub){
            population+=f->population;
            for(int i=0; i<f->dados.size(); i++){
                if((int)dados.size()-1 < i) dados.push_back(f->dados[i]);
                else {
                    dados[i]+=f->dados[i];
                }
            }
        }
    }
};
node* search(string& name, node* cur){
    if(cur->getname() == name) return cur;
    /*
    //cout << cur->getname() << endl;
    vector <node*>::iterator it;
    for (it = cur->getsub().begin(); it != cur->getsub().end(); it++) {
        //cout << (*it)->getname() << endl;
        node* aux = search(name, *it); 
        if (aux) return aux;
    }
    */
    for(int i=0; i<cur->getsub().size(); i++){
        node* aux = search(name, cur->getsub()[i]);
        if(aux) return aux;
    }
    
    return nullptr;
}
#endif