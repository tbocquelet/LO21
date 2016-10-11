#include "fonction.h"

using namespace std;

// exercice 1
void bonjour() {
    cout<<"Entrez votre prenom : "; 
    string prenom;
    cin>>prenom;
    cout<<"Bonjour "<<prenom<<"\n";
}

// exercice 5
void exerciceA() {
    int r;
    double p, s;
    cout<<"Donnez le rayon entier d’un cercle : ";
    cin>>r;
    const float PI=3.14159;
    p=2*PI*r;
    s=PI*r*r;
    cout<<"Le cercle de rayon "<<r<<" a un perimetre de "<<p<<" et une surface de "<<s<<"\n";
}

// exercice 9
int fct(int x){
    std::cout<<"1:"<<x<<"\n";
    return 0;
}

int fct(float y){
    std::cout<<"2:"<<y<<"\n";
    return 0;
}

int fct(int x, float y){
    std::cout<<"3:"<<x<<y<<"\n";
    return 0;
}

float fct(float x, int y){
    std::cout<<"4:"<<x<<y<<"\n";
    return 3.14;
}

void exercice_surcharge(){
    int i=3,j=15;
    float x=3.14159,y=1.414;
    char c='A';
    double z=3.14159265;
    fct(i); //appel 1               res : 1:3
    fct(x); //appel 2               res : 2:3.14159
    fct(i,y); //appel 3             res : 3:31.414
    fct(x,j); //appel 4             res : 4:3.1415915
    fct(c); //appel 5               res : 1:65
    fct(i,static_cast<float>(j)); //appel 6      // on cast car il n'a pas de fonction correspondant aux types des parametres initiaux
    fct(static_cast<float>(i),static_cast<int>(c)); //appel 7
    fct(i,z); //appel 8             res : 3:33.14159
    fct(z,static_cast<int>(z)); //appel 9
}



