#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

class Fone{
private:
    string label;
    string number;
public:
    /* Construtor */
    Fone(string label = "", string number = ""):
        label(label), number(number)
    {
    }

    /* Serializar */
    string toString(){
        stringstream ss;
        ss << label << ":" << number;
        return ss.str();
    }

    static bool validate(string number){
        string data("012345678().");
        for(auto letter : number){
            if(data.find(letter) == string::npos)
                return false; 
        }
        return true;
    }
};

class Contato{
private:
    vector<Fone> fones;
    string name;

public:
    /* Construtor */
    Contato(string name = "vazio"):
        name(name)
    {
    }

    /* Serializar */
    string toString(){
        stringstream ss;
        size_t i;
        if(fones.size() == 0){
            ss << name << "=>";
            return ss.str();
        }
        ss << name << "=> ";
        for(i = 0;i < fones.size();i++){
            ss << "[";
            ss << i << ":" << fones[i].toString();
            ss << "]";
        }
        
        return ss.str(); 
    }

    /* Métodos */
    void add(Fone fone){
        fones.push_back(fone);
    }
    void rm(unsigned int id){
        size_t i;
        for(i = 0;i < fones.size();i++){
            if(i == id){
                fones.erase(fones.begin() + i);
            }
        }
    }
};

class Controller{
private:
    Contato contato;
public:

    void shell(string line){
        stringstream ss(line);
        string op;

        ss >> op;
        if(op == "help"){
            cout << "show" << endl;
            cout << "init {name}" << endl;
            cout << "add {label, number}" << endl;
            cout << "rm {id}" << endl;
            cout << "update {name label:number}" << endl;

        }else if(op == "show"){
            cout << contato.toString() << endl;
        }else if(op == "init"){
            string name;
            ss >> name;
            contato = Contato(name);
        }else if(op == "add"){
            string label, number;
            ss >> label >> number;
            if(Fone::validate(number))
                contato.add(Fone(label, number));
            else
                cout << "fail: invalid number" << endl;
        }else if(op == "rm"){
            int id;
            ss >> id;
            contato.rm(id);
        }else if(op == "update"){
            string name, in;
            ss >> name;
            contato = Contato(name);
            while(ss >> in){ // Enquanto tiver algo pra ler
                stringstream data(in);
                string label, number;
                getline(data, label,':');
                getline(data, number);
                if(Fone::validate(number))
                    contato.add(Fone(label, number));
            }
        }else 
            return;
    }

    void exec(){
        string line, op;
        stringstream ss;

        while(true){
            getline(cin, line);
            ss << line;
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