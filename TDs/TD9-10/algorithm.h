#ifndef Algorithm_T_H
#define Algorithm_T_H

namespace TD {
  /**
   * Recherche du plus petit élément situé dans l'intervalle [it1, it2[
   */
  // 2 itérateurs de n'importe quel type => type paramètrable => template
  // Patron de fonction
  template<class IT> IT element_minimum(IT it1, IT it2);

  template<class IT, class COMP> IT element_minimum(IT it1, IT it2, COMP comp);

}

template<class IT, class COMP>
IT TD::element_minimum(IT it1, IT it2, COMP comp) {
  IT it_min = it1;// Mémorise l'iterateur vers la plus petite valeur
  ++it1;
  while(it1!=it2) {
    if(comp(*it1, *it_min)) {
      it_min=it1;
    }
    ++it1;
  }
  return it_min;
}


template<class IT>
IT TD::element_minimum(IT it1, IT it2) {
  IT it_min = it1;// Mémorise l'iterateur vers la plus petite valeur
  ++it1;
  while(it1!=it2) {
    if(*it1<*it_min) {
      it_min=it1;
    }
    ++it1;
  }
  return it_min;
}


#endif
