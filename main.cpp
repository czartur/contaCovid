#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
public:
    node** sub;
    int subn, dadosn;
    int id;
    node(int n_id): dados{nullptr}, sub{nullptr}, subn{0}, dadosn{0}, id{n_id} {
        dados = nullptr;
        sub = nullptr;
    }

    info total(int inicio, int fim){
        return dados[fim] - dados[inicio-1];
    }
    info media(int dia, int janela){
        double casos = (double) (dados[dia].casos-dados[dia-janela].casos)/((double)janela);
        double obitos = (double) (dados[dia].obitos-dados[dia-janela].obitos)/((double)janela);
        return info(casos, obitos);
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
    if(cur->id == id) return cur;
    for(int i=0; i<cur->subn; i++){
        node* aux = search(id, cur->sub[i]);
        if(aux) return aux;
    }
    return nullptr;
}

vector <string> divide_line(string& line){
    vector <string> ans(1);
    "brasil", "RO", "Boa Visto"
    int i=0;
    for(auto p: line){
        if(p == ';') {
            ans.resize(++i + 1);
            continue;
        }
        ans[i].push_back(p);
    }
    return ans;
}

int main(){
    map<string, int> mid; 
    node* brasil = nullptr;

    ifstream file ("data.csv");
    if(!file.is_open()){
        return cout << "Problema na arbetura do arquivo..." << endl, 1;
    }
    string line;
    vector <string> dividida;
    while(getline(file, line)){
        dividida = divide_line(line);
    }
    for(auto p: dividida){
        cout << p << endl;
    }
} 