#ifndef _VectorAll_T_H
#define _VectorAll_T_H

#include "contener.h"

namespace TD {

// VectorAll "est un" Contener
template<class T>
class VectorAll : public Contener<T> {
private:
    // Pointe sur un tableau de T alloué dynamiquement
    T * tab;
    // Capacité du tableau (peut être différent de nbEl)
    unsigned int cap;
    std::allocator<T> mem; // Allocator
    void reserve(unsigned int n);
    void resize(unsigned int s=0, const T  & initialize_with=T());
public:
    /**
     * n : nombre d'éléments, 0 par défaut
     * x : valeur initiale des éléments, appel au constructeur sans arg par défaut (nécessite l'existant d'un tel
     * constructeur !)
     */
    VectorAll(unsigned int n=0, const T & x=T());
    ~VectorAll();
    VectorAll(const VectorAll<T> & v);
    VectorAll<T> & operator=(const VectorAll<T> & v);
    T & operator[](unsigned int i) { return tab[i]; }
    const T & operator[](unsigned int i)const { return tab[i]; }
    T & element(unsigned int i);
    const T & element(unsigned int i) const;
    void push_back(const T & x);
    void pop_back();
    void clear();

    // Implémentation du pattern iterator
    class iterator {
      T * courant; // Pointeur vers l'élément courant
    public:
      iterator(T * c=0) : courant(c) {}
      iterator & operator++() { courant++; return *this; } // Opérateur postfixe
      iterator operator++(int) { iterator tmp = *this; courant++; return tmp; } // Opérateur prefixe renvoie une copie avant incrémentation
      bool operator==(const iterator & it) const { return courant==it.courant; }
      bool operator!=(const iterator & it) const { return courant!=it.courant; }
      T& operator*() const { return *courant; }
    };
    iterator begin() { return iterator(tab); }
    iterator end() { return iterator(tab+Contener<T>::nbEl); }

    class const_iterator {
      T * courant; // Pointeur vers l'élément courant
    public:
      const_iterator(const T * c=0) : courant(c) {}
      const_iterator & operator++() { courant++; return *this; } // Opérateur postfixe
      const_iterator operator++(int) { const_iterator tmp = *this; courant++; return tmp; } // Opérateur prefixe renvoie une copie avant incrémentation
      bool operator==(const iterator & it) const { return courant==it.courant; }
      bool operator!=(const iterator & it) const { return courant!=it.courant; }
      const T& operator*() const { return *courant; }
    };
    const_iterator begin() const { return iterator(tab); }
    const_iterator end() const { return iterator(tab+Contener<T>::nbEl); }


};
} // fin namespace

template<class T>
TD::VectorAll<T>::VectorAll(unsigned int n, const T & x) : 
    Contener<T>(n), // Constructeur de la classe de base
    cap(n) { // La zone mémoire peut accueillir n éléments au plus
    // allocator permet de décorréler l'allocation mémoire de la construction
    tab=mem.allocate(Contener<T>::size());
    for(unsigned int i=0; i<Contener<T>::nbEl; i++) {
      mem.construct(tab+i, x);
    }
}

template<class T>
void TD::VectorAll<T>::reserve(unsigned int n) {
  if(n>cap) {
    // allocate(taille, adresse début allocation)
    T * newtab=mem.allocate(n-cap, tab+cap); // Alloue la mémoire supplémentaire nécessaire, à la suite si possible, ailleurs sinon
    if(newtab!=tab+cap) { // Si l'allocation a eu lieu ailleurs, ce n'est pas ce qu'on souhaite
        mem.deallocate(newtab, n-cap); // On désalloue cette nouvelle zone
      // deallocate (adresse début, taille)
        newtab=mem.allocate(n); // On alloue une zone suffisament grande pour toute les valeurs
        for(unsigned int i=0; i<Contener<T>::nbEl; i++) {
          mem.construct(newtab+i, tab[i]); // Construction depuis l'ancien élément dans la nouvelle zone mémoire
          mem.destroy(tab+i); // Déstruction de l'ancien élément
        }
        mem.deallocate(tab, cap); // La déstruction et désallocation mémoire sont décorrélés
        tab= newtab;
    } 
    cap=n;
  }
}

template<class T>
void TD::VectorAll<T>::resize(unsigned int s, const T& initialize_with) {
  if(s>Contener<T>::nbEl) { // Si la taille augmente
      reserve(s); // Réservation mémoire effectuées si nécessaire
      for(unsigned int i=Contener<T>::nbEl; i<s; i++) {
        mem.construct(tab+i, initialize_with); // Construction
        Contener<T>::nbEl=s; // Maj du nombre d'éléments
      }
  } else {
    while(Contener<T>::nbEl>s) {
      Contener<T>::nbEl--;
      mem.destroy(tab+Contener<T>::nbEl);
    }
  }
}


template<class T>
TD::VectorAll<T>::VectorAll(const TD::VectorAll<T> & t) :
    Contener<T>(t.size()), // Constructeur de la classe de base
    cap(t.size()) {

    tab=mem.allocate(t.size());
    for(unsigned int i=0; i<t.size(); i++) {
      mem.construct(tab+1, t.tab[i]);
    }
}

template<class T> TD::VectorAll<T>::~VectorAll() {
  clear();
  mem.deallocate(tab, cap);
}

template<class T> T& TD::VectorAll<T>::element(unsigned int i) {
    if(i<Contener<T>::nbEl) return tab[i];
    throw ContenerException("erreur VectorAll : demande hors limite");
}

template<class T> const T& TD::VectorAll<T>::element(unsigned int i) const {
    if(i<Contener<T>::nbEl) return tab[i];
    throw ContenerException("erreur VectorAll : demande hors limite");
}


template<class T>
TD::VectorAll<T> & TD::VectorAll<T>::operator=(const TD::VectorAll<T> & t) {

    if(this!= &t ) { // Rien à faire si this == &t
      for(unsigned int i=0; i<Contener<T>::nbEl;i++) {
        mem.destroy(tab+i);
      }
      Contener<T>::nbEl = t.nbEl; 
      reserve(Contener<T>::nbEl); // Allocation mémoire réalisée si nécessaire
      for(unsigned int i=0; i<Contener<T>::nbEl; i++) {
        // construct (adresse , élément)
        mem.construct(tab+i, t.tab[i]); // Construction des objets en mémoire
      }


    }
    return *this;
}

template<class T> void TD::VectorAll<T>::push_back(const T & x) {
  resize(Contener<T>::nbEl+1, x);    
}

template<class T> void TD::VectorAll<T>::pop_back() {
    // this permet également l'accès aux membres de la classe de base
    if(this->empty()) {
        throw ContenerException("erreur VectorAll : Vector vide");
    }
    Contener<T>::nbEl--;
    mem.destroy(tab+Contener<T>::nbEl); // Appel au destructeur associé à l'élément supprimé
}

// Version plus simple et plus rapide que la version générique définie dans la classe de base
template<class T> void TD::VectorAll<T>::clear() {
  for(unsigned int i=0; i<Contener<T>::nbEl; i++) {
    mem.destroy(tab+i);
  }
  Contener<T>::nbEl = 0;
}


#endif
