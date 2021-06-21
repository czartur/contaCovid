#include <iostream>
#include <string>
#include <map>
using namespace std;


class info{
public:
    int chave, casos, obitos;
    info(int n_casos=0, int n_obitos=0)
        : casos{n_casos}, obitos{n_obitos} {}
    friend info operator+(const info& i1, const info& i2){
        return info(i1.casos+i2.casos, i1.obitos+i2.obitos); 
    }
    friend info operator-(const info& i1, const info& i2){
        return info(i2.casos-i1.casos, i2.obitos-i1.obitos);
    }
};

class node{
private:
    info* dados;
    node** sub;
    int subn, dadosn;
public:
    int id;
    node(): dados{nullptr}, sub{nullptr}, sub{0}, dadosn{0} {}

    int total(int inicio, int fim){
        return dados[fim] - dados[inicio-1];
    }
    double media(int dia, int janela){
        return (double) (dados[dia]-dados[dia-janela])/((double)janela);
    }

    void addsub(node* novo){
        sub = new node* [subn+1];
        sub[subn++] = novo;
    }
    void adddados(info novo){
        dados = new info [dadosn+1];
        dados[dadosn++] = novo;
    }
    //falta ver tendencia de crescimento
};

node* search(int id, node* cur){
    if(cur.id == id) return cur;
    for(int i=0; i<subn; i++){
        node* aux = search(id, sub[i]);
        if(aux) return aux;
    }
    return nullptr;
}

int main(){
    map<string, int> mid;
    node* brasil = nullptr;
} 