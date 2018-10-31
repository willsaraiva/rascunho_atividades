#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Pessoa{
    string name;
    int age;
 
    /* Construtor */
    Pessoa(string name = "", int age = 0):
        name(name), age(age)
    {}

    /* Serializar */ 
    string toString(){
        return "[" + name + ":" + to_string(age) + "]"; 
    }
};

struct Pet{
    string name;
    string raca;
 
    /* Construtor */
    Pet(string name = "", string raca = ""):
        name(name), raca(raca)
    {}

    /* Serializar */ 
    string toString(){
        return "[" + name + ":" + raca + "]"; 
    }
};


struct Repositorio{
    vector<Pessoa> pessoas;

    void add(Pessoa pessoa); 
    Pessoa& get(string chave, Pessoa pessoa);
    void rm(string chave);
    vector<Pessoa> getAll();
};


int main(){
    map<string, Pessoa> rep;
    rep["gui"] = Pessoa("Guilherme Willian", 10);
    rep["samu"] = Pessoa("Samuel Aquino", 9);
    rep.insert(pair<string, Pessoa>("merda", Pessoa("francisco", 20)));

    cout << rep["gui"].name << endl;

    for(pair<string, Pessoa> par : rep){
        cout << "key: " << par.first << " valor: " << par.second.toString() << endl;
    }
    rep.erase("gui");
    cout << "-----------------------" << endl;
    for(pair<string, Pessoa> par : rep){
        cout << "key: " << par.first << " valor: " << par.second.toString() << endl;
    }
    return 0;
}