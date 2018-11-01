#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
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
    map<string, Pessoa> pessoas;

    void add(string chave, Pessoa pessoa){
        if(exists)
            throw "chave duplicadas";
        pessoas.insert(pair<string, Pessoa>(chave, Pessoa(pessoa.name, pessoa.age)));
    }
    bool exists(string chave){
        return pessoas.find(chave) != pessoas.end();
    }
    Pessoa& get(string chave, Pessoa pessoa){
        auto it = pessoas.find(chave);
        if(it == pessoas.end())
            throw "chave inexistente";
        return it->second;
    }
    void rm(string chave){ 
        if(!exists(chave))
            throw "chave inesxistente";
        pessoas.erase(chave);
    }
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