#include "vector.h"
#include "stack.h"
#include "vectorAll.h"
#include <iostream>

using namespace TD;


template<typename T> void afficher(const Contener<T> & c) {
  for(unsigned int i=0; i<c.size(); i++) {
    std::cout << c.element(i) << " ";
  }
  std::cout << std::endl;
}

// Créer une fonction de comparaison de 2 entiers
// Renvoie vrai si l'entier en premier paramètre est plus petit que l'entier en second paramètre
bool inf(int a, int b) { return a<b; }


// Créer un objet fonction de 2 entiers
// Contient un attribut bool
//  Renvoie vrai si l'entier en premier paramètre est plus petit que l'entier en second paramètre et si l'attribut est VRAI
// Renvoie vrai si l'entier en premier paramètre est plus grand que l'entier en second pparamètre et si l'attribut est FAUX
class Comparateur {
  bool cmp;
public:
  Comparateur(bool o=true) : cmp(o) {}
  bool operator()(int a, int b) {if(cmp) return a<b; else return a>b; }
};



int main() {
 
    VectorAll<int> v1(10, 5);
    std::cout << "v1(10,5)" << std::endl;
    afficher(v1);
    // Ajout de la valeur 3
    v1.push_back(3); 
    std::cout << "v1.push_back(3)" << std::endl;
    afficher(v1);
    // Ajout de la valeur 9 en 4ème position
    v1[3] = 9;
    std::cout << "v1[3] = 9" << std::endl;
    afficher(v1);
    // Suppression des 4 dernières valeurs
    for(unsigned int i=0; i<4; i++) {
        v1.pop_back();
        std::cout << "v1.pop_back()" << std::endl;
        afficher(v1);
    }

    Vector<int> v2(3, 9);
    // Vide le tableau
    v2.clear();
    std::cout << "v2.clear()" << std::endl;
    afficher(v2);
    // Reconstruction avec 30 valeurs de 0 à 29
    for(unsigned int i=0; i<30; i++) {
        v2.push_back(i);
    }
    std::cout << "v2.push_back(i) // i de 0 à 29"<< std::endl;
    afficher(v2);




  return 0;
}
