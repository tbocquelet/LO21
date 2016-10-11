#ifndef _Vector_T_H
#define _Vector_T_H

#include "contener.h"

namespace TD {

template<class T>
// Vector "est un" Contener
class Vector : public Contener<T> {
private:
  // Pointe sur un tableau de T alloué dynamiquement
  T * tab;
  // Capacité du tableau (!= nbEl)
  unsigned int cap;
public:
  /**
   * n : nombre d'éléments, 0 par défaut
   * x : valeur initiale des éléments, constructeur sans arg par défaut
   */
  Vector(unsigned int n=0, const T & x=T()); 
  ~Vector(); // Destructeur
  Vector(const Vector<T> & v); // Constructeur par recopie
  Vector<T> & operator=(const Vector<T> & v); // Opérateur d'affectation
  // Les opérateurs[] n'effectuent pas de contrôle et ne lèvent pas d'exception même si l'indice passé en paramètre est aberrant
  T & operator[](unsigned int i) { return tab[i]; }
  const T & operator[](unsigned int i) const { return tab[i]; }
  // element effectue un contrôle sur l'indice passé en paramètre et lève une exception si nécessaire
  T & element(unsigned int i);
  const T & element(unsigned int i) const;
  void push_back(const T & x);
  void pop_back();
  void clear();

  // Implémentation du pattern iterator
  class iterator {
    T * courant;
  public:
    iterator(T * c=0) : courant(c) {}
    iterator & operator++() {  courant++; return *this; } // Opérateur prefixe
    iterator operator++(int) { iterator tmp= *this; courant++; return tmp;} // Opérateur postfixe
    bool operator==(const iterator & it) const { return courant==it.courant; }
    bool operator!=(const iterator & it) const { return courant!=it.courant; }
    const T& operator*() const { return *courant; }
    T& operator*() { return *courant; }
  };
  iterator begin() { return iterator(tab); }
  iterator end() { return iterator(tab+Contener<T>::nbEL); }
};

} // fin du namespace TD

template<class T>
TD::Vector<T>::Vector(unsigned int n, const T & x) :
  Contener<T>(n), // Constructeur de la classe de base
  tab(new T[n]), // Allocation mémoire pour n éléments de type T
  cap(n) { // La zone mémoire peut accueillir n éléments au plus
  // Initialisation avec la valeur de x
  // Accès direct à attribut de la classe de base refusé
  // Accès à l'attribut de la classe de base via opérateur de résolution de portée ::
  for(unsigned int i=0; i<Contener<T>::nbEl;i++) {
    tab[i] = x;
  }
}

template<class T>
TD::Vector<T>::~Vector() {
  delete[] tab;
}

template<class T>
TD::Vector<T>::Vector(const TD::Vector<T> & t) :
  Contener<T>(t.size()), // Constructeur de la classe de base
  tab(new T[t.size()]),
  cap(t.size()) {
  // Recopie des éléments contenus dans t
  for(unsigned int i=0; i<t.size(); i++) {
    tab[i] = t.tab[i];
  } 
}

template<class T>
TD::Vector<T> & TD::Vector<T>::operator=(const TD::Vector<T> & t) {
  if(this != &t) { // Rien à faire si this == &t
    T * newtab = new T[t.size()]; // Allocation mémoire d'une zone permettant de recopie les valeurs des éléments contenus dans t
    // Recopie des éléments contenus dans t
    for(unsigned int i=0; i<t.size(); i++) {
      newtab[i] = t.tab[i]; // Recopie des éléments de t
    } 
    Contener<T>::nbEl=t.nbEl;
    cap = t.cap;
    T* old= tab; // Sauvegarde de l'adresse vers l'ancien tableau
    tab = newtab;
    delete[] old; // Libération de la zone mémoire allouée à l'ancien tableau
  }
  return *this;
}

template<class T> T& TD::Vector<T>::element(unsigned int i) {
  if(i<Contener<T>::nbEl) return tab[i];
  throw ContenerException("erreur Vector : demande hors limite");
}

template<class T> const T& TD::Vector<T>::element(unsigned int i) const {
  if(i<Contener<T>::nbEl) return tab[i];
  throw ContenerException("erreur Vector : demande hors limite");
}

template<class T> void TD::Vector<T>::push_back(const T & x) {

  if(Contener<T>::nbEl==cap) {
    T * newtab = new T[cap+5]; // ALlocation mémoire
    for(unsigned int i=0; i<Contener<T>::nbEl; i++) { // Recopie des valeurs
      newtab[i] = tab[i];
    }
    T * old = tab; // Libération mémoire
    tab = newtab;
    delete[] old;
    cap+=5;
  }

  // Ajout de l'élément en dernière position
  tab[Contener<T>::nbEl]=x;
  Contener<T>::nbEl++;
}

template<class T> void TD::Vector<T>::pop_back() {
  if(!this->empty())  {
    Contener<T>::nbEl--;
  } else {
    throw ContenerException("erreur Vector : Vector vide");
  }
}

template<class T> void TD::Vector<T>::clear() {
  Contener<T>::nbEl = 0;
}


#endif
