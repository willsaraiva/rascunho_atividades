#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Cliente{
private:
    string id, name;
    int amount;
    bool alive; 
public:
    /* Construtor */
    Cliente(string id = "", string name = ""):
        id(id), name(name), amount(0), alive(true)
    {
    }

    /* Serializar */
    string toString(){
        stringstream ss;
        ss << id << " : " << name << " : " <<  amount;
        return ss.str();
    } 

    /* Métodos get */
    string getId(){
        return this->id;
    }
    int getAmount(){
        return this->amount;
    }

    /* Métodos set */
    void setAmount(int value){
        this->amount += value;
    }
};

class Transaction{
private:
    string name;
    int value;
public:
    /* Construtor */
    Transaction(string name = "", int value = 0):
        name(name), value(value)
    {
    }

    /* Serializar */
    string toString(){
        stringstream ss;
        ss << "[" << name << " " << value << "]";
        return ss.str();
    }

    /* Métodos get */
    string getName(){
        return this->name;
    }
};

class Sistema{
private:
    vector<Cliente> clients;
    vector<Transaction> transactions;
    int capacity;
public:
    /* Construtor */
    Sistema(int value = 0):
        capacity(value)
    {    
    }

    /* Serializar */
    string toString(){
        stringstream ss;
        for(auto client : clients)
            ss << client.toString() << endl;
        ss << "agiota" << " : " << this->capacity << endl;
        return ss.str();
    }  
    string toStringTr(){
        stringstream ss;
        size_t i;
        for(i = 0;i < transactions.size();i++){
            ss << "id: " << i << " " << transactions[i].toString() << endl;
        }
        return ss.str();
    } 

    /* Método set */
    void setCapacity(int value){
        this->capacity += value;
    }
    /* Método get */
    int getCap(){
        return this->capacity;
    }

    /* Métodos */
    void cleanTr(){
        transactions.erase(transactions.begin(), transactions.end());
    }
    int findAmount(string id){
        for(auto cliente : clients){
            if((cliente.getId()) == id)
                return cliente.getAmount();
        }
        return 0;
    }
    void findCli(string id){
        size_t i;
        for(i = 0;i < transactions.size();i++){
            if((transactions[i].getName()) == id)
                cout << "id:" << i << " " << transactions[i].toString() << endl;
        }
        cout << "saldo" << " " << id << ": " << findAmount(id) << endl;
    }
    void addCli(Cliente cliente){
        for(auto element : clients){
            if((element.getId()) == (cliente.getId())){
                cout << "fail: cliente ja existe" << endl;
                return;
            }
        }
        clients.push_back(cliente);
    }
    void emprestar(string id, int value){
        if(this->capacity < value){
            cout << "fail: fundos insuficientes" <<  endl;
            return;
        }
        for(auto& cliente : clients){
            if((cliente.getId()) == id){
                cliente.setAmount(value);
                setCapacity(-value);
                transactions.push_back(Transaction(id, (-1) * value));
                return;
            }
        }
        cout << "fail: cliente nao existe" << endl;
    }
    void receber(string id, int value){
        for(auto& cliente : clients){
            if((cliente.getId()) == id){
                if((cliente.getAmount()) > value){
                    cout << "fail: valor maior que a divida" << endl;
                    return;
                }
                cliente.setAmount(-value);
                setCapacity(value);
                transactions.push_back(Transaction(id, value));
                return;
            }
        }
        cout << "fail: cliente nao existe" << endl;
        return;
    }
    void kill(string id){
        size_t i;
        for(i = 0;i < clients.size();i++){
            if((clients[i].getId()) == id)
                clients.erase(clients.begin() + i);
            }
        for(auto it = transactions.begin();it != transactions.end();){
            if((it->getName() == id)
                it = transactions.erase(it);
            else
                it++;
        }   
    }
    
};

class Controller{
public:
    Sistema sistem;

    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;

        if(op == "init"){
            int amount;
            ss >> amount;
            sistem = Sistema(amount);
            sistem.cleanTr();
        }else if(op == "help"){
            cout << "showAll" << endl;
            cout << "showTr {id}" << endl;
            cout << "showCli {id}" << endl;
            cout << "addCli {id, name}" << endl;
            cout << "emprestar {id, value}" << endl;
            cout << "receber {id, value}" << endl;
            cout << "kill {id}" << endl;
        }else if(op == "showAll"){ // resumo
            cout << sistem.toString();
        }else if(op == "showTr"){ // historico
            cout << sistem.toStringTr();
        }else if(op == "showCli"){ // filtrar
            string id;
            ss >> id;
            sistem.findCli(id);
        }else if(op == "addCli"){
            string id, name;
            ss >> id;
            getline(ss, name,'\n');
            sistem.addCli(Cliente(id, name));
        }else if(op == "emprestar"){
            string id;
            int value;
            ss >> id >> value;
            sistem.emprestar(id, value);
        }else if(op == "receber"){
            string id;
            int i;
            ss >> id >> i;
            sistem.receber(id, i);
        }else if(op == "kill"){
            string id;
            ss >> id;
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
            shell(line);
        }
    }
};

int main(){

    Controller controll;
    controll.exec();
    return 0;
}