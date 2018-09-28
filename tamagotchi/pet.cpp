#include <iostream>
#include <sstream>
#include "pet.hpp"

    /* Construtor */
    Pet::Pet(string name, int energyMax, int satietyMax, int cleanMax, bool alive):
        name(name), alive(alive),
        satiety(satietyMax), energy(energyMax), clean(cleanMax),
        satietyMax(satietyMax), energyMax(energyMax), cleanMax(cleanMax)
    {
        this->age = 0;
        this->diamonds = 0;
    }

    /* Serializar */
    string Pet::toString(){
        stringstream ss; 
            ss << "E: " << energy  << "/" << energyMax << ", "
                << "H: " << satiety << "/" << satietyMax << ", "
                << "C: " << clean << "/" << cleanMax << ", "
                << "D: " << diamonds << ", " << "A: " << age;
        return ss.str();
    }

    void Pet::setValue(int value, int &target, int limit){  
        if(value <= 0){
            if(this->diamonds >= 5){
                cout << "entrou nessa merda" << endl;
                setDiamonds(-5);
                target = 0;
                this->alive = true;    
                return;
            }
            this->alive = false;
            target = 0;
        }else if(value > limit){
            target = limit;
        }else
            target = value;
    }

    /* Métodos set */
    void Pet::setEnergy(int value){
        setValue(value, energy, energyMax);
    }
    void Pet::setSatiety(int value){
        setValue(value, satiety, satietyMax);
    }
    void Pet::setClean(int value){
        setValue(value, clean, cleanMax);
    }
    void Pet::setAge(int value){
        this->age += value;
    }
    void Pet::setDiamonds(int value){
        this->diamonds += value;
    }

    /* Métodos */ 
    bool Pet::testAlive(){
        if(alive)
            return true;
        return false;
    }    

    void Pet::play(){
        if(!testAlive()){
            cout << "pet esta morto" << endl;
            return;
        }
        setEnergy(energy - 2);
            if(!testAlive()){
                cout << "pet morreu de fraqueza" << endl;
                return;
            }
        setSatiety(satiety - 1);
            if(!testAlive()){
                cout << "pet morreu de fome" << endl;
                return;
            }
        setClean(clean - 3);
            if(!testAlive()){
                cout << "pet morreu de sujeira" << endl;
                return;
            }
        setAge(1);
        setDiamonds(1);
    }

    void Pet::eat(){
        if(!testAlive()){
            cout << "pet esta morto" << endl;
            return;
        }
        setEnergy(energy - 1);
            if(!testAlive()){
                cout << "pet morreu de fraqueza" << endl;
                return;
            }
        setClean(clean - 2);
            if(!testAlive()){
                cout << "pet morreu de fome" << endl;
                return;
            }
        setSatiety(satiety + 4);
            if(!testAlive()){
                cout << "pet morreu de fome" << endl;
                return;
            }
        setAge(1);
    }        

    void Pet::sleep(){   
        if(!testAlive()){
            cout << "pet esta morto" << endl;
            return;
        }
        if((energyMax - energy) < 5){
            cout << "pet nao esta com sono" << endl;
            return;
        }
        setSatiety(satiety - 1);
            if(!testAlive()){
                cout << "pet morreu de fome" << endl;
                return;
            }
        setAge(energyMax - energy);
        setEnergy(energyMax);   
    }

    void Pet::toClean(){
        if(!testAlive()){
            cout << "pet esta morto" << endl;
            return;
        }
        setSatiety(satiety - 1);
            if(!testAlive()){
                cout << "pet morreu de fome" << endl;
                return;
            }
        setEnergy(energy - 3);
            if(!testAlive()){
                cout << "pet morreu de fome" << endl;
                return;
            }
        setClean(cleanMax);
        setAge(2);
    }

    /* Métodos de Controle */
    void Controller::shell(string line){
        stringstream in(line);
        string op;
        in >> op;
        
        if(op == "help"){
            cout << "show" << endl;
            cout << "init {satiety energy clean}" << endl;
            cout << "play" << endl;
            cout << "eat" << endl;
            cout << "sleep" << endl;
            cout << "clean" << endl;
        }else if(op == "show"){
            cout << pet.toString() <<  endl;
        }else if(op == "init"){
            int energy, clean, hungry;
            in >> energy >> hungry >> clean;
            pet = Pet("pet", energy, hungry,clean, true);
        }else if(op == "play"){
            pet.play();
        }else if(op == "eat"){
            pet.eat();
        }else if(op == "sleep"){
            pet.sleep();
        }else if(op == "clean"){
            pet.toClean();
        }else
            return; 
            
    }
    void Controller::exec(){
        string line;
        while(true){
            getline(cin, line);
            if(line == "end")
                return;
            shell(line);
        }        
    }