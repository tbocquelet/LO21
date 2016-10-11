#include <iostream> 
#include "evenement.h"

using namespace std;
using namespace TIME;

int main(){
// EX 27 - QUESTION 2
	// Evt1j e1(Date(4,10,1957),"Spoutnik"); 
	// Evt1j e2(Date(11,6,2013),"Shenzhou"); 
	// e1.afficher();
	// e2.afficher();
	// system("pause");
	
// EX 27 - QUESTION 4
	// début de bloc
	// Rdv e(Date(11,11,2013),"reunion UV",Horaire(17,30),Duree(60),"Intervenants UV","bureau");
	// std::cout<<"RDV:";
	// e.afficher();
	// fin de bloc

// EX 29 - QUESTION 1
	// Evt1j e1(Date(4,10,1957),"Spoutnik");
	// Evt1j e2(Date(11,6,2013),"Shenzhou");
	// Evt1jDur e3(Date(11,6,2013),"Lancement de Longue Marche",Horaire(17,38),Duree(0,10));
	// Rdv e4(Date(11,4,2013),"reunion UV",Horaire(17,30),Duree(60),"Intervenants UV","bureau");
	// e1.afficher(); e2.afficher(); e3.afficher(); e4.afficher();

	// Evt1j* pt1= &e1;
	// Evt1j* pt2=&e2; 
	// Evt1j* pt3=&e3; 
	// Evt1j* pt4=&e4;

	// pt1->afficher();
	// pt2->afficher(); 
	// pt3->afficher(); 
	// pt4->afficher();

// EX 29 - QUESTION 2
	// Rdv* pt5= new Rdv(Date(12,11,2013),"reunion UV",Horaire(17,30),Duree(60)," Intervenants UV","bureau");
	// pt5->afficher(); 
	// delete pt5;
	
// on cree un pointeur de classe de base vers une classe derivee, ca fonctionne 
	// Evt1j* pt6= new Rdv(Date(12,11,2013),"reunion UV",Horaire(17,30),Duree(60)," Intervenants UV","bureau");
	// pt6->afficher(); 
	// delete pt6;

// EXERCICE 32
	Evt1j e1(Date(4,10,1957),"Spoutnik");
	Evt1j e2(Date(11,6,2013),"Shenzhou");
	Evt1jDur e3(Date(11,6,2013),"Lancement de Longue Marche",Horaire(17,38),Duree(0,10));
	Rdv e4(Date(11,4,2013),"reunion UV",Horaire(17,30),Duree(60),"Intervenants UV","bureau");
	
// operations d'upcast, pas besoin d'utiliser de dynamic_cast
	Evt1j* pt1= &e1; 
	Evt1j* pt2=&e2; 
	Evt1j* pt3=&e3; 
	Evt1j* pt4=&e4;

	Evt1j& ref1=e1;
	Evt1j& ref2=e2; 
	Evt1j& ref3=e3; 
	Evt1j& ref4=e4;

// renvoie nullptr si le cast a echoue
// cas des 3 premiers dynamic_cast : il faudrait que les objets apaprtiennent soit a une classe qui derivent de Rdv, soit appartiennent a Rdv
// partout ou il y a des downcast, il faut faire un dynamic_cast
	Rdv* pt=dynamic_cast<Rdv*>(pt1); if (pt) pt->afficher(); 
	pt=dynamic_cast<Rdv*>(pt2); if (pt) pt->afficher(); 
	pt=dynamic_cast<Rdv*>(pt3); if (pt) pt->afficher();
// seule la conversion suivante renverra un pointeur non null 
	pt=dynamic_cast<Rdv*>(pt4); if (pt) pt->afficher(); 
	
	try{
		Rdv& r1=dynamic_cast<Rdv&>(ref1); 
		r1.afficher();
	} catch (std::bad_cast & e) {
		std::cout<<e.what()<<std::endl;
	}

	try{
		Rdv& r2=dynamic_cast<Rdv&>(ref2); 
		r2.afficher();
	} catch (std::bad_cast & e) {
		std::cout<<e.what()<<std::endl;
	}

	try{
		Rdv& r3=dynamic_cast<Rdv&>(ref3); 
		r3.afficher();
	} catch (std::bad_cast & e) {
		std::cout<<e.what()<<std::endl;
	}
// seule la conversion suivante ne delenchera pas d'exception
	try{
		Rdv& r4=dynamic_cast<Rdv&>(ref4); 
		r4.afficher();
	} catch (std::bad_cast & e) {
		std::cout<<e.what()<<std::endl;
	}


	return 0;
}