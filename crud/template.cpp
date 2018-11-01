/* Atividade que exemplifica o uso de 
    Templates */

#include <iostream>
using namespace std;

    /* Estruturas */
template <typename T>
struct Elemento{
    T value;

    /* Construtor */
    Elemento(T value = 0){
        this->value = value;
    }   

    /* Métodos */
    T getValue(){
        return this->value;
    }
};

    /* Funções */
template <typename T>
T soma(T first, T second){
    return first + second;
}
template <typename T>
T procriar(T macho, T femea){
    if((macho.sexo() == 'M') && (femea.sexo() == 'F'))
        return macho + femea;
}

int main(){
    
    return 0;
}