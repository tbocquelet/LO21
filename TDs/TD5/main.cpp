#include "computer.h"
#include <iostream>

// g++ *.cpp -std=c++11

using namespace std;

int main(){
    try {
    ExpressionManager& expMng=ExpressionManager::getInstance(); // singleton pattern

    Pile expAff;
    Controleur controleur(expMng,expAff);
    expAff.setMessage("Bienvenue");
    controleur.executer();
    for(ExpressionManager::iterator it=expMng.begin();it!=expMng.end();++it){ 
// si on fait const_iterator... la methode end choisit va etre celle de l'iterator donc ca va planter. Correction ? declarer un objet expMng de type const. 
// sinon on peut aussi faire un constructeur const_iterator(const iterator& it) 
        std::cout<<(*it).toString()<<"\n";
    }

    } catch(ComputerException& e) {
        cout << e.getInfo();
    }
    ExpressionManager::libererInstance(); // singleton pattern
    // c'est a nous d'appeller libererInstance ce qui est dommage. De plus, si il y a une erreur avant (try), la memoire ne sera pas liberee
    return 0;
}
