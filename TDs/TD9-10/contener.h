#if !defined(_Contener_T_H)
#define _Contener_T_H

#include <string>
#include <stdexcept>

namespace TD {

  class ContenerException : public std::exception {
    protected :
    std::string info;
    public:
    ContenerException(const std::string& i="") throw() :info(i){}
    const char * what() const throw() { return info.c_str(); }
    ~ContenerException()throw(){}
  };
  // Interface commune à tous les contenurs
  // Patro de classe : Le paramètre T désigne le type d'objet stocké dans notre conteneur
  template<class T>
  class Contener {
  protected:
    unsigned int nbEl; // Nombre d'éléments contenus dans notre conteneur
  public:
    // Constructeur
    Contener(unsigned int n) : nbEl(n) {}

    // Pas besoin de redéfinir les méthodes dans les classes dérivées
    // Elles ne sont donc pas virtual
    unsigned int size() const { return nbEl;}
    bool empty() const { return nbEl==0;}

    // Ces méthodes pourront être définies en s'appuyant sur la méthode element et la méthode pop_back (Pattern Template Method)
    // Elles sont virtuelles pour laisser la possibilité aux classes dérivées de fournir une implémentation plus adaptée (optimisée)

    // Renvoie le premier élément contenu dans notre conteneur
    virtual T & front();
    virtual const T & front() const;
    // Renvoie le dernier élément
    virtual T & back();
    virtual const T & back() const;
    // Vide la liste d'éléments
    virtual void clear();
    
    // Méthodes à définir dans les classes dérivées
    virtual T & element(unsigned int i) = 0;
    virtual const T & element(unsigned int i) const = 0;
    // Ajoute un élément en dernière position
    virtual void push_back(const T & x) = 0;
    // Supprime l'élément en dernière position
    virtual void pop_back() = 0;

    virtual ~Contener() {};
  };
}
// Définitions des méthodes non inlines figurent dans le fichier header
// Chaqueméthode non inline doit être précédée de "template" suivi des paramètres entre chevrons
template<class T> T& TD::Contener<T>::front() {
 if(!empty()) { // Si le conteneur contient au moins 1 élément (n'est pas vide)
   return element(0);
 } else { // Si aucune élément
  throw ContenerException("erreur Contener : demande hors limite");
 }
}

template<class T> const T& TD::Contener<T>::front() const {
 if(!empty()) // Si le conteneur contient au moins 1 élément (n'est pas vide)
   return element(0);
 throw ContenerException("erreur Contener : demande hors limite");
}

template<class T> T& TD::Contener<T>::back() {
  if(!empty()) return element(nbEl-1); // Les éléments sont indicés à partir de 0
  throw ContenerException("erreur Contener : demande hors limite");
}

template<class T> const T& TD::Contener<T>::back() const {
  if(!empty()) return element(nbEl-1); // Les éléments sont indicés à partir de 0
  throw ContenerException("erreur Contener : demande hors limite");
}

template<class T>
void TD::Contener<T>::clear() {
  while(!empty()) {
    pop_back();
  }
}



#endif
