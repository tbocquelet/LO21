#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class ComputerException {
	string info;
public:
	ComputerException(const string& str):info(str){}
	string getInfo() const { return info; }
};

class Expression {
    int value;
    // comme on declare le constructeur de recopie et l'operateur d'affectation sans les definir, le compilateur n'en genere plus par defaut 
    // donc ca plante lorsqu'on essaye d'affecter une expression a une autre (en plus c'est prive==> affectation par le biais d'ExpressionManager)
    Expression& operator=(const Expression& e); // ajoutee pour l'exo
    Expression(const Expression &e); // ajoutee pour l'exo
    Expression(int v) : value(v) {} // on interdit a tout le monde de creer des Expressions
    friend class ExpressionManager; // on donne un acces aux membres prives donc aux constructeurs et operateur d'affectation. 
    // Il n'y a plus que ExpressionManager qui peut creer un objet Expression
public:
    int getValue() const { return value;}
    string toString() const;
};

class ExpressionManager {
    //static ExpressionManager* instance; // declaration de notre instance pour le singleton - 1ere implementation
    Expression ** exps; // Tableau de pointeurs vers des Expressions, vide initialement
    unsigned int nb;  // Nombre d'adresses sauvegardées dans le tableau
    unsigned int nbMax; // Nombre max d'adresses que peut contenir le tableau
    void agrandissementCapacite(); // Agrandir la capacité de stockage du tableau
    ExpressionManager();
    ExpressionManager(const ExpressionManager & m); // constructeur par recopie
    ~ExpressionManager();
    ExpressionManager & operator=(const ExpressionManager & m); // redefinition de l'operateur d'affectation pour la classe ExperessionManager
    // operator= ne sert plus a rien si on a qu'un seul objet de la classe 

    // on encapsule notre instance dans un objet interne de type handler - 3eme implementation
    struct Handler{
        ExpressionManager* instance;
        Handler():instance(nullptr){}
        ~Handler(){delete instance;}
    };
    static Handler handler;

public: // deplacement de la partie publique
    static ExpressionManager& getInstance(); // methode statique renvoyant l'instance unique de la classe - toutes implementation - pour les 3 implementations
    static void libererInstance(); // methode statique liberant la memoire allouee dynamiquement lors de la creation de l'instance - 1ere et 3eme implementation 
    Expression & addExpression(int v); // Crée une expression et ajouter un pointeur vers celle-ci dans exps
    void removeExpression(Expression& e); // Supprime du tableau le pointeur vers e

// QUESTION 4
    class iterator {
        Expression** current; // element en cours
        iterator(Expression** c): current(c){}
        friend class ExpressionManager; // pour acceder au constructeur prive sur Expression
    public:
        iterator& operator++(){
            ++current; // pointeur vers l'element suivant du tableau
            return *this; // this : pointeur vers l'objet appelant de la methode
        }
        Expression& operator*() const{ // droit en lecture-ecrite ici comme on renvoit une reference
            return **current;
        }
        bool operator!=(iterator it) const{
            return current!=it.current; // on regarde s'ils en sont a la meme adresse memoire, comparaison avec m.end !
        }
    };
    iterator begin(){return iterator(exps);}
    iterator end(){return iterator(exps+nb);}

    class const_iterator{
        Expression** current; // element en cours
        const_iterator(Expression** c): current(c){}
        friend class ExpressionManager; // pour accepter au constructeur prive sur Expression
    // on veut un acces uniquement en lecture
    public:
        const Expression& operator*() const {return **current;} // renvoie un objet constant non modifiable
        bool operator!=(const_iterator it) const {
            return current!=it.current;
        }
        const_iterator& operator++(){
            ++current;
            return *this;
        }
    };
    const_iterator begin() const{return const_iterator(exps);} 
    // comment differencier les deux methodes ? on indique qu'elles ne modifient pas l'objet appelant => permet a l'ordi de resoudre le conflit
    const_iterator end() const{return const_iterator(exps+nb);}

// QUESTION 3
    // design pattern ITERATOR
    class Iterator{ // objectif : afficher la valeur de chaque expression
        Expression** currentExp; // element en cours
        unsigned int nbRemain; // nombre d'elements qu'il reste a parcourir
        Iterator(Expression** u, unsigned nb):currentExp(u), nbRemain(nb){}
        friend class ExpressionManager;
    public:
        bool isDone() const {return nbRemain==0;} // indique si on a finit de parcourir tous les elements
        void next(){ // acceder a l'expression suivante
            if (isDone()){
                throw ComputerException("error, next on an iterator which is done");
            }
            nbRemain--; // il reste un element au moins a parcourir
            currentExp++; // acces a l'element suivant
        }
        Expression & current() const{ // renvoie l'element courant 
            if(isDone()){
                throw ComputerException("error, indirection on an iterator which is done");
            }
            return **currentExp;
        }
    };
    Iterator getIterator(){ // cree un objet iterator
        return Iterator(exps,nb);
    }
};

class Item {
    Expression * exp;
public:
    Item() : exp(0) {}
    void setExpression(Expression & e) { exp=&e;}
    void raz() { exp=0;}
    Expression & getExpression() const;
};


class Pile {
    Item* items; // Tableaux d'items
    unsigned int nb; // Nombre d'item faisant partie de la pile dans le tableau
    unsigned int nbMax; // Nombre max d'item que peut contenir le tableau
    string message; // Contient le message sur l'état de la pile pour l'utilisateur
    void agrandissementCapacite(); // Agrandir la capacité de stockage du tableau
    unsigned int nbAffiche; // Nb d'item à afficher au max 
    public:
    Pile():items(0),nb(0),nbMax(0),message(""),nbAffiche(4){}
    ~Pile();
    void push(Expression& e); // Empile une nouvelle expression dans items
    void pop(); // Depile l'item au somme de la pile
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    void affiche() const; // Affiche un message et l'état de la pile 
    Expression& top() const;
    void setNbItemsToAffiche(unsigned int n) { nbAffiche=n; }
    void setMessage(const string& m) { message=m; }
    string getMessage() const { return message; }
};

class Controleur {
    ExpressionManager& expMng; // Gestionnaire d'expressions (création, suppression)
    Pile& expAff; // Stocke les entrées/sorties (Expressions empilées et messages pour l'utilisateur)
public:
    Controleur(ExpressionManager& m, Pile& v):expMng(m), expAff(v){} // constructeur
    void commande(const string& c); // Gère la saisie par l'utilisateur d'un nouveau caractère (Expression ou Operateur)
    void executer(); // Méthode principale appelée depuis le main
};

#endif
