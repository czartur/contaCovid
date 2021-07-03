#include <vector>
#include <string>
#include "info.h"
#include "node.h"

info node::total(int inicio, int fim){
    fim--, inicio--;
    return dados[fim] - dados[inicio-1];
}
info node::media(int dia, int janela){
    dia--;
    double casos = (double) (dados[dia].getcasos()-dados[dia-janela].getcasos())/((double)janela);
    double obitos = (double) (dados[dia].getobitos()-dados[dia-janela].getobitos())/((double)janela);
    return (dados[dia]-dados[dia-janela])/info(janela, janela);
}
info node::tendencia(int inicio, int fim, int janela){
    fim--, inicio--;
    info m_inicio = media(inicio, janela);
    info m_fim = media(fim, janela);
    return (m_fim-m_inicio)/m_inicio;
}

void node::fix(){
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

node* search(string& name, node* cur){
    if(cur->name == name) return cur; 
    vector<node*>::iterator it;
    for(it = cur->sub.begin(); it != cur->sub.end(); it++){
        node* aux = search(name, *it);
        if(aux) return aux;
    }
    return nullptr;
}
