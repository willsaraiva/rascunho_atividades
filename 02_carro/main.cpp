#include <iostream>
#include <sstream>
using namespace std;
	
struct controller{

    Carro car;

  // Chama as funções de acordo com a op do usuario
  string shell(string line){

  }

  // Interface de entrada e saida de dados do usuario
  void io(){

    string line;
    while(true){
       getline(cin, line);
       if(line == "fim")
         return;
       cout << shell(line);
    }
  }



};

struct Carro{

   int pass;
   int passMax;
   float gas;
   float gasMax;
   float km;	

   // Construtor
   Carro(int pass, float gas, float km){ 
      this->pass = pass;
      this->passMax = 2;
      this->gas = gas;
      this->gasMax = 10;
      this->km = km;
   }

   // Mostra o status do carro
   string toString(){
     stringstream saida;

     saida << "pass: " << this->pass << "," << "gas: " << this->gas <<  "," <<"km: " << this->km;
     return saida.str();
   }
   
   // Embarca um passageiro no veiculo
   bool in(){
     if(this->pass >= this->passMax){
       cout << "fail : limite de passageiros atingido" << endl;
       return false;
     }
     this->pass += 1;
     return true;		
   }

   // Desembarca um passageiro do veiculo
   bool out(){
     if(this->pass == 0){
       cout << "fail : nao ha ninguem no veiculo" << endl;
       return false;
     }
     this->pass -= 1;
     return true;
   }

   // Abastece o tanque do veiculo
   void fuel(float value){	
	   this->gas += value;
     if(this->gas >= this->gasMax)
        this->gas = 10;
   }
   
   // Realiza o trajeto  	
   bool drive(float value){
     float qtd_km = this->gas * 10;

     if(this->pass == 0){
        cout << "fail : nao ha ninguem no veiculo" << endl; 
        return false;
     }
     if(value >= qtd_km){
        cout << "fail : gasolina insuiciente" << endl; 
        return false;
     }
     this->km += value;
     this->gas -= (value/10);
     return true;    
   }
};

int main(){
  
   string op;
   Carro car(0, 0, 0);

   while(true){
      cin >> op;      

      if(op == "show"){
         cout << car.toString();
      }else if(op == "in"){
        if(car.in())
          cout << "done" << endl; 
      }else if(op == "out"){
        if(car.out())
          cout << "done" << endl;
      }else if(op == "fuel"){
        float value;
        cin >> value;
        car.fuel(value);
      }else if(op == "drive"){
        float value;
        cin >> value;
        if(car.drive(value))
          cout << "done" << endl;
      }else if(op == "fim")
        break;	
     }	
   return 0;
}
