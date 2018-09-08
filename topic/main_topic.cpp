#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Passageiro{
    string name;
    int age;

    // Construtor
    Passageiro(string name = "fulano", int age = 0){
        this->name = name;
        this->age = age;
    }

    // Serializar
    string toString(){
        stringstream ss;
        ss << this->name << ":" << this->age;
        return ss.str();
    }
};

struct Topic{
    vector<Passageiro*> cadeiras;
    int amount_pref, amount_max;

    // Construtor
    /*Topic(int max = 0, int pref = 0){
        this->amount_pref = pref;   
        for(int i = 0;i < max;i++){
            cadeiras.push_back(nullptr);
        }
    }*/

    Topic(int max = 0, int pref = 0) : cadeiras(max, nullptr){
        this->amount_pref = pref;
    }

    // Serializar
    string toString(){
        stringstream ss;
        int qtd_pref = 0;

        ss << "[";
        for(int i = 0;i < cadeiras.size();i++){
            if(cadeiras[i] == nullptr){
                if(qtd_pref <= amount_pref){
                    ss << "@";
                    qtd_pref++;
                }
                else 
                    ss << "=";
            }
            else 
                ss << cadeiras[i]->toString();
        }
        ss << "]";
    }

    // Criar
};

int main(){

    Topic topic;
    string op;

    while(true){
        cin >> op;

        if(op == "show"){
            cout << topic.toString() << endl;
        }
        else if(op == "new"){
            int max;
            int pref;
            cin >> max >> pref;
            topic = Topic(max, pref);
        }
    }
    return 0;
}