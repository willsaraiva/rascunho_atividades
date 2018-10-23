#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/* Aprendendo como se ordena um conjunto de elementos
    que não sejam tipos primitivos de dados usando
    a sobrecarga de operadores*/

/* "bool operator<(Pessoa other)" essa determinada função
     ensina para o operador "<" como deve se comparar du-
     as pessoas usando o "name" como critério */

/* O exemplo utilizado, função "sort", utiliza o operador
    "<" para realizar a comparação entre dois elementos que
    estão em um determinado intervalo previamente informado.
    Como o operador "<" não sabe comparar duas pessoas, a fun-
    ção criada "ensina" como se compara duas pessoas através
    da sobrecarga do operando "<"  */

/* Pode ser usado também função que não esteja dentro da pró-
    pria classe mas que ensina como os seus elementos são com-
    parados. A função que deseja utilizar para com seus respe-
    ctivos critérios, deve ser informado no chamado da função 
    de ordenação  */

struct Pessoa{
    string name;
    int age;

    /* Construtor */
    Pessoa(string name, int age){
        this->name = name;
        this->age = age;
    }

    /* Sobrecarga de operador */ 
    bool operator<(Pessoa other){
        if(this->age == other.age)
            return this->name < other.name;
        return this->age < other.age; 
    } 
    
}; 

    /* Métodos de Comparação */ 
    bool compareAge(Pessoa first, Pessoa second){
        if(first.age == second.age)
            return first.name < second.name;
        return first.age < second.age;
    }
    bool compareName(Pessoa first, Pessoa second){
        return first.name < second.name;
    }

int main(){
    vector<Pessoa> vp = {Pessoa("samuel", 3), Pessoa("ana", 7), 
                          Pessoa("guilherme", 5)};

    /* Utilizando "compareAge" */
    std::sort(vp.begin(), vp.end(), compareAge);
    for(auto& element :  vp)
        cout << "[" << element.name  << ":" << element.age << "]";
    cout << endl;

    /* Utlizando "compareName" */
    std::sort(vp.begin(), vp.end(), compareName);
    for(auto& element :  vp)
        cout << "[" << element.name  << ":" << element.age << "]";
    cout << endl;
     
    return 0;
}