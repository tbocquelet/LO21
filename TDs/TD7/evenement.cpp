#include "timing.h"
#include "evenement.h"

// une reference de type Evt1j peut etre initialisee avec un objet appartenant
// a la classe de base Evt1j ou une classe derivee (Evt1jDur/Rdv)

// les Evt1j etaient des Evt avant
std::ostream& operator<<(std::ostream& s, const TIME::Evt& e){
// polymorphisme : la methode "afficher" appelee depend du type reel de l'objet
// reference e
// fonctionne uniquement car la methode "afficher" est virtual
	e.afficher(s); 
 	return s;
}

TIME::Agenda::~Agenda(){
	delete[] tab;
}

TIME::Agenda & TIME::Agenda::operator<<(TIME::Evt& e){
	// agrandissement du tableau si necessaire
	if(nbEvts==nbMaxEvts){
		Evt **newtab=new Evt*[nbMaxEvts+10]; // allocation + 10 emplacements
		for (int i = 0; i < nbEvts;i++)
		{		
			newtab[i]=tab[i]; // recopie de l'adresse de chaque evenement
		}
		Evt** old=tab; // sauvegarde pour liberation de la memoire
		tab=newtab; // valuation de l'attribut avec l'adresse du nouveau tableau
		nbMaxEvts+=10;
		delete[] old; // liberation de la memoire allouee a l'ancien tableau
	}
	tab[nbEvts++]=&e;
	return *this;
}

void TIME::Agenda::afficher(std::ostream& f) const {
	f<<"#### AGENDA ####"<<std::endl;
// la methode afficher a appeler depend du type reel de l'objet pointe (polymorphisme)
	for (int i = 0; i < nbEvts;i++)		
	{
		tab[i]->afficher(f); // parcequ'on a un pointeur donc ->
	}

	f<<"#### FIN AGENDA ####"<<std::endl;
}