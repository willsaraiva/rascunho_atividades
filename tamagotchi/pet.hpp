#ifndef PET_H 
#define PET_H

#include <iostream>
#include <sstream>
using namespace std;

class Pet{
    private:
        string name;
        int satiety, energy, clean;
        int satietyMax, energyMax, cleanMax;    
        int age, diamonds;
        bool alive;

        /* Método set(interno) */ 
        void setValue(int value, int &target, int limit);

    public:

        /* Construtor */
        Pet(string name = "pet", int energyMax = 0, int satietyMax = 0, int cleanMax = 0, bool alive = true);

        /* Serializar */
        string toString();

        /* Métodos set */
        void setEnergy(int value);
        void setSatiety(int value);
        void setClean(int value);
        void setAge(int value);
        void setDiamonds(int value);

        /* Métodos */ 
        bool testAlive();
        void play();
        void eat();
        void sleep();
        void toClean();
};

class Controller{
        Pet pet;
    public:
        void shell(string line);
        void exec();
};

#endif