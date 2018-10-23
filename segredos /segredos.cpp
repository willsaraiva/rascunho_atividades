#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Segredo{
    int nivel;
    string texto;
public:
    /* Construtor */
    Segredo(int nivel = 0, string texto = ""){
        setNivel(nivel);
        this->texto = texto;
    }

    /* Serializar */ 
    string toString(){ 
        return "[" + texto + "] " + to_string(nivel);
    }

    /* Métodos */
    void setNivel(int value){
        if((value < 0) || (value > 10))
            throw "fail: nivel invalido";
        this->nivel = value;
    }
};

class User{
    string id;
    string passwd;
    Segredo segredo;
public:
    /* Construtor */
    User(string id = "", string passwd = ""):
        id(id), passwd(passwd)
    {}
    
    /* Serializar */
    string toString(){
        return id + segredo.toString();
    }

    /* Métodos */
    bool verifyPass(string value){
        return this->passwd == value;
    }
    string getId(){
        return id;
    }
    void changePass(string oldPass, string newPass){
        if(this->passwd == oldPass)
            throw "fail: senha invalida";
        this->passwd = newPass;
    }
};

class Sistema{
    vector<User> usuarios;
    string adminName;
public:
    /* Construtor */ 
    Sistema(){
        usuarios.push_back(User("admin", "admin"));
        this->adminName = "admin";
    }

    /* Métodos */
    void addUser(User user){
        for(auto& usuario : usuarios){
            if((usuario.getId()) == (user.getId()))
                throw "fail: usuario ja existe";
        }
        usuarios.push_back(user);
    }
    User& getUser(string id){
        for(auto& usuario : usuarios){
            if((usuario.getId()) == id)
                return usuario;
        }
        throw "fail: usuario nao existe";
    }
};

class LoginManager{
    User* current;
    Sistema * sistema;
public:
    /* Construtor */
    LoginManager(Sistema* sistema){
        this->sistema = sistema;
        this->current = nullptr;
    }

    /* Métodos */
    User& getCurrent(){
        if(current == nullptr)
            throw "fail: ninguem logado";
        return *current;
    }
    void login(string id, string passwd){
        if(current != nullptr)
            throw "fail: ja existe alguem logado";
        User& user = sistema->getUser(id);
        if(!user.verifyPass(passwd))
            throw "fail: senha invalida";
        current = &user;
    }
    void logout(){
        if(current == nullptr)
            throw "fail: nao existe ninguem logado";
        current = nullptr;
    }   
};

class Controller{
    Sistema sistema;
    LoginManager loginMan;
public:
    /* Construtor */
    Controller():
        loginMan(&sistema)
    {}

    /* Métodos */
    void shell(string line){
        stringstream in(line);
        string op;
        in >> op;
        if(op == "addUser"){
            string id, passwd;
            in >> id >> passwd;
            sistema.addUser(User(id, passwd));
        }else if(op == "login"){
            string id, passwd;
            in >> id >> passwd;
            loginMan.login(id, passwd); 
        }else if(op == "logout"){
            loginMan.logout();
        }else if(op == "show"){
            cout << loginMan.getCurrent().toString() << endl;
        }else if(op == "changePass"){
            string oldPass, newPass;
            in >> oldPass >> newPass;
            loginMan.getCurrent().changePass(oldPass, newPass);
        }
    }
    void exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line  == "end")
                return;
            try{
                shell(line);
            }catch(const char* value){
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