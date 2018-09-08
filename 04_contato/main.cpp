#include <iostream>
#include "sstream"
#include <iomanip>
#include <vector>


/*  setw e setprecision
    static method
*/

using namespace std;

int main(){
    // mary vivo:1234 home:4321 work:4444 vivo:1235

   // string line;
  //  getline(cin, line);
  //  stringstream ss(line);
   // string word;
    
    // Retirar informações que forem inseridas de forme serial
   /* while(ss >> word){

        stringstream ss(word);
        string nome, fone;
        getline(ss, nome ':';
        getline(ss, fone))
    }*/

    vector<int> vetor;

    vetor.push_back(2);

    
    for(auto elemento : vetor){
        cout << elemento << endl;
    }

    //cout << fixed << setprecision(5) << 2344.5932489 << endl;

    return 0;
}