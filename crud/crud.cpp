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

template<typename T>
struct Repositorio{
    map<string, T> data;

    bool exists(string key){
        return data.find(key) != data.end();
    }
    void add(string key, T element){
        if(exists(key))
            throw "chave duplicadas";
        // data[key] = element;
        data.insert(pair<string, T>(key, T(element.name, element .age)));
    }  
    T& get(string key, T element){
        auto it = data.find(key);
        if(it == data.end())
            throw "chave inexistente";
        return it->second;
    }
    void rm(string key){ 
        if(!exists(key))
            throw "chave inesxistente";
        data.erase(key);
    }
    vector<T> getValues(){
        vector<T> vetorE;
        for(auto& par : data)
            vetorE.push_back(par.second);
        return vetorE;
    }
    vector<string> getKeys(){
        vector<string> vetork;
        for(auto& par : data)
            vetork.push_back(par.first);
        return vetork;
    }
};


int main(){
    
    /* Testando */
    Repositorio<Pessoa> rpes;
    Repositorio<Pet> rpet;

    try{
    rpes.add("gui", Pessoa("Guilherme Willian", 10)); 
    rpes.add("gui", Pessoa("Guilherme Saraiva", 10));
    }catch(const char * value){
        cout << value << endl;
    }
    rpes.add("samu", Pessoa("Samuel de Aquino", 20));
    rpes.add("ian", Pessoa("Ian Torres", 30));    

    for(auto& pessoa : rpes.getValues()){
        cout << pessoa.toString() << endl;
    }

    rpes.rm("samu");

    for(auto& pessoa : rpes.getValues()){
        cout << pessoa.toString() << endl;
    }

    try{
        rpes.rm("bu");
    }catch(const char* value){
        cout << value << endl;
    }

    /*----------------------------*/
    
    return 0;
}