#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class info{
public:
    int casos, obitos;
    info(int n_casos=0, int n_obitos=0)
        : casos{n_casos}, obitos{n_obitos} {}
    friend info operator+=(const info& i1, const info& i2){
        return info(i1.casos+i2.casos, i1.obitos+i2.obitos); 
    }
    friend info operator-(const info& i1, const info& i2){
        return info(i1.casos-i2.casos, i1.obitos-i2.obitos);
    }
};

class node{
public:
    vector <info> dados;
    vector <node*> sub;
    string name;
    node(string n_name): name{n_name} {}

    info total(int inicio, int fim){
        return dados[fim] - dados[inicio-1];
    }
    info media(int dia, int janela){
        double casos = (double) (dados[dia].casos-dados[dia-janela].casos)/((double)janela);
        double obitos = (double) (dados[dia].obitos-dados[dia-janela].obitos)/((double)janela);
        return info(casos, obitos);
    }
    
    void addsub(node* novo){ sub.push_back(novo); }
    void adddados(info &novo){ dados.push_back(novo); }

    void fix(){
        for(auto f:sub){
            for(int i=0; i<f->dados.size(); i++){
                if((int)dados.size()-1 < i) dados.push_back(f->dados[i]);
                else {
                    dados[i]+=f->dados[i];
                }
            }
        }
    }
    //falta ver tendencia de crescimento
};

node* search(string name, node* cur){
    if(cur->name == name) return cur;
    for(int i=0; i<cur->sub.size(); i++){
        node* aux = search(name, cur->sub[i]);
        if(aux) return aux;
    }
    return nullptr;
}

vector <string> splitline(string& line){
    vector <string> ans(1);
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

int toINT(string &number){
    int ans=0, pdez=1;
    for(int i=number.size(); i--; i>=0){
        ans+=(number[i]-'0')*pdez;
        pdez*=10;
    }
    return ans;
}

int main(){
    enum Col {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q};
    int idn = 0;
    map<string, int> mid;
    ifstream file ("data.csv");
    if(!file.is_open()){
        return cout << "Problema na arbetura do arquivo..." << endl, 1;
    }


    string line;
    getline(file, line); // read the header
    vector <string> splited;
    int estadon=0, municipion=0;
    node* pais = new node("Brasil");
    node* estado = nullptr;
    node* municipio = nullptr;
    // vector<node*> sub;
    // void addsub(node* novo){ sub.push_back(novo); }
    int curline = 0;
    int tag=0;
    while(getline(file, line)){
        //cout << ++curline << endl;
        splited = splitline(line);
        if(splited[B].empty() || splited[C].empty()) continue;
        if((estado == nullptr) || (estado!=nullptr)&&(estado->name != splited[B])){
            if(estado){
                cout << estadon << ": " << estado->name << " " << estado->sub.size() << endl;
                estado->fix();
                cout << estado->dados[0]
            }
            pais->addsub(new node(splited[B]));
            estado = pais->sub[estadon++];
            municipion=0;
        }
        if((municipio == nullptr) || (municipio!=nullptr)&&(municipio->name != splited[C])){
            estado->addsub(new node(splited[C]));
            municipio = estado->sub[municipion++];
        }
        info novo_dado(toINT(splited[K]), toINT(splited[M]));
        municipio->adddados(novo_dado); 
    }
    pais->fix();
    cout << pais->dados[0].casos << endl;
} 