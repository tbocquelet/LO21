#include "computer.h"

#include <cstring>
#include <stdexcept>
#include <iostream>

using namespace std;
 

///////////////////////////////////////////////////////////////////
/////////////////// DEBUT singleton pattern ///////////////////////
///////////////////////////////////////////////////////////////////

// PREMIERE IMPLEMENTATION

/*ExpressionManager* ExpressionManager::instance=nullptr;

ExpressionManager& ExpressionManager::getInstance() {
    if(instance==nullptr){
        instance=new ExpressionManager;
    }
    return *instance;
}

void ExpressionManager::libererInstance(){
    // liberation de la memoire
    delete instance; // si on le mettait dans le destructeur, on aurait des appels recursifs du destructeur car cela appelerait le destructeur d'ExpressionManager
    // retour a nullptr
    instance=nullptr;
}
*/

// SECONDE IMPLEMENTATION

/*
on fera appel au destructeur de la classe normalement 

ExpressionManager& ExpressionManager::getInstance() {
    static ExpressionManager instance;
    return instance;
}
*/

// TROISIEME IMPLEMENTATION

ExpressionManager::Handler ExpressionManager::handler=ExpressionManager::Handler();

ExpressionManager& ExpressionManager::getInstance(){
    if(handler.instance==nullptr){
        handler.instance=new ExpressionManager;
    }
    return *handler.instance;
}

void ExpressionManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}

///////////////////////////////////////////////////////////////////
/////////////////// FIN singleton pattern /////////////////////////
///////////////////////////////////////////////////////////////////


string Expression::toString() const {
    stringstream s;
    s<<value; // conversion de int vers stringstrem
    return s.str(); // conversion implicite en str ?

}

ExpressionManager::ExpressionManager() : exps(0), nb(0), nbMax(0) {
   
}

/*
// pour ce constructeur de recopie, on veut que les expressions ont des adresses differentes pour chaque ExpressionManager ?
ExpressionManager::ExpressionManager(const ExpressionManager & m) :  // constructeur par recopie
    exps(new Expression*[m.nbMax]), // Allocation mémoire   penser a la syntaxe du constructeur, c'est comme si on avait exps=new Expression*[m.nbMax]
    nb(m.nb),  // Initialisation de nb avec m.nb
    nbMax(m.nbMax) { // Initialisation de nbMax avec m.nbMax
    for(unsigned int i=0; i<nb;i++) {
        exps[i] = new Expression(*m.exps[i]); // Appel du constructeur de recopie de l'expression, on alloue une nouvelle adresse a cette valeur ?
    
    }
}
*/

ExpressionManager::~ExpressionManager() { // besoin d'un destructeur car alloue dynamiquement
    for(unsigned int i=0; i<nb; i++) {
        delete exps[i]; // Supprime les pointeurs créés via l'operateur new
    }
    delete[] exps; // Supprime le tableau de pointeurs vers les expressions

}

/* 

On commente car on utilise l'operateur de recopie de Expression dans cette classe. Or on ne la pas definit donc ca va planter. En effet,
le compilateur n'en genere plus un par defaut comme on en a declare un. C'est malin !
De plus cette operation n'a plus de sens comme on a un singleton d'ExpressionManager.


ExpressionManager & ExpressionManager::operator=(const ExpressionManager & m) {
    // nouvelleExpressionManager=m;
    if(this==&m) return *this; // Si l'objet en param et l'objet designé par this, il s'agit du même objet, rien à faire
    // En plus des opérations de recopie, il faut libérer la mémoire occupée par notre tableau exps
    // si nouvelleExpressionManager possedait un tableau exps, on va vouloir le remplacer, donc il faudra le liberer
    Expression ** newtab = new Expression*[m.nbMax]; // Création d'un nouveau tableau
    for(unsigned int i=0; i<nb; i++) {
        newtab[i]=new Expression(*m.exps[i]); // Appel du constructeur de recopie de l'expression
    }
    Expression ** old=exps; // Sauvegarde de l'ancien tableau pour libération de la mémoire
    int oldnb=nb; // Sauvegarde de la taille de l'ancien tableau pour libération de la mémoire
    exps = newtab; // Mise à jour des attributs
    nb=m.nb;
    nbMax=m.nbMax;
    // Il reste à libérer la mémoire occupée par notre ancien tableau args de nouvelleExpressionManager
    for(unsigned int i=0; i<oldnb; i++) {
        delete old[i];
    }
    delete[] old;
    return *this;
}
*/


void ExpressionManager::agrandissementCapacite() {
    nbMax =(nbMax+1)*2; // Nouvelle capacité max ciblée
    Expression ** newtab = new Expression*[nbMax]; // Crée un nouveau tableau en doublant la taille
    std::memcpy(newtab, exps, nb*sizeof(Expression*)); // Copie du tableau de pointeurs, on copie exps dans newtab
    
    Expression ** old = exps; // Sauvegarde pour appel à l'opérateur delete[]
    exps = newtab; // Remplace l'ancien tableau par le nouveau
    delete old;
}

Expression & ExpressionManager::addExpression(int v) {
    if(nb>=nbMax) { // Si la capacité du tableau est atteinte
        agrandissementCapacite(); // Augmente la capacité du tableau
    }
    exps[nb++] = new Expression(v); // Ajout d'un pointeur vers nouvelle expression 
    for(int i=0; i<nb; i++) { // Affiche les nbAffiche premières expressions de la pile
    	cout << exps[i]->getValue() << " ";
    }
    cout << endl;
    return *exps[nb-1]; // Retour par référence de l'expression (-1 car le tableau commence a 0)
}
void ExpressionManager::removeExpression(Expression& e) {
    unsigned int i=0;
    while(i<nb && exps[i]!=&e) { // Compare l'adresse de l'expression avec les adresses du tableau
    	i++;
    }
    if(i==nb) { // Si on a bouclé jusqu'à nb, l'expression n'a pas été trouvée
        throw ComputerException("elimination d'une Expression inexistante"); // throw donc le reste n'est pas execute
    }
    delete exps[i]; // Libération mémoire
    i++; // Regarde l'adresse qui suit l'adresse de l'expression qu'on vient de supprimer
    while(i<nb) { // Décale toutes les adresses de une case pour "boucher" le trou de l'adresse supprimée
        exps[i-1] = exps[i];
        i++;
    }
    nb--; // Le tableau a une expression en moins

    for(int i=0; i<nb; i++) { // Affiche les nbAffiche premières expressions de la pile
    	cout << exps[i]->getValue() << " ";
    }
    cout << endl;


}

Expression & Item::getExpression() const {
    if(exp==0) throw ComputerException("Item : tentative d'accès à une expression inexistante");
    return *exp;

}

/**
 * Même fonctionnement que agrandissementCapacite définie dans ExpressionManager
 */
void Pile::agrandissementCapacite() {
    Item* newtab=new Item[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=items[i];
    Item* old=items;
    items=newtab;
    nbMax=(nbMax+1)*2;
    // ici pas besoin de faire un delete pour chaque element, ils ne sont pas alloues dynamiquement
    delete[] old;
}

/**
 * Ajoute une expression dans le tableau
 */
void Pile::push(Expression& e){
    if (nb==nbMax) agrandissementCapacite(); // Augmente si besoin la taille allouée
    items[nb].setExpression(e); // Renseigne l'expression
    nb++; // Incrémente le nombre d'expressions
}
void Pile::pop(){
    nb--; // Décrémente le nombre d'expressions
    items[nb].raz(); // Vide l'expression contenue dans le dernier emplacement
}
void Pile::affiche() const{
    cout<<"********************************************* \n";
    cout<<"M : "<<message<<"\n"; // Affiche le message
    cout<<"---------------------------------------------\n";
    for(int i=nbAffiche; i>0; i--) { // Affiche les nbAffiche premières expressions de la pile
        if (i<=nb) cout<<i<<": "<<items[nb-i].getExpression().toString()<<"\n";
        else cout<<i<<": \n";
    }
    cout<<"---------------------------------------------\n";
}

Expression& Pile::top() const {
    if (nb==0) throw ComputerException("aucune expression sur la pile");
    return items[nb-1].getExpression();
}


Pile::~Pile() {
    // on a declare un tableau d'items, il suffit juste de desalloue ce tableau sans devoir desalloue chaque item !
    delete[] items;
}

/**
 * Indique si l'utilisateur a saisi un opérateur géré
 */
bool estUnOperateur(const string& s){
    if (s=="+") return true;
    if (s=="-") return true;
    if (s=="*") return true;
    if (s=="/") return true;
    return false;
}
/**
 * Indique si l'utilisateur a saisi un nombre
 */ 
bool estUnNombre(const string& s){
    try{
        stoi(s); // Exception levée si la string n'est pas convertible en int, juste un test, la conversion n'est pas stockee
        return true;
    }catch(std::invalid_argument& e){
        return false;
    }
}

/*
 
bool estUnNombre(const string& s){
    if (strtol(s.c_str(), NULL, 0)!=0) {
        return true;
    }
    else {
        return false;
    }
}
    
*/

/**
 * Gère la saisie d'un caractère par l'utilisateur
 */
void Controleur::commande(const string& c){
    if (estUnNombre(c)){ // Si c'est un nombre
        // Création d'une expression représentant ce nombre
        // Ajout de l'expression dans la pile
        expAff.push(expMng.addExpression(stoi(c)));
    }else{
        if (estUnOperateur(c)){ // Si c'est un opérateur
            if (expAff.taille()>=2) { // On ne gère que des opérateurs binaires, il faut donc 2 expressions dans la pile
                // variable 2
                int v2=expAff.top().getValue(); // Récupération de l'expression au sommet de la pile
                expMng.removeExpression(expAff.top()); // On la supprime
                expAff.pop(); // On la retire de la pile
                // variable 1
                int v1=expAff.top().getValue(); // Récupération de la nouvelle expression au sommet de la pile
                expMng.removeExpression(expAff.top());
                expAff.pop();

                int res;
                if (c=="+") res=v1+v2; // On effectue le calcul en fonction de l'opérateur choisi par l'utilisateur
                if (c=="-") res=v1-v2;
                if (c=="*") res=v1*v2;
                if (c=="/") res=v1/v2;

                Expression& e=expMng.addExpression(res); // Création de l'expression résultat du calcul
                expAff.push(e); // Ajout à la pile
            }else{
                // Message de Pile rempli : Appel d'un opérateur avec moins de 2 expressions dans la pile
                expAff.setMessage("Erreur : pas assez d’arguments"); 
                
            }
        }else{
            // Message de Pile rempli : le caractère saisi n'a pas été reconnu
            expAff.setMessage("Erreur : commande inconnue");
        }
    }
}
/** 
 * Méthode principale
 * Gère toute la saisie utilisateur et effectue le calcul
 */
void Controleur::executer(){
    string c;
    do {
        expAff.affiche(); // Affichage du message sur l'état courant et les valeurs de la pile
        cout<<"?-";
        cin>>c; // Récupération de la saisie utilisateur
        if (c!="Q") commande(c); // Le caractère Q est le caractère de fin de saisie
    }while(c!="Q");
}






