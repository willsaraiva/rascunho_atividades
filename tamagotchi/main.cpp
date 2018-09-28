#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Pet{
    private:
        string name;
        int satiety, energy, clean;
        int satietyMax, energyMax, cleanMax;    
        int age, diamonds;
        bool alive;

        void setValue(int value, int &target, int limit){
            if(value <= 0){
                this->alive = false;
                target = 0;
            }else if(value > limit){
                target = limit;
            }else
                target = value;
        }

    public:

        /* Construtor */
        Pet(std::string name = "pet", int satietyMax = 0, int energyMax = 0, int cleanMax = 0, bool alive = true):
            name(name), alive(alive),
            satiety(satietyMax), energy(energyMax), clean(cleanMax),
            satietyMax(satietyMax), energyMax(energyMax), cleanMax(cleanMax)
        {
            this->age = 0;
            this->diamonds = 0;
        }

        /* Serializar */
        string toString(){
            stringstream ss; 
                ss << "E: " << energy  << "/" << energyMax << ", "
                    << "H: " << satiety << "/" << satietyMax << ", "
                    << "C: " << clean << "/" << cleanMax << ", "
                    << "D: " << diamonds << ", " << "A: " << age;
            return ss.str();
        }

        /* Métodos set */
        void setEnergy(int value){
            setValue(value, energy, energyMax);
        }
        void setSatiety(int value){
            setValue(value, satiety, satietyMax);
        }
        void setClean(int value){
            setValue(value, clean, cleanMax);
        }
        void setAge(int value){
            this->age += value;
        }
        void setDiamonds(int value){
            this->diamonds += value;
        }

        /* Métodos */ 
        bool testAlive(){
            if(alive)
                return true;
            cout << "pet esta morto" << endl;
            return false;
        }    

        void play(){
            if(!testAlive())
                return;
            setEnergy(energy - 2);
            setSatiety(satiety - 1);
            setClean(clean - 3);
            setAge(1);
            setDiamonds(1);
        }

        void eat(){
            if(!testAlive())
                return;
            setEnergy(energy - 1);
            setClean(clean - 2);
            setSatiety(satiety + 4);
            setAge(1);
        }

        void sleep(){   
            if(!testAlive())
                return;
            if((energyMax - energy) < 5){
                cout << "pet nao esta com sono" << endl;
                return;
            }
            setSatiety(satiety - 1);
            setAge(energyMax - energy);
            setEnergy(energyMax);
        }
};

class Controller{
        Pet pet;
    public:
        void shell(string line){
            stringstream in(line);
            string op;
            in >> op;
            
            if(op == "help"){
                cout << "show" << endl;
                cout << "init {satiety energy clean}" << endl;
                cout << "play" << endl;
            }else if(op == "show"){
                cout << pet.toString() <<  endl;
            }else if(op == "init"){
                int energy, clean, hungry;
                in >> hungry >> energy >> clean;
                pet = Pet("pet", hungry, energy, clean, true);
            }else if(op == "play"){
                pet.play();
            }else if(op == "eat"){
                pet.eat();
            }else if(op == "sleep"){
                pet.sleep();
            }else 
                return;
        }

        void exec(){
            string line;
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