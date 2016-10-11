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

// TIME::Agenda & TIME::Agenda::operator<<(TIME::Evt& e){
TIME::Agenda & TIME::Agenda::operator<<(const TIME::Evt& e){
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
	// tab[nbEvts++]=&e;
	tab[nbEvts++]=e.clone();
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

// EXERCICE 31 - QUESTION 2

TIME::Agenda::~Agenda(){
	for (int i = 0; i < nbEvts; i++)
	{
		delete tab[i];
	}
	delete[] tab;
}

// On s'appuie sur le constructeur par recopie 
TIME::EvtPj * TIME::EvtPj::clone() const {return new EvtPj(*this);}
TIME::Evt1j * TIME::Evt1j::clone() const {return new Evt1j(*this);}
TIME::Evt1jDur * TIME::Evt1jDur::clone() const {return new Evt1jDur(*this);}
TIME::Rdv * TIME::Rdv::clone() const {return new Rdv(*this);}

// EXERCICE 31 - QUESTION 3

std::string TIME::EvtPj::toString() const {
	std::stringstream f;
	f<<"**** EvtPj ****"<<std::endl<<"Debut"<<debut<<"Fin"<<fin<<"sujet"<<getDescription()<<std::endl; // operation "hook" ? on ne 
	//rappelle pas la fonciton de base mais on la redéfinit
	return f.str();
}

std::string TIME::Evt1j::toString() const {
	std::stringstream f;
	f<<"***** Evt ********"<<"\n"<<"Date="<<date<<" sujet="<<sujet<<"\n"; 
	return f.str();
}

std::string TIME::Evt1jDur::toString() const {
	std::stringstream f;
	f<<Evt1j::toString()<<"debut"<<debut<<"duree"<<duree<<std::endl; 
	return f.str();
}

std::string TIME::Rdv::toString() const {
	std::stringstream f;
	f<<Evt1jDur::toString()<<"personne="<<personne<<"lieu"<<lieu<<std::endl; 
	return f.str();
}

bool TIME::Evt1j::operator<(const TIME::Evt1j & e) const{
// la seule comparaison possible est celle sur la date
	return date<e.date;
}

bool TIME::Evt1jDur::operator<(const TIME::Evt1j & e) const{
// appel a l'operateur < de la classe Evt1j via l'operateur de resolution de portee 
// on essaie dans un premier temps de comparer les dates
// si les dates sont egales, il faudra comparer les horaires de debut (mais verifier avant que e est bien de type Evt1jDur)
	if (this->Evt1j::operator<(e)) return true;
	if (e.Evt1j::operator<(*this)) return false;
// les dates sont les memes, il faut comparer les horaires si possible
	const Evt1jDur * ex=dynamic_cast<const Evt1jDur *>(&e);
	//l'operateur renvoie null (ou 0) si la conversion echoue
	if (ex!=0 && debut<ex->debut) return true; // comparaison horaires
	// sinon
	return false;
}
























