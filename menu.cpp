#include <iostream>
#include "menu.h"
using namespace std;

void wait(){
    cout << "press anything to continue... ";
    fflush(stdin);
    fgetc(stdin);
    getchar();
}

void pLevel::flow(node* head, sLevel m2, tLevel m3){
    string inp;
    do{
        display();
        cout << "Ex: \"Brasil\", \"RJ\", \"Niterói\"\n[0] para sair\n\nLocal: "; 
        getline(cin, inp);
        node* local = search(inp, head); 
        if(local) {
            m2.header = ">> " + local->getname() + " <<";
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

void sLevel::flow(node* local, tLevel m3){
    int inp;
    do{ 
        display();
        cin >> inp;
        //HERE
        if(inp == 0) {
            fflush(stdin);
            getc(stdin);
            break;
        }
        else if(inp > opcoes.size()-1 || inp<0) cout << "Invalid option! " << endl;
        else {
            m3.header = ">> " + local->getname() + " (" + opcoes[inp] + ") <<";
            m3.flow(local, inp);
        }
        wait();
    }while(inp != 0);
}

void tLevel::flow(node* local, int mode){
    display();
    if(mode == 4 || mode == 5){
        if(local->getsub().empty()){
            cout << "Por favor, selecione um estado ou país para essa opção!" << endl;
            return;
        }
        int rankopcao;
        cout << "0. Voltar\n1. by Total\n2. by Media\n3. by Tendencia" << endl;
        //HERE
        cin >> rankopcao;
        try {
            if (!rankopcao) throw 0;
            if (rankopcao < 0 || 3 < rankopcao) throw 1;
			vector<int> candidate = input[rankopcao - 1](local);
            if (candidate.empty()) throw 2;
			vector<pair<double, node*>> rank;
			for (auto p : local->getsub()) {
				if (p->getname() == "Outras") continue;
				if (mode == 4) rank.push_back({ inpTOres(p, candidate, rankopcao).getcasos(), p });
				else rank.push_back({ inpTOres(p, candidate, rankopcao).getobitos(), p });
			}
			sort(rank.begin(), rank.end());
			cout << fixed;

			for (int i = rank.size() - 1; i >= 0; i--) {
				cout << rank.size() - i << ". " << rank[i].second->getname() << " com [" << setprecision(2) << rank[i].first;
				if (rankopcao == 3) cout << "%";
				cout << "]\n";
			}
			cout << endl;
        }
        catch (int e) {
            if (e == 0) return;
            if (e == 1) {
				cout << "\nInvalid option! " << endl;
				return;
            }
            if (e == 2) {
				cout << "\nInvalid option! " << endl;
				return;
            }
        }

        /*
        if(!rankopcao) return;
        //HERE
        vector<int> candidate = input[rankopcao-1](local);
        if(candidate.empty()){
            cout << "\nInvalid option! " << endl;
            return;
        }
        vector<pair<double, node*>> rank;
        for(auto p:local->getsub()){
            if(p->getname() == "Outras") continue;
            if(mode == 4) rank.push_back({inpTOres(p, candidate, rankopcao).getcasos(), p});
            else rank.push_back({inpTOres(p, candidate, rankopcao).getobitos(), p});
        }
        sort(rank.begin(), rank.end());
        cout << fixed;
        
        for(int i=rank.size()-1; i>=0; i--){
            cout << rank.size()-i << ". " << rank[i].second->getname() << " com [" << setprecision(2) << rank[i].first;
            if(rankopcao == 3) cout << "%";
            cout << "]\n";
        }
        cout << endl;
        */
    }
    else{
        vector<int> candidate = input[mode-1](local);
        if(candidate.empty()){
            cout << "\nInvalid option! " << endl;
            return;
        }
        result(inpTOres(local, candidate, mode), mode==3);
    }
}

info tLevel::inpTOres(node*local, vector<int> &candidate, int mode){
    info res;
    switch (mode)
    {
    case 1:
        res = local->total(candidate[0], candidate[1]);
        break;
    case 2:
        res = local->media(candidate[0], candidate[1]);
        break;
    case 3:
        res = local->tendencia(candidate[0], candidate[1], candidate[2]);
        break;
    default: 
        break;
    }
    return res;
}

void tLevel::result(const info& res, bool is_tend=0){
    cout << fixed;
    cout << "casos--> " << setprecision(2) << res.getcasos();
    if(is_tend) cout << "%";
    cout << endl;
    cout << "obitos--> " << setprecision(2) << res.getobitos();
    if(is_tend) cout << "%";
    cout << endl;
}