#include <iostream>
#include <vector>
#include <sstream>

using namespace std;    
 
class Cliente{
    private:
        string id, name;
        int sale;
        bool alive;
    public:
        // Construtor
        Cliente(string name = "", string id = ""):
            id(id), name(name), sale(0), alive(true)
        {
        }

        // Serializar
        string toString(){
            stringstream ss;
            ss << this->id << " : " << this->name << " : " << "Saldo: " << this->sale
                << " : " << alive;
            return ss.str();
        }

        /* Método get */
        string getId(){
            return id;
        }
};

class Sistema{
    private:
        vector<Cliente> clientes;
        vector<Cliente> transaction;
        int capacity;
    public:
        // Construtor
        Sistema(int value = 0):
            capacity(value)
        {
        }

        // Serializar
        string toString(){
            stringstream ss;
            for(Cliente cliente : clientes){
                ss << cliente.toString();
            }
            return ss.str();
        }

        /* Métodos */
        void addCli(Cliente cliente){
            for(auto element : clientes){
                if((element.getId()) == (cliente.getId())){
                    cout << "fail: cliente ja existe" << endl;
                    return ;
                }
                clientes.push_back(cliente);
            }
        }
};

class Controller{
private:
    Sistema sistema;
public:
    void shell(string line){
        stringstream ss(line);
        string op;
        ss >> op;
        if(op == "show"){
            cout << "entrou nessa merda" << endl;
            cout << sistema.toString() << endl;
        }else if(op == "addCli"){
            string id, name;
            ss >> id;
            ss >> name;
            sistema.addCli(Cliente(id, name));
        }else
            return;
    }

    void exec(){
        string line, op;
        while(true){
            getline(cin, line);
            if(line == "end")
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