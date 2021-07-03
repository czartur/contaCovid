#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "menu.h"
using namespace std;

//miscellaneous
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
int strTOint(string &number){
    int ans=0, pdez=1;
    for(int i=number.size()-1; i>=0; i--){
        if(number[i]<'0' || number[i]>'9') return -1;
        ans+=(number[i]-'0')*pdez;
        pdez*=10;
    }
    return ans;
}
int dateTOint(string &date){
    int moisize[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for(int i=1; i<13; i++) moisize[i]+=moisize[i-1];
    int raw = strTOint(date);
    if(raw == -1 || date.size()!= 4) return -1;
    int mois = raw%100, jour = raw/100;
    if(mois<=0 || mois> 12 || jour<=0 ||(mois>0 && mois<=12 && jour>moisize[mois]-moisize[mois-1])) return -1;
    return jour + moisize[mois-1];
}

//third level menu functions
vector<int> inp_total(node* local){
    string inp;
    int inicio, fim;
    cout << "Data de inicio [DDMM]: ";
    cin >> inp;
    inicio = dateTOint(inp);
    cout << "Data de fim [DDMM]: ";
    cin >> inp;
    fim = dateTOint(inp);
    if(inicio==-1 || fim==-1 || fim<inicio || fim>local->getdados().size()) return vector<int>();
    return vector<int>({inicio, fim});
}
vector<int> inp_media(node* local){
    string inp;
    int dia, janela;
    cout << "Data [DDMM]: ";
    cin >> inp;
    dia = dateTOint(inp);
    cout << "Janela [numero]: ";
    cin >> inp;
    janela = strTOint(inp);
    if(janela==-1 || janela==0 || dia-janela+1 <= 0 || dia>local->getdados().size()) return vector<int>();
    return vector<int>({dia, janela});
}
vector<int> inp_tendencia(node* local){
    string inp;
    int inicio, fim, janela;
    cout << "Data posterior [DDMM]: ";
    cin >> inp;
    fim = dateTOint(inp);
    cout << "Data anterior [DDMM]: ";
    cin >> inp;
    inicio = dateTOint(inp);
    cout << "Janela [numero]: ";
    cin >> inp;
    janela = strTOint(inp);
    if(janela==-1 || janela==0 || fim<inicio || inicio-janela+1 <=0 || fim>local->getdados().size()) return vector<int>();
    return vector<int>({inicio, fim, janela});
}

//read csv file
bool fetchData(node** pais){
    enum Col {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q};
    ifstream file ("data.csv");
    if(!file.is_open()){
        return cout << "Problema na arbetura do arquivo..." << endl, 1;
    }
    string line;
    getline(file, line); // read the header
    vector <string> splited;
    int estadon=0, municipion=0;
    node* estado = nullptr;
    node* municipio = nullptr;
    while(getline(file, line)){
        splited = splitline(line);
        if(splited[E].empty()) continue; //dados irrelevantes ou redundantes possuem a coluna E vazia
        if(splited[C].empty()) splited[C] = "Outras";
        if((estado == nullptr) || (estado!=nullptr)&&(estado->getname() != splited[B])){
            if(estado) estado->fix();
            (*pais)->addsub(new node(splited[B]));
            estado = (*pais)->getsub()[estadon++];
            municipion=0;
        }
        if((municipio == nullptr) || (municipio!=nullptr)&&(municipio->getname() != splited[C])){
            estado->addsub(new node(splited[C], strTOint(splited[J])));
            municipio = estado->getsub()[municipion++];
        }
        info novo_dado(strTOint(splited[K]), strTOint(splited[M]));
        municipio->adddados(novo_dado);
    } 
    estado->fix();
    (*pais)->fix();
    file.close();
    return 0;
}

int main(){
    node* pais = new node("Brasil");
    if(fetchData(&pais)) return 1;

    pLevel m0("### Covid-19 (database) ###\n");
    sLevel m1(vector<string>({"Voltar", "Total", "Média móvel", "Tendência", "Ranking (casos)", "Ranking (obitos)"}));
    tLevel m2(vector<vector<int>(*)(node*)>({inp_total, inp_media, inp_tendencia}));
    m0.flow(pais, m1, m2);
    
    delete pais;
}