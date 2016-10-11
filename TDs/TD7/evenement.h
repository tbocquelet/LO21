#if !defined(_EVENEMENT_H) 
#define _EVENEMENT_H 

#include <iostream> 
#include <string>
#include "timing.h"

namespace TIME{ 

// avec la portee "private", les classes filles ne peuvent pas acceder aux attributs de la classe mere
// avec la porte "protected", c'est possible, mais l'utilisateur ne peut pas y acceder

	class Evt{
	protected: // ou alors utiliser getDescription en dessous pour obtenir le sujet (utilise dans les fonctions "afficher")
		std::string sujet;
	public:
		Evt(const std::string& s):sujet(s){}
// methode virutelle pure
// devra etre definie dans les classes filles pour les rendre instanciables 
		virtual void afficher(std::ostream& f=std::cout) const =0;
		const std::string& getDescription() const { return sujet; } 
	};

// EvtPj "est un" Evt avec date de debut et date de fin
	class EvtPj : public Evt{
	private:
		Date debut;
		Date fin;
	public:
		EvtPj(const Date& d, const Date& f, const std::string& s):Evt(s), debut(d), fin(f){}
		~EvtPj();
		// ajout des accesseurs
		const Date& getDebut() const {return debut;}
		const Date& getFin() const {return fin;}	
		void afficher(std::ostream& f=std::cout) const {
			f<<"**** EvtPj ****"<<std::endl<<"Debut"<<debut<<"Fin"<<fin<<"sujet"<<getDescription()<<std::endl;
		}	
	};


	class Evt1j : public Evt { // modif ex 30
	private:
		Date date;
		//std::string sujet; 
	public:
		// sujet(s) devient Evt(s)
		Evt1j(const Date& d, const std::string& s):date(d),Evt(s){
			std::cout<<"Construction d'un objet Evt1j"<<std::endl;
		} 
		virtual ~Evt1j(){
			std::cout<<"Destruction d'un objet Evt1j"<<std::endl;
		}
		//const std::string& getDescription() const { return sujet; } 
		const Date& getDate() const { return date; }
		// virtual n'apporte plus rien vu la classe abstraite au dessus
		//virtual void afficher(std::ostream& f= std::cout) const {
		void afficher(std::ostream& f= std::cout) const {
			f<<"***** Evt ********"<<"\n"<<"Date="<<date<<" sujet="<<sujet<<"\n";
		}
	}; 

	class Evt1jDur : public Evt1j {
	private:
		Horaire debut;
		Duree duree;
	public:
// obige de definir le constructeur explicitement 
// car la classe de base ne possede pas de constructeur sans parametre
		Evt1jDur(const Date& d, const std::string& s, const Horaire& h, const Duree& t): Evt1j(d,s),debut(h),duree(t){
			std::cout<<"Construction d'un objet Evt1jDur"<<std::endl;
		}
		~Evt1jDur(){
			std::cout<<"Destruction d'un objet Evt1jDur"<<std::endl;
		}
// accesseurs pour les nouveaux attributs
		const Horaire& getHoraire() const {return debut;}
		const Duree& getDuree() const {return duree;}
		void afficher(std::ostream& f = std::cout) const { // f= parametre par defaut, sortie par defaut = cout
			Evt1j::afficher(f); // rappel de la methode de la classe de base via l'operateur de resolution
			// de portee
			f<<"debut"<<debut<<"duree"<<duree<<std::endl;
		}
	};

	class Rdv : public Evt1jDur {
	private:
		std::string personne;
		std::string lieu;
	public:
		Rdv(const Date& d, const std::string& s, const Horaire& h, const Duree& dur, const std::string& p, const std::string& l): Evt1jDur(d,s,h,dur),personne(p),lieu(l){
			std::cout<<"Construction d'un objet Rdv"<<std::endl;
		}
		~Rdv(){
			std::cout<<"Destruction d'un objet Rdv"<<std::endl;
		}
		const std::string & getPersonne() const {return personne;}
		const std::string & getLieu() const {return lieu;}
		// redefinition de la methode afficher
		void afficher(std::ostream& f=std::cout) const {
			Evt1jDur::afficher(f); // rappel de la methode de la classe de base
			f<<"personne="<<personne<<"lieu"<<lieu<<std::endl;
		}
	};

	class Agenda {
	private:
// tableau dynamique 
// contient des pointeurs vers tout objet de type Evt1j ou heritant de la classe Evt1j
		// les Evt etaient des Evt1j avant
		Evt **tab;
		unsigned int nbEvts; // nombre d'elements dans le tableau
		unsigned int nbMaxEvts; // nombre max d'elements que peut contenir le tableau	
// interdiction de la duplication par definition en prive
		Agenda(const Agenda& a); // constructeur par recopie
		void operator=(const Agenda& a); // operateur d'affectation
	public:
// 10 evenements geres par defaut dans l'agenda
		Agenda():nbEvts(0), nbMaxEvts(10), tab(new Evt*[10]) {}
		~Agenda();
		Agenda & operator<<(Evt &e); // operateur d'insertion d'un evenement dans l'agenda
		void afficher(std::ostream& f=std::cout) const;

		class iterator{
		private:
			Evt** current; // pointeur vers l'evenement courant
			iterator(Evt **c):current(c){}
		public:
			iterator& operator++() {current++; return *this;}
			iterator& operator--() {current--; return *this;}
			Evt& operator*(){return **current;}
			bool operator!=(const iterator& it) const {
				return current!=it.current;
			}
			bool operator==(const iterator& it) const {
				return current==it.current;
			}
			friend class Agenda;
		};
		
		iterator begin() const {
			return iterator(tab);
		}
		iterator end() const {
			return iterator(tab+nbEvts);
		}
	};
}

std::ostream& operator<<(std::ostream& s, const TIME::Evt& e);

#endif