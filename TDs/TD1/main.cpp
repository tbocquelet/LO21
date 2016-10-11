#include "fonction.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    // exercice 1
    //bonjour();
    
    // exercice 5
    //exerciceA();
    
    // exercice 6
    double x=3.14;
    cout<<"Valeur de x: "<<x<<"\n";
    
    double y;
    cout<<"Valeur de y avant affectation : "<<y<<"\n";
    y=3.14;
    cout<<"Valeur de y apres affectation : "<<y<<"\n";
    
    // exercice 7
    const double pi=3.14;
    cout<<"Valeur de pi : "<<pi<<"\n";
    // pi=2; bug
    
    // exercice 9
    exercice_surcharge();
    
    // quelles sont les fonctions qui ont le bon nombre de parametres ?
    // quelle est la meilleure conversion a faire ? float vers double ou float vers int ? on selectionne celle avec float vers double car plus simple etc
    
    // exercice 10
    
    // T const* l; objet pointe non modifiable
    // const T* l; objet pointe non modifiable
    // T* const p; pointeur non modifiable
    
    // const int* ptc=&i;   *ptc=7; erreur  ptc=&j; OK
    // int* const ptc=&i;   *ptc=18; OK     ptc=&j; erreur
    // const int* const ptc=&i; *ptc=4; erreur      ptc=&j; erreur
    
    double* pt1=4096; // bug car n'est pas un float
    double* pt2=(double*)4096; // le pointeur pointe sur 4096
    void* pt3=pt1; // conversion implicite de double* en void*
    pt1=pt3; // non car conversion non implicite
    pt1=(double*)pt3; // conversion explicite de void* en double*
    double d1=36;
    const double d2=36;
    double* pt4=&d1; // initialisation d'un pointeur double*
    const double* pt5=&d1;
    *pt4=2.1; // ok, on peut modifier la valeur pointee
    *pt5=2.1; // erreur, on ne peut pas modifier la valeur pointee
    pt4=&d2;  // ok on peut modifier la valeur du pointeur mais on ne peut pas assigner un const a un pointeur non constant
    pt5=&d2; // ok on peut modifier la valeur du pointeur
    double* const pt6=&d1;
    pt6=&d1; // erreur car la valeur du pointeur est constante
    *pt6=2.78; // ok
    double* const pt6b=&d2; // erreur, on ne peut pas modifier la valeur du pointeur
    const double* const pt7=&d1;
    pt7=&d1; // impossible, tout est constant
    *pt7=2.78; // impossible, tout est constant
    double const* pt8=&d1; // equivalent a const double* pt8=&d1;
    pt8=&d2; // ok
    pt8=&d1; // ok conversion implicite
    *pt8=3.14; // impossible, on ne peut pas modifier la valeur pointee
    
    
    return 0;
}




