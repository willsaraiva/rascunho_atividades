#include <iostream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

class Cliente{
private:
    string id, name;
    int saldo;
    bool alive; 
public:
    /* Construtor */
    Cliente(string id = "", string name = ""):
        id(id), name(name), saldo(0), alive(true)
    {
    }

    /* Serializar */
    string toString(){
        stringstream ss;
        ss << id << " : " << name << " : " <<  saldo;
        return ss.str();
    } 

    /* Métodos get */
    string getId(){
        return this->id;
    }
    int getSaldo(){
        return this->saldo;
    }

    /* Métodos set */
    void setSaldo(int value){
        this->saldo += value;
    }
};

class Transaction{
private:
    string key;
    int value;
public:
    /* Construtor */
    Transaction(string key = "", int value = 0):
        key(key), value(value)
    {
    }

    /* Serializar */
    string toString(){
        stringstream ss;
        ss << " [" << key << " " << value << "]";
        return ss.str();
    }

    /* Métodos get */
    string getKey(){
        return this->key;
    }
};

template<typename T>
struct Repositorio{
public:
    map<string, T> data;

    bool exists(string key){
        return data.find(key) != data.end();
    }
    void add(string key, T element){
       // data[key] = element; // Não entendi isso
        data.insert(pair<string, T>(key, element));
    }  
    T& get(string key){
        auto it = data.find(key);
        if(it == data.end())
            throw "fail: chave inexistente";
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

class Sistema{
private:
    Repositorio<Cliente> clients;
    Repositorio<Transaction> transactions;
    int capacity;
public:
    /* Construtor */
    Sistema(int value = 0){
        this->capacity = value;
    }

    /* Serializar */
    string toStringCli(){
        stringstream ss;
        for(auto cliente : clients.data){
            ss << cliente.second.toString() << endl;
        }
        return ss.str();
    }
    string toStringTr(){
        stringstream ss;
        for(auto& elemento : transactions.data){
            ss << "id: " << elemento.first << elemento.second.toString() << endl;
        }
        return ss.str();
    }

    /* Meétodos auxiliares */
    int getCap(){
        return this->capacity;
    }
    void setCap(int value){
        this->capacity += value;
    }

    /* Métodos */
    void saldoSis(){
        cout << "Agiota" << " : " << this->capacity << endl;
    }
    string filter(string key){
        stringstream ss;
        for(auto& elemento : transactions.data){
            if(elemento.second.getKey() == key)
                ss << "id: " << elemento.first << elemento.second.toString() << endl;
        }
        ss << "Saldo: " << clients.get(key).getSaldo() << endl;
        return ss.str();
    }
    void addCli(Cliente cliente){
        if(clients.exists(cliente.getId()))
            throw "fail: cliente ja existe";
        clients.add(cliente.getId(), cliente);
    }
    void emprestar(string id, int value){
        if(value > capacity)
            throw "fail: fundos insuficientes";
        transactions.add(to_string(transactions.data.size()), Transaction(id, -value));
        clients.get(id).setSaldo(value);
        setCap(-value);
    }
    void receber(string id, int value){
        if(value > clients.get(id).getSaldo())
            throw "fail: valor maior que a divida";
        transactions.add(to_string(transactions.data.size()), Transaction(id, value));
        clients.get(id).setSaldo(-value);
        setCap(value);
    }
    void kill(string id){
        clients.rm(id);
        for(auto& elemento : transactions.data){
            if(elemento.second.getKey() == id)
                clients.rm(elemento.second.getKey());
        }
    }
};

class Controller{
private:
    Sistema sistem;
public:
    void shell(string line){
        stringstream in(line);
        string op;
        in >> op;
        if(op == "help"){
            cout << "init {value}" << endl;
            cout << "showAll" << endl;
            cout << "showTr" << endl;
            cout << "showCli {id}" << endl;
            cout << "add {id, name}" << endl;
            cout << "emprestar {id, value}" << endl;
            cout << "receber {id, value}" << endl;
            cout << "kill {id}" << endl;
        }else if(op == "init"){
            int amount;
            in >> amount;
            sistem = Sistema(amount);
        }else if(op == "showAll"){
            cout << sistem.toStringCli();
            sistem.saldoSis();
        }else if(op == "showTr"){
            cout << sistem.toStringTr();
        }else if(op == "showCli"){
            string key;
            in >> key;
            cout << sistem.filter(key);
        }else if(op == "addCli"){
            string id, name;
            in >> id >> name;
            sistem.addCli(Cliente(id, name));
        }else if(op == "emprestar"){
            string id;
            int value;
            in >> id >> value;
            sistem.emprestar(id, value);
        }else if(op == "receber"){
            string id;
            int value;
            in >> id >> value;
            sistem.receber(id, value);
        }else if(op == "kill"){
            string id;
            in >> id;
            sistem.kill(id);
        }else
            return;
    }

    void exec(){
        string line, op;
        while(true){
            getline(cin, line);
            stringstream ss(line);
            ss >> op;
            if(op == "end")
                return;
            try{
                shell(line);
            }catch(const char * value){
                cout << value << endl;
            }
        }
    }
};

int main(){
    Controller controll;
    controll.exec();
    return 0;
}