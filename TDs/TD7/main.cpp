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
	Rdv* pt5= new Rdv(Date(12,11,2013),"reunion UV",Horaire(17,30),Duree(60)," Intervenants UV","bureau");
	pt5->afficher(); 
	delete pt5;
	
// on cree un pointeur de classe de base vers une classe derivee, ca fonctionne 
	Evt1j* pt6= new Rdv(Date(12,11,2013),"reunion UV",Horaire(17,30),Duree(60)," Intervenants UV","bureau");
	pt6->afficher(); 
	delete pt6;

	return 0;
}