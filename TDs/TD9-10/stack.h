#ifndef _Stack_T_H
#define _Stack_T_H

namespace TD {

// Adaptateur de classe 
template<class T>
class Stack1 : private Vector<T> { // Relation "est implémenté en terme de"
public:
  Stack1():Vector<T>(0) {}  // La pile est initialement vide
  void push(const T & x) { Vector<T>::push_back(x); }
  void pop() { Vector<T>::pop_back();  }
  const T & top() const { return Vector<T>::back(); } // Renvoie le dernier élément ajouté à tab 
  T & top() {  return Vector<T>::back(); }
  bool empty() { return Vector<T>::empty();  } 
  void clear() { Vector<T>::clear(); }
};

// Généralisation de l'adaptation à n'importe quelle classe conteneur
template<class T, class CONT=Vector<T> > // Conteneur à utiliser par défaut
class Stack2 : private CONT {
public:
  Stack2(): CONT(0) {}
  void push(const T& x) { CONT::push_back(x); }
  void pop() { CONT::pop_back(); }
  const T & top() const { return CONT::back(); }
  T & top() { return CONT::back(); }
  // L'instruction using introduit un membre de la classe de base dans la classe dérivée
  using CONT::empty;
  using CONT::clear;
  // Implémentation du pattern iterator via adaptateur d'objet
 /** class iterator {
    // Par défaut, le compilateur considère  qu'un identificateur dépendant d'un paramètre de type (CONT) n'est PAS un type
    // Il est nécessaire d'utiliser le mot clé typename pour le lui indiquer
    typename CONT::iterator courant;
  public:
    iterator(typename CONT::iterator c) : courant(c) {}
    iterator & operator++() {  ++courant; return *this; }
    iterator operator++(int) { iterator tmp=*this; courant++; return tmp;   }
    bool operator==(const iterator & it) const { return courant==it.courant;     }
    bool operator!=(const iterator & it) const { return courant!=it.courant; }
    T & operator*() {  return *courant;    }
    const T & operator*() const { return *courant; }
  };
  iterator begin() { return iterator(CONT::begin()); }
  iterator end() { return iterator(CONT::end()); }
  */

  /**
  class iterator : public CONT::iterator {
     iterator(typename CONT::iterator c) : CONT::iterator(c) {}
  };
  iterator begin() { return iterator(CONT::begin()); }
  iterator end() { return iterator(CONT::end()); }
  */
  
  // Implémentation du pattern iterator via isntruction using
  // Using introduit un nom déclaré dans la classe de base dans la région de déclaration où il apparait
  // Rappel : l'instruction typename doit être précisée lorsqu'on fait référence à un type défini dans un type générique (ici dans CONT)
  using typename CONT::iterator;
  // using typename CONT::const_iterator;
  using CONT::begin;
  using CONT::end;


};

template<class T, class CONT=Vector<T> >
class Stack3 {
  CONT cont;
public:
  Stack3():cont(0){}
  void push(const T & x) { cont.push_back(x); }
  void pop() { cont.pop_back(); }
  const T & top() const { return cont.back(); }
  T & top() { return cont.back();}
  bool empty() { return cont.empty(); }
  void clear() { cont.clear(); }
};


}
#endif
